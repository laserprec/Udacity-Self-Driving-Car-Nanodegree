#include <iostream>
#include "../../lib/ukf.h"

UKF::UKF()
{
    //TODO Auto-generated constructor stub
    Init();
}

UKF::~UKF()
{
    //TODO Auto-generated destructor stub
}

void UKF::Init()
{
}

/*******************************************************************************
* Programming assignment functions: 
*******************************************************************************/

void UKF::SigmaPointPrediction(MatrixXd *Xsig_out)
{

    //set state dimension
    int n_x = 5;

    //set augmented dimension
    int n_aug = 7;

    //create example sigma point matrix
    MatrixXd Xsig_aug = MatrixXd(n_aug, 2 * n_aug + 1);
    Xsig_aug << 5.7441, 5.85768, 5.7441, 5.7441, 5.7441, 5.7441, 5.7441, 5.7441, 5.63052, 5.7441, 5.7441, 5.7441, 5.7441, 5.7441, 5.7441,
        1.38, 1.34566, 1.52806, 1.38, 1.38, 1.38, 1.38, 1.38, 1.41434, 1.23194, 1.38, 1.38, 1.38, 1.38, 1.38,
        2.2049, 2.28414, 2.24557, 2.29582, 2.2049, 2.2049, 2.2049, 2.2049, 2.12566, 2.16423, 2.11398, 2.2049, 2.2049, 2.2049, 2.2049,
        0.5015, 0.44339, 0.631886, 0.516923, 0.595227, 0.5015, 0.5015, 0.5015, 0.55961, 0.371114, 0.486077, 0.407773, 0.5015, 0.5015, 0.5015,
        0.3528, 0.299973, 0.462123, 0.376339, 0.48417, 0.418721, 0.3528, 0.3528, 0.405627, 0.243477, 0.329261, 0.22143, 0.286879, 0.3528, 0.3528,
        0, 0, 0, 0, 0, 0, 0.34641, 0, 0, 0, 0, 0, 0, -0.34641, 0,
        0, 0, 0, 0, 0, 0, 0, 0.34641, 0, 0, 0, 0, 0, 0, -0.34641;

    //create matrix with predicted sigma points as columns
    MatrixXd Xsig_pred = MatrixXd(n_x, 2 * n_aug + 1);

    double delta_t = 0.1; //time diff in sec
                          /*******************************************************************************
 * Student part begin
 ******************************************************************************/

    //predict sigma points
    for (int i = 0; i < 2 * n_aug + 1; ++i)
    {
        double px = Xsig_aug(0, i);
        double py = Xsig_aug(1, i);
        double v = Xsig_aug(2, i);
        double phi = Xsig_aug(3, i);
        double phi_dot = Xsig_aug(4, i);
        double noise_a = Xsig_aug(5, i);
        double noise_phi_dot = Xsig_aug(6, i);

        double px_p, py_p;
        //avoid division by zero
        if (phi_dot > 0.001) {
            px_p = px + v/phi_dot * ( sin (phi + phi_dot*delta_t) - sin(phi));
            py_p = py + v/phi_dot * ( cos(phi) - cos(phi+phi_dot*delta_t) );
        }
        else {
            px_p = px + v*delta_t*cos(phi);
            py_p = py + v*delta_t*sin(phi);
        }
        double v_p = v;
        double phi_p = phi + phi_dot*delta_t;
        double phi_dot_p = phi_dot;

        //add noise
        px_p = px_p + 0.5*noise_a*delta_t*delta_t * cos(phi);
        py_p = py_p + 0.5*noise_a*delta_t*delta_t * sin(phi);
        v_p = v_p + noise_a*delta_t;

        phi_p = phi_p + 0.5*noise_phi_dot*delta_t*delta_t;
        phi_dot_p = phi_dot_p + noise_phi_dot*delta_t;

        //write predicted sigma point into right column
        Xsig_pred(0,i) = px_p;
        Xsig_pred(1,i) = py_p;
        Xsig_pred(2,i) = v_p;
        Xsig_pred(3,i) = phi_p;
        Xsig_pred(4,i) = phi_dot_p;
    }

    /*******************************************************************************
 * Student part end
 ******************************************************************************/

    //print result
    std::cout << "Xsig_pred = " << std::endl
              << Xsig_pred << std::endl;

    //write result
    *Xsig_out = Xsig_pred;
}
