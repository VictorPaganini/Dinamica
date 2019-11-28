#include "force.h"

int main(){
   
    Force f;
    f.setParameters(1.0,1.0,2.0*PI);
    double t=0.0,dt;
    int nsteps = 300;
    dt = 1.0/12.0;
    double v;
    
    std::cout << "step; time(s); force(kN)" << std::endl;
    for (int i = 0; i < nsteps; i++){
        t += dt;
        v = f.getValue(t);
        std::cout << i << ";" << t << ";" << v << std::endl;
    }

    return 0;
}

