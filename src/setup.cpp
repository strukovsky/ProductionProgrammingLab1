//
// Created by Дмитрий Стрюковский on 08.03.2022.
//

#include <iostream>
using namespace std;

void setupMatrix(int &n, int &m, int **&matrix)
{
    matrix = new int *[n];
    do {
        cout << "Введите размеры первой матрицы\n";
        cin >> n >> m;
    } while (n <= 0 || m <= 0);
    for (int i = 0; i < n; i++)
        matrix[i] = new int[m];
}
