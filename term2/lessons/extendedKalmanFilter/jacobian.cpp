#include <iostream>
#include "../lib/Eigen/Dense"
#include <cmath>
#include <vector>

using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;

MatrixXd CalculateJacobian(const VectorXd& x_state);

int main() {

	/*
	 * Compute the Jacobian Matrix
	 */

	//predicted state  example
	//px = 1, py = 2, vx = 0.2, vy = 0.4
	VectorXd x_predicted(4);
	x_predicted << 1, 2, 0.2, 0.4;

	MatrixXd Hj = CalculateJacobian(x_predicted);

	cout << "Hj:" << endl << Hj << endl;

	return 0;
}

MatrixXd CalculateJacobian(const VectorXd& x_state) {

	MatrixXd Hj(3,4);
	//recover state parameters
	float px = x_state(0);
	float py = x_state(1);
	float vx = x_state(2);
	float vy = x_state(3);

	// float px_py_sq_sum = pow(px, 2) + pow(py, 2);
    // float sq_sum_pow = pow(px_py_sq_sum, 3/2);
    // float v_p_diff = vx * py - vy * px;
    
	// //check division by zero
    // if (px_py_sq_sum == 0)
    //     cerr << "Error: both px and py are zero" << '\n';
	
	// //compute the Jacobian matrix
    // Hj << px / sqrt(px_py_sq_sum),      py / sqrt(px_py_sq_sum),        0,                          0,
    //       -py / px_py_sq_sum,           px/ px_py_sq_sum,               0,                          0,
    //       py * (v_p_diff) / sq_sum_pow, py * (v_p_diff) / sq_sum_pow,   px / sqrt(px_py_sq_sum),    py / sqrt(px_py_sq_sum);


    //pre-compute a set of terms to avoid repeated calculation
	float c1 = px*px+py*py;
	float c2 = sqrt(c1);
	float c3 = (c1*c2);

	//check division by zero
	if(fabs(c1) < 0.0001){
		cout << "CalculateJacobian () - Error - Division by Zero" << endl;
		return Hj;
	}

	//compute the Jacobian matrix
	Hj << (px/c2), (py/c2), 0, 0,
		  -(py/c1), (px/c1), 0, 0,
		  py*(vx*py - vy*px)/c3, px*(px*vy - py*vx)/c3, px/c2, py/c2;

	return Hj;
}