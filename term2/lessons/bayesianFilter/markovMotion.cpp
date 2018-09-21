
#include <iostream>
#include <algorithm>
#include <vector>

#include "../lib/helpers.h"
using namespace std;

std::vector<float> initialize_priors(int map_size, std::vector<float> landmark_positions,
                                     float position_stdev);

float motion_model(float pseudo_position, float movement, std::vector<float> priors,
                   int map_size, int control_stdev);

int main() {
    
    //set standard deviation of control:
    float control_stdev = 1.0f;
    
    //set standard deviation of position:
    float position_stdev = 1.0f;

    //meters vehicle moves per time step
    float movement_per_timestep = 1.0f;

    //number of x positions on map
    int map_size = 25;

    //initialize landmarks
    std::vector<float> landmark_positions {5, 10, 20};
    
    // initialize priors
    std::vector<float> priors = initialize_priors(map_size, landmark_positions,
                                                  position_stdev);
    
    //step through each pseudo position x (i)    
    for (unsigned int i = 0; i < map_size; ++i) {
        float pseudo_position = float(i);

        //get the motion model probability for each x position
        float motion_prob = motion_model(pseudo_position, movement_per_timestep,
                            priors, map_size, control_stdev);
        
        //print to stdout
        std::cout << pseudo_position << "\t" << motion_prob << endl;
    }    

    return 0;
};

//TODO, implement the motion model: calculates prob of being at an estimated position at time t
float motion_model(float pseudo_position, float movement, std::vector<float> priors,
                   int map_size, int control_stdev) {
    // For each x_t:
    // a. Calculate the transition probability for each potential value x_t-1 	
    // b. Calculate the discrete motion model probability by multiplying the 
    //    transition model probability by the belief state (prior) for x_t-1 
    // c. Return total probability (sum) of each discrete probability

    //initialize probability
    float position_prob = 0.0f;
    float trans_prob = 0.0f;
    float delta_pos = 0.0f;
    
    //YOUR CODE HERE
    for (int i=0; i<priors.size(); ++i) {
        delta_pos = pseudo_position - i;
        trans_prob = Helpers::normpdf(delta_pos, movement, control_stdev);
        position_prob += trans_prob * priors[i];
    }
    
    return position_prob;
}

//initialize priors assumimg vehicle at landmark +/- 1.0 meters position stdev
std::vector<float> initialize_priors(int map_size, std::vector<float> landmark_positions,
                                     float position_stdev) {
//initialize priors assumimg vehicle at landmark +/- 1.0 meters position stdev

    //set all priors to 0.0
    std::vector<float> priors(map_size, 0.0);

    //set each landmark positon +/1 to 1.0/9.0 (9 possible postions)
    float normalization_term = landmark_positions.size() * (position_stdev * 2 + 1);
    for (unsigned int i = 0; i < landmark_positions.size(); i++){
        int landmark_center = landmark_positions[i];
        priors[landmark_center] = 1.0f/normalization_term;
        priors[landmark_center - 1] = 1.0f/normalization_term;
        priors[landmark_center + 1] = 1.0f/normalization_term;
    }
    return priors;
}
