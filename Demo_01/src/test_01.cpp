/**
* Created by WuXiangGuJun on 2023/4/7.
*/
#include <iostream>
#include <list>

class Test {
public:
    Test(int a, int b, int c) {
        this->ma = a;
        this->mb = b;
        this->mc = c;

        std::cout << "Test constructed." << std::endl;
    }

    ~Test() {
        std::cout << "Test destructed." << std::endl;
    }

    Test(const Test &rhs) {
        if (this == &rhs) {
            return;
        }
        this->ma = rhs.ma;
        this->mb = rhs.mb;
        this->mc = rhs.mc;
        std::cout << "Test copy-constructed" << std::endl;
    }

private:
    int ma;
    int mb;
    int mc;
};


int main() {
    std::list<Test> collections;

    for (int i = 0; i < 10; ++i) {
        collections.emplace_back(1 * i, 2 * i, 3 * i);
    }
    return 0;
}