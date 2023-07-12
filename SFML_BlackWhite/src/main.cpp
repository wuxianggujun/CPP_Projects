//
// Created by WuXiangGuJun on 2023/7/12.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <string>
#include <chrono>

std::string loadImage(sf::Texture &texture) {
    bool imgLoaded = false;
    std::string imagePath;
    while (!imgLoaded) {
        std::cout << "Give path to an image you want to modify or drag your image here: ";
        std::cin >> imagePath;
        if (texture.loadFromFile(imagePath)) {
            imgLoaded = true;
        }
    }
    return imagePath;
}

int chooseAlgorithm() {
    int algorithmChosen = -1;
    while (algorithmChosen == -1) {
        std::cout << "Choose algorithm to modify your picture:" << std::endl;
        std::cout << "(1) Grayscale conversion with average of rbg." << std::endl;
        std::cout << "(2) Grayscale conversion corrected for human eye." << std::endl;
        std::cout << "(3) Desaturation." << std::endl;
        std::cout << "(4) Decomposition with MAX values." << std::endl;
        std::cout << "(5) Decomposition with MIN values." << std::endl;
        std::string line;
        std::cin >> line;

        if (line.length() == 1) {
            try {
                algorithmChosen = std::stoi(line);
                if (algorithmChosen < 1 || algorithmChosen > 5) algorithmChosen = -1;

            } catch (std::invalid_argument const &e) {
                std::cout << "Choose a number from 1 to S." << std::endl;
                algorithmChosen = -1;
            }
        }
    }
    return algorithmChosen;
}

bool askSave() {
    int option = -1;
    while (option == -1) {
        std::cout << "Do you want to save the image?" << std::endl;
        std::cout << "(1) Yes, save it." << std::endl;
        std::cout << "(2) No, do not save it." << std::endl;
        std::string line;
        std::cin >> line;
        if (line.length() == 1) {
            try {
                option = std::stoi(line);
                if (option < 1 || option > 2) option = -1;

            } catch (std::invalid_argument const &e) {
                option = -1;
            }
        }
    }
    return option == 1;
}

int averageGrey(sf::Color const &pixel) {
    return (pixel.r + pixel.g + pixel.b) / 3;
}

int correctedGray(sf::Color const &pixel) {
    return (pixel.r * 0.3f + pixel.g * 0.59f + pixel.b * 0.11f);
}

int desaturatedGrey(sf::Color const &pixel) {
    return (std::max(std::max(pixel.r, pixel.g), pixel.b) + std::min(std::min(pixel.r, pixel.g), pixel.b)) / 2;
}

int decompositedMaxGrey(sf::Color const &pixel) {
    return std::max(std::max(pixel.r, pixel.g), pixel.b);
}

int decompositedMinGrey(sf::Color const &pixel) {
    return std::min(std::min(pixel.r, pixel.g), pixel.b);
}


int main() {
    sf::Texture texture;

    const std::string imagePath = loadImage(texture);
    int algorithmChosen = chooseAlgorithm();
    bool save = askSave();

    sf::Image image;
    image = texture.copyToImage();

    typedef int (*GreyScaleFunction)(sf::Color const &pixel);
    GreyScaleFunction greyFunction;

    switch (algorithmChosen) {
        case 1:
            greyFunction = averageGrey;
            break;
        case 2:
            greyFunction = correctedGray;
            break;
        case 3:
            greyFunction = desaturatedGrey;
            break;
        case 4:
            greyFunction = decompositedMaxGrey;
            break;
        case 5:
            greyFunction = decompositedMinGrey;
            break;
        default:
            greyFunction = averageGrey;
            break;
    }

    int grey = 0;

    auto start = std::chrono::high_resolution_clock::now();

    for (unsigned int x = 0; x < texture.getSize().x; x++) {

        for (unsigned int y = 0; y < texture.getSize().y; y++) {
            grey = greyFunction(image.getPixel(x, y));
            image.setPixel(x, y, sf::Color(grey, grey, grey));
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Time taken: " << duration.count() << " milliseconds\n";

    texture.update(image);

    sf::Sprite sprite;
    sprite.setTexture(texture);

    sf::RenderWindow window(sf::VideoMode(texture.getSize().x, texture.getSize().y), "SFML - Grey scale",
                            sf::Style::Titlebar | sf::Style::Close);
    window.clear();
    window.draw(sprite);
    window.display();

    sf::Event event{};

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }
    if (save) {
        std::string newFileName =
                imagePath.substr(0, imagePath.length() - 4) + "-grey" + std::to_string(algorithmChosen) + ".jpg";
        image.saveToFile(newFileName);
    }
    return 0;
}