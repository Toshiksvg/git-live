//
// Created by Anton on 8/14/2016.
//
#include "../libr/graphic.h"


void clearWindow()
{
    system("cls");
}

void draw(char** fieldOfAction, std::pair<int, int> sizeField, const bool flag)
{
    if (flag) {
        clearWindow();
    }
    
    for (int i = 0; i < sizeField.first; i++){
        for (int j = 0; j < sizeField.second; j++){
            std::cout << fieldOfAction[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}