#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
    p_error = i_error = d_error = 0.0;
}

void PID::UpdateError(double cte) {
    double prev_error = p_error;
    double dt = 1.0; // assume dt is 1 unit of interval?
    p_error = cte;
    i_error += cte * dt;
    d_error = (cte - prev_error) / dt;
}

double PID::TotalError() {
    return -(Kp * p_error) - (Ki * i_error) - (Kd * d_error);
}

