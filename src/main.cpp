#include "mpc_local_planner/CppADMPC.h"
#include "mpc_local_planner/utilities.h"

#include <iostream>
#include <thread>
#include <chrono>

#include <ros/ros.h>

int main(int argc, char** argv){
    ros::init(argc, argv, "MPC");
    ROS_INFO("MPC node intitialized");
    ros::NodeHandle nh;
    ros::Publisher pathPub;
    pathPub = nh.advertise<nav_msgs::Path>("local_path", 1);
    mpc::State refState{10, 10, M_PI};
    mpc::State state{0, 0, 0};
    mpc::nonlinear::MPC mpc{refState};
    std::cout << "x\ty\tpsi\tcost\n";
    auto refresh = std::chrono::high_resolution_clock::now();
    while(true){
        auto solution = mpc.solve(state);
        mpc::nonlinear::diffDriveModel(state, solution.u0, 0.1);
        std::cout << state.x << '\t' << state.y << '\t' << state.psi << '\t' << solution.cost << std::endl;
        pathPub.publish(getPathMsg(solution));
        if (solution.cost < 100){
            state = mpc::State{0, 0, 0};
        }
        refresh += std::chrono::milliseconds{100};
        std::this_thread::sleep_until(refresh);
    }

    return 0;
}