#include <iostream>
#include <cstdlib>
#include <ctime>
#include "headers/setup.h"
#include "headers/fill.h"
#include "headers/cast.h"

using namespace std;


int main() {
    srand(time(NULL));
    int n1, m1, n2, m2, k, maxDimension = 2;
    system("chcp 1251");
    cout << "Вас приветствует программа" << endl <<
         "быстрого перемножения матриц методом Штрассена\n\n";

    ///////////////////////////////////////////////////////////////////////////////
    ////////////////////Ввод размеров матрицы пользователем////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    int **M1;
    int **M2;
    setupMatrix(n1, m1, M1);
    setupMatrix(n2, m2, M2);

    ///////////////////////////////////////////////////////////////////////////////
    ////////////////Выбор способа заполнения и заполнение матриц///////////////////
    ///////////////////////////////////////////////////////////////////////////////

    fillMatrices(n1, m1, n2, m2, M1, M2);

    ///////////////////////////////////////////////////////////////////////////////
    /////////////////Приведение матриц к требуемому размеру////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    int **castedM1;
    int **castedM2;
    maxDimension = calculateMaxDimension(n1,m1,n2,m2, maxDimension);
    cout << "Приведенные матрицы\n";
    cout << "\nМатрица 1\n\n";
    castMatrix(n1, m1, maxDimension, M1, castedM1);
    cout << "\nМатрица 2\n\n";
    castMatrix(n2, m2, maxDimension, M2, castedM2);

    ///////////////////////////////////////////////////////////////////////////////
    ///////////////Разбиение матриц на подматрицы и их заполнение//////////////////
    ///////////////////////////////////////////////////////////////////////////////

    int **mat1 = new int *[maxDimension / 2];
    for (int i = 0; i < maxDimension / 2; i++) {
        mat1[i] = new int[maxDimension / 2];
        for (int j = 0; j < maxDimension / 2; j++)
            mat1[i][j] = castedM1[i][j];
    }
    int **mat2 = new int *[maxDimension / 2];
    for (int i = 0; i < maxDimension / 2; i++) {
        mat2[i] = new int[maxDimension / 2];
        for (int j = 0; j < maxDimension / 2; j++)
            mat2[i][j] = castedM1[i][j + maxDimension / 2];
    }
    int **mat3 = new int *[maxDimension / 2];
    for (int i = 0; i < maxDimension / 2; i++) {
        mat3[i] = new int[maxDimension / 2];
        for (int j = 0; j < maxDimension / 2; j++)
            mat3[i][j] = castedM1[i + maxDimension / 2][j];
    }
    int **mat4 = new int *[maxDimension / 2];
    for (int i = 0; i < maxDimension / 2; i++) {
        mat4[i] = new int[maxDimension / 2];
        for (int j = 0; j < maxDimension / 2; j++)
            mat4[i][j] = castedM1[i + maxDimension / 2][j + maxDimension / 2];
    }
    int **mat5 = new int *[maxDimension / 2];
    for (int i = 0; i < maxDimension / 2; i++) {
        mat5[i] = new int[maxDimension / 2];
        for (int j = 0; j < maxDimension / 2; j++)
            mat5[i][j] = castedM2[i][j];
    }
    int **mat6 = new int *[maxDimension / 2];
    for (int i = 0; i < maxDimension / 2; i++) {
        mat6[i] = new int[maxDimension / 2];
        for (int j = 0; j < maxDimension / 2; j++)
            mat6[i][j] = castedM2[i][j + maxDimension / 2];
    }
    int **mat7 = new int *[maxDimension / 2];
    for (int i = 0; i < maxDimension / 2; i++) {
        mat7[i] = new int[maxDimension / 2];
        for (int j = 0; j < maxDimension / 2; j++)
            mat7[i][j] = castedM2[i + maxDimension / 2][j];
    }
    int **mat8 = new int *[maxDimension / 2];
    for (int i = 0; i < maxDimension / 2; i++) {
        mat8[i] = new int[maxDimension / 2];
        for (int j = 0; j < maxDimension / 2; j++)
            mat8[i][j] = castedM2[i + maxDimension / 2][j + maxDimension / 2];
    }

    ///////////////////////////////////////////////////////////////////////////////
    ////////////////////////Создание промежуточных матриц//////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    int **p1 = new int *[maxDimension / 2];
    for (int i = 0; i < maxDimension / 2; i++) {
        p1[i] = new int[maxDimension / 2];
    }
    int **p2 = new int *[maxDimension / 2];
    for (int i = 0; i < maxDimension / 2; i++) {
        p2[i] = new int[maxDimension / 2];
    }
    int **p3 = new int *[maxDimension / 2];
    for (int i = 0; i < maxDimension / 2; i++) {
        p3[i] = new int[maxDimension / 2];
    }
    int **p4 = new int *[maxDimension / 2];
    for (int i = 0; i < maxDimension / 2; i++) {
        p4[i] = new int[maxDimension / 2];
    }
    int **p5 = new int *[maxDimension / 2];
    for (int i = 0; i < maxDimension / 2; i++) {
        p5[i] = new int[maxDimension / 2];
    }
    int **p6 = new int *[maxDimension / 2];
    for (int i = 0; i < maxDimension / 2; i++) {
        p6[i] = new int[maxDimension / 2];
    }
    int **p7 = new int *[maxDimension / 2];
    for (int i = 0; i < maxDimension / 2; i++) {
        p7[i] = new int[maxDimension / 2];
    }

    ///////////////////////////////////////////////////////////////////////////////
    ////////////////////Вычисление значений промежуточных матриц///////////////////
    ///////////////////////////////////////////////////////////////////////////////

    for (int i = 0; i < maxDimension / 2; i++) {
        for (int j = 0; j < maxDimension / 2; j++) {
            p1[i][j] = 0;
            for (int z = 0; z < maxDimension / 2; z++) {
                p1[i][j] += (mat1[i][z] + mat4[i][z]) * (mat5[z][j] + mat8[z][j]);
            }

            p2[i][j] = 0;
            for (int z = 0; z < maxDimension / 2; z++) {
                p2[i][j] += (mat3[i][z] + mat4[i][z]) * mat5[z][j];
            }

            p3[i][j] = 0;
            for (int z = 0; z < maxDimension / 2; z++) {
                p3[i][j] += mat1[i][z] * (mat6[z][j] - mat8[z][j]);
            }

            p4[i][j] = 0;
            for (int z = 0; z < maxDimension / 2; z++) {
                p4[i][j] += mat4[i][z] * (mat7[z][j] - mat5[z][j]);
            }

            p5[i][j] = 0;
            for (int z = 0; z < maxDimension / 2; z++) {
                p5[i][j] += (mat1[i][z] + mat2[i][z]) * mat8[z][j];
            }

            p6[i][j] = 0;
            for (int z = 0; z < maxDimension / 2; z++) {
                p6[i][j] += (mat3[i][z] - mat1[i][z]) * (mat5[z][j] + mat6[z][j]);
            }

            p7[i][j] = 0;
            for (int z = 0; z < maxDimension / 2; z++) {
                p7[i][j] += (mat2[i][z] - mat4[i][z]) * (mat7[z][j] + mat8[z][j]);
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////Создание вспомогательных матриц/////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    int **mat9 = new int *[maxDimension / 2];
    for (int i = 0; i < maxDimension / 2; i++) {
        mat9[i] = new int[maxDimension / 2];
    }
    int **mat10 = new int *[maxDimension / 2];
    for (int i = 0; i < maxDimension / 2; i++) {
        mat10[i] = new int[maxDimension / 2];
    }
    int **mat11 = new int *[maxDimension / 2];
    for (int i = 0; i < maxDimension / 2; i++) {
        mat11[i] = new int[maxDimension / 2];
    }
    int **mat12 = new int *[maxDimension / 2];
    for (int i = 0; i < maxDimension / 2; i++) {
        mat12[i] = new int[maxDimension / 2];
    }

    ///////////////////////////////////////////////////////////////////////////////
    ////////////Подсчет значений вспомогательных матриц из промежуточных///////////
    ///////////////////////////////////////////////////////////////////////////////

    for (int i = 0; i < maxDimension / 2; i++) {
        for (int j = 0; j < maxDimension / 2; j++) {
            mat9[i][j] = p1[i][j] + p4[i][j] - p5[i][j] + p7[i][j];
            mat10[i][j] = p3[i][j] + p5[i][j];
            mat11[i][j] = p2[i][j] + p4[i][j];
            mat12[i][j] = p1[i][j] - p2[i][j] + p3[i][j] + p6[i][j];
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////Создание результирующей матрицы/////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    int **M5 = new int *[maxDimension];
    for (int i = 0; i < maxDimension; i++) {
        M5[i] = new int[maxDimension];
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///////Занесение информации из вспомогательных матриц в результирующую/////////
    ///////////////////////////////////////////////////////////////////////////////

    for (int i = 0; i < maxDimension / 2; i++) {
        for (int j = 0; j < maxDimension / 2; j++) {
            M5[i][j] = mat9[i][j];
            M5[i][j + maxDimension / 2] = mat10[i][j];
            M5[i + maxDimension / 2][j] = mat11[i][j];
            M5[i + maxDimension / 2][j + maxDimension / 2] = mat12[i][j];
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    ////////////////Выравнивание границ результирующей матрицы/////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    int x = 0, f = 100, s = 100;
    for (int i = 0; i < maxDimension; i++) {
        x = 0;
        for (int j = 0; j < maxDimension; j++) {
            if (M5[i][j] != 0) {
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
            if (M5[j][i] != 0) {
                x++;
                s = 100;
            }
        }
        if (x == 0 && i < s) {
            s = i;
        }
    }

    int **M6 = new int *[f];
    for (int i = 0; i < f; i++) {
        M6[i] = new int[s];
        for (int j = 0; j < s; j++)
            M6[i][j] = M5[i][j];
    }

    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////Вывод результирующей матрицы////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    cout << "\nРезультирующая матрица\n\n";
    for (int i = 0; i < f; i++) {
        for (int j = 0; j < s; j++)
            cout << M6[i][j] << " ";
        cout << endl;
    }

    system("pause");

    ///////////////////////////////////////////////////////////////////////////////
    /////////////////////Очистка динамической памяти///////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    for (int i = 0; i < n1; i++)
        delete[] M1[i];
    for (int i = 0; i < n2; i++)
        delete[] M2[i];
    for (int i = 0; i < maxDimension; i++) {
        delete[] castedM1[i];
        delete[] castedM2[i];
        delete[] M5[i];
    }
    for (int i = 0; i < f; i++)
        delete[] M6[i];
    for (int i = 0; i < maxDimension / 2; i++) {
        delete[] mat1[i];
        delete[] mat2[i];
        delete[] mat3[i];
        delete[] mat4[i];
        delete[] mat5[i];
        delete[] mat6[i];
        delete[] mat7[i];
        delete[] mat8[i];
        delete[] mat9[i];
        delete[] mat10[i];
        delete[] mat11[i];
        delete[] mat12[i];
        delete[] p1[i];
        delete[] p2[i];
        delete[] p3[i];
        delete[] p4[i];
        delete[] p5[i];
        delete[] p6[i];
        delete[] p7[i];
    }
    delete[] M1, M2, castedM1, castedM2, M5, M6;
    delete[] mat1, mat2, mat3, mat4, mat5, mat6, mat7, mat8, mat9, mat10, mat11, mat12;
    delete[] p1, p2, p3, p4, p5, p6, p7;

    return 0;
}