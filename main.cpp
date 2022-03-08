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
    /**
     * Eight splitted matrices are stored in this array
     * They comprise 2 matrices (4 parts for each one respectively)
     */
    int *** splittedMatrices = new int**[8];

    splitMatrix(maxDimension,
                castedM1,
                splittedMatrices[0],
                0,
                0);
    splitMatrix(maxDimension,
                castedM1,
                splittedMatrices[1],
                0,
                maxDimension / 2);
    splitMatrix(maxDimension,
                castedM1,
                splittedMatrices[2],
                maxDimension / 2,
                0);
    splitMatrix(maxDimension,
                castedM1,
                splittedMatrices[3],
                maxDimension / 2,
                maxDimension / 2);

    splitMatrix(maxDimension,
                castedM2,
                splittedMatrices[4],
                0,
                0);
    splitMatrix(maxDimension,
                castedM2,
                splittedMatrices[5],
                0,
                maxDimension / 2);
    splitMatrix(maxDimension,
                castedM2,
                splittedMatrices[6],
                maxDimension / 2,
                0);
    splitMatrix(maxDimension,
                castedM2,
                splittedMatrices[7],
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
    calculateIntermediateMatrices(maxDimension, splittedMatrices, intermediateMatrices);

    ///////////////////////////////////////////////////////////////////////////////
    ///////////////////////Создание вспомогательных матриц/////////////////////////
    ///////////////////////////////////////////////////////////////////////////////
    int *** supportMatrices = new int**[4];
    for (int i = 0; i < 4; ++i) {
        initMatrix(maxDimension, supportMatrices[i]);
    }

    ///////////////////////////////////////////////////////////////////////////////
    ////////////Подсчет значений вспомогательных матриц из промежуточных///////////
    ///////////////////////////////////////////////////////////////////////////////

    for (int i = 0; i < maxDimension / 2; i++) {
        for (int j = 0; j < maxDimension / 2; j++) {
            supportMatrices[0][i][j] = intermediateMatrices[0][i][j] + intermediateMatrices[3][i][j] - intermediateMatrices[4][i][j] + intermediateMatrices[6][i][j];
            supportMatrices[1][i][j] = intermediateMatrices[2][i][j] + intermediateMatrices[4][i][j];
            supportMatrices[2][i][j] = intermediateMatrices[1][i][j] + intermediateMatrices[3][i][j];
            supportMatrices[3][i][j] = intermediateMatrices[0][i][j] - intermediateMatrices[1][i][j] + intermediateMatrices[2][i][j] + intermediateMatrices[5][i][j];
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
            M5[i][j] = supportMatrices[0][i][j];
            M5[i][j + maxDimension / 2] = supportMatrices[1][i][j];
            M5[i + maxDimension / 2][j] = supportMatrices[2][i][j];
            M5[i + maxDimension / 2][j + maxDimension / 2] = supportMatrices[3][i][j];
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
    delete[] M1, M2, castedM1, castedM2, M5, M6;
    delete[] splittedMatrices[0], splittedMatrices[1], splittedMatrices[2], splittedMatrices[3], splittedMatrices[4], splittedMatrices[5], splittedMatrices[6], splittedMatrices[7], supportMatrices[0], supportMatrices[1], supportMatrices[2], supportMatrices[3];
    // delete[] intermediateMatrices[0], intermediateMatrices[1], intermediateMatrices[2], intermediateMatrices[3], intermediateMatrices[4], intermediateMatrices[5], intermediateMatrices[6];

    return 0;
}