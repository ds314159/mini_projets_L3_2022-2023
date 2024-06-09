//
// Created by Mehdi on 07/01/2023.
//



#include <iostream>
#include <cassert>
#include <Eigen/Dense>
#include <cmath>
#include <iomanip>
#include "BasicSIR.h"
#include "SEIR.h"

SEIR::SEIR(Eigen::Vector4d &initialComposition, double infectionRate, double contagiousRate, double recoveryRate,
           int maxProjection) {
    this->states_t_zero = initialComposition;
    this->beta = infectionRate;
    this->alpha = contagiousRate;
    this->gamma = recoveryRate;
    this->sigma = this->beta / this->gamma ;
    this->T = maxProjection;

}

double SEIR::getAlpha() {
    return this->alpha;
}

Eigen::Vector4d SEIR::getInitialComposition() {
    return this->states_t_zero;
}

void SEIR::setAlpha(double newValue) {
    this->alpha = newValue;
}

void SEIR::setInitialComposition(Eigen::Vector4d newValues) {
    this->states_t_zero = newValues;
}

Eigen::MatrixXd SEIR::evolutionEuler() {
    // Instantiate the return Matrix
    Eigen::MatrixXd evolution(T, 4); // we change columns number to 4, SEIR contain 4 compartments
    evolution = Eigen::ArrayXXd::Zero(T,4); // advanced initialisation method to put zeros everywhere

    // Initialise evolutionEuler first row with states_t_zero values
    evolution.block<1,4>(0,0)= states_t_zero; // block operations are facilities given by Eigen library, here we inject a vector in the first row

    // declare the derivatives of each state : Susceptibles , infected and "Rétablis ( cured and immunised over T)"
    double dS, dE, dI, dR;

    // Iteration , and states percentages computing of each time step
    for(int i=1; i<T ; ++i){
        // Computing the derivatives
        dS = (-beta) * evolution(i-1, 0) * evolution(i-1, 2) ; // dS/dt = -beta*S*I
        dE = (beta * evolution(i-1, 0) * evolution(i-1, 2)) - ( alpha * evolution(i-1, 1) ); // dE/dt = beta*S*I - alpha*E
        dI = ( alpha * evolution(i-1, 1) ) - (gamma * evolution(i - 1, 2) ) ; // dI/dt = alpha*E - gamma*I
        dR = gamma * evolution(i - 1, 2) ; // dR/dt = gamma*I

        // Computing States percentages at time step i, and saving in evolutionEuler i row
        evolution(i, 0) = evolution(i-1,0) + dS;
        evolution(i, 1) = evolution(i-1,1) + dE;
        evolution(i, 2) = evolution(i-1,2) + dI;
        evolution(i, 3) = evolution(i-1,3) + dR;

        // Verifications,  to preserve our model coherence:

        if (evolution(i, 0) < 0 or evolution(i, 0)  > 1  ) {
            break;
            //evolution(i, 0) = 0;
        }

        if (evolution(i, 1) < 0 or evolution(i, 1)  > 1  ) {
            break;
            //evolution(i, 0) = 0;
        }

        if (evolution(i, 2) < 0 or evolution(i, 2)  > 1  ) {
            break;
            //evolution(i, 0) = 0;
        }

        if (evolution(i, 3) < 0 or evolution(i, 3)  > 1  ) {
            break;
            //evolution(i, 0) = 0;
        }


    }
    return evolution;

}

