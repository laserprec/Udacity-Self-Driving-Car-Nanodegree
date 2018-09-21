## Bayes Filter for Localization (Markov Localization)

![filter](./img/bayes_local.png)

Bayes filter is a recursive procedure to predict the probability distribution of car's location with the 1st order Markov assumption that the prediction at `x_t` only depends on `x_t-1`. NOTE: this is a recursive procedure. 

This provide a framework to keep an internal state car's current location where the motion model predicts the probability distribution at the next time period and the observation model updates the filter's internal state using the current measurments and controls. NOTE: this two-step updat/predict procedure mirrors that of the Kalman Filter.

NOTE: `x_t` is the car's position at time t, 
`u_t` is the control info of the car (velocity, yaw, acceleration, etc.) and `z_t` is the sensor measurement at time t.

![bayes](./img/bayes_rule.png)
![bayes](./img/bayes_rule2.png)

## Motion Model
![motion](./img/motion_model.png)

The motion model is consisted of the following steps:


    For each x_t:
        a. Calculate the transition probability for each potential value x_t-1 	
        b. Calculate the discrete motion model probability by multiplying the transition model probability by the belief state (prior) for x_t-1 
        c. Return total probability (sum) of each discrete probability



## Observation Model
![model](./img/obs_model.png)

The observation model will be implemented by performing the following at each time step:

    1. Measure the range to landmarks up to 100m from the vehicle, in the driving direction (forward)
    2. Estimate a pseudo range from each landmark by subtracting pseudo position from the landmark position
    3. Match each pseudo range estimate to its closest observation measurement
    4. For each pseudo range and observation measurement pair, calculate a probability by passing relevant values to norm_pdf: norm_pdf(observation_measurement, pseudo_range_estimate, observation_stdev)
    Return the product of all probabilities

Why do we multiply all the probabilities in the last step? Our final signal (probability) must reflect all pseudo range, observation pairs. This blends our signal. For example, if we have a high probability match (small difference between the pseudo range estimate and the observation measurement) and low probability match (large difference between the pseudo range estimate and the observation measurement), our resultant probability will be somewhere in between, reflecting the overall belief we have in that state.
