/**
* Created by WuXiangGuJun on 2023/4/19.
*/
#include <iostream>

//由于该程序不需要处理负数，因此它将计数变量的类型声明为unsigned int
unsigned int c_in_str(const char *str, char ch);


int main() {
    using namespace std;
    char mmm[15] = "minimum";

    char *wail = "ululate";

    unsigned int ms = c_in_str(mmm, 'm');
    unsigned int us = c_in_str(wail, 'u');

    cout << ms << " m charactere in" << mmm << endl;
    cout << us << " m charactere in" << wail << endl;
}

//使用一个函数来计算特定的字符在字符串中出现的次数
//由于函数不应该修改原始字符串，因此在声明形参str时，使用了限定符const
unsigned int c_in_str(const char *str, char ch) {
    //str最初指向字符串的第一个字符，因此*str表示的是第一个字符
    unsigned int count = 0;
    //只要字符不为空值字符(\0)，*str就为非零值，因此循环就将继续下去
    while (*str) {
        if (*str == ch) {
            count++;
        }
        //将指针增加一个字符
        str++;
        std::cout << *str << std::endl;
    }
    return count;
}

