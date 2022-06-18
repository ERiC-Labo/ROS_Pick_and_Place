#include <ros/ros.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <geometry_msgs/Point.h>
#include <math.h>

float x, y, z;
void Callback(const geometry_msgs::Point::ConstPtr& msg)
{
    x = msg->x;
    y = msg->y;
    z = msg->z;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "pick_and_place");
    ros::NodeHandle nh;
    ros::AsyncSpinner spinner(1);
    spinner.start();
    ros::Subscriber sub = nh.subscribe("/picking_position", 1000, Callback);

    moveit::planning_interface::MoveGroupInterface manipulator("manipulator");
    moveit::planning_interface::MoveGroupInterface gripper("gripper");

    manipulator.setJointValueTarget(manipulator.getNamedTargetValues("home"));
    manipulator.move();

    geometry_msgs::PoseStamped current_pose;
    current_pose = manipulator.getCurrentPose("ee_link");

    geometry_msgs::Pose target_pose1;
    std::vector<geometry_msgs::Pose> waypoints;
    target_pose1.orientation = current_pose.pose.orientation;
    target_pose1.position.x = x;
    target_pose1.position.y = y;
    target_pose1.position.z = z;
    waypoints.push_back(target_pose1);
    moveit_msgs::RobotTrajectory trajectory;
    const double jump_thresold = 0.0;
    const double eef_step = 0.01;
    double fraction = manipulator.computeCartesianPath(waypoints, eef_step, jump_thresold, trajectory);
    manipulator.execute(trajectory);
    
    geometry_msgs::Pose target_pose2;
    std::vector<geometry_msgs::Pose> waypoints2;
    target_pose2.orientation = current_pose.pose.orientation;
    target_pose2.position.z = -0.1;
    waypoints2.push_back(target_pose2);
    double fraction = manipulator.computeCartesianPath(waypoints2, eef_step, jump_thresold, trajectory);
    manipulator.execute(trajectory);
    return 0;
}