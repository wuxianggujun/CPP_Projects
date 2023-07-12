/**
* Created by WuXiangGuJun on 2023/4/4.
*/
#include <iostream>

struct inflatable {
    char name[20];
    float volume;
    double price;
};

struct perks {
    int key_number;
    char car[12];
} mr_smith, ms_jones;

int main() {
    using namespace std;
    inflatable bouquet = {
            "sunflowers",
            0.20,
            12.49
    };

    //C++11也支持将列表初始化用于结构，且等号（=）是可选的，其次，如果大括号内未包含任何东西，每个成员都将被设置为零。
    inflatable choice{};

    cout << "bouquet: " << bouquet.name << " for $";
    cout << bouquet.price << endl;

    choice = bouquet;
    cout << "choice: " << choice.name << " for $";
    cout << choice.price << endl;



    //结构数组
    inflatable guests[2] = {
            {"Bambi", 0.5, 21.99},
            {"Godzilla", 2000, 565.99}
    };

    cout << "The guests " << guests[0].name << " and " << guests[1].name << "\nhave a combined volume of "
         << guests[0].volume + guests[1].volume << " cubic feet.\n";



    //结构中的位字段
    struct torgle_register {
        unsigned int SN: 4;
        unsigned int : 4;
        bool hoodIn: 1;
        bool goodTorgle: 1;
    };
    

}