//
// Created by Mehdi on 07/01/2023.
//

/*
 * The SEIR (Susceptible-Exposed-Infectious-Recovered) model is a modification of the Basic SIR (Susceptible-Infectious-Recovered) model
 * The SEIR model adds an "Exposed" compartment to the SIR model to account for the incubation period of the disease,
 * during which individuals are infected but not yet infectious themselves.
 * We continue to assume all the previous (basicSIR) working hypothesis and approximations ( negligible vital dynamics, no vaccine..)
 * So, in our SEIR Model, we have :
 * - Susceptible: individuals who are susceptible to the disease but have not yet been infected.
 * - Exposed: individuals who have been infected but are not yet infectious.
 * - Infectious: individuals who are infectious and can spread the disease to susceptible individuals.
 * - Recovered: individuals who have recovered from the disease and are immune to it.
 * This SEIR model can be represented by the following system of differential equations:

 * dS/dt = -beta*S*I

 * dE/dt = beta*S*I - alpha*E

 * dI/dt = alpha*E - gamma*I

 * dR/dt = gamma*I

 * where S, E, I, and R are the number of individuals in the Susceptible, Exposed, Infectious, and Recovered compartments, respectively, beta is the transmission rate, alpha is the rate at which exposed individuals become infectious, and gamma is the recovery rate.

 * The SEIR model is more complex than the SIR model, but it can provide a more accurate description of the spread of infectious diseases, particularly when the incubation period is significant.
 */
#ifndef EPIDEMYMODELS_SEIR_H
#define EPIDEMYMODELS_SEIR_H

#include <Eigen/Dense>
#include "BasicSIR.h"


class SEIR : public BasicSIR {
public:
    // Constructors
    SEIR(Eigen::Vector4d &initialComposition, double infectionRate, double contagiousRate, double recoveryRate, int maxProjection);

    // Getters, we keep BasicSIR beta gamma and T getters , and we define getters for initial conditions and alpha


    double getAlpha();
    Eigen::Vector4d getInitialComposition();

    // Setters
    void setInitialComposition(Eigen::Vector4d newValues);
    void setAlpha(double newValue);

    // overriding Euler method for approximating disease spread, the signature is not changed because we use the same return type : a dynamic container Eigen::VectorXd
    Eigen::MatrixXd evolutionEuler() ;






private:

    // For greater readability, I transcribe here the Base class variables as well, it was possible not to do so with inheritance, but the readability would have been lower;
    // Vector describing the composition of the population at time t zero at the beginning of the modelling, expressed as a Fraction of the total population ( sum of all components equal to 1)
    // Notice that we pass to a 4 initial compartments, so we change to a four rows vector as a container
    Eigen::Vector4d states_t_zero;

    // Moving from S to E  rate : probability of disease transmission when Susceptibles are exposed to Infected
    //double beta;

    // Moving from E to I rate : probability of becoming contagious after being Exposed
    double alpha;

    // Recovery rate : probability of transition from Infected to Recovered
    //double gamma;

    // Intensity of the transmission : rate of change of the number of infected individuals. ( Sometimes called Ro, remember covid crisis)
    //double sigma;


    // maximum duration over which the model is projected.
    //int T ;

};


#endif //EPIDEMYMODELS_SEIR_H

