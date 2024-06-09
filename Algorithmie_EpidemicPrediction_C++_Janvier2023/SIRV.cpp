//
// Created by Mehdi on 07/01/2023.
//
#include "BasicSIR.h"
#include "SIRV.h"

SIRV::SIRV(Eigen::Vector3d &initialComposition, double infectionRate, double recoveryRate, double fractionVaccinated,
           int maxProjection) : BasicSIR(initialComposition, infectionRate, recoveryRate, maxProjection), vax(fractionVaccinated) {

}

double SIRV::getVax() {
    return this->vax;
}

void SIRV::setVax(double newValue) {
    this->vax = newValue;
}

Eigen::MatrixXd SIRV::evolutionEuler() {
    Eigen::MatrixXd evolution(T, 3);
    evolution = Eigen::ArrayXXd::Zero(T,3); // advanced initialisation method to put zeros everywhere

    // Initialise evolutionEuler first row with states_t_zero values
    evolution.block<1,3>(0,0)= states_t_zero; // block operations are facilities given by Eigen library, here we inject a vector in the first row

    // declare the derivatives of each state : Susceptibles , infected and "Rétablis ( cured and immunised over T)"
    double dS, dI, dR;

    // Iteration , and states percentages computing of each time step
    for(int i=1; i<T ; ++i){
        // Computing the derivatives
        dS = ((-beta) * evolution(i-1, 0) * evolution(i-1, 1)) - vax ;
        dI = beta * evolution(i-1, 0) * evolution(i-1, 1) - (gamma * evolution(i - 1, 1) ) ;
        dR = (gamma * evolution(i - 1, 1)) + vax ;

        // Computing States percentages at time step i, and saving in evolutionEuler i row
        evolution(i, 0) = evolution(i-1,0) + dS;
        evolution(i, 1) = evolution(i-1,1) + dI;
        evolution(i, 2) = evolution(i-1,2) + dR;

        // Verifications,  to preserve our model coherence: ( all fractions must be between 0 and 1)

        if (evolution(i, 0) < 0 or evolution(i, 0)  > 1  ) {
            break;

        }

        if (evolution(i, 1) < 0 or evolution(i, 1)  > 1  ) {
            break;

        }



        if (evolution(i, 2) < 0 or evolution(i, 2)  > 1  ) {
            break;

        }





    }

    return evolution;
}

