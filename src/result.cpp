//
// Created by Дмитрий Стрюковский on 08.03.2022.
//


#include <iostream>
#include "../headers/result.h"

void writeToFinalMatrix(int maxDimension, int **const *supportMatrices, int **beforePadding) {
    for (int i = 0; i < maxDimension / 2; i++) {
        for (int j = 0; j < maxDimension / 2; j++) {
            beforePadding[i][j] = supportMatrices[0][i][j];
            beforePadding[i][j + maxDimension / 2] = supportMatrices[1][i][j];
            beforePadding[i + maxDimension / 2][j] = supportMatrices[2][i][j];
            beforePadding[i + maxDimension / 2][j + maxDimension / 2] = supportMatrices[3][i][j];
        }
    }
}

void doPadding(int maxDimension, int *const *beforePadding, int &f, int &s, int **&afterPadding) {
    f= 100;
    s= 100;
    afterPadding= new int *[f];
    int x = 0  ;
    for (int i = 0; i < maxDimension; i++) {
        x = 0;
        for (int j = 0; j < maxDimension; j++) {
            if (beforePadding[i][j] != 0) {
                x++;
                f = 100;
            }
        }
        if (x == 0 && i < f) {
            f = i;
        }
    }
    for (int i = 0; i < maxDimension; i++) {
        x = 0;
        for (int j = 0; j < maxDimension; j++) {
            if (beforePadding[j][i] != 0) {
                x++;
                s = 100;
            }
        }
        if (x == 0 && i < s) {
            s = i;
        }
    }
    for (int i = 0; i < f; i++) {
        afterPadding[i] = new int[s];
        for (int j = 0; j < s; j++)
            afterPadding[i][j] = beforePadding[i][j];
    }
}

void clearMemory(int n1, int n2, int maxDimension, int *const *M1, int *const *M2, int *const *castedM1,
                 int *const *castedM2, int **const *splittedMatrices, int **const *intermediateMatrices,
                 int **const *supportMatrices, int *const *beforePadding, int f, int *const *afterPadding) {
    for (int i = 0; i < n1; i++)
        delete[] M1[i];
    for (int i = 0; i < n2; i++)
        delete[] M2[i];
    for (int i = 0; i < maxDimension; i++) {
        delete[] castedM1[i];
        delete[] castedM2[i];
        delete[] beforePadding[i];
    }
    for (int i = 0; i < f; i++)
        delete[] afterPadding[i];
    for (int i = 0; i < maxDimension / 2; i++) {
        delete[] splittedMatrices[0][i];
        delete[] splittedMatrices[1][i];
        delete[] splittedMatrices[2][i];
        delete[] splittedMatrices[3][i];
        delete[] splittedMatrices[4][i];
        delete[] splittedMatrices[5][i];
        delete[] splittedMatrices[6][i];
        delete[] splittedMatrices[7][i];
        delete[] supportMatrices[0][i];
        delete[] supportMatrices[1][i];
        delete[] supportMatrices[2][i];
        delete[] supportMatrices[3][i];
        delete[] intermediateMatrices[0][i];
        delete[] intermediateMatrices[1][i];
        delete[] intermediateMatrices[2][i];
        delete[] intermediateMatrices[3][i];
        delete[] intermediateMatrices[4][i];
        delete[] intermediateMatrices[5][i];
        delete[] intermediateMatrices[6][i];
    }
    delete[] M1, M2, castedM1, castedM2, beforePadding, afterPadding;
    delete[] splittedMatrices[0], splittedMatrices[1], splittedMatrices[2], splittedMatrices[3], splittedMatrices[4], splittedMatrices[5], splittedMatrices[6], splittedMatrices[7], supportMatrices[0], supportMatrices[1], supportMatrices[2], supportMatrices[3];
    delete[] intermediateMatrices[0], intermediateMatrices[1], intermediateMatrices[2], intermediateMatrices[3], intermediateMatrices[4], intermediateMatrices[5], intermediateMatrices[6];
}