//
// Created by Дмитрий Стрюковский on 08.03.2022.
//

#include <iostream>
#include "../headers/cast.h"
#include "../headers/utils.h"

using namespace std;

int calculateMaxDimension(int n1, int m1, int n2, int m2, int initialValue) {
    int result = initialValue;
    while (result < n1 || result < n2 || result < m1 || result < m2)
        //TODO: here can be problems
        result *= 2;
    return result;
}

void castMatrix(int n1, int m1, int l, int *const *inputMatrix, int **&outputMatrix)
{
    outputMatrix = new int *[l];
    for (int i = 0; i < l; i++) {
        outputMatrix[i] = new int[l];
        for (int j = 0; j < l; j++)
            outputMatrix[i][j] = 0;
    }
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m1; j++)
            outputMatrix[i][j] = inputMatrix[i][j];
    }
    printMatrix(l, l, outputMatrix);
}
