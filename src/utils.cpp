//
// Created by Дмитрий Стрюковский on 08.03.2022.
//

#include <iostream>
#include "../headers/utils.h"

using  namespace std;

void printMatrix(int n, int m, int *const *matrix) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
}