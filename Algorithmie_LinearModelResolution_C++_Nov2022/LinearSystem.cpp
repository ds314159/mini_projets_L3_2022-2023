//
// Created by Mehdi on 18/11/2022.
//

#include "LinearSystem.h"
#include "Matrix.h"

LinearSystem::LinearSystem( Matrix& A,  Matrix& B) {
    assert(B.GetNColumns()==1); // check B is a vector
    assert(A.IsSquare());       // check A is square
    assert(A.GetNRows()==B.GetNRows()); // check compatible size

    this->A = Matrix(A);  // we work on copies
    this->B = Matrix(B);
    nUnknowns = A.GetNRows(); // or B.GetnRows

}

LinearSystem::LinearSystem(LinearSystem& original) {
    A = Matrix(original.GetA());
    B = Matrix(original.GetB());
    nUnknowns = original.GetSize();
}

//Getters and setters
Matrix LinearSystem::GetA(){return A;}
Matrix LinearSystem::GetB(){return B;}
int LinearSystem::GetSize() {return nUnknowns;}
void LinearSystem::SetA(Matrix& value){
    assert(value.IsSquare());
    assert(value.GetNRows()==B.GetNRows());
    this->A= Matrix(value);
}
void LinearSystem::SetB(Matrix& value){
    assert(value.GetNColumns()==1);
    assert(value.GetNRows()==A.GetNRows());
    this->B= Matrix(value);
}

//Destructor
LinearSystem::~LinearSystem() = default;
    /* we can also define it as:
     {
        this->A.Matrix::~Matrix();
        this->B.Matrix::~Matrix();
     }
     */


Matrix LinearSystem::Solution() {
    // We begin by making A triangular , using the algo seen in TD, every time we make a combination in a A's row, we do
    // the same operation in the B's row

    double **tempDataA = A.GetMatrixData();//new double *[nUnknowns];
    //for (int i = 0; i < nUnknowns; i++) { tempDataA[i] = new double[nUnknowns]; }
    //for (int m = 0; m < nUnknowns; m++) {
    //    for (int n = 0; n < nUnknowns; n++) {
    //        tempDataA[m][n] = A.GetMatrixData()[m][n];
    //}
    //}// tempDataA is now a copy of A.matrixData
    auto **tempDataB = B.GetMatrixData();//new double[nUnknowns];
    //for (int i = 0; i < nUnknowns; i++) {
    //    tempDataB[i] = B.GetMatrixData()[i][0];
    //} // tempDataB is now a copy of B.matrixData

    auto *tempDataX = new double[nUnknowns];

    // we will use it to  temporary stock the solution

    double l;
    for (int k = 0; k < (nUnknowns - 1); k++) {
        for (int i = k + 1; i < nUnknowns; i++) {
            if (tempDataA[k][k] != 0) {
                l = tempDataA[i][k] / tempDataA[k][k];
                tempDataA[i][k] = 0;
                tempDataB[i][0] -= l * tempDataB[k][0];
                for (int j = k + 1; j < nUnknowns; j++) {
                    tempDataA[i][j] = tempDataA[i][j] - l * tempDataA[k][j];
                }

            }
        }
    }

    // Now we go back to compute the solution one by one
    for(int i=(nUnknowns-1); i>=0; i--){
        tempDataX[i]=tempDataB[i][0];
        for(int j=(i+1); j< nUnknowns; j++){
            tempDataX[i]= tempDataX[i] - ( tempDataX[j] * tempDataA[i][j] );
        }
        tempDataX[i]= tempDataX[i] / tempDataA[i][i];

    }

    Matrix result(nUnknowns, 1, tempDataX);




    for (int i = 0; i < nUnknowns; i++) { delete[] tempDataA[i]; }
    delete[] tempDataA;
    delete[] tempDataB;
    delete[] tempDataX;
    return result;

}
