//
// Created by WuXiangGuJun on 2023/7/16.
//
#include <iostream>

char *buildstr(char c, int n);

int main() {
    using namespace std;
    int times;
    char ch;

    cout << "Enter a character: ";
    cin >> ch;
    cout << "Enter an integer: ";
    cin >> times;
    char *ps = buildstr(ch, times);
    cout << ps << endl;
    delete[] ps;
    ps = buildstr('+', 20);
    cout << ps << "-DONE-" << ps << endl;
    delete[] ps;
    return 0;
}

char *buildstr(char c, int n) {
    char *pstr = new char[n + 1];
    pstr[n] = '\0';
    // 从后向前对数组进行填充
    while (n-- > 0) {
        pstr[n] = c;
    }
    return pstr;
}
