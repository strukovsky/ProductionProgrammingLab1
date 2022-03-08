#include <iostream>
#include <cstdlib>
#include <ctime>
#include "headers/setup.h"
#include "headers/fill.h"
#include "headers/cast.h"
#include "headers/split.h"
#include "headers/utils.h"
#include "headers/intermediate.h"

using namespace std;


int main() {
    srand(time(NULL));
    int n1, m1, n2, m2, maxDimension = 2;
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

    int **splitM1First;
    splitMatrix(maxDimension,
                castedM1,
                splitM1First,
                0,
                0);
    int **splitM1Second;
    splitMatrix(maxDimension,
                castedM1,
                splitM1Second,
                0,
                maxDimension / 2);
    int **splitM1Third;
    splitMatrix(maxDimension,
                castedM1,
                splitM1Third,
                maxDimension / 2,
                0);
    int **splitM1Fourth;
    splitMatrix(maxDimension,
                castedM1,
                splitM1Fourth,
                maxDimension / 2,
                maxDimension / 2);

    int **splitM2First;
    splitMatrix(maxDimension,
                castedM2,
                splitM2First,
                0,
                0);
    int **splitM2Second;
    splitMatrix(maxDimension,
                castedM2,
                splitM2Second,
                0,
                maxDimension / 2);
    int **splitM2Third;
    splitMatrix(maxDimension,
                castedM2,
                splitM2Third,
                maxDimension / 2,
                0);
    int **splitM2Fourth;
    splitMatrix(maxDimension,
                castedM2,
                splitM2Fourth,
                maxDimension / 2,
                maxDimension / 2);


    ///////////////////////////////////////////////////////////////////////////////
    ////////////////////////Создание промежуточных матриц//////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    /**
     * Intermediate matrices are stored as sequence of matrices in intermediateMatrices
     */
    int *** intermediateMatrices = new int**[7];
    for (int i = 0; i < 7; ++i) {
        initMatrix(maxDimension, intermediateMatrices[i]);
    }

    ///////////////////////////////////////////////////////////////////////////////
    ////////////////////Вычисление значений промежуточных матриц///////////////////
    ///////////////////////////////////////////////////////////////////////////////
    calculateIntermediateMatrices(maxDimension, splitM1First, splitM1Second, splitM1Third, splitM1Fourth, splitM2First,
                                  splitM2Second, splitM2Third,
                                  splitM2Fourth, intermediateMatrices);

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
            mat9[i][j] = intermediateMatrices[0][i][j] + intermediateMatrices[3][i][j] - intermediateMatrices[4][i][j] + intermediateMatrices[6][i][j];
            mat10[i][j] = intermediateMatrices[2][i][j] + intermediateMatrices[4][i][j];
            mat11[i][j] = intermediateMatrices[1][i][j] + intermediateMatrices[3][i][j];
            mat12[i][j] = intermediateMatrices[0][i][j] - intermediateMatrices[1][i][j] + intermediateMatrices[2][i][j] + intermediateMatrices[5][i][j];
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
        delete[] splitM1First[i];
        delete[] splitM1Second[i];
        delete[] splitM1Third[i];
        delete[] splitM1Fourth[i];
        delete[] splitM2First[i];
        delete[] splitM2Second[i];
        delete[] splitM2Third[i];
        delete[] splitM2Fourth[i];
        delete[] mat9[i];
        delete[] mat10[i];
        delete[] mat11[i];
        delete[] mat12[i];
        delete[] intermediateMatrices[0][i];
        delete[] intermediateMatrices[1][i];
        delete[] intermediateMatrices[2][i];
        delete[] intermediateMatrices[3][i];
        delete[] intermediateMatrices[4][i];
        delete[] intermediateMatrices[5][i];
        delete[] intermediateMatrices[6][i];
    }
    delete[] M1, M2, castedM1, castedM2, M5, M6;
    delete[] splitM1First, splitM1Second, splitM1Third, splitM1Fourth, splitM2First, splitM2Second, splitM2Third, splitM2Fourth, mat9, mat10, mat11, mat12;
    // delete[] intermediateMatrices[0], intermediateMatrices[1], intermediateMatrices[2], intermediateMatrices[3], intermediateMatrices[4], intermediateMatrices[5], intermediateMatrices[6];

    return 0;
}