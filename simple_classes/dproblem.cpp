#include "dproblem.h"

Dynamical_problem::Dynamical_problem(){}

void Dynamical_problem::setInitialDisplacements(double dx, double dy, double dr){
    _dx_ = dx;
    _dy_ = dy;
    _dr_ = dr;
}

void Dynamical_problem::setInitialVelocities(double vx, double vy, double vr){
    _vx_ = vx;
    _vy_ = vy;
    _vr_ = vr;
}

void Dynamical_problem::setForce(std::string direction, double a, double b, double w){
    if (direction == "x"){
        _fx_.a=a;
        _fx_.b=b;
        _fx_.w=w;
    }
    else if (direction == "y"){
        _fy_.a=a;
        _fy_.b=b;
        _fy_.w=w;
    }
    else if (direction == "r"){
        _mz_.a=a;
        _mz_.b=b;
        _mz_.w=w;
    }
}

struct force Dynamical_problem::getForce(std:: string direction){
    if (direction == "x"){
        return _fx_;
    }
    else if (direction == "y"){
        return _fy_;
    }
    else if (direction == "r"){
        return _mz_;
    }



}


void Dynamical_problem::setMass(double mass){
    _m_ = mass;
}

void Dynamical_problem::setAlpha(double alpha){
    _alpha_ = alpha;    
}

void Dynamical_problem::setBeta(double beta){
    _beta_ = beta;
}

void Dynamical_problem::setTotalTime(double time){
    _totalTime_ = time;
}

void Dynamical_problem::setTimeSteps(int steps){
    _timeSteps_ = steps;
}


