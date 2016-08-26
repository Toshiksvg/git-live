//
// Created by Anton on 8/14/2016.
//
#include "../libr/engine.h"

bool aroundLivingCell  (Fields field, std::pair<int, int> livingCell);
bool aroundDeadCell    (Fields field, std::pair<int, int> livingCell);
bool checkFieldsMatch  (Fields field, std::pair<int, int> sizeField);

/*******************Temp**************************/
int addressCellX[] = {1, -1, 1, 0, -1, 1, 0, -1};
int addressCellY[] = {0, 0, 1, 1, 1, -1, -1, -1};
/*************************************************/

Fields initialization(std::pair<int, int> sizeField)
{
    char** fieldOfAction = new char* [sizeField.first];

    for (int i = 0; i < sizeField.first; i++){
        fieldOfAction[i] = new char [sizeField.second];
    }

    fieldOfAction[0][2] = fieldOfAction[2][0] = 'A';

    for (int i = 3; i < sizeField.second - 1; i++) {
        fieldOfAction[0][i] = fieldOfAction[0][i - 1] + 1;            //инициализация букв поля
    }

    for (int i = 3; i < sizeField.first-1; i++) {
        fieldOfAction[i][0] = fieldOfAction[i - 1][0] + 1;            //инициализация букв поля
    }

    for (int i = 0; i < sizeField.second; i++){
        fieldOfAction[1][i] = fieldOfAction[sizeField.first - 1][i] = '#';    //границы поля
    }

    for (int i = 0; i < sizeField.first; i++){
        fieldOfAction[i][1] = fieldOfAction[i][sizeField.second - 1] = '#';    //границы поля
    }

    fieldOfAction[0][0]                                        = ' ';
    fieldOfAction[0][sizeField.second - 1]                     = ' ';
    fieldOfAction[sizeField.first - 1][0]                      = ' ';
    fieldOfAction[sizeField.first - 1][sizeField.second - 1]   = ' ';

    for (int i = 2; i < sizeField.first - 1; i++){
        for (int j = 2; j < sizeField.second - 1; j++){
            fieldOfAction[i][j] = '*';
        }
    }

    char** tempField = new char* [sizeField.first - 3];

    for (int i = 0; i < sizeField.first - 3; i++){
        tempField[i] = new char [sizeField.second - 3];
    }

    Fields field;
    field.fieldOfAction = fieldOfAction;
    field.tempField = tempField;

    return field;
}

void initLivingCell(Fields field, int addressHight, int addressWight)
{
    field.fieldOfAction[addressHight][addressWight] = '0';
}

bool gamingProcess(Fields field, std::pair<int, int> sizeField, int &quantityLivingCell)
{
    for (int i = 2; i < sizeField.first - 1; i++){
        for (int j = 2; j < sizeField.second - 1; j++){
            if (field.fieldOfAction[i][j] == '0'){
                if(aroundLivingCell(field, std::make_pair(i, j) ) ){
                    field.tempField[i - 2][j - 2] = '0';
                    quantityLivingCell++;
                }
                else {
                    field.tempField[i - 2][j - 2] = '*';
                    quantityLivingCell--;
                }
            }
            else{
                if(aroundDeadCell(field, std::make_pair(i, j) ) ){
                    field.tempField[i - 2][j - 2] = '0';
                    quantityLivingCell++;
                }
                else
                    field.tempField[i - 2][j - 2] = '*';
            }
        }
    }

    if (checkFieldsMatch(field, sizeField) ){
        for (int i = 2; i < sizeField.first - 1; i++){
            for (int j = 2; j < sizeField.second - 1; j++){
                field.fieldOfAction[i][j] = field.tempField[i - 2][j - 2];
            }
        }
        if (quantityLivingCell > 0){
            return 1;
        }

    }
    else{
        return 0;
    }
}

bool checkFieldsMatch(Fields field, std::pair<int, int> sizeField)
{
    for (int i = 2; i < sizeField.first - 1; i++){
        for (int j = 2; j < sizeField.second - 1; j++){
            if(field.tempField[i - 2][j - 2] != field.fieldOfAction[i][j])
                return 1;
        }
    }

    return 0;
}

bool aroundLivingCell(Fields field, std::pair<int, int> livingCell)
{
    int count = 0;

    for (int i = 0; i < 8; i++) {
        if (field.fieldOfAction[livingCell.first + addressCellX[i] ][livingCell.second + addressCellY[i] ] == '0')
            count++;
    }

    if (count == 2 || count == 3)
        return true;
    else
        return false;
}

bool aroundDeadCell(Fields field, std::pair<int, int> deadCell)
{
    int count = 0;

    for (int i = 0; i < 8; i++) {
        if (field.fieldOfAction[deadCell.first + addressCellX[i] ][deadCell.second + addressCellY[i] ] == '0')
            count++;
    }

    if (count == 3)
        return true;
    else
        return false;
}

void destroyAllFields(Fields field, std::pair<int, int> sizeField)
{
    for (int i = sizeField.first - 1; i >= 0; i--){
        delete[] field.fieldOfAction[i];
    }
    delete[] field.fieldOfAction;

    for (int i = sizeField.first-4; i >= 0; i--){
        delete[] field.tempField[i];
    }
    delete[] field.tempField;
}