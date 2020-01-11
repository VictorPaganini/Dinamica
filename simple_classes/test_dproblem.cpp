#include "dproblem.h"

int main(){
    Dynamical_problem dprob;
    Section sec;
    sec.setCenter(0.0,0.0);

    sec.addBoundaryPoint(0,-6.0,-1.0);
    sec.addBoundaryPoint(1,6.0,-1.0);
    sec.addBoundaryPoint(2,9.0,1.0);
    sec.addBoundaryPoint(3,-9.0,1.0);
  
    sec.addBoundaryLine(0,0,1);
    sec.addBoundaryLine(1,1,2);
    sec.addBoundaryLine(2,2,3);
    sec.addBoundaryLine(3,3,0);

    std::cout << "Creating a dynamical problem instance " << std::endl;
    dprob.setInitialPosition(0.0,0.0,0.0);
    dprob.setInitialVelocities(0.0,0.0,0.0);
    dprob.setStiffness(5.1,5.2,5.3);
    dprob.setDumping(0.5,0.6,2);
    dprob.setMass(10.0);
    dprob.setForceParameters("x",0.0,30.0,4.0);
    dprob.setForceParameters("y",0.0,20.0,5.0);
    dprob.setForceParameters("r",0.0,10.0,2.0);
    dprob.setGamma(0.5);
    dprob.setBeta(0.25);
    dprob.setTotalTime(5.0);
    dprob.setTimeSteps(100);
    dprob.resetTime();
    //std::cout << dprob.getDataReport();
    dprob.integrate("test.csv",sec);




    return 0;
}
