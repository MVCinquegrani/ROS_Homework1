#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/Float64.h>



void jointStateCallback(const sensor_msgs::JointState::ConstPtr& joint_state) {
   
   ROS_INFO("\nReceived joint positions:");
    for (size_t i = 0; i < joint_state->position.size(); i++) {
        ROS_INFO("Joint %zu: %f", i, joint_state->position[i]);
    }
}
   
 int main(int argc, char** argv) {
    ros::init(argc, argv, "arm_controller");
    ros::NodeHandle nh;
    ros::Rate loop_rate(10);

    // Create a publisher to send joint position commands
    ros::Publisher joint0_pub = nh.advertise<std_msgs::Float64>("/arm/j0p_controller/command", 1);
    ros::Publisher joint1_pub = nh.advertise<std_msgs::Float64>("/arm/j1p_controller/command", 1);
    ros::Publisher joint2_pub = nh.advertise<std_msgs::Float64>("/arm/j2p_controller/command", 1);
    ros::Publisher joint3_pub = nh.advertise<std_msgs::Float64>("/arm/j3p_controller/command", 1);
  

    // Create a subscriber to receive joint state information
    ros::Subscriber joint_state_sub = nh.subscribe("joint_states", 10, jointStateCallback);

    // Implement any necessary control logic
    while (ros::ok())
  {
  // Generate a command for each joint
    std_msgs::Float64 joint0_command;
    std_msgs::Float64 joint1_command;
    std_msgs::Float64 joint2_command;
    std_msgs::Float64 joint3_command;

    joint0_command.data =-5.0;      // rotate the arm clockwise
    joint1_command.data = 0.5;
    joint2_command.data = -1.2;
    joint3_command.data = -1;

   // publish the command
    joint0_pub.publish(joint0_command);
    joint1_pub.publish(joint1_command);
    joint2_pub.publish(joint2_command);
    joint3_pub.publish(joint3_command);

    // Wait as long as necessary to maintain the desired frequency
    
    loop_rate.sleep();
  }


    ros::spin();

    return 0;
}
