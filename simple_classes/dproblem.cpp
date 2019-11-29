#include "dproblem.h"
#include <cmath>

Dynamical_problem::Dynamical_problem(){}

void Dynamical_problem::setInitialPosition(double x, double y, double r){
    _x0_ = x;
    _y0_ = y;
    _r0_ = r;
}

void Dynamical_problem::setInitialVelocities(double vx, double vy, double vr){
    _vx0_ = vx;
    _vy0_ = vy;
    _vr0_ = vr;
}

void Dynamical_problem::setStiffness(double kx, double ky, double kr){
    _kx_ = kx;
    _ky_ = ky;
    _kr_ = kr;
}

void Dynamical_problem::setDumping(double cx, double cy, double cr){
    _cx_ = cx;
    _cy_ = cy;
    _cr_ = cr;
}

void Dynamical_problem::setMass(double mass){
    _m_ = mass;
}

void Dynamical_problem::setForceParameters(std::string direction, double a, double b, double w){
    if (direction == "x"){
        _fx_.setParameters(a,b,w);
    }
    else if (direction == "y"){
        _fy_.setParameters(a,b,w);
    }
    else if (direction == "r"){
        _mr_.setParameters(a,b,w);
    }
}

void Dynamical_problem::setGamma(double gamma){
    _gamma_ = gamma;
}

void Dynamical_problem::setBeta(double beta){
    _beta_ = beta;
}

void Dynamical_problem::setTotalTime(double time){
    _totalTime_ = time;
}

void Dynamical_problem::setTimeSteps(int steps){
    _timeSteps_ = steps; // Number of time steps
}

void Dynamical_problem::resetTime(){
    /*
    Resets dproblem to start time integration
    */
    // Computing initial acceleration
    computeInitialAcceleration();
    // Reseting position, velocity and acceleration
    _x_ = _x0_;
    _y_ = _y0_;
    _r_ = _r0_;
    _vx_ = _vx0_;
    _vy_ = _vy0_;
    _vr_ = _vr0_;
    _ax_ = _ax0_;
    _ay_ = _ay0_;
    _ar_ = _ar0_;
    // Reseting time variables
    _currentTimeStep_ = 0;
}

void Dynamical_problem::computeInitialAcceleration(){
    _ax0_ = (1.0/_m_)*(-_kx_*_x0_-_cx_*_vx0_+_fx_.getValue(0.0));
    _ay0_ = (1.0/_m_)*(-_ky_*_y0_-_cy_*_vy0_+_fy_.getValue(0.0));
    _ar0_ = (1.0/_m_)*(-_kr_*_r0_-_cr_*_vr0_+_mr_.getValue(0.0));
}

std::string Dynamical_problem::getDataReport(){
    std::stringstream ss;
    ss.precision(6);
    ss << std::fixed;
    //ss << std::scientific;
    //ss.width(12);

    ss << "Dynamical problem:" << std::endl;
    ss << "  Initial position: ";
    ss << "x0 = " << _x0_ << ", ";
    ss << "y0 = " << _y0_ << ", ";
    ss << "r0 = " << _r0_ << std::endl;
    ss << "  Initial velocity: ";
    ss << "vx0 = " << _vx0_ << ", ";
    ss << "vy0 = " << _vy0_ << ", ";
    ss << "vr0 = " << _vr0_ << std::endl;
    ss << "  Initial Acceleration: ";
    ss << "ax0 = " << _ax0_ << ", ";
    ss << "ay0 = " << _ay0_ << ", ";
    ss << "ar0 = " << _ar0_ << std::endl;
    // Time integration parameters:
    ss.precision(3);
    ss << "  Time integration parameters: ";
    ss << "gamma: " << _gamma_ << ", ";
    ss << "beta: " << _beta_ << std::endl;
    // About the current time:
    ss.precision(5);
    if (_currentTimeStep_==0){
        ss << "  Current time step is zero (t = 0.000 s)" << std::endl;
        ss << "  Total number of steps: " << _timeSteps_;
        ss << " (for integrating " << _totalTime_ << " s)" << std::endl;
    }else{
        ss << "  Current time step:"<< _currentTimeStep_ << "/";
        ss << _timeSteps_ << std::endl;
        ss << "  (current time is ";
        ss << _totalTime_ * ((double) _currentTimeStep_) /((double) _timeSteps_);
        ss << " (s) - Total time is " << _totalTime_ << " (s)" << std::endl;
    }


    return ss.str();
}

