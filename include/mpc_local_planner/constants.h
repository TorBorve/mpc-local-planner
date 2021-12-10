#pragma once

// Parameters for mpc

#define MPC_N 10 // number of steps in mpc

#define MPC_dt 0.2 // time increment in between steps

#define MPC_LOOP_Hz 30 // the hertz of the mpc. It could hurt performance if this is too low

#define MPC_LOOP_dt 1.0 / MPC_LOOP_Hz // time between outputs from the MPC

// Constants for car

#define MPC_MAX_STEERING_ANGLE 0.57 // maxium steering angle on the wheels in radians

#define MPC_MIN_STEERING_ANGLE -MPC_MAX_STEERING_ANGLE // minimum steering angle on the wheels in radians

#define MPC_MAX_STEERING_ROTATION_SPEED 800.0 / 17.3 * M_PI / 180.0 // maximum ratation speed on the wheels in [rad / s]

#define MPC_WHEELBASE 2.65 // the length between the front and rear axle