#include <ros/ros.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <geometry_msgs/Point.h>
#include <math.h>

class Pick_and_Place{
    public:
        Pick_and_Place(ros::NodeHandle& node_handle);
        void DoPickAndPlace(geometry_msgs::Point::ConstPtr const &msg);
        void MoveManipulator(float x, float y, float z, geometry_msgs::PoseStamped pose);
        void MoveDown(float z);
        void MoveUp(float z);
    private:
        moveit::planning_interface::MoveGroupInterface manipulator;
        moveit::planning_interface::MoveGroupInterface gripper;
        ros::Subscriber sub;
};