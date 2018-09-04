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

    MatrixXd Xsig = MatrixXd(5, 11);
    ukf.GenerateSigmaPoints(&Xsig);

    //print result
    std::cout << "Xsig = " << std::endl << Xsig << std::endl;

	return 0;
}