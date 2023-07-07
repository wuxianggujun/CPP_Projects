/**
* Created by WuXiangGuJun on 2023/4/6.
*/
#include <iostream>

void simple();

int main() {
    using namespace std;
    cout << "main() will call the simple() function:\n";
    simple();
    return 0;
}

void simple() {
    using namespace std;
    cout << "I am but a simple function.\n";
}