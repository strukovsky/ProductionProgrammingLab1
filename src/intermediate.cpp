//
// Created by Дмитрий Стрюковский on 08.03.2022.
//

#include <ctime>
#include <cstdlib>
#include <iostream>
#include "../headers/intermediate.h"

void calculateIntermediateMatrices(int maxDimension, int *const *splitM1First, int *const *splitM1Second,
                                   int *const *splitM1Third, int *const *splitM1Fourth, int *const *splitM2First,
                                   int *const *splitM2Second, int *const *splitM2Third, int *const *splitM2Fourth,
                                   int ***intermediateMatrices) {
    for (int intermediateMatrixIdx = 0; intermediateMatrixIdx < 7; intermediateMatrixIdx++) {
        for (int i = 0; i < maxDimension / 2; i++) {
            for (int j = 0; j < maxDimension / 2; j++) {
                intermediateMatrices[intermediateMatrixIdx][i][j] = 0;
            }
        }
    }
    for (int i = 0; i < maxDimension / 2; i++) {
        for (int j = 0; j < maxDimension / 2; j++) {
            for (int z = 0; z < maxDimension / 2; z++) {
                intermediateMatrices[0][i][j] +=
                        (splitM1First[i][z] + splitM1Fourth[i][z]) * (splitM2First[z][j] + splitM2Fourth[z][j]);
            }

            for (int z = 0; z < maxDimension / 2; z++) {
                intermediateMatrices[1][i][j] += (splitM1Third[i][z] + splitM1Fourth[i][z]) * splitM2First[z][j];
            }

            for (int z = 0; z < maxDimension / 2; z++) {
                intermediateMatrices[2][i][j] += splitM1First[i][z] * (splitM2Second[z][j] - splitM2Fourth[z][j]);
            }

            for (int z = 0; z < maxDimension / 2; z++) {
                intermediateMatrices[3][i][j] += splitM1Fourth[i][z] * (splitM2Third[z][j] - splitM2First[z][j]);
            }

            for (int z = 0; z < maxDimension / 2; z++) {
                intermediateMatrices[4][i][j] += (splitM1First[i][z] + splitM1Second[i][z]) * splitM2Fourth[z][j];
            }

            for (int z = 0; z < maxDimension / 2; z++) {
                intermediateMatrices[5][i][j] +=
                        (splitM1Third[i][z] - splitM1First[i][z]) * (splitM2First[z][j] + splitM2Second[z][j]);
            }

            for (int z = 0; z < maxDimension / 2; z++) {
                intermediateMatrices[6][i][j] +=
                        (splitM1Second[i][z] - splitM1Fourth[i][z]) * (splitM2Third[z][j] + splitM2Fourth[z][j]);
            }
        }
    }
}