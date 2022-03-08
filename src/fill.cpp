//
// Created by Дмитрий Стрюковский on 08.03.2022.
//

#include "../headers/fill.h"
#include "../headers/utils.h"
#include <iostream>

using namespace std;

void fillFromCin(int n, int m, int **matrix) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> matrix[i][j];
}

void fillRandom(int n, int m, int **matrix) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            matrix[i][j] = rand() % 10;
}

void fillMatrices(int n1, int m1, int n2, int m2, int **M1, int **M2) {
    int k;
    do {
        cout << "Выберите способ заполнения матриц\n" <<
             "1 - Вручную \n2 - Случайным образом\n";
        cin >> k;
    } while (k < 1 || k > 2);
    switch (k) {
        case 1:
            fillFromCin(n1, m1, M1);
            fillFromCin(n2, m2, M2);
            cout << "\nМатрица 1\n\n";
            printMatrix(n1, m1, M1);
            cout << "\nМатрица 2\n\n";
            printMatrix(n2, m2, M2);
            break;
            case 2: default:
            fillRandom(n1, m1, M1);
            fillRandom(n2, m2, M2);
            cout << "\nМатрица 1\n\n";
            printMatrix(n1, m1, M1);
            cout << "\nМатрица 2\n\n";
            printMatrix(n2, m2, M2);
            break;

    }
}