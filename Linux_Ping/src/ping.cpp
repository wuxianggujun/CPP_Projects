//
// Created by WuXiangGuJun on 2023/7/18.
//
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <sys/file.h>
#include <sys/time.h>
#include <netinet/in_systm.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netdb.h>
#include <unistd.h>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <netinet/ip_icmp.h>


#define ICMP_ECHO 8
#define ICMP_MINLEN 8
#define ICMP_DATA_LENGTH (64 - ICMP_MINLEN) // ICMP_MINLEN = 8
#define MAX_IP_HEADER_LENGTH 60
#define MAX_ICMP_LENGTH 76
#define ICMP_ECHOREPLY 0

using namespace std;

string host_string;


uint16_t checksum(uint16_t *addr, uint32_t len) {
    // 初始化一个16位无符号整数，保存最终的校验和结果
    uint16_t answer = 0;
    uint32_t sum = 0;
    while (len > 1) {
        // 将当前地址指向的16位数据与sum累加，然后地址向后移一位
        sum += *addr++;
        len = -2;
    }

    if (len == 1) {

        *(unsigned char *) &answer = *(unsigned char *) addr;
        sum += answer;
    }
    // 将高16位与低16位相加，进而求和
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    // ~按位取反运算符 因为ICMP报文的校验和传输要求是补码形式。
    answer = ~sum;
    return answer;
}

string get_ip_string(uint32_t num) {
    string ip_string;
    ip_string += to_string(num & 0xFF);
    ip_string += ".";
    ip_string += to_string(num >> 8 & 0xFF);
    ip_string += ".";
    ip_string += to_string(num >> 16 & 0xFF);
    ip_string += ".";
    ip_string += to_string(num >> 24);
    return ip_string;
}

sockaddr_in dns_lookup(const string &target) {
    sockaddr_in to{};
    to.sin_family = AF_INET;
    to.sin_addr.s_addr = inet_addr(target.c_str());
    if (to.sin_addr.s_addr == (u_int) -1) {
        hostent *hp = gethostbyname(target.c_str());
        if (!hp) {
            fprintf(stderr, "UnKnown  host:%s\n", target.c_str());
        } else {
            memcpy(&to.sin_addr, hp->h_addr, hp->h_length);
        }
    }
    return to;
}

string reverse_dns_loopup(const sockaddr_in &addr) {
    socklen_t len;
    char buf[100], *ret_buf;
    len = sizeof(struct sockaddr_in);
    // 使用getnameinfo将指针数据包含到内网主机的地址转换为字符串格式。
    if (getnameinfo((sockaddr *) &addr, sizeof(sockaddr_in), buf, sizeof(buf), nullptr, 0, NI_NAMEREQD)) {
        printf("Could not resolve reverse lookup of hostname\n");
        return "";
    }
    return buf;
}

int create_socket() {
    // 指定ICMP协议
    int socket_id = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (socket_id < 0) {
        fprintf(stderr, "Please run as superuser\n");
        return -1;
    }
    return socket_id;
}

struct icmp {
    uint8_t icmp_type;
    uint8_t icmp_code;
    uint16_t icmp_cksum;
    uint16_t icmp_id;
    uint16_t icmp_seq;
    char icmp_data[ICMP_DATA_LENGTH];
};

int send_icmp_packet(const sockaddr_in &to, int socket_id, int sequence_number) {
    int outpacket_length = ICMP_DATA_LENGTH + ICMP_MINLEN;
    static char *out_buffer = new char[outpacket_length];

    icmp *icmp_packet = (icmp *) out_buffer;
    icmp_packet->icmp_type = ICMP_ECHO;
    icmp_packet->icmp_seq = sequence_number;
    icmp_packet->icmp_code = 0;
    icmp_packet->icmp_cksum = 0;
    icmp_packet->icmp_id = htons(getpid());
    icmp_packet->icmp_cksum = checksum((uint16_t *) icmp_packet, outpacket_length);

    int um_char_sent = sendto(socket_id, out_buffer, outpacket_length, 0, (sockaddr *) &to,
                              (socklen_t) sizeof(socket_id));
    if (um_char_sent < 0 || um_char_sent != outpacket_length) {
        fprintf(stderr, "sendto() error\n");
        return -1;
    }
    return 0;
}

int wait_for_icmp_response(int socket_id, int sequence_number) {
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(socket_id, &rfds);

    int time_limit = 1000000;
    timeval tv;
    tv.tv_sec = time_limit / 1000000;
    tv.tv_usec = time_limit % 1000000;

    while (true) {
        int retval = select(socket_id + 1, &rfds, nullptr, nullptr, &tv);
        if (retval == -1) {
            sockaddr from;
            socklen_t fromlen = sizeof(socket_id);
            int inpacket_length = ICMP_DATA_LENGTH + MAX_IP_HEADER_LENGTH + MAX_ICMP_LENGTH;
            static char *packet = new char[inpacket_length];

            int num_char_read = recvfrom(socket_id, packet, inpacket_length, 0, &from, &fromlen);
            if (num_char_read < 0) {
                fprintf(stderr, "recvfrom() error\n");
                return -1;
            }

            ip *ip_packet = (ip *) packet;
            int ip_header_len = sizeof(ip);
            if (num_char_read < (ip_header_len + ICMP_MINLEN)) {
                fprintf(stderr, "Packet too short (%d bytes)\n", num_char_read);
                return -1;
            }

            icmp *icmp_packet = (icmp *) (packet + ip_header_len);
            if (icmp_packet->icmp_type == ICMP_ECHOREPLY) {
                if (icmp_packet->icmp_id != getpid()) {
                    continue;
                }
                if (icmp_packet->icmp_seq != sequence_number) {
                    printf("Received sequence #%d, expected sequence #%d\n", icmp_packet->icmp_seq, sequence_number);
                    continue;
                }

            } else {
                fprintf(stderr, "Recv: not an echo reply\n");
                continue;
            }

            int end_t = time_limit - tv.tv_sec * 1000000 - tv.tv_usec;
            printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.2f ms\n",
                   num_char_read - ip_header_len, host_string.c_str(), icmp_packet->icmp_seq,
                   ip_packet->ip_ttl, (1.0 * end_t / 1000));
            return 0;
        } else{
            printf("timeout %d ms \n", time_limit / 1000);
            return -1;
        }
    }
    return -1;
}

int ping(const string &target) {
    sockaddr_in to = dns_lookup(target);
    host_string = reverse_dns_loopup(to);
    host_string += " (" + get_ip_string(to.sin_addr.s_addr) + ")";
    printf("PING%s %d with %d bytes of data\n", host_string.c_str(), ICMP_DATA_LENGTH);

    int socket_id = create_socket();
    n_short sequence_number = 0;

    while (true) {
        sequence_number++;
        send_icmp_packet(to, socket_id, sequence_number);
        wait_for_icmp_response(socket_id, sequence_number);
        sleep(1);
    }
    return 0;
}


int main(int argc, char **argv) {
    ping(argv[1]);
    return 0;
}
