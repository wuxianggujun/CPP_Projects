//
// Created by WuXiangGuJun on 2023/7/16.
//
#include <iostream>
#include <array>
#include <string>

const int seasons = 4;

const std::array<std::string,seasons> snames = { "spring", "summer", "fall", "winter" };

void fill(std::array<double,seasons> *pa);

void show(std::array<double,seasons> da);

int main(){
    std::array<double,seasons> expenses{};
    fill(&expenses);
    show(expenses);
    return 0;
}

void fill(std::array<double,seasons> *pa){
    using namespace std;

    for (int i = 0; i <seasons; ++i) {
        cout << "Enter " << snames[i] << " expenses: ";
        cin >> (*pa)[i];
    }
}

void show(std::array<double,seasons> da){
    using namespace std;
    double total = 0.0;
    cout << "\nEXPENSES\n";
    for (int i = 0;i< seasons;i++){
        cout << snames[i] << ": $" << da[i] << "\n";
        total += da[i];
    }
    cout << "TOTAL EXPRESSED: $" << total << "\n";
}