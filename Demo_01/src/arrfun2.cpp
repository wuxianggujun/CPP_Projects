//
// Created by WuXiangGuJun on 2023/6/28.
//
#include <iostream>

const int arsize = 8;

int sum_arr(int arr[], int n);


int main() {
    int cookies[arsize] = {1, 2, 4, 8, 16, 32, 64, 128};
    std::cout << cookies << " = array address, ";

    std::cout << sizeof cookies << "  = sizeof cookies\n";
    int sum = sum_arr(cookies, arsize);
    std::cout << "Total cookies eaten : " << sum << std::endl;
    sum = sum_arr(cookies, 3);
    std::cout << "First three eaters ate" << sum << " cookies.\n";
    sum = sum_arr(cookies + 4, 4);
    std::cout << "Last four eaters ate " << sum << " cookies.\n";
    return 0;
}

int sum_arr(const int *arr, int n) {
    int total = 0;
    std::cout << arr << " = arr, ";
    std::cout << sizeof arr << " = sizeof arr\n";
    for (int i = 0; i < n; ++i) {
        total = total + arr[i];
    }
    return total;
}
