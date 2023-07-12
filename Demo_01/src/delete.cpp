/**
* Created by WuXiangGuJun on 2023/4/6.
*/
#include <iostream>
#include <cstring>

using namespace std;

char *getName(void);

int main() {
    char *name;
    name = getName();
    cout << name << " at " << (int *) name << endl;
    delete[] name;

    name = getName();
    cout << name << " at " << (int *) name << endl;
    delete[] name;
}

char *getName() {
    char temp[80];
    cout << "Enter last name: ";
    cin >> temp;

    char *pn = new char[strlen(temp) + 1];
    strcpy(pn, temp);
    return pn;
}
