//
// Created by Дмитрий Стрюковский on 08.03.2022.
//

#ifndef LAB1_RESULT_H
#define LAB1_RESULT_H


void writeToFinalMatrix(int maxDimension, int **const *supportMatrices, int **beforePadding);
void doPadding(int maxDimension, int *const *beforePadding, int &f, int &s, int **&afterPadding);
void clearMemory(int n1, int n2, int maxDimension, int *const *M1, int *const *M2, int *const *castedM1,
                 int *const *castedM2, int **const *splittedMatrices, int **const *intermediateMatrices,
                 int **const *supportMatrices, int *const *beforePadding, int f, int *const *afterPadding);

#endif //LAB1_RESULT_H
