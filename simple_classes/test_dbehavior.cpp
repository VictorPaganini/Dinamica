#include <iostream>

#include "dproblem.h"


int main(){
    Dynamical_problem dbh;
    dbh.setInitialDisplacements(0.0,0.0,0.0);
    dbh.setInitialVelocities(0.0,0.0,0.0);
    dbh.setForce("y",1,2,3);
    struct force fy = dbh.getForce("y");
    std::cout << fy.a << " " << fy.b << " " << fy.w << std::endl;
    return 0;


}
