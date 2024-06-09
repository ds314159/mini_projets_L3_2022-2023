//
// Created by Mehdi on 07/01/2023.
//

/*
 * SIRV model (Susceptibles-Infected-Removed-Vaccinated),
 * This model is derived from the BasicSIR, it allows to study the dynamics of the vaccination capacity on the spread of the disease
 * Vaccinated are a fraction of the population per unit of time, that move directly from Susceptibles to Removed
 * This SIRV model can be represented by the following system of differential equations:

 * dS/dt = -beta*S*I - vax

 * dI/dt = beta*S*I

 * dR/dt = gamma*I + vax
 */
#ifndef EPIDEMYMODELS_SIRV_H
#define EPIDEMYMODELS_SIRV_H
#include "BasicSIR.h"

class SIRV : public BasicSIR {
public:
    // Constructors :
    SIRV(Eigen::Vector3d &initialComposition, double infectionRate, double recoveryRate, double Vax, int maxProjection);

    // new getter :
    double getVax();

    // new setter
    void setVax(double newValue);

    // Override Euler approximation
    Eigen::MatrixXd evolutionEuler() override;



private:
    // variable representing : fraction of the population being vaccinated per unit of time
    double vax;

};


#endif //EPIDEMYMODELS_SIRV_H

