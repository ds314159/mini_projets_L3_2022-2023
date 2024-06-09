//
// Created by Mehdi on 17/11/2022.
//

#ifndef MATRIX_H
#define MATRIX_H
#define TOLERANCE 1.0e-6

#include <cassert>
#include <cmath>
#include <string>



class Matrix {
public:
    // Various constructors
    Matrix();
    Matrix(int nRows, int nColumns);
    Matrix(int nRows, int nColumns, const double* inputData);
    Matrix(int nRows, int nColumns, double** inputData);
    Matrix( const Matrix& original) ;

    // And the destructor.
    ~Matrix();

    // Getters and setters
    int GetNRows() const;
    int GetNColumns() const;
    double ** GetMatrixData() const;
    double GetValueAt(int row, int column) const;

    void SetValueAt(int row, int column, double newValue);
    void SetData(double ** newData);



    // Overload == operator.
    bool operator== (const Matrix& rhs) const;

    // Overload the assignment operator.
    Matrix& operator= (const Matrix& rhs);

    // Overload +, - and * operators (friends).
    friend Matrix operator+ (const Matrix& lhs, const Matrix& rhs);
    friend Matrix operator+ (const double& lhs, const Matrix& rhs);
    friend Matrix operator+ (const Matrix& lhs, const double& rhs);

    friend Matrix operator- (const Matrix& lhs, const Matrix& rhs);
    friend Matrix operator- (const double& lhs, const Matrix& rhs);
    friend Matrix operator- (const Matrix& lhs, const double& rhs);

    friend Matrix operator* (const Matrix& lhs, const Matrix& rhs);
    friend Matrix operator* (const double& lhs, const Matrix& rhs);
    friend Matrix operator* (const Matrix& lhs, const double& rhs);

    // Matrices Operations:
    // returns a simple matrix's transpose
    Matrix Transpose() const;
    // Return the superior triangle matrix (row echelon form ) of the matrix calling her, built with the algorithm seen in Class (Gauss Jordan)
    Matrix UpperTriangleForm() const;
    // Returns a truncated matrix of the row and column specified in the parameters
    Matrix InfraMatrix(int row, int column) const;
    // Recursively compute the determinant, Cofactor method, for the moment based on the first row, will be improved later  by choosing the less resources consuming row(or column)
    double DeterminantCofactorFR() const ;
    // Compute the determinant by obtaining the upper triangular form, our process of triangularisation include only linear combination of rows so that does not affect the determinant.
    double DeterminantTriangularForm() const;
    //Compute the Cofactor matrix ( which will help us  to compute the inverse, using another method then the gaussian seen before)
    Matrix Cofactor() const;
    // to get a matrix which is the adjugate ( classical adjoint), adjugate is just the transpose of the cofactor matrix
    Matrix Adjugate() const;
    // Compute the inverse, I made the choice to not use the gaussian elimination, to explore more numeric algebra methods, this solution use the formula : inverse = ( 1/determinant ) * adjugate
    // In terms of resource consumption, I have not yet compared my method ( Laplace expansion) , to the Gauss jordan elimination. I will do it before Christmas.
    Matrix InverseLE() const;


    // Facilities, some small functions that make assertions easier, and code more readable
    void Print();
    bool IsSquare() const;
    bool IsUpperTriangular() const;
    bool IsLowerTriangular() const;
    bool IsInversible() const;






private:
    double** matrixData;
    int nRows, nColumns;

};
#endif //DM1_MRMANSOUR_MATRIX_H
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





