//
// Created by Anton on 8/14/2016.
//
#include <windows.h>
#include "../libr/live.h"
#include "../libr/engine.h"
#include "../libr/graphic.h"


enum ErrorVariant{ERROR_MENU, ERROR_SIZE_FIELD};


//int readItemsMenu();
void menu();
void error(ErrorVariant);
std::pair<int, int> readFieldSize();
void startGame(std::pair<int, int> sizeField);
void readUserLivingCell(Fields& field, std::pair<int, int> sizeField, int& quantityLivingCell);
void gameOver(Fields& field, std::pair<int, int> sizeField);
void gameRestart();

void Live()
{
    clearWindow();
    std::cout << "We are welcome you! You start playing our game!" << std::endl;

    menu();
}

void menu()
{
    bool flag = true;
    std::cout << "1 - Start\n2 - Exit\nYour choice: ";

    while (flag) {
        int variant;
        std::cin >> variant;

        while (std::cin.fail()) {
            std::cin.clear();
            char temp;
            std::cin >> temp;
        }

        switch (variant) {
            case 1:
                flag = false;
                gameRestart();
                break;
            case 2:
                flag = false;
                break;
            default:
                error(ERROR_MENU);
                std::cout << "1 - Start\n2 - Exit\nYour choice: ";
        }
    }
}

void error(ErrorVariant option)
{
    switch (option) {
        case ERROR_MENU:
            clearWindow();
            std::cout << "Error! You should write your variant anew.\n";
            break;
        case ERROR_SIZE_FIELD:
            clearWindow();
            std::cout << "Error! Your number excluded in range. Try again\n";
            break;
    }
}

std::pair<int, int> readFieldSize()
{
    clearWindow();
    int hight, wight;
    bool flag = true;

    std::cout << "Write hight and wight of field\nHight (min - 5, max - 26): ";

    while (flag) {
        std::cin >> hight;

        if (std::cin.fail()){
            std::cin.clear();
            char temp;
            std::cin >> temp;
        }

        if (hight >= 5 && hight <= 26) {
            flag = false;
        }
        else {
            error(ERROR_SIZE_FIELD);
            std::cout << "Hight (min - 5, max - 26): ";
        }
    }

    flag = true;
    std::cout << "Wight (min - 5, max - 26): ";

    while (flag) {
        std::cin >> wight;

        if (std::cin.fail()){
            std::cin.clear();
            char temp;
            std::cin >> temp;
        }

        if (wight >= 5 && wight <= 26){
            flag = false;
        }
        else {
            error(ERROR_SIZE_FIELD);
            std::cout << "Wight (min - 5, max - 26): ";
        }
    }

    hight += 3;
    wight += 3;

    return std::make_pair(hight, wight);
}


void startGame(std::pair<int, int> sizeField)
{
    static int quantityLivingCell = 0;
    bool flag = true;

    Fields field = initialization(sizeField);
    draw(field.fieldOfAction, sizeField);

    readUserLivingCell(field, sizeField, quantityLivingCell);

    while (gamingProcess(field, sizeField, quantityLivingCell)) {
        Sleep(300);
        draw(field.fieldOfAction, sizeField);
        //system("pause>>null");
    }

    gameOver(field, sizeField);

    quantityLivingCell = 0;
}

void gameRestart()
{
    bool flag = true;
    while(flag) {
        startGame(readFieldSize());
        std::cout << "1 - Restart\n2 - Exit\nYour choice: ";

        while (flag) {
            int variant;
            std::cin >> variant;

            if (std::cin.fail()) {
                std::cin.clear();
                char temp;
                std::cin >> temp;
            }

            switch (variant) {
                case 1:
                    flag = true;
                    break;
                case 2:
                    flag = false;
                    break;
                default:
                    error(ERROR_MENU);
                    std::cout << "1 - Restart\n2 - Exit\nYour choice: ";
            }
        }
    }
}

void readUserLivingCell(Fields& field, std::pair<int, int> sizeField, int& quantityLivingCell)
{
    std::cout << "Write address of living cell. For Example: AB(A - hight, B - wight)\nYour address: ";

    bool flag = true;
    char addressHight, addressWight;

    while (flag){
        std::cin >> addressHight >> addressWight;

        if ( (addressHight >= 'A' && addressHight <= ('A'+sizeField.first-4) ) &&
                (addressWight >= 'A' && addressWight <= ('A'+sizeField.second-4) ) ){

            initLivingCell(field, int(addressHight-'A'+2), int(addressWight-'A'+2));  //инициализируем клетку

            draw(field.fieldOfAction, sizeField); //рисуем поле

            quantityLivingCell++;  //добавляем к счётчику еще клетку

            bool tempFlag =  true; //вопрос о создании еще одной живой клетке
            std::cout << "\nWould you like to write another one address of living cell?\n1 - Yes\n2 - No\nYour choice: ";

            while (tempFlag){
                int variant;
                std::cin >> variant;

                if (std::cin.fail()) {
                    std::cin.clear();
                    char temp;
                    std::cin >> temp;
                }

                switch (variant){
                    case 1:
                        tempFlag = false;
                        std::cout << "Write address of living cell. For Example: AB(A - hight, B - wight)\nYour address: ";
                        break;
                    case 2:
                        tempFlag = false;
                        flag = false;
                        break;
                    default:
                        error(ERROR_MENU);
                        draw(field.fieldOfAction, sizeField, false);
                        std::cout << "\nWould you like to write another one address of living cell?\n1 - Yes\n2 - No\nYour choice: ";
                }
            }

        }
        else{
            error(ERROR_SIZE_FIELD);
            draw(field.fieldOfAction, sizeField, false);
            std::cout << "\nWrite address of living cell. For Example: AB(A - hight, B - wight)\nYour address: ";
        }
    }
}

void gameOver(Fields& field, std::pair<int, int> sizeField)
{
    std::cout << "Game Over!\n";

    destroyAllFields(field, sizeField);
}