#include "dproblem.h"

int main(){
    Dynamical_problem dprob;
    Section sec;
    
    
    std::cout << "Creating a dynamical problem instance " << std::endl;
    dprob.setInitialPosition(0.0,0.0,0.0);
    dprob.setInitialVelocities(0.0,0.0,0.0);
    dprob.setStiffness(1.0,1.0,1.0);
    dprob.setDumping(1.0,2.0,3.0);
    dprob.setMass(100.0);
    dprob.setForceParameters("x",1.0,1.0,0.0);
    dprob.setForceParameters("y",1.0,1.0,0.0);
    dprob.setForceParameters("r",1.0,1.0,2.0);
    dprob.setGamma(0.5);
    dprob.setBeta(0.25);
    dprob.setTotalTime(3.0);
    dprob.setTimeSteps(1000);
    dprob.resetTime();
    std::cout << dprob.getDataReport();
    dprob.nextStep();
    std::cout << dprob.getDataReport();
    
    dprob.integrate("test.csv");
    std::cout << "Done!" <<std::endl;
    
    std::cout << "Creating a dynamical problem instance with inputfile " << std::endl;
    dprob.readInputData();
    dprob.setForceParameters("x",1.0,1.0,0.0);
    dprob.setForceParameters("y",1.0,1.0,0.0);
    dprob.setForceParameters("r",1.0,1.0,2.0);
    dprob.resetTime();

    dprob.integrate("test2.csv");
    std::cout << "Done!" <<std::endl;

    return 0;
}
