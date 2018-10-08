#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

static const int P_ERROR = 0;
static const int I_ERROR = 0;
static const int D_ERROR = 0;

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
    Kp = Kp;
    Ki = Ki;
    Kd = Kd;
    p_error = P_ERROR;
    i_error = I_ERROR;
    d_error = D_ERROR;
}

void PID::UpdateError(double cte) {
}

double PID::TotalError() {
}

