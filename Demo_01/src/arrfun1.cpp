/**
* Created by WuXiangGuJun on 2023/4/15.
*/
#include <iostream>

const int ArSize = 8;

int sum_arr(const int arr[], int n);

int main() {
    using namespace std;
    int cookies[ArSize] = {1, 2, 4, 8, 16, 32, 64, 128};

    int sum = sum_arr(&cookies[4], 4);

    cout << "Total cookies eaten: " << sum << endl;


    //常量指针
    int age = 39;
    //const int *pt = &age;
    //*pt = 10; 无法被修改


    int *pd = &age;
    const int *pt = pd;


}

int sum_arr(const int arr[], int n) {
    //传进来的arr是数组的地址
    int total = 0;

    for (int i = 0; i < n; i++) {
        total += arr[i];
    }
    return total;
}
