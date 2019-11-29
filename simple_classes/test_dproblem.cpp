#include "dproblem.h"

int main(){
    Dynamical_problem dprob;
    std::cout << "Created a dynamical problem instance " << std::endl;
    dprob.setInitialPosition(0.0,0.0,0.0);
    dprob.setInitialVelocities(0.0,0.0,0.0);
    dprob.setStiffness(1.0e3,1.0e3,1.0e6);
    dprob.setDumping(1.0,2.0,3.0);
    dprob.setMass(100.0);
    dprob.setForceParameters("x",1.0,1.0,2.0*PI);
    dprob.setForceParameters("y",1.0,1.0,2.0*PI);
    dprob.setForceParameters("r",1.0,1.0,1.0*PI);
    dprob.setGamma(0.5);
    dprob.setBeta(0.25);
    dprob.setTotalTime(3.0);
    dprob.setTimeSteps(1000);
    dprob.resetTime();
    //std::cout << dprob.getDataReport();
    //dprob.nextStep();
    //std::cout << dprob.getDataReport();
    
    dprob.integrate("test.csv");


    return 0;
}
