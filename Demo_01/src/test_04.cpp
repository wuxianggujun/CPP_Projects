//
// Created by WuXiangGuJun on 2023/7/16.
//
#include <iostream>

int sum(int arr[],int n);

int main() {
    int age = 39;
    int *pd = &age;
    const int *pt = pd;
    std::cout << pt << std::endl;


    const int **pp2;
    int *p1;
    const int n = 13;
    //pp2 = &p1;
    //*pp2 = &n;
    *p1 = 10;

    int aloth = 3;
    //只能防止修改ps指向的值，而不能防止修改ps的值，也就是说ps的地址
    const int *ps = &aloth;
    //允许修改指向的值，但不能修改地址。
    int *const finger = &aloth;
    *finger = 20;

    const int months[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    // 禁止将常量数组的地址赋值给非常量指针，不能将数组名作为参数传递给使用非常量形参的函数。
//    int j = sum(months,12);
}