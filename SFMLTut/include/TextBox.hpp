//
// Created by WuXiangGuJun on 2023/7/15.
//
#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

class TextBox {
private:
    sf::Text textBox;
    std::ostringstream text;
    bool isSelected = false;
    bool hasLimit = false;
    int limit;

    void inputLogic(int charTyped){

    }

public:
    TextBox(){}
    TextBox(int size,sf::Color color,bool sel){
        textBox.setCharacterSize(size);
        textBox.setColor(color);
        isSelected = sel;


    }

};
