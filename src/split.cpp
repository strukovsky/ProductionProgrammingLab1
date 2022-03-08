//
// Created by Дмитрий Стрюковский on 08.03.2022.
//


#include <iostream>
#include "../headers/split.h"

void splitMatrix(int maxDimension, int *const *castedMatrix, int **&result, int paddingRow, int paddingColumn) {
    result = new int *[maxDimension / 2];
    for (int i = 0; i < maxDimension / 2; i++) {
        result[i] = new int[maxDimension / 2];
        for (int j = 0; j < maxDimension / 2; j++)
            result[i][j] = castedMatrix[i + paddingRow][j + paddingColumn];
    }
}