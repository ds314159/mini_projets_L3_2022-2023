//
// Created by Mehdi on 30/12/2022.
//
#include <iostream>
#include <cassert>
#include <Eigen/Dense>
#include <cmath>
#include <iomanip>
#include "BasicSIR.h"

using namespace std;


// Helping function to compute natural logarithm using Taylor series, I did it just to compare with the <cmath> log function precision ( it is almost the same finally)
double naturalLog(double input){
        double result = 0;
        for (int i = 300; i >= 1; i--) {
            double Taylor_i = pow(-1, i + 1) * pow(input - 1, i) / i;
            result += Taylor_i;
        }
        return result;


}


BasicSIR::BasicSIR(Eigen::Vector3d &initialComposition, double infectionRate, double recoveryRate, int maxProjection) {
        // Sum of all states fractions must be equal to 1
        assert( initialComposition.sum() == 1);// function sum(), offered by Eigen, compute the sum of all coefficients in a Matrix
        states_t_zero = initialComposition;
        beta = infectionRate;
        gamma = recoveryRate;
        sigma = beta / gamma;
        T = maxProjection;

}

BasicSIR::BasicSIR(Eigen::Vector3d &initialComposition, int maxProjection) {
    this->states_t_zero = initialComposition;
    this->T = maxProjection;

}

Eigen::Vector3d BasicSIR::getInitialComposition() {
    return states_t_zero;
}

double BasicSIR::getBeta() {
    return beta;
}

double BasicSIR::getGamma()  {
    return gamma;
}

double BasicSIR::getSigma() {
    return sigma;
}

int BasicSIR::getT() {
    return T;
}

void BasicSIR::setInitialComposition(Eigen::Vector3d newValues) {
    states_t_zero = newValues;

}

void BasicSIR::setGamma(double newValue) {
    gamma = newValue;
    // update sigma value
    sigma = beta / gamma ;
}

void BasicSIR::setBeta(double newValue) {
    beta = newValue;
    // update sigma value
    sigma = beta / gamma ;
}

void BasicSIR::setSigma(double newBeta, double newGamma) {
    setBeta(newBeta);
    setGamma(newGamma);

}

void BasicSIR::setT(int newValue){
    T = newValue;
}

Eigen::MatrixXd BasicSIR::evolutionEuler() {
    // Instantiate the return Matrix
    Eigen::MatrixXd evolution(T, 3);
    evolution = Eigen::ArrayXXd::Zero(T,3); // advanced initialisation method to put zeros everywhere

    // Initialise evolutionEuler first row with states_t_zero values
    evolution.block<1,3>(0,0)= states_t_zero; // block operations are facilities given by Eigen library, here we inject a vector in the first row

    // declare the derivatives of each state : Susceptibles , infected and "Rétablis ( cured and immunised over T)"
    double dS, dI, dR;

    // Iteration , and states percentages computing of each time step
    for(int i=1; i<T ; ++i){
        // Computing the derivatives
        dS = (-beta) * evolution(i-1, 0) * evolution(i-1, 1);
        dI = beta * evolution(i-1, 0) * evolution(i-1, 1) - (gamma * evolution(i - 1, 1) ) ;
        dR = gamma * evolution(i - 1, 1) ;

        // Computing States percentages at time step i, and saving in evolutionEuler i row
        evolution(i, 0) = evolution(i-1,0) + dS;
        evolution(i, 1) = evolution(i-1,1) + dI;
        evolution(i, 2) = evolution(i-1,2) + dR;

        // Verifications,  to preserve our model coherence:

        // Susceptibles values are a strictly decreasing function in this model, and it must not be lower than zero, so we only check the lower bound at every iteration
        if (evolution(i, 0) < 0) {
            break;
            //evolution(i, 0) = 0;
        }

        // Infected values are between 0 and 1 ( from no disease to all infected )
        if (evolution(i, 1) < 0) {
            break;}
            // evolution(i,1) = 0;}

        if (evolution(i, 1) > 1) {
            break;}
            // evolution(i,1) = 1;}

        // R values are a strictly increasing function in this model, and it must be lower than 1, so we only check the upper bound
        if (evolution(i, 2) > 1) {
            break;}
            // evolution(i,2) = 1;}





                }
                return evolution;
            }
double BasicSIR::computeInfected(double S) {
    /* Dynamic of the disease follow these derivatives : dS/dt = -beta*S*I
     *                                                   dI/dt =  beta*S*I - gamma*I
     *                                                   dR/dt = gamma * I
     * according to the first and second derivatives : dI/dS =   (dI/dt)/(dS/dt) = -1 + ( gamma / (beta * S) = -1 + ( 1/ sigma * S)
     * We can integrate this derivative to find I in terms of S, and this integral is: I = I_zero + S_zero -S + ( ln(S/S_zero)/sigma)
     * In our basic model I_zero + S_zero = 1 ( initial composition that represent all the population ), So our Formula is :I = 1 -S + ( ln(S/S_zero)/sigma)
    */
    double infectedAtS;
    infectedAtS = 1 - S + (naturalLog(S / states_t_zero[0]) / sigma); //

    return (infectedAtS > 0) ? infectedAtS : 0; // ternary condition ton ensure that "I" can't be lower than zero
}

double BasicSIR::computeMaxInfected() {
    /* Computing I in terms of S gave us this formula : I(S) = 1 -  S + ( ln(S/S_zero) / sigma )
     * this equation has maximum when it's derivative :  dI/dS = -1 + 1/(sigma * S) = 0
     * The solution is S = 1/sigma
     * => Computing the max infected ratio is computing I(1/sigma)
     */

    return computeInfected(1 / sigma);
}









