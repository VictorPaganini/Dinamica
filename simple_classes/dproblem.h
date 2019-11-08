#include <iostream>
#include <string>
#include "section.h"

struct force{
// Force = a + b*sin(w*t)
    double a, b, w;    
};

class Dynamical_problem{
    public:
        Dynamical_problem();
        void setInitialDisplacements(double dx, double dy, double dr);
        void setInitialVelocities(double vx, double vy, double vr);
        void setMass(double mass);
        void setForce(std::string direction, double a, double b, double w);
        void setAlpha(double alpha);
        void setBeta(double beta);
        void setTotalTime(double time);
        void setTimeSteps(int steps);
        double getDisplacement(std::string direction);
        double getVelocity(std::string direction);
        double getAcceleration(std::string direction);
        double getMass();
        double getStiffness(std::string direction);
        double getDumping(std::string direction);
        struct force getForce(std::string direction);
        double getAlpha();
        double getBeta();
        double getTotalTime();
        double getTimeSteps();
        void integrate(std::string outputFile);


    private:
        double _dx_, _dy_, _dr_;
        double _vx_, _vy_, _vr_;
        double _ax_, _ay_, _ar_;
        double _m_;
        double _kx_, _ky_, _kr_;
        double _cx_, _cy_, _cr_;
        struct force _fx_, _fy_, _mz_;
        double _alpha_, _beta_;
        double _totalTime_;
        int _timeSteps_;
        Section _crossSection_;
        /*
            Class attributes:
            * Initial values of:
            _dx_ - horizontal displacement
            _dy_ - vertical displacement
            _dr_ - rotational displacement 
            _vx_ - velocity horizontal component
            _vy_ - velocity vertical component
            _vr_ - velocity rotational component
            _ax_ - acceleration horizontal component
            _ay_ - acceleration vertical component
            _ar_ - acceleration rotational component
            * Dynamical properties
            _m_ - mass
            _kx_ - stiffness - horizontal direction
            _ky_ - stiffness - vertical direction
            _kr_ - stiffness - rotation
            _cx_ - dumping - horizontal direction
            _cy_ - dumping - vertical direction
            _cr_ - dumping - rotation
         */

};


