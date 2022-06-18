#include <pick_and_place.hpp>

Pick_and_Place::Pick_and_Place(ros::NodeHandle& node_handle)
    :   manipulator("manipulator"),
        gripper("gripper"){
            // 把持位置をsubscribeし、把持を実行
            sub = node_handle.subscribe("/picking_position", 1000, &Pick_and_Place::DoPickAndPlace, this);
        }

void Pick_and_Place::DoPickAndPlace(geometry_msgs::Point::ConstPtr const &msg)
{
    // 初期位置に移動
    manipulator.setJointValueTarget(manipulator.getNamedTargetValues("home"));
    manipulator.move();
    // グリッパーを開く
    gripper.setJointValueTarget(gripper.getNamedTargetValues("open"));
    gripper.move();
    // ロボットハンドの姿勢を保存
    geometry_msgs::PoseStamped current_pose;
    current_pose = manipulator.getCurrentPose("ee_link");
    // subscribeした把持位置に移動
    MoveManipulator(msg->x, msg->y, msg->z, current_pose);
    // 対象物体にアプローチ
    MoveDown(0.11);
    // グリッパーを閉じて対象物体を把持
    gripper.setJointValueTarget(gripper.getNamedTargetValues("closed"));
    gripper.move();
    // 一秒待機
    ros::Duration(1.0).sleep();
    // 垂直方向に移動
    MoveUp(0.11);
    // 箱の上まで移動
    MoveManipulator(0.0, 0.8, 0.8, current_pose);
    // グリッパーを開いて対象物体を離す
    gripper.setJointValueTarget(gripper.getNamedTargetValues("open"));
    gripper.move();
    // 一秒待機
    ros::Duration(1.0).sleep();
    // 初期位置に移動
    manipulator.setJointValueTarget(manipulator.getNamedTargetValues("home"));
    manipulator.move();
    sub.shutdown();
    
}

// マニピュレータを動かす関数
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

// マニピュレータを垂直に下げる関数
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

// マニピュレータを垂直に上げる関数
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