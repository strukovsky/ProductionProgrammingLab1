//
// Created by Дмитрий Стрюковский on 08.03.2022.
//

#ifndef LAB1_INTERMEDIATE_H
#define LAB1_INTERMEDIATE_H


void calculateIntermediateMatrices(int maxDimension, int ***splittedMatrices,
                                   int ***intermediateMatrices);
void writeFromIntermediate(int maxDimension, int **const *intermediateMatrices, int ***supportMatrices);

#endif //LAB1_INTERMEDIATE_H
