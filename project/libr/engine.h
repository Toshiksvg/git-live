//
// Created by Anton on 8/14/2016.
//

#ifndef TEST1_ENGINE_H
#define TEST1_ENGINE_H

#include <iostream>

#endif //TEST1_ENGINE_H

struct Fields
{
    char** fieldOfAction;
    char** tempField;
};


Fields initialization(std::pair<int, int> sizeField);
void initLivingCell(Fields field, int addressHight, int addressWight);
bool gamingProcess(Fields field, std::pair<int, int> sizeField, int& quantityLivingCell);
void destroyAllFields(Fields field, std::pair<int, int> sizeField);
