#include <stdio.h>
#include "matrix.h"

int main()
{
    Matrix * matA = createMat(2,3);
    Matrix * matB = createMat(2,3);
    Matrix * matC = createMat(2,3);
    Matrix * matD = createMat(3,2);
    Matrix * matNULL = NULL;
    printf("create Mat sucess!");
    matA->data[3] = 2.3f;
    matB->data[3] = 3.1f;

    if(!add(matA, matB, matC))
    {
        fprintf(stderr, "Matrix addition failed!");
    }
    else{
        printf("result=%f\n", matC->data[3]);

    }

    // more tests
    add(matA, matB, matD);

    add(matNULL, matB, matC);

    return 0;
}