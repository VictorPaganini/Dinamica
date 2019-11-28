#include <iostream>
#include <vector>
#include <cmath>

#ifndef PI
#define PI 3.14159265358979323846
#endif

class Force{
    /*
    Force value for a given time.
    Parameters for computing the force value: a, b and w
    */
    public:
        void setParameters(double a, double b, double w);
        double getParameter(std::string parameter);
        double getValue(double time);
        void printInfo();
    private:
        double _a_;
        double _b_;
        double _w_;
};
