#include <iostream>
#include "Matrix.h"
#include "LinearSystem.h"

using namespace std;

// Some little functions just to help us make tests easier
// Output preferences:
void SetOutputPreferences(){
    cout.setf(std::ios::scientific);
    cout.setf(std::ios::showpos);
    cout.precision(2);
}
// Allocate memory for a 2 dimensions table
double ** allocateMemory(int rows, int columns) {
    auto **tab = new double *[rows];
    for (int i = 0; i < rows; i++) {
        tab[i] = new double[columns];
    }
    return tab;
}

// randomly fill a 2 dimensions table
void randFill(double ** tab, int rows, int columns){
    srand(123);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            tab[i][j] = rand() % 5 +10 ;


}

// Freed 2d table memory
void freedMemory(double ** tab, int rows){
    for (int i=0; i<rows; i++){
        delete[] tab[i];
    }
    delete[] tab;

}
int main() {
    SetOutputPreferences(); //You can erase this instruction if you don't want scientific presentation


    // TESTS
    // Define some data tables to use it later
    double ** tab1 = allocateMemory(3,4);
    randFill(tab1, 3, 4);

    double ** tab2 = allocateMemory(3,4);
    randFill(tab2, 3, 4);

    auto * tab3 = new double[12];
    tab3[0]=1.0;tab3[1]=2.0;tab3[2]=3.0 ;tab3[3]=4.0;
    tab3[4]=1.0;tab3[5]=2.0;tab3[6]=3.0 ;tab3[7]=4.0;
    tab3[8]=1.0;tab3[9]=2.0;tab3[10]=3.0;tab3[11]=4.0;

    // Test Constructors
    Matrix m1;

    Matrix m2(3,4); // a zeros filled matrix with the specified rows and columns
    cout << "this is Matrix m2" << endl;
    m2.Print();

    Matrix m3(3,4, tab3); // with 1 dimension data table
    cout << "this is Matrix m3" << endl;
    m3.Print();

    Matrix m4(3,4, tab1); // with 2 dimensions data table
    cout << "this is Matrix m4" << endl;
    m4.Print();

    Matrix m5(3,4, tab2); // another instance with 2 dim data table argument
    cout << "this is Matrix m5" << endl;
    m5.Print();

    Matrix m6(m3); // duplicate m3
    cout << "this is Matrix m6, she's an m3 copy" << endl;
    m6.Print();

    Matrix m7(4,3, tab3); // just to make a multiplication test later
    cout << "this is Matrix m7, built to test a multiplication operation" << endl;
    m7.Print();

   // Test overloaded operators
   // Assignment
   cout << "\n\n\nLet's Test our overloaded operators\n" << endl;
   cout << "We assign m1 ( built by the default constructor) to m6, m1 = m6" << endl;
   m1 = m6;
   cout << "this is Matrix m1 after assignment" << endl;
   m1.Print();

   // Operator +
    cout << "We test the three addition possibilities" << endl;
    cout << "this is m1 = m1 + m6" << endl;
    m1 = m1 + m6;
    m1.Print();

    cout << "this is m1 = m6 + scalar" << endl;
    m1 = m6 + 3.00;
    m1.Print();

    cout << "this is m1 = scalar + m6" << endl;
    m1 = 3.00 + m6;
    m1.Print();

    // Operator -
    cout << "We test the three subtraction possibilities" << endl;
    cout << "this is m1 = m1 - m6" << endl;
    m1 = m1 - m6;
    m1.Print();

    cout << "this is m1 = m6 - scalar" << endl;
    m1 = m6 - 3.00;
    m1.Print();

    cout << "this is m1 = scalar - m6" << endl;
    m1 = 3.00 - m6;
    m1.Print();


    // Operator 3
    cout << "We test the three multiplication possibilities" << endl;
    cout << "this is m1 = m7 * m6" << endl;
    m1 = m7 * m6;
    m1.Print();

    cout << "this is m1 = m6 * scalar" << endl;
    m1 = m6 * 3.00;
    m1.Print();

    cout << "this is m1 = scalar * m6" << endl;
    m1 = 3.00 * m6;
    m1.Print();

    // Equals ==
    cout << "Is it true that m6==m3 (original and copy) ?" << endl;
    cout << (m6==m3)<< endl;
    cout << "Is it true that m1==m6 ?" << endl;
    cout << (m1==m6)<< endl;


    // Test getters and setters
    cout << "\n\n\nLet's Test our getters and setters\n" << endl;
    cout << "m1 has " << m1.GetNRows() << " rows, and " << m1.GetNColumns() << " columns." << endl;
    cout << "the [1][2] element is " << m1.GetValueAt(1,2) << endl;
    m1.SetValueAt(1,2,0.0);
    cout << "after using the element setter, the value is now: " << m1.GetValueAt(1,2)<<"\n" << endl;
    cout << "Lets set m1 data to m6 data, this is m1 and m6, before setter use"<< endl;
    m1.Print();
    m6.Print();
    m1.SetData(m6.GetMatrixData());
    cout << "and this m1 after change" << endl;
    m1.Print();


    // Test facilities functions
    Matrix m20 = m6*m7; // just to get a square matrix
    cout << "\n\n\nLet's Test facilities Functions\n" << endl;
    cout << "This is m6 and m20 , let s test our functions on it \n" << endl;
    m6.Print();
    m20.Print();
    cout << "Is m6 a square Matrix : " << m6.IsSquare() << endl;
    cout << "Is m6 an Upper triangular Matrix : " << m6.IsUpperTriangular() << endl;
    cout << "Is m6 an Lower triangular Matrix : " << m6.IsLowerTriangular() << endl;
    cout << "Is m20 a square Matrix : " << m20.IsSquare() << endl;
    cout << "Is m20 an Upper triangular Matrix : " << m20.IsUpperTriangular() << endl;
    cout << "Is m20 an Lower triangular Matrix : " << m20.IsLowerTriangular() << endl;
    cout << "Is m20 an inversible Matrix : " << m20.IsInversible() << endl;


    // Test usual operations and algebra calculation
    // Test Transpose()
    cout << "\n\n\nLet's Test Transpose() Function\n" << endl;
    cout << "this matrix m6  :" << endl;
    m6.Print();
    cout << "and this is the transpose :" << endl;
    m6.Transpose().Print();

    // Test UpperTriangleForm()
    cout << "\n\n\nLet's Test UpperTriangleForm() Function\n" << endl;
    auto * tab4 = new double[9];
    tab4[0]=1.0;tab4[1]=2.0;tab4[2]=3.0 ;
    tab4[3]=0.0;tab4[4]=1.0;tab4[5]= -2.0 ;
    tab4[6]=3.0;tab4[7]=0.0;tab4[8]=0.0;
    Matrix m8(3,3, tab4);
    cout << "this is matrix m8 before calling the function :" << endl;
    m8.Print();
    cout << "this is matrix m8 after calling the function :" << endl;
    m8.UpperTriangleForm().Print();

    // Test SubMatrix, truncate a matrix of one row and one column specified by parameters
    cout << "\n\n\nLet's Test InfraMatrix() Function\n" << endl;
    cout << "this is the mother matrix m8 before calling the function :" << endl;
    m8.Print();
    cout << "and this is the daughter truncated of the first row and first column :" << endl;
    m8.InfraMatrix(0,0).Print();
    cout << "and this is the daughter truncated of the first row and the second column :" << endl;
    m8.InfraMatrix(0,1).Print();
    cout << "and this is the daughter truncated of the last row and first last :" << endl;
    m8.InfraMatrix(2,2).Print();

    // Test of Determinant Computing

    cout << "\n\n\nLet's Test Determinant computing\n" << endl;
    cout << "this is matrix m8 again" << endl;
    m8.Print();
    cout << "using the recursive method , the m8 determinant is equal to : ";
    cout << m8.DeterminantCofactorFR() << endl;
    // Test the Gauss jordan elimination to obtain a triangular form, and calculate the product of the elements in the main diagonal
    cout << "using the triangularisation method , the m8 determinant is equal to : ";
    cout << m8.DeterminantTriangularForm() << endl;

    // Test Cofactor method, the suffix Fr mean that it is based on the First Row
    // we create these 3 matrices for the rest of the tests
    cout << "\n\n\nLet's Test Cofactor and adjugate computing\n" << endl;

    auto * tab5 = new double[9];
    tab5[0]=1.0;tab5[1]=1.0;tab5[2]=1.0 ;
    tab5[3]=0.0;tab5[4]=1.0;tab5[5]=1.0 ;
    tab5[6]=0.0;tab5[7]=0.0;tab5[8]=1.0;

    auto * tab6 = new double[3];
    tab6[0]=3.0;tab6[1]=2.0;tab6[2]=1.0 ;

    auto * tab7 = new double[9];
    tab7[0]=1.0;tab7[1]=0.0;tab7[2]=0.0 ;
    tab7[3]=1.0;tab7[4]=1.0;tab7[5]=0.0 ;
    tab7[6]=1.0;tab7[7]=1.0;tab7[8]=1.0;

    Matrix A(3,3,tab5);
    Matrix B(3,1,tab6);
    Matrix C(3,3,tab7);

    cout << "this is matrix A :" << endl;
    A.Print();
    cout << "this is matrix B :" << endl;
    B.Print();
    cout << "this is matrix C :" << endl;
    C.Print();


    // Test of cofactor and adjugate matrix computing:
    cout << "Cofactor matrix of A is :" << endl;
    A.Cofactor().Print();
    cout << "Adjugate matrix of A is :" << endl;
    A.Adjugate().Print();
    cout << "Cofactor matrix of C is :" << endl;
    C.Cofactor().Print();
    cout << "Adjugate matrix of C is :" << endl;
    C.Adjugate().Print();

    // Test of Inverse Computing function , using Laplace expansion properties
    cout << "Inverse matrix of A is :" << endl;
    A.InverseLE().Print();
    cout << "Inverse matrix of C is :" << endl;
    C.InverseLE().Print();



    /*
     In the following, I will test a linear system resolution using our LinearSystem Class
     I made the deliberate choice not to create a vector class, because a very good vector
     class already exists, and a vector is just a special case of a matrix. So, as you will
     have noticed, my linear system takes two matrices as arguments, the necessary assertions
     are made at the time of construction to be sure to have the right format, answering the problem: AX = B.


     Let's Construct  an instance of LinearSystem, Using the matrix A and the matrix B ,
     recently constructed, and answering the problem of finding the vector X such that A*X = B

     */
    cout << "\n\n\nLet's Test a linear system resolution\n" << endl;

    LinearSystem system1(A,B);
    cout << "a LinearSystem instance called system1 have been created using Matrix A and Vector B as arguments, \nLet's discover private members :\n" << endl;
    cout << "system1 size is : " << system1.GetSize() << endl;
    cout << "\nsystem1 represent the problem A*X = B, where A is the Matrix : "  << endl;
    system1.GetA().Print();
    cout << "And B is the Vector : " << endl;
    system1.GetB().Print();
    cout <<"\nthe role of this instance is to find the vector X allowing to solve A*X = B, \nit has a method which allows this resolution which is called solution(), \nlet's test this method\n" << endl;
    cout << "in system 1, Vector X, Solution to A*X=B is :\n" << endl;
    system1.Solution().Print();


    cout << "\nLet's test another system : \n" << endl;
    LinearSystem system2(C, B);
    cout << "a LinearSystem instance called system2 have been created using Matrix C and Vector B as arguments \nLet's discover it's private members :\n" << endl;
    cout << "\nsystem2 represent the problem A*X = B, where A is the Matrix : "  << endl;
    system2.GetA().Print();
    cout << "And B is the Vector : " << endl;
    system2.GetB().Print();
    cout << "In system2, Vector X, Solution to A*X=B is :\n" << endl;
    system2.Solution().Print();

    /*
     *These classes will be subject to enrichment or modification to optimise performance.
     * By progressing in matrix algebra, I think it will be easier to drastically
     * reduce the number of operations to calculate the determinant or the inverse for example.
     * I m optimistic for the second semester
     */




    freedMemory(tab1, 3);
    freedMemory(tab2, 3);
    delete[] tab3;
    delete[] tab4;
    delete[] tab5;
    delete[] tab6;
    delete[] tab7;
    return 0;
}







