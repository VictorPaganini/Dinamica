#include "force.h"

void Force::setParameters(double a, double b, double w){
    _a_ = a;
    _b_ = b;
    _w_ = w;
}

double Force::getParameter(std::string parameter){ 
    double value;
    if (parameter == "a")
        value = _a_;
    else if (parameter == "b")
        value = _b_;
    else if (parameter == "w")
        value = _w_;
    else
        value = 0.0;
    return value;
}

double Force::getValue(double time){
    return _a_ + _b_ * sin(_w_* time);    
}

void Force::printInfo(){
    std::cout << "Not implemented yet!" << std::endl;
}