void Dynamical_problem::nextStep(){
    /*
    Advances one step in the time integration and computes
    the news values of current position, velocity and acceleration.
    */
    _currentTimeStep_++;
    // Computing the time increment - dt
    double dt = _totalTime_ / ((double) _timeSteps_);
    // Computing the current time (s) - it will be used to compute the forces
    double t = (double) _currentTimeStep_ * dt;
    // For the current step, the variables inside the
    // class instance are the values of the previous step
    double px = _x_, py = _y_, pr = _r_;
    double pvx = _vx_, pvy = _vy_, pvr = _vr_;
    double pax = _ax_, pay = _ay_, par = _ar_;
    // Computing force components for the current time
    double fx = _fx_.getValue(t);
    double fy = _fy_.getValue(t);
    double mr = _mr_.getValue(t);
    // For shorter names in expression _gamma_ -> gm, _beta_ -> bt
    double gm = _gamma_, bt = _beta_;
    // Computing current _x_, _vx_ and _ax_
    _x_ = (fx + ((1.0/bt)*(_m_/(dt*dt))+(gm/bt)*(_cx_/dt))*px
         +((1.0/bt)*(_m_/dt)+((gm/bt)-1.0)*_cx_)*pvx+((1.0/(2.0*bt)-1.0)*_m_
         +(gm/(2.0*bt)-1.0)*_cx_*dt)*pax)
         /((1.0/bt)*(_m_/(dt*dt))+_kx_+(gm/bt)*(_cx_/dt));

    _vx_ = ((gm/bt)/dt)*_x_-((gm/bt)/dt)*px+(1.0-(gm/bt))*pvx
          +(1.0-(gm/(2.0*bt)))*dt*pax;

    _ax_ = (fx - _kx_*_x_-_cx_*_vx_)/_m_;

    // Computing current _y_, _vy_ and _ay_
    _y_ = (fy + ((1.0/bt)*(_m_/(dt*dt))+(gm/bt)*(_cy_/dt))*py
         +((1.0/bt)*(_m_/dt)+((gm/bt)-1.0)*_cy_)*pvy+((1.0/(2.0*bt)-1.0)*_m_
         +(gm/(2.0*bt)-1.0)*_cy_*dt)*pay)
         /((1.0/bt)*(_m_/(dt*dt))+_ky_+(gm/bt)*(_cy_/dt));

    _vy_ = ((gm/bt)/dt)*_y_-((gm/bt)/dt)*py+(1.0-(gm/bt))*pvy
          +(1.0-(gm/(2.0*bt)))*dt*pay;

    _ay_ = (fy - _ky_*_y_-_cy_*_vy_)/_m_;

    // Computing current _r_, _vr_ and _ar_
    _r_ = (mr + ((1.0/bt)*(_m_/(dt*dt))+(gm/bt)*(_cr_/dt))*pr
         +((1.0/bt)*(_m_/dt)+((gm/bt)-1.0)*_cr_)*pvr+((1.0/(2.0*bt)-1.0)*_m_
         +(gm/(2.0*bt)-1.0)*_cr_*dt)*par)
         /((1.0/bt)*(_m_/(dt*dt))+_kr_+(gm/bt)*(_cr_/dt));

    _vr_ = ((gm/bt)/dt)*_r_-((gm/bt)/dt)*pr+(1.0-(gm/bt))*pvr
          +(1.0-(gm/(2.0*bt)))*dt*par;

    _ar_ = (mr - _kr_*_r_-_cr_*_vr_)/_m_;

}

void Dynamical_problem::integrate(std::string csvOutputFile){
    std::ofstream ofile;
    ofile.open(csvOutputFile.c_str(),std::ofstream::out);
    ofile << "step;x;y;r;vx;vy;vr;ax;ay;ar" << std::endl;
    resetTime();
    while (_currentTimeStep_<_timeSteps_){
        nextStep();
        ofile << _currentTimeStep_ << ";";
        ofile << _x_ << ";" << _y_ << ";" << _r_ << ";";
        ofile << _vx_ << ";" << _vy_ << ";" << _vr_ << ";";
        ofile << _ax_ << ";" << _ay_ << ";" << _ar_ << std::endl;
    }
    ofile.close();
}

