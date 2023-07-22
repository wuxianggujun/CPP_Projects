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

    cout << "rats = " << &rats;
    cout << ", rodents = " << &rodents << endl;

    int bunnies = 50;
    rodents = bunnies;
    cout << "bunnies = " << bunnies;
    cout << ", rats = " << rats;
    cout << ", rodents = " << rodents << endl;

    cout << "bunnies address = " << &bunnies;
    // 引用的变量的地址
    cout << ", bunnies address = " << &rodents << endl;
    return 0;
}