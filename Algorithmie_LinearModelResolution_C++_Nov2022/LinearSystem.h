//
// Created by Mehdi on 19/11/2022.
//

#ifndef LINEARSYSTEM_H
#define LINEARSYSTEM_H

#include "Matrix.h"


class LinearSystem {
public:
    //constructors
    LinearSystem( Matrix& A,  Matrix& B); // Matrix B is a vector, il will be asserted in the implementation
    LinearSystem( LinearSystem& original);

    //Destructor
    ~LinearSystem();

    //Getters and setters
    Matrix GetA();
    Matrix GetB();
    int GetSize();
    void SetA(Matrix& value);
    void SetB(Matrix& value);



    //Do the job, find solution
    Matrix  Solution(); // will return a one column matrix ( vector), representing the X of A*X=B

private:
    Matrix A;
    Matrix B;
    int nUnknowns;

};


#endif //DM1_MRMANSOUR_LINEARSYSTEM_H

