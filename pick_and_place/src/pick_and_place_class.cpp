#include <pick_and_place.hpp>

Pick_and_Place::Pick_and_Place(ros::NodeHandle& node_handle)
    :   manipulator("manipulator"),
        gripper("gripper"){
            sub = node_handle.subscribe("/picking_position", 1000, &Pick_and_Place::DoPickAndPlace, this);
        }

void Pick_and_Place::DoPickAndPlace(geometry_msgs::Point::ConstPtr const &msg)
{
    manipulator.setJointValueTarget(manipulator.getNamedTargetValues("home"));
    manipulator.move();
    gripper.setJointValueTarget(gripper.getNamedTargetValues("open"));
    gripper.move();
    geometry_msgs::PoseStamped current_pose;
    current_pose = manipulator.getCurrentPose("ee_link");
    MoveManipulator(msg->x, msg->y, msg->z, current_pose);
    MoveDown(0.11);
    gripper.setJointValueTarget(gripper.getNamedTargetValues("closed"));
    gripper.move();
    ros::Duration(1.0).sleep();
    MoveUp(0.11);
    MoveManipulator(0.0, 0.8, 0.8, current_pose);
    gripper.setJointValueTarget(gripper.getNamedTargetValues("open"));
    gripper.move();
    ros::Duration(1.0).sleep();
    manipulator.setJointValueTarget(manipulator.getNamedTargetValues("home"));
    manipulator.move();
    sub.shutdown();
    
}

void Pick_and_Place::MoveManipulator(float x, float y, float z, geometry_msgs::PoseStamped pose)
{
    geometry_msgs::Pose target_pose;
    std::vector<geometry_msgs::Pose> waypoints;
    target_pose.orientation = pose.pose.orientation;
    target_pose.position.x = x;
    target_pose.position.y = y;
    target_pose.position.z = z;
    waypoints.push_back(target_pose);
    moveit_msgs::RobotTrajectory trajectory;
    const double jump_thresold = 0.0;
    const double eef_step = 0.01;
    double fraction = manipulator.computeCartesianPath(waypoints, eef_step, jump_thresold, trajectory);
    manipulator.execute(trajectory);
}

void Pick_and_Place::MoveDown(float z)
{
    std::vector<geometry_msgs::Pose> waypoints;
    geometry_msgs::Pose target_pose = manipulator.getCurrentPose().pose;
    target_pose.position.z -= z;
    waypoints.push_back(target_pose);
    moveit_msgs::RobotTrajectory trajectory;
    const double jump_thresold = 0.0;
    const double eef_step = 0.01;
    double fraction = manipulator.computeCartesianPath(waypoints, eef_step, jump_thresold, trajectory);
    manipulator.execute(trajectory);
}

void Pick_and_Place::MoveUp(float z)
{
    std::vector<geometry_msgs::Pose> waypoints;
    geometry_msgs::Pose target_pose = manipulator.getCurrentPose().pose;
    target_pose.position.z += z;
    waypoints.push_back(target_pose);
    moveit_msgs::RobotTrajectory trajectory;
    const double jump_thresold = 0.0;
    const double eef_step = 0.01;
    double fraction = manipulator.computeCartesianPath(waypoints, eef_step, jump_thresold, trajectory);
    manipulator.execute(trajectory);
}