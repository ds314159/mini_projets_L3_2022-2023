//
// Created by Mehdi on 06/01/2023.
//

/*"In this model, we start from BasicSIR as Base, we derive it and we enrich its equations with  Vital dynamics:
 * A variable µ that represent birth and death rate.
 * In this model, we assume as a working hypothesis that the population is stable over the duration of the modeling (µ_birth = µ_death = µ).
 * In this  model, birth and death factors are included as µ, the dynamics of the disease are described by the following system of differential equations:
 *
 *   dS/dt = -beta*S*I + µ - µ*S
 *   dI/dt =  beta*S*I - gamma*I - µ*I
 *   dR/dt =  gamma*I - µ*R
 */

#ifndef EPIDEMYMODELS_VITALDYNAMICSSIR_H
#define EPIDEMYMODELS_VITALDYNAMICSSIR_H

#include "BasicSIR.h"
#include <Eigen/Dense>


class VitalDynamicsSIR : public BasicSIR {
    using BasicSIR::BasicSIR;
public:

    // Constructor
    VitalDynamicsSIR(Eigen::Vector3d &initialComposition, double infectionRate, double recoveryRate, double birthRate, int maxProjection);

    // Getters : Base getters for initial conditions and max projection time, for other base getters , they are overridden to avoid bugs
    double getBeta() override;
    double getGamma() override;
    double getSigma() override;
    double getMu();

    // Setters : Base getters for initial conditions and max projection time, for other base setters , they are overridden to avoid bugs

    void setGamma(double newValue) override;
    void setBeta(double newValue) override;
    void setSigma(double newBeta, double newGamma) override;
    void setMu(double newValue) ;






    // Euler Method for Vital Dynamics SIR
    Eigen::MatrixXd evolutionEuler() override ;








private:




    // Infection rate : probability of disease transmission when Susceptibles are exposed to Infected
    double beta;

    // Recovery rate (called alpha in "When zombies attack", but it's more commonly called gamma in epidemiology): probability of transition from Infected to Removed ( cured or dead)
    double gamma;

    // Intensity of the transmission : rate of change of the number of infected individuals. ( Sometimes called Ro, remember covid crisis)
    double sigma;

    // Birth rate , which is equal to death rate in our working hypothesis, called mu ( µ )
    double µ;





};


#endif //EPIDEMYMODELS_VITALDYNAMICSSIR_H

