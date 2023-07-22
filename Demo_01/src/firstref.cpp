//
// Created by WuXiangGuJun on 2023/7/22.
//
#include <iostream>

int main() {
    using namespace std;
    int rats = 101;
    // 指向int变量的引用
    int &rodents = rats;
    cout << "rats = " << rats;
    cout << ", rodents = " << rodents << endl;
    rodents++;
    cout << "rats = " << rats;
    cout << ", rodents = " << rodents << endl;

    cout << "rats address = " << &rats;
    // 引用的变量的地址
    cout << ", rodents address = " << &rodents << endl;
    return 0;
}