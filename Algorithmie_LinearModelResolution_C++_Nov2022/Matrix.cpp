//
// Created by Mehdi on 16/11/2022.
//
#include <iostream>
#include <string>
#include "Matrix.h"
#include "LinearSystem.h"





// Various Constructors and Destructor.
// Default Constructor
Matrix::Matrix()
{
    nRows = 0;
    nColumns = 0;
    matrixData = nullptr;
}

// Construct a zeros matrix, with an entry parameters defining size
Matrix::Matrix(int c_nRows, int c_nColumns)
{
    nRows = c_nRows;
    nColumns = c_nColumns;
    matrixData = new double*[nRows];
    for(int i=0; i<nRows; i++) {matrixData[i]=new double[nColumns];}
    for(int i=0; i<nRows; i++){for(int j=0; j<nColumns; j++){matrixData[i][j]=0;}}
}

//Construct from a given 1 dimension table
Matrix::Matrix(int c_nRows, int c_nColumns, const double* inputData)
{
    nRows = c_nRows;
    nColumns = c_nColumns;
    matrixData = new double*[nRows];
    for(int i=0; i<nRows; i++) {matrixData[i]=new double[nColumns];}
    for(int i=0; i<nRows; i++){for(int j=0; j<nColumns; j++){matrixData[i][j]=inputData[(i*nColumns) + j];}}
}

// Construct from a given 2 dimension table
Matrix::Matrix(int c_nRows, int c_nColumns, double** inputData)
{
    nRows = c_nRows;
    nColumns = c_nColumns;
    matrixData = new double*[nRows];
    for(int i=0; i<nRows; i++) {matrixData[i]=new double[nColumns];}
    for(int i=0; i<nRows; i++){for(int j=0; j<nColumns; j++){matrixData[i][j]=inputData[i][j];}}
}

// Duplicator (copy) from an original matrix.
Matrix::Matrix(const Matrix& original)
{
    nRows = original.nRows;
    nColumns = original.nColumns;
    matrixData = new double*[nRows];
    for(int i=0; i<nRows; i++) {
        matrixData[i]=new double[nColumns];

    }
    for(int i=0; i<nRows; i++){
        for(int j=0; j<nColumns; j++){
            this->matrixData[i][j]=original.matrixData[i][j];
        }
    }


}


// Destructor
Matrix::~Matrix() = default;
    /* we can also define it as:

      {
           for(int i=0; i<nRows; i++){
              delete[] matrixData[i];
           }
           delete[] matrixData;
      }

    */





// Getters et Setters
// Getters
int Matrix::GetNRows() const  { return nRows;}

int Matrix::GetNColumns() const { return nColumns;}

double ** Matrix::GetMatrixData() const { return matrixData;}

double Matrix::GetValueAt(int row, int column) const  { return matrixData[row][column];}

// Setters
void Matrix::SetValueAt(int row, int column, double newValue) { matrixData[row][column] = newValue; }

void Matrix::SetData(double** newData)
{
    for(int i=0; i<nRows; i++)
    {
        for(int j=0; j<nColumns; j++)
        {
            matrixData[i][j] = newData[i][j];
        }

    }
}


// Overloading operators
// Operator +
// Left hand side Matrix (lhs) + right hand side Matrix (rhs)
Matrix operator+ (const Matrix& lhs, const Matrix& rhs)
{
    assert(lhs.GetNRows()==rhs.GetNRows() && lhs.GetNColumns()==rhs.GetNColumns());
    int c_nRows = lhs.GetNRows();
    int c_nColumns = lhs.GetNColumns();
    auto** dataResult = new double* [c_nRows];
    for(int i=0; i<c_nRows; i++) { dataResult[i] = new double [c_nColumns];}
    for(int i=0; i<c_nRows; i++){for(int j=0; j<c_nColumns; j++){ dataResult[i][j]= lhs.GetValueAt(i, j) + rhs.GetValueAt(i,j);}}

    Matrix result(c_nRows,c_nColumns,dataResult);
    for(int i=0; i<c_nRows; i++){ delete[] dataResult[i];}
    delete[] dataResult;
    return result;
}


// Left hand side double (lhs) + right hand side Matrix (rhs)
Matrix operator+ (const double& lhs, const Matrix& rhs)
{
    int c_nRows = rhs.GetNRows();
    int c_nColumns = rhs.GetNColumns();
    auto** dataResult = new double* [c_nRows];
    for(int i=0; i<c_nRows; i++) { dataResult[i] = new double [c_nColumns];}
    for(int i=0; i<c_nRows; i++){for(int j=0; j<c_nColumns; j++){ dataResult[i][j]= lhs + rhs.GetValueAt(i,j);}}
    Matrix result(c_nRows, c_nColumns, dataResult);
    for(int i=0; i<c_nRows; i++){ delete[] dataResult[i];}
    delete[] dataResult;
    return result;
}

// Left hand side Matrix (lhs) + right hand side double (rhs)
Matrix operator+ (const Matrix& lhs, const double& rhs)
{
    int c_nRows = lhs.GetNRows();
    int c_nColumns = lhs.GetNColumns();
    auto** dataResult = new double* [c_nRows];
    for(int i=0; i<c_nRows; i++) { dataResult[i] = new double [c_nColumns];}
    for(int i=0; i<c_nRows; i++){for(int j=0; j<c_nColumns; j++){ dataResult[i][j]= rhs + lhs.GetValueAt(i,j);}}
    Matrix result(c_nRows, c_nColumns, dataResult);
    for(int i=0; i<c_nRows; i++){ delete[] dataResult[i];}
    delete[] dataResult;
    return result;
}

// Operator -
// Left hand side Matrix (lhs) - right hand side Matrix (rhs)
Matrix operator- (const Matrix& lhs, const Matrix& rhs)
{
    assert(lhs.GetNRows()==rhs.GetNRows() && lhs.GetNColumns()==rhs.GetNColumns());
    int c_nRows = lhs.GetNRows();
    int c_nColumns = lhs.GetNColumns();
    auto** dataResult = new double* [c_nRows];
    for(int i=0; i<c_nRows; i++) { dataResult[i] = new double [c_nColumns];}
    for(int i=0; i<c_nRows; i++){for(int j=0; j<c_nColumns; j++){ dataResult[i][j]= lhs.GetValueAt(i, j) - rhs.GetValueAt(i,j);}}

    Matrix result(c_nRows,c_nColumns,dataResult);
    for(int i=0; i<c_nRows; i++){ delete[] dataResult[i];}
    delete[] dataResult;
    return result;
}


// Left hand side double (lhs) - right hand side Matrix (rhs)
Matrix operator- (const double& lhs, const Matrix& rhs)
{
    int c_nRows = rhs.GetNRows();
    int c_nColumns = rhs.GetNColumns();
    auto** dataResult = new double* [c_nRows];
    for(int i=0; i<c_nRows; i++) { dataResult[i] = new double [c_nColumns];}
    for(int i=0; i<c_nRows; i++){for(int j=0; j<c_nColumns; j++){ dataResult[i][j]= lhs - rhs.GetValueAt(i,j);}}
    Matrix result(c_nRows, c_nColumns, dataResult);
    for(int i=0; i<c_nRows; i++){ delete[] dataResult[i];}
    delete[] dataResult;
    return result;
}

// Left hand side Matrix (lhs) - right hand side double (rhs)
Matrix operator- (const Matrix& lhs, const double& rhs)
{
    int c_nRows = lhs.GetNRows();
    int c_nColumns = lhs.GetNColumns();
    auto** dataResult = new double* [c_nRows];
    for(int i=0; i<c_nRows; i++) { dataResult[i] = new double [c_nColumns];}
    for(int i=0; i<c_nRows; i++){for(int j=0; j<c_nColumns; j++){ dataResult[i][j]= rhs - lhs.GetValueAt(i,j);}}
    Matrix result(c_nRows, c_nColumns, dataResult);
    for(int i=0; i<c_nRows; i++){ delete[] dataResult[i];}
    delete[] dataResult;
    return result;
}


// Operator *
// Left hand side Matrix (lhs) * right hand side Matrix (rhs)
Matrix operator* (const Matrix& lhs, const Matrix& rhs)
{
    assert(lhs.GetNColumns()==rhs.GetNRows());
    int c_nRows = lhs.GetNRows();
    int c_nColumns = rhs.GetNColumns();
    auto** dataResult = new double* [c_nRows];
    for(int i=0; i<c_nRows; i++) { dataResult[i] = new double [c_nColumns];}
    for(int i=0; i<c_nRows; i++){for(int j=0; j<c_nColumns; j++){ dataResult[i][j]= 0.0;}}
    for(int i=0; i<c_nRows; i++){
        for(int j=0; j<c_nColumns; j++){
            for(int k=0; k<lhs.GetNColumns(); k++) {
                dataResult[i][j] += lhs.GetValueAt(i, k) * rhs.GetValueAt(k, j);
            }
        }
    }
    Matrix result(c_nRows,c_nColumns,dataResult);
    for(int i=0; i<c_nRows; i++){ delete[] dataResult[i];}
    delete[] dataResult;
    return result;
}


// Left hand side double (lhs) * right hand side Matrix (rhs)
Matrix operator* (const double& lhs, const Matrix& rhs)
{
    int c_nRows = rhs.GetNRows();
    int c_nColumns = rhs.GetNColumns();
    auto** dataResult = new double* [c_nRows];
    for(int i=0; i<c_nRows; i++) { dataResult[i] = new double [c_nColumns];}
    for(int i=0; i<c_nRows; i++){for(int j=0; j<c_nColumns; j++){ dataResult[i][j]= lhs * rhs.GetValueAt(i,j);}}
    Matrix result(c_nRows, c_nColumns, dataResult);
    for(int i=0; i<c_nRows; i++){ delete[] dataResult[i];}
    delete[] dataResult;
    return result;
}

// Left hand side Matrix (lhs) * right hand side double (rhs)
Matrix operator* (const Matrix& lhs, const double& rhs)
{
    int c_nRows = lhs.GetNRows();
    int c_nColumns = lhs.GetNColumns();
    auto** dataResult = new double* [c_nRows];
    for(int i=0; i<c_nRows; i++) { dataResult[i] = new double [c_nColumns];}
    for(int i=0; i<c_nRows; i++){for(int j=0; j<c_nColumns; j++){ dataResult[i][j]= rhs * lhs.GetValueAt(i,j);}}
    Matrix result(c_nRows, c_nColumns, dataResult);
    for(int i=0; i<c_nRows; i++){ delete[] dataResult[i];}
    delete[] dataResult;
    return result;
}



// Operator ==
bool Matrix::operator== (const Matrix& rhs) const
{
    // Check simple conditions first
    if ((this->nRows != rhs.nRows) || (this->nColumns != rhs.nColumns))
        return false;

    // Check element by element
    for (int i=0; i<this->nRows; ++i){
        for (int j=0; j<this->nColumns; j++){
            if (fabs(this->matrixData[i][j] - rhs.matrixData[i][j]) > TOLERANCE)
                return false;
        }
    }
    return true;

}

// Assignment operator =
Matrix& Matrix::operator= (const Matrix& rhs)
{

    for(int i=0; i<nRows; i++){ delete[] matrixData[i];}
    delete[] matrixData;
    nRows= rhs.nRows;
    nColumns = rhs.nColumns;
    matrixData = new double* [nRows];
    for(int i=0; i<nRows; i++){
        matrixData[i] = new double [nColumns];
    }
    for (int i=0; i<nRows; i++){
        for (int j=0; j<nColumns; j++){
            matrixData[i][j] = rhs.matrixData[i][j];
        }
    }

    return *this;
}

// Facilities :
void Matrix::Print(){
    for(int i=0; i<nRows; i++){
        for(int j=0; j<nColumns; j++){
            std::cout << matrixData[i][j]  << "\t"; }
        std::cout << "\n"; }
    std::cout << "\n" << std::endl;
}

// Matrices operations

Matrix Matrix::Transpose() const {
    auto**  tempData = new double* [nColumns];
    for(int i=0; i<nColumns; i++){tempData[i]=new double[nRows];}
    for(int i=0; i<nColumns; i++){
        for(int j=0; j<nRows; j++){
            tempData[i][j]=matrixData[j][i];
        }
    }
    Matrix result(nColumns, nRows, tempData);
    for(int i=0; i<nColumns; i++){ delete[] tempData[i];}
    delete[] tempData;
    return result;
}

Matrix Matrix::UpperTriangleForm() const {
    assert(nRows == nColumns); // Only squared matrices can be transformed to triangle form
    // At this point, we know the matrix is squared, but we continue to use nRows and nColumns
    // for more readability, and to understand algorithm process
    auto **tempData = new double *[nRows];
    for (int i = 0; i < nRows; i++) { tempData[i] = new double[nColumns]; }
    for (int m = 0; m < nRows; m++) {
        for (int n = 0; n < nColumns; n++) {
            tempData[m][n] = matrixData[m][n];}
    } // tempData is now a copy of matrixData
    double l;
    for (int k = 0; k < (nColumns - 1); k++) {
        for (int i = k + 1; i < nRows; i++)
            if (tempData[k][k] != 0) {
                l = tempData[i][k] / tempData[k][k];
                tempData[i][k] = 0;
                for (int j = k + 1; j < nColumns; j++) {
                    tempData[i][j] = tempData[i][j] - l * tempData[k][j];
                }

            }

    }
    Matrix result(nRows, nColumns, tempData);
    for (int i = 0; i < nRows; i++) { delete[] tempData[i]; }
    delete[] tempData;
    return result;
}

Matrix Matrix::InfraMatrix(int row, int column) const {
    assert(row < nRows && column < nColumns);
    auto *tempData = new double [(nRows-1)*(nColumns-1)];

    int count=0;
    for (int i=0; i<nRows; i++)
    {
        for (int j=0; j<nColumns; j++)
        {
            // We copy only if i and j are different of row and column to truncate
            if ((i != row) && (j != column))
            {
                tempData[count] = matrixData[i][j];
                count++;
            }
        }
    }
    Matrix daughter(nRows-1, nColumns-1, tempData);


    delete[] tempData;
    return daughter;
}

double Matrix::DeterminantCofactorFR() const {
    // I put "this->" everywhere, to avoid any ambiguity when recursive application
    assert(this->IsSquare()); // Check if square matrix
    double result= 0;

    if (this->nRows == 1 && this->nColumns==1){  // case : 1*1 matrix
        result = this->matrixData[0][0];
        return result;
    } // case : 1*1 matrix

    for(int j=0; j<this->nColumns; j++) { // else, we simply  use the cofactor formula seen in TD
        Matrix daughter = this->InfraMatrix(0,j);
        double daughterDeterminant = daughter.DeterminantCofactorFR();
        result += pow(-1, j)*(this->matrixData[0][j])*daughterDeterminant;

    }

    return result;
}

double Matrix::DeterminantTriangularForm() const {
    assert(this->IsSquare()); // Check if square matrix
    double result = 1;
    Matrix triangle = this->UpperTriangleForm();
    for(int i=0; i<nRows; i++){ result *= triangle.matrixData[i][i];}
    return result;
}

Matrix Matrix::Cofactor() const {

    auto *tempData = new double [nRows * nColumns];

    int count=0;
    for (int i=0; i<nRows; i++)
    {
        for (int j=0; j<nColumns; j++)
        {
            tempData[count] = pow(-1, i+j) * this->InfraMatrix(i,j).DeterminantCofactorFR();
            count++;

        }
    }
    Matrix cofactor(nRows, nColumns, tempData);


    delete[] tempData;
    return cofactor;

}

Matrix Matrix::Adjugate() const {
    return (this->Cofactor().Transpose());
}

Matrix Matrix::InverseLE() const {
    // Formula : if inversible, Inverse = ( 1/determinant) * this->Cofactor.transpose
    double determinant = this->DeterminantCofactorFR();

    assert(determinant != 0.0); // equivalent to ( this->IsInversible ), without computing the determinant a second time

    Matrix adjugate = this->Adjugate();

    auto *tempData = new double [nRows * nColumns];

    int count=0;
    for (int i=0; i<nRows; i++)
    {
        for (int j=0; j<nColumns; j++)
        {
            tempData[count] = (1/determinant) * adjugate.matrixData[i][j];
            count++;

        }
    }
    Matrix inverse(nRows, nColumns, tempData);


    delete[] tempData;
    return inverse;

}

bool Matrix::IsSquare() const{
    return nRows==nColumns;
}

bool Matrix::IsUpperTriangular() const {
    if (nColumns != nRows) {return false;}
    for(int j=0; j<nColumns; j++){
        for(int i=j+1; i<nRows; i++){
            if (this->matrixData[i][j] != 0.0) {
                return false;
            }
        }
    }
    return true ;
}

bool Matrix::IsLowerTriangular() const {
    if (nColumns != nRows) {return false;}
    for(int j=0; j<nColumns; j++){
        for(int i=0; i<j; i++){
            if (this->matrixData[i][j] != 0.0) {
                return false;
            }
        }
    }
    return true ;

}

bool Matrix::IsInversible() const {
    return (this->DeterminantCofactorFR() != 0.0);
}