// Verified up to this points

/*

double Dynamical_problem::ForceValue(std::string direction, double time){
    struct force cforce = getForce(direction);
    double fvalue = cforce.a + cforce.b*sin(cforce.w*time);
    return fvalue;
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

void Dynamical_problem::getInitialAcelleration(std::string direction){}

void Dynamical_problem::getNewRotation(){}

void Dynamical_problem::getInitialAcceleration(){
    _a0x_ = (1.0/_m_)*(-_kx_*_center_.x-_cx_*_v0x_+_fx_);
    _a0y_ = (1.0/_m_)*(-_ky_*_center_.y-_cy_*_v0y_+_fy_);
    _a0z_ = (1.0/_m_)*(-_kr_*_center_.r-_cr_*_v0r_+_mz_);
}

void Dynamical_problem::getPreviousVelocity(std::string direction){}

    if time = 0 
        v i-1 = v0x 

    if t =/ 0




void Dynamical_problem::getPreviousAcceleration(){}

struct point Dynamical_problem::getNewCenterCoordinates(double time){

       //New X coordinates
       //Check Time
        if (time == 0.){
            double vx = _v0x_;
            double ax = _a0x_;
            double ay = _a0y_;
            double vy = _v0y_;
        }

        else{

            double vx = getPreviousVelocity("x",steps);
            double ax = getPreviousAcceleration("x",steps);
            double vy = getPreviousVelocity("y",steps);
            double ay = getPreviousAcceleration("y",steps);

        }  

        //Current force
        double cfx = ForceValue("x", time);
        double cfy = ForceValue("y", time);
        double cfz = ForceValue("z", time);

        //Numeric method
        struct point currentcenter;
    
        currentcenter.x = (cfx+((1./_beta_)*(_m_/(_timeSteps_*_timeSteps_))+
        (_gama_/_beta_)*(_cx_/_timeSteps_))*_center_.x+((1./_beta_)*(_m_/_timeSteps_)+
        ((_gama_/_beta_)-1.)*_cx_)*vx+((1./(2.*_beta_)-1.)*_m_+
        (_gama_/(2.*_beta_)-1.)*__cx__*_timeSteps_)*ax)
        /((1./_beta_)*(_m_/(_timeSteps_*_timeSteps_))+_kx_+
        (_gama_/_beta_)*(_cx_/_timeSteps_)); 

        //New Y coordinates

        currentcenter.y = (cfy+((1./_beta_)*(_m_/(_timeSteps_*_timeSteps_))+
        (_gama_/_beta_)*(_cy_/_timeSteps_))*_center_.y+((1./_beta_)*(_m_/_timeSteps_)+
        ((_gama_/_beta_)-1.)*_cy_)*vy+((1./(2.*_beta_)-1.)*_m_+
        (_gama_/(2.*_beta_)-1.)*_cy_*_timeSteps_)*ay)
        /((1./_beta_)*(_m_/(_timeSteps_*_timeSteps_))+_ky_+
        (_gama_/_beta_)*(_cy_/_timeSteps_));

        //New Rotation
        currentcenter.r = (cfz+((1./_beta_)*(_m_/(_timeSteps_*_timeSteps_))+
        (_gama_/_beta_)*(_cr_/_timeSteps_))*_center_.r+((1./_beta_)*(_m_/_timeSteps_)+
        ((_gama_/_beta_)-1.)*_cr_)*vr+((1./(2.*_beta_)-1.)*_m_+
        (_gama_/(2.*_beta_)-1.)*_cr_*_timeSteps_)*ar)
        /((1./_beta_)*(_m_/(_timeSteps_*_timeSteps_))+_kr_+
        (_gama_/_beta_)*(_cr_/_timeSteps_));

}

double Dynamical_problem::getTotalTime(int steps){

    double TotalTime = steps*_timeSteps_;
    return TotalTime;

}
*/
