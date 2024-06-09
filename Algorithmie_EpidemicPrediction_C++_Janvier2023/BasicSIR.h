// Created by Mehdi on 30/12/2022.

/*
 * This  is a simple mathematical model used to describe the spread of an infectious disease in a population.
 * In  this model, the population is divided into three compartments: susceptible (S), infected (I), and recovered (R).
 * The basic assumption of this SIR model is that individuals in the susceptible compartment are at risk of becoming infected,
 * while individuals in the infected compartment are infectious and can transmit the disease to susceptible individuals.
 * Individuals in the Recovered compartment are no longer infectious and are  immunised ( can't move to I or S during the study).
 * In this SIR model, birth and death factors are not included, the dynamics of the disease are described by the following system of differential equations:
 *
 *   dS/dt = -beta*S*I
 *   dI/dt =  beta*S*I - gamma*I
 *   dR/dt =  gamma*I
 *
 * Where S, I, and R are respectively the number of susceptible, infected, and recovered individuals,
 * t is time, so dt is a step of time, in this basic model it can be a day for example
 * beta is the transmission rate of the disease (i.e., the probability that a susceptible individual will become infected per time unit),
 * and gamma is the recovery rate of the disease (i.e., the probability that an infected individual will recover or die per time unit).
 */

#ifndef EPIDEMYMODELS_BASICSIR_H
#define EPIDEMYMODELS_BASICSIR_H

#include <Eigen/Dense>



class BasicSIR {
public:
    // Constructors
    // Default
    BasicSIR() = default;
    // partial initialiser
    BasicSIR(Eigen::Vector3d &initialComposition, int maxProjection);
    // full constructor
    BasicSIR(Eigen::Vector3d &initialComposition, double infectionRate, double recoveryRate, int maxProjection);

    // Getters and setters
    Eigen::Vector3d getInitialComposition();
    virtual double getBeta();
    virtual double getGamma();
    virtual double getSigma();
    virtual int getT();

    virtual void setInitialComposition(Eigen::Vector3d newValues);
    virtual void setGamma(double newValue);
    virtual void setBeta(double newValue);
    virtual void setSigma(double newBeta, double newGamma);
    virtual void setT(int newValue);
    // a basic and ancestral way to compute population states evolutionEuler, during T, numerical recipe called Euler method
    // this method return a matrix where  rows specify the population composition from t_zero to t_T  , there are T rows ( T time steps, days for exemple)
    virtual Eigen::MatrixXd evolutionEuler();

    // Computing I ratio from S ratio ( initial conditions allow the integration of dI/dS, will be explained in the implementation)
    virtual double computeInfected(double S);

    // Computing the maximum ratio of simultaneous infected people, based on the initial conditions and the value of sigma.
    // Sigma, in this case, is known in advance because the epidemic has already occurred before or elsewhere.
    // This calculation is really useful because it allows us, for example, to predict the strain on  hospital infrastructures,
    // or  the stocks of drugs to be prepared .
    // ( During the COVID-19 crisis, the former Minister of Health, Agnes Buzin, was summoned before Parliament,
    // and was criticized for underestimating this value).
    // Explanations on the formula in the implementation.
    double computeMaxInfected();


protected:
    //Vector describing the composition of the population at time t zero at the beginning of the modelling, expressed as a Fraction of the total population ( sum of all components equal to 1)
    Eigen::Vector3d states_t_zero;
    // Infection rate : probability of disease transmission when Susceptibles are exposed to Infected
    double beta;
    // Recovery rate (called alpha in "When zombies attack", but it's more commonly called gamma in epidemiology): probability of transition from Infected to "Rétablis"
    double gamma;
    // Intensity of the transmission : rate of change of the number of infected individuals with respect to the number of susceptible individuals. ( Sometimes called Ro, remember covid crisis)
    double sigma;
    // maximum duration over which the model is projected, Let's choose days as unit for the basic SIR model
    int T ;





};


#endif //EPIDEMYMODELS_BASICSIR_H

