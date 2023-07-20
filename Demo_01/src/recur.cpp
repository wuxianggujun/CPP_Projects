//
// Created by WuXiangGuJun on 2023/7/16.
//
#include <iostream>

void countdown(int n);

int main() {
    countdown(4);
}

void countdown(int n) {
    using namespace std;
    cout << "Counting down..." << n << " : " << &n << endl;
    if (n > 0)
        countdown(n - 1);
    cout << n << ": Kaboom;\n";
}