//
// Created by WuXiangGuJun on 2023/7/22.
//
#include <iostream>

int main() {
    using namespace std;
    int rats = 101;
    // ָ��int����������
    int &rodents = rats;

    cout << "rats = " << rats;
    cout << ", rodents = " << rodents << endl;

    cout << "rats = " << &rats;
    cout << ", rodents = " << &rodents << endl;

    int bunnies = 50;
    rodents = bunnies;
    cout << "bunnies = " << bunnies;
    cout << ", rats = " << rats;
    cout << ", rodents = " << rodents << endl;

    cout << "bunnies address = " << &bunnies;
    // ���õı����ĵ�ַ
    cout << ", bunnies address = " << &rodents << endl;
    return 0;
}