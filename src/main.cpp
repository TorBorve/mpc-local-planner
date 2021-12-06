#include "mpc_local_planner/RosMpc.h"
#include <ros/ros.h>

int main(int argc, char** argv){
    ros::init(argc, argv, "MPC");
    ROS_INFO("MPC node intitialized");

    mpc::RosMpc mpc;
    mpc.verifyInputs();
    ROS_INFO("Topics and transfroms are ok!");
    ros::Duration(2).sleep(); // sleep for two sec
    ros::Rate loopRate(30);
    while(ros::ok()) {
        ros::spinOnce();
        mpc.solve();
        loopRate.sleep();
    }
    return 0;
}