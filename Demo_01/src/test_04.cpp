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
    //ֻ�ܷ�ֹ�޸�psָ���ֵ�������ܷ�ֹ�޸�ps��ֵ��Ҳ����˵ps�ĵ�ַ
    const int *ps = &aloth;
    //�����޸�ָ���ֵ���������޸ĵ�ַ��
    int *const finger = &aloth;
    *finger = 20;

    const int months[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    // ��ֹ����������ĵ�ַ��ֵ���ǳ���ָ�룬���ܽ���������Ϊ�������ݸ�ʹ�÷ǳ����βεĺ�����
//    int j = sum(months,12);
}