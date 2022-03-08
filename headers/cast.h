//
// Created by Дмитрий Стрюковский on 08.03.2022.
//

#ifndef LAB1_CAST_H
#define LAB1_CAST_H

int calculateMaxDimension(int n1, int m1, int n2, int m2, int result);
void castMatrices(int n1, int m1, int n2, int m2, int *const *M1, int *const *M2, int l, int **&M3, int **&M4);
void castMatrix(int n1, int m1, int l, int *const *inputMatrix, int **&outputMatrix);

#endif //LAB1_CAST_H
