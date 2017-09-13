## CarND PID Control Project

### Self Driving Car Engineering Nanodegree

---

The goals / steps of this project are the following:

* Compilation: Code must compile without errors with cmake and make.
* Implementation: The PID procedure follows what was taught in the lessons.
* Student describes the effect of the P, I, D component of the PID algorithm in their implementation. Is it what you expected?
* Optionally, Visual aids are encouraged, i.e. record of a small video of the car in the simulator and describe what each component is set to.
* Student discusses how they chose the final hyperparameters (P, I, D coefficients). This could be have been done through manual tuning, twiddle, SGD, or something else, or a combination!
* Simulation: No tire may leave the drivable portion of the track surface. The car may not pop up onto ledges or roll over any surfaces that would otherwise be considered unsafe.

[//]: # (Image References)
[image1]: ./output/img_pid.png

---
## [Rubric](https://review.udacity.com/#!/rubrics/824/view) Points
### Here I will consider the rubric points individually and describe how I addressed each point in my implementation.  

---
### Writeup / README

#### [Here](https://github.com/abhardwajnv/CarND-PID-Control-Project/blob/master/Reflections.md) is the writeup for this project.  

You are reading it!

---

### 1. Student describes the effect of the P, I, D component of the PID algorithm in their implementation. Is it what you expected?

#### PID Controller

A Proportional integral derivative controller (PID controller) is a control loop feedback mechanism which continuously calculates an error value e(t) as the difference between a desired setpoint and a measured process variable and applies a correction based on proportional, integral and derivative terms denoted by P, I & D respectively. The controller attempts to minimize the error value over the time by adjusting the control variable u(t) to a new value determined by a weighted sum of the control terms. [Referenced from Wikipedia.]

#### Implementation

Here i edited PID.cpp & PID.h to update the process of PID Calculation.

Initially i wrote an init function for initialization of PID error variables & PID coefficients.
This function takes 3 inputs of PID hyperparameters (Kp, Ki, Kd).
It then initializes these hyperparameters to be taken as an input.
This function also initializes the PID error variables as 0.0.
Here i defined one more error variable t_error to calculate total error in other function. For this i created declaration in PID.h
This Function does not return anything.

Secondly i created the update function which takes the current error value (cte) as input and updates the error values.
Update step i kept as it was explained in the PID implementation chapter. The Calculation updated 

* diff_cte as the difference between current cte & previous cte.
* prev_cte as the current cte.
* int_cte as the addition of last int_cte & current cte.

This function as well does not return anything.

Lastly, i created a TotalError function to calculate the updated total error using the current values of all coefficients & error variables.
The equation looked like this :

**t_error = - Kp * p_error - Ki * i_error - Kd * d_error**

We can express this equation of control function mathamatically like this :

**u(t) = Kp e(t) + Ki intgral(e(tau)) d(tau) + Kd (d(e(t))/dt)**

Where, 
* Kp, Ki & Kd denotes the coefficients for the proportional, integral and derivative terms, respectively.
* u(t) is the control variable 
* p_error, i_error & d_error are Cross track error values for current , integral & differential terms, respectively.

Below is a reference graph which show nature of PID Controller.

![PIDController][image1]

---

### 2. Student discusses how they chose the final hyperparameters (P, I, D coefficients). This could be have been done through manual tuning, twiddle, SGD, or something else, or a combination!

Here i edited main.cpp to update the hyperparameters for the PID controller using manual tuning method.
I initialized 3 hyperparameters i.e., P, I, D coefficients as explained above.

**Kp: Proportional Coefficient**

Initially i started with setting Kp value to 1.0 and Ki & Kd values to 0.0.
With this i observed that the car was steering very hard and taking jerks towards center from left & right.
So decided to optimize it, i started increasing the value with which i observed that the car is still swerving and there was no improvements.
Then i started reducing the the Kp value which gave me pretty intersting results, the swerving was getting reduced with low values of Kp.
So i optimized the parameter till value 0.2 and kept that value.

**Ki: Integral Coefficient**

Second i moved to Ki, keeping Kp as 0.2 and Kd as 0.
Since we dont have any systamatic bias in this case hence i kept the value of Ki at 0.0001.


**Kd: Diffrential Coefficient**

Lastly with Kp as 0.2 and Kd as 0.0001 i tried tuning the Kd parameter as the car movement was still not smooth.
Again i started with value 1.0 for Kd and saw a bit improvement in the car movement.
So i dicided to increase the value a bit more by 0.5 step.
With value 5.0, i observed pretty good result so decided to stick to that value.

Final Coefficient values looked something like this:

* Kp = 0.2
* Ki = 0.0001
* Kd = 5.0

