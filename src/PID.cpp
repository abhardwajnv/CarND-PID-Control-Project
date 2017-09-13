#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

// Code Referenced from learning in PID Control Chapter.
void PID::Init(double Kp, double Ki, double Kd) {
  // Coefficients assignment
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;

  // Error Initialization
  p_error = 0.0;
  i_error = 0.0;
  d_error = 0.0;
  t_error = 0.0;
}

void PID::UpdateError(double cte) {
  d_error = cte - p_error;
  i_error += cte;
  p_error = cte;
}

double PID::TotalError() {
  t_error = - Kp * p_error - Ki * i_error - Kd * d_error;
  return t_error;
}
