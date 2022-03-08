#include <iostream>
#include <cstdlib>
#include <ctime>
#include "headers/setup.h"
#include "headers/fill.h"
#include "headers/cast.h"
#include "headers/split.h"
#include "headers/utils.h"
#include "headers/intermediate.h"
#include "headers/result.h"

using namespace std;


int main() {
    srand(time(NULL));
    int n1, m1, n2, m2, maxDimension = 2;
    system("chcp 1251");
    cout << "Вас приветствует программа" << endl <<
         "быстрого перемножения матриц методом Штрассена\n\n";

    /**
     * Input dimensions
     */
    int **M1;
    int **M2;
    setupMatrix(n1, m1, M1);
    setupMatrix(n2, m2, M2);

    /**
     * Fill matrix data via desired option
     */
    fillMatrices(n1, m1, n2, m2, M1, M2);

   /**
    * Cast dimensions of matrices to required values
    */
    int **castedM1;
    int **castedM2;
    maxDimension = calculateMaxDimension(n1,m1,n2,m2, maxDimension);
    cout << "Приведенные матрицы\n";
    cout << "\nМатрица 1\n\n";
    castMatrix(n1, m1, maxDimension, M1, castedM1);
    cout << "\nМатрица 2\n\n";
    castMatrix(n2, m2, maxDimension, M2, castedM2);

    /**
     * Split matrices to submatrices and their filling
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


    /**
     * Intermediate matrices are stored as sequence of matrices in intermediateMatrices
     */

    int *** intermediateMatrices = new int**[7];
    for (int i = 0; i < 7; ++i) {
        initMatrix(maxDimension, intermediateMatrices[i]);
    }
    calculateIntermediateMatrices(maxDimension, splittedMatrices, intermediateMatrices);

    /**
     * Create support matrices
     */
    int *** supportMatrices = new int**[4];
    for (int i = 0; i < 4; ++i) {
        initMatrix(maxDimension, supportMatrices[i]);
    }

    /**
     * calculate values of support matrices from intermediate
     */
    writeFromIntermediate(maxDimension, intermediateMatrices, supportMatrices);

    /**
     * create resulting matrix (this matrix will contain data before padding)
     */
    int **beforePadding = new int *[maxDimension];
    for (int i = 0; i < maxDimension; i++) {
        beforePadding[i] = new int[maxDimension];
    }
    /**
     * Write data from support matrix to resulting
     */
    writeToFinalMatrix(maxDimension, supportMatrices, beforePadding);
    /**
     * Perform padding
     * function doPaddings returns both padded dimensions and padded matrix itself
     */
    int resultingAmountOfRows;
    int resultingAmountOfColumns;
    int **afterPadding;
    doPadding(maxDimension, beforePadding, resultingAmountOfRows, resultingAmountOfColumns, afterPadding);
    cout << "\nРезультирующая матрица\n\n";
    printMatrix(resultingAmountOfRows, resultingAmountOfColumns, afterPadding);
    clearMemory(n1, n2, maxDimension, M1, M2, castedM1, castedM2, splittedMatrices, intermediateMatrices,
                supportMatrices,
                beforePadding, resultingAmountOfRows, afterPadding);

    return 0;
}