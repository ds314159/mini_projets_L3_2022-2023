//
// Created by Mehdi on 06/01/2023.
//

#include <iostream>
#include <cassert>
#include <Eigen/Dense>
#include <cmath>
#include <iomanip>
#include "BasicSIR.h"
#include "VitalDynamicsSIR.h"


// Constructor
VitalDynamicsSIR::VitalDynamicsSIR(Eigen::Vector3d &initialComposition,
                                   double infectionRate,
                                   double recoveryRate,
                                   double birthRate,
                                   int maxProjection) : BasicSIR(initialComposition,maxProjection){


    this->beta = infectionRate;
    this->gamma = recoveryRate;
    this->µ = birthRate;
    this->sigma = infectionRate / (recoveryRate + birthRate);


}

double VitalDynamicsSIR::getBeta() {
    return this->beta;
}

double VitalDynamicsSIR::getGamma() {
    return this->gamma;
}

double VitalDynamicsSIR::getSigma() {
    return (this->beta / ( this->gamma + this->µ));
}

double VitalDynamicsSIR::getMu() {
    return µ;
}

void VitalDynamicsSIR::setGamma(double newValue) {
    this->gamma = newValue;
    this->sigma = this->beta / ( this->gamma + this->µ);
}

void VitalDynamicsSIR::setBeta(double newValue) {
    this->beta = newValue;
    this->sigma = this->beta / ( this->gamma + this->µ);
}

void VitalDynamicsSIR::setSigma(double newBeta, double newGamma) {
    this->beta = newBeta;
    this->gamma = newGamma;
    this->sigma = this->beta / ( this->gamma + this->µ);
}

void VitalDynamicsSIR::setMu(double newValue) {
    this->µ = newValue;
    this->sigma = this->beta / ( this->gamma + this->µ);

}



Eigen::MatrixXd VitalDynamicsSIR::evolutionEuler() {
    // Instantiate the return Matrix
    Eigen::MatrixXd evolution(T, 3);
    evolution = Eigen::ArrayXXd::Zero(T, 3); // advanced initialisation method to initialise at zeros all the coefficients

    // Initialise evolutionEuler first row with states_t_zero values
    evolution.block<1, 3>(0,0) = states_t_zero; // block operations are facilities given by Eigen library, here we inject a vector in the first row
    // declare the derivatives of each state : Susceptibles , infected and Removed ( (cured and immunised) or Dead, over T)"
    double dS, dI, dR;

    // Iteration , and states percentages computing of each time step
    for (int i = 1; i < T; ++i) {
        // Computing the derivatives
        dS = ((-beta) * evolution(i - 1, 0) * evolution(i - 1, 1)) +
             (µ * (1 - evolution(i - 1, 0))); // Numerical form of the derivative : dS/dt = µ - beta*S*I  - µ*S
        dI = beta * evolution(i - 1, 0) * evolution(i - 1, 1) - (gamma * evolution(i - 1, 1)) -
             (µ * evolution(i - 1, 1)); // dI/dt =  beta*S*I - gamma*I - µ*I
        dR = gamma * evolution(i - 1, 1) - (µ * evolution(i - 1, 2)); // dR/dt = gamma*I - µ*R

        // Computing States percentages at time step i, and saving in evolutionEuler i row
        evolution(i, 0) = evolution(i - 1, 0) + dS;
        evolution(i, 1) = evolution(i - 1, 1) + dI;
        evolution(i, 2) = evolution(i - 1, 2) + dR;

        // Verifications,  to preserve our model coherence:

        // Susceptibles values are between  1 and 0
        if (evolution(i, 0) < 0) {
            //break;
            evolution(i, 0) = 0;
        }

        // Infected values are between 0 and 1 ( from no disease to all infected )
        if (evolution(i, 1) < 0) {
            //break;
            evolution(i, 1) = 0;
        }


        if (evolution(i, 1) > 1) {
            //break;

            evolution(i, 1) = 1;
        }

        // R values are between 0 and 1
        if (evolution(i, 2) > 1) {
            //break;

            evolution(i, 2) = 1;
        }
    }
        return evolution;

}









