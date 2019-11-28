#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "section.h"
#include "force.h"

class Dynamical_problem{
    public:
        Dynamical_problem();
        void setInitialPosition(double x, double y, double r);
        void setInitialVelocities(double vx, double vy, double vr);
        void setStiffness(double kx, double ky, double kr);
        void setDumping(double cx, double cy, double cr);
        void setMass(double mass);
        void setForceParameters(std::string direction, double a, double b, double w);
        void setAlpha(double gamma);
        void setBeta(double beta);
        void setTotalTime(double time);
        void setTimeSteps(int steps);
        void resetTime();
        void computeInitialAcceleration();
        std::string getDataReport();
        void nextStep();
        void integrate(std::string csvOutputFile);
//        void setIntialAcelleration(); is this really necessary?
/*      double ForceValue(std::string direction; double time)
        double setStiffness(std::string direction);
        double setDumping(std::string direction);
        double getDisplacement(std::string direction);
        double getVelocity(std::string direction);
        double getAcceleration(std::string direction);
        double getMass();
        Force getForce(std::string direction);
        double getAlpha();
        double getBeta();
        double getTotalTime(int steps);
        double getTimeSteps();
        struct point Dynamical_problem::getNewCenterCoordinates(){
        void integrate(std::string outputFile);
*/
    private:
        // Initial position, velocity and acceleration 
        double _x0_, _y0_, _r0_;
        double _vx0_, _vy0_, _vr0_;
        double _ax0_, _ay0_, _ar0_;
        // Current position, velocity and acceleration
        double _x_, _y_, _r_;
        double _vx_, _vy_, _vr_;
        double _ax_, _ay_, _ar_;
        // Dynamic properties
        double _m_;
        double _kx_, _ky_, _kr_;
        double _cx_, _cy_, _cr_;
        // forces
        Force _fx_, _fy_, _mr_; 
        // Time integration parameters
        double _gamma_, _beta_;
        double _totalTime_; // Total time (s)
        int _timeSteps_; // Number of time steps
        int _currentTimeStep_; // (or cts)->  0 <= cts <= _timeSteps_
        /*
            Class attributes:
            * Initial values of:
            _x0_ - initial horizontal coordinate
            _y0_ - initial vertical displacement
            _r0_ - initial rotation
            _v0x_ - initial velocity horizontal component
            _v0y_ - initial velocity vertical component
            _v0r_ - initial velocity rotational component
            _a0x_ - initial acceleration horizontal component
            _a0y_ - initial acceleration vertical component
            _a0r_ - initial acceleration rotational component
            _x_ - horizontal coordinate (current)
            _y_ - vertical coordinate (current)
            _r_ - rotation (current)
            _vx_ - velocity horizontal component (current)
            _vy_ - velocity vertical component (current)
            _vr_ - velocity rotational component (current)
            _ax_ - acceleration horizontal component (current)
            _ay_ - acceleration vertical component (current)
            _ar_ - acceleration rotational component (current)
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


