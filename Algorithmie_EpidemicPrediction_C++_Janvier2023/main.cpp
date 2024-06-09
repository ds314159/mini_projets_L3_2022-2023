#include "BasicSIR.h"
#include "VitalDynamicsSIR.h"
#include "SEIR.h"
#include "SIRV.h"
#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <ostream>
#include <iomanip>





using namespace std;
using namespace Eigen;


// Helping function SaveMatrixAsCSV, to stock the different models evolution as a CSV file in the working directory , a CSV file is easily plottable with python

template <typename T> // Using template because we need to stock different size matrices
void saveMatrixAsCSV(T inputMatrix, string fileName){
    std::ofstream file(fileName);

    // checking if the output file exist , and is open
    if (!file.is_open()) {
        std::cerr << "the output file is not open or doesn't exist !" << std::endl;

    }
    // cheking if the epidemic model type is handled by our function
    if(inputMatrix.cols() != 3 && inputMatrix.cols() != 4){
        std::cerr << "Unknown columns types for the moment!" << std::endl;
    }

    // Giving a title for each column, it makes things easier to plot with panda
    if (inputMatrix.cols() == 3) {

        // writing
        file << "t";
        file << ",";
        file << "S";
        file << ",";
        file << "I";
        file << ",";
        file << "R";
        file << ",";
        file << std::endl;
    }
    if (inputMatrix.cols() == 4) {

        // writing
        file << "t"; // first column, the time step number, equivalent to row number
        file << ",";
        file << "S"; // Susceptibles
        file << ",";
        file << "E"; // Exposed
        file << ",";
        file << "I"; // Infected
        file << ",";
        file << "R"; // Recovered
        file << ",";
        file << std::endl;
    }


    for (int i = 0; i < inputMatrix.rows(); ++i) {
        file << i ;
        file << ",";
        for (int j = 0; j < inputMatrix.cols(); ++j) {
            file << inputMatrix(i, j);

            if (j < inputMatrix.cols() - 1) {
                file << ","; // Separate Columns

            }
        }
        file << std::endl; // jump to line at the end of a row

    }

    // Close the file
    file.close();


}





int main() {


    cout << "\n\n\n*******************************************************************" << endl;

    cout << "                      Basic SIR Model                              " << endl;

    cout << "*******************************************************************" << endl;
    cout << endl;
    cout << "Summary of model characteristics: "
            "\nPopulation  of Susceptibles, Infected, and Recovered. \n"
            "We deliberately choose to consider as negligible birth and death rate.\n" << endl ;


    Vector3d  initialCompositionPopulation1(0.99 , 0.01, 0.0);  // State the initial composition of the population, you can modify these values to see the impact on the evolution of the disease
    BasicSIR basicSir(initialCompositionPopulation1, 0.18, 0.09, 180); // Instanciate a BasicSIR model with the appropriate rates and Max time steps.

    cout << "basicSir, instance of BasicSIR Class:\n" << endl;
    cout << "- Population initial composition : " << initialCompositionPopulation1(0) << " Susceptibles, "
                                                  << initialCompositionPopulation1(1) << " Infected and "
                                                  << initialCompositionPopulation1(2) << " of Recovered. " << endl;

    cout << "- Infection Rate beta : " << basicSir.getBeta() << " ." << endl;
    cout << "- Recovery Rate gamma  : " << basicSir.getGamma()<< " ." << endl;
    cout << "- Duration ( maximum time steps) : " << basicSir.getT() << " .\n" << endl;
    cout << "With these initial parameters, the maximum peak of infected individuals expected during this period is: " << basicSir.computeMaxInfected() << " .\n"<< endl;
    double S = 0.92; // you can try various values of S to check accuracy of the method computeInfected( Susceptibles).
    cout << "With these initial parameters, When Susceptibles Will be  :" << S << " , Infected will be : " << basicSir.computeInfected(S) << " of the population.\n" << endl;

    Eigen::MatrixXd basicSirEvolution(basicSir.getT(), basicSir.getInitialComposition().rows()); // we Instantiate a container for the evolution Data
    basicSirEvolution = basicSir.evolutionEuler(); // we fill this container with the data computed by the Euler iteration
    saveMatrixAsCSV(basicSirEvolution, "basicSirEvolution.csv"); // we save this data as a CSV file thinks to a dedicated function (implemented above)

    cout << "Evolution of the proportions of the population is plotted in the python files, but it can also be represented by "
            "\nthe three columns of this matrix, respectively the fraction of susceptible, infected, and recovered :\n\n\n\n" << endl;
    cout << basicSirEvolution << endl; // Eigen library override the << operator to allow the direct transcription of matrix


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    cout << "\n\n\n*******************************************************************" << endl;

    cout << "                    Vital dynamics SIR Model                              " << endl;

    cout << "*******************************************************************" << endl;
    cout << endl;
    cout << "Summary of model characteristics: "
            "\nPopulation  of Susceptibles, Infected, and Recovered. \n"
            "we enrich the basic model, with the variable birth rate \n"
            "and death rate, we continue to consider that the population is stable, \n"
            "i.e. the hypothesis of a birth rate equal to the death rate.\n" << endl ;


    Vector3d  initialCompositionPopulation2(0.98 , 0.02, 0.0);  // State the initial composition of the population, you can modify these values to see the impact on the evolution of the disease
    VitalDynamicsSIR vitalDynamicsSir(initialCompositionPopulation2, 0.18, 0.12, 0.00002,  180); // Instantiate a VitalDynamicsSir model with the appropriate rates and Max time steps.

    cout << "vitalDynamicsSIR, instance of VitalDynamicsSIR Class:\n" << endl;
    cout << "- Population initial composition : " << initialCompositionPopulation2(0) << " Susceptibles, "
                                                  << initialCompositionPopulation2(1) << " Infected and "
                                                  << initialCompositionPopulation2(2) << " of Recovered. " << endl;

    cout << "- Infection Rate beta : " << vitalDynamicsSir.getBeta() << " ." << endl;
    cout << "- Recovery Rate gamma  : " << vitalDynamicsSir.getGamma() << " ." << endl;
    cout << "- Birth Rate Mu : " << vitalDynamicsSir.getMu() << " ." << endl;
    cout << "- Duration ( maximum time steps) : " << basicSir.getT() << " .\n" << endl;



    Eigen::MatrixXd vitalDynamicsSirEvolution(vitalDynamicsSir.getT(), vitalDynamicsSir.getInitialComposition().rows()); // we Instantiate a container for the evolution Data
    vitalDynamicsSirEvolution = vitalDynamicsSir.evolutionEuler(); // we fill this container with the data computed by the Euler iteration
    saveMatrixAsCSV(vitalDynamicsSirEvolution, "vitalDynamicsSirEvolution.csv"); // we save this data as a CSV file thinks to a dedicated function (implemented above)

    cout << "Evolution of the proportions of the population is plotted in the python files, but it can also be represented by "
            "\nthe three columns of this matrix, respectively the fraction of susceptible, infected, and recovered :\n\n\n\n" << endl;
    cout << vitalDynamicsSirEvolution << endl; // Eigen library override the << operator to allow the direct transcription of matrix


    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    cout << "\n\n\n*******************************************************************" << endl;

    cout << "                     SIRV Model                              " << endl;

    cout << "*******************************************************************" << endl;
    cout << endl;
    cout << "Summary of model characteristics: "
            "\nPopulation  of Susceptibles, Infected, and Removed ( immunised). \n"
            "The SIRV model here integrates a variable corresponding to a number of "
            "\nvaccinated individuals per unit of time. This number is added to the recovered individuals to form the Removed, "
            "\nthose who are no longer part of the game, due to immunity. "
            "\nThe number of vaccinated individuals per unit of time is obviously subtracted from the Susceptibles, as they can no longer become ill if vaccinated.\n" << endl;


    Vector3d  initialCompositionPopulation3(0.99 , 0.01, 0.0);  // State the initial composition of the population, you can modify these values to see the impact on the evolution of the disease
    SIRV sirVaccinated(initialCompositionPopulation3, 0.18, 0.09, 0.0002,  180); // Instantiate a SIRV model with the appropriate rates and Max time steps.

    cout << "sirVAccinated, instance of SIRV Class:\n" << endl;
    cout << "- Population initial composition : " << initialCompositionPopulation3(0) << " Susceptibles, "
                                                  << initialCompositionPopulation3(1) << " Infected and "
                                                  << initialCompositionPopulation3(2) << " of Removed. " << endl;

    cout << "- Infection Rate beta : " << sirVaccinated.getBeta() << " ." << endl;
    cout << "- Recovery Rate gamma  : " << sirVaccinated.getGamma() << " ." << endl;
    cout << "- Vaccination rate vax: " << sirVaccinated.getVax() << " ." << endl;
    cout << "- Duration ( maximum time steps) : " << sirVaccinated.getT() << " .\n" << endl;



    Eigen::MatrixXd sirVaccinatedEvolution(sirVaccinated.getT(), sirVaccinated.getInitialComposition().rows()); // we Instantiate a container for the evolution Data
    sirVaccinatedEvolution = sirVaccinated.evolutionEuler(); // we fill this container with the data computed by the Euler iteration
    saveMatrixAsCSV(sirVaccinatedEvolution, "sirVaccinatedEvolution.csv"); // we save this data as a CSV file thinks to a dedicated function (implemented above)

    cout << "Evolution of the proportions of the population is plotted in the python files, but it can also be represented by "
            "\nthe three columns of this matrix, respectively the fraction of susceptible, infected, and removedd :\n\n\n\n" << endl;
    cout << sirVaccinatedEvolution << endl; // Eigen library override the << operator to allow the direct transcription of matrix


    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    cout << "\n\n\n*******************************************************************" << endl;

    cout << "                     SEIR Model                              " << endl;

    cout << "*******************************************************************" << endl;
    cout << endl;
    cout << "Summary of model characteristics: "
            "\nPopulation  of Susceptibles, Exposed,  Infected, and Removed. \n"
            "The SEIR model adds an \"Exposed\" compartment to the basic SIR model to account for the incubation period of the disease, \n"
            "We continue to assume all the other basicSIR working hypothesis and approximations ( negligible vital dynamics, no vaccine..) \n" << endl;


    Vector4d  initialCompositionPopulation4(0.98 , 0.02, 0.0,0.0);  // State the initial composition of the population, you can modify these values to see the impact on the evolution of the disease
    SEIR seir(initialCompositionPopulation4, 0.18, 0.18, 0.09,  180); // Instantiate a SEIR model with the appropriate rates and Max time steps.

    cout << "seir, instance of SEIR Class:\n" << endl;
    cout << "- Population initial composition : " << initialCompositionPopulation4(0) << " Susceptibles, "
                                                  << initialCompositionPopulation4(1) << " Exposed, "
                                                  << initialCompositionPopulation4(2) << " Infected and "
                                                  << initialCompositionPopulation4(3) << " of Removed. " << endl;

    cout << "- Infection Rate beta : " << seir.getBeta() << " ." << endl;
    cout << "- Exposed to infected  Rate  : " << seir.getAlpha() << " ." << endl;
    cout << "- RecoveryRate gamma " << seir.getGamma() << " ." << endl;
    cout << "- Duration ( maximum time steps) : " << seir.getT() << " .\n" << endl;



    Eigen::MatrixXd seirEvolution(seir.getT(), seir.getInitialComposition().rows()); // we Instantiate a container for the evolution Data
    seirEvolution = seir.evolutionEuler(); // we fill this container with the data computed by the Euler iteration
    saveMatrixAsCSV(seirEvolution, "seirEvolution.csv"); // we save this data as a CSV file thinks to a dedicated function (implemented above)

    cout << "Evolution of the proportions of the population is plotted in the python files, but it can also be represented by "
            "\nthe four columns of this matrix, respectively the fraction of susceptible, Exposed, infected, and removed :\n\n\n\n" << endl;
    cout << seirEvolution << endl; // Eigen library override the << operator to allow the direct transcription of matrix





    cout << "*******************************************************************" << endl;

    cout << "*******************************************************************" << endl;





    return 0;
}
