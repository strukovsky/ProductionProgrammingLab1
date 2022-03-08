//
// Created by Дмитрий Стрюковский on 08.03.2022.
//

#include "../headers/intermediate.h"

void calculateIntermediateMatrices(int maxDimension, int ***splittedMatrices,
                                   int ***intermediateMatrices) {
    for (int intermediateMatrixIdx = 0; intermediateMatrixIdx < 7; intermediateMatrixIdx++) {
        for (int i = 0; i < maxDimension / 2; i++) {
            for (int j = 0; j < maxDimension / 2; j++) {
                intermediateMatrices[intermediateMatrixIdx][i][j] = 0;
            }
        }
    }
    /**
     * 0 splitM1First
     * 1 splitM1Second
     * 2 splitM1Third
     * 3 splitM1Fourth
     * 4 splitM2First
     * 5 splitM2Second
     * 6 splitM2Third
     * 7 splitM2Fourth
     */
    for (int i = 0; i < maxDimension / 2; i++) {
        for (int j = 0; j < maxDimension / 2; j++) {
            for (int z = 0; z < maxDimension / 2; z++) {
                intermediateMatrices[0][i][j] +=
                        (splittedMatrices[0][i][z] + splittedMatrices[3][i][z]) * (splittedMatrices[4][z][j] + splittedMatrices[7][z][j]);
            }

            for (int z = 0; z < maxDimension / 2; z++) {
                intermediateMatrices[1][i][j] += (splittedMatrices[2][i][z] + splittedMatrices[3][i][z]) * splittedMatrices[4][z][j];
            }

            for (int z = 0; z < maxDimension / 2; z++) {
                intermediateMatrices[2][i][j] += splittedMatrices[0][i][z] * (splittedMatrices[5][z][j] - splittedMatrices[7][z][j]);
            }

            for (int z = 0; z < maxDimension / 2; z++) {
                intermediateMatrices[3][i][j] += splittedMatrices[3][i][z] * (splittedMatrices[6][z][j] - splittedMatrices[4][z][j]);
            }

            for (int z = 0; z < maxDimension / 2; z++) {
                intermediateMatrices[4][i][j] += (splittedMatrices[0][i][z] + splittedMatrices[1][i][z]) * splittedMatrices[7][z][j];
            }

            for (int z = 0; z < maxDimension / 2; z++) {
                intermediateMatrices[5][i][j] +=
                        (splittedMatrices[2][i][z] - splittedMatrices[0][i][z]) * (splittedMatrices[4][z][j] + splittedMatrices[5][z][j]);
            }

            for (int z = 0; z < maxDimension / 2; z++) {
                intermediateMatrices[6][i][j] +=
                        (splittedMatrices[1][i][z] - splittedMatrices[3][i][z]) * (splittedMatrices[6][z][j] + splittedMatrices[7][z][j]);
            }
        }
    }
}