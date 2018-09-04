#include <iostream>
#include "../../lib/Eigen/Dense"
#include <vector>
#include "../../lib/ukf.h"

using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;
using std::vector;

int main() {

	//Create a UKF instance
	UKF ukf;

/*******************************************************************************
* Programming assignment calls
*******************************************************************************/

    MatrixXd Xsig_aug = MatrixXd(7, 15);
    ukf.AugmentedSigmaPoints(&Xsig_aug);

	return 0;
}