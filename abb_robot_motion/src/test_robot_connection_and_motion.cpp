#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/JointState.h"
#include "trajectory_msgs/JointTrajectory.h"
#include "control_msgs/FollowJointTrajectoryAction.h"
#include "actionlib/client/simple_action_client.h"
#include <actionlib/client/terminal_state.h>

int main(int argc, char **argv)
{	
	ROS_INFO("Starting Node robot_trajectory_node");
	ros::init(argc, argv, "robot_trajectory_node");
	ros::NodeHandle n;

	actionlib::SimpleActionClient<control_msgs::FollowJointTrajectoryAction> ac("/joint_trajectory_action");
	ROS_INFO("Waiting for action server to start.");
	ac.waitForServer(); //will wait for infinite time
	ROS_INFO("Action server started, sending goal.");

	control_msgs::FollowJointTrajectoryGoal curr_goal;
	
	trajectory_msgs::JointTrajectory new_joint_trajectory;

	new_joint_trajectory.header.stamp = ros::Time::now();
	new_joint_trajectory.header.frame_id = "temp_pose";
	new_joint_trajectory.joint_names.resize(6);
	new_joint_trajectory.points.resize(2);

	new_joint_trajectory.joint_names[0] = "joint_1";
	new_joint_trajectory.joint_names[1] = "joint_2";
	new_joint_trajectory.joint_names[2] = "joint_3";
	new_joint_trajectory.joint_names[3] = "joint_4";
	new_joint_trajectory.joint_names[4] = "joint_5";
	new_joint_trajectory.joint_names[5] = "joint_6";

	trajectory_msgs::JointTrajectoryPoint next_joint_values;

	// first waypoint
	next_joint_values.positions.resize(6);
	next_joint_values.positions[0] = -1.03;
	next_joint_values.positions[1] = -0.06;
	next_joint_values.positions[2] = 0.06;
	next_joint_values.positions[3] = 1.657;
	next_joint_values.positions[4] = 0.52;
	next_joint_values.positions[5] = 0.122;

	new_joint_trajectory.points[0] = next_joint_values;

	// second waypoint
	next_joint_values.positions.resize(6);
	next_joint_values.positions[0] = -1.03;
	next_joint_values.positions[1] = -0.06;
	next_joint_values.positions[2] = 0.06;
	next_joint_values.positions[3] = 1.607;
	next_joint_values.positions[4] = 0.52;
	next_joint_values.positions[5] = 0.122;

	next_joint_values.time_from_start = ros::Duration(0.01);

	new_joint_trajectory.points[1] = next_joint_values;

	curr_goal.trajectory = new_joint_trajectory;

	ac.sendGoal(curr_goal);

	//wait for the action to return
	bool finished_before_timeout = ac.waitForResult(ros::Duration(30.0));

	if (finished_before_timeout)
	{
		actionlib::SimpleClientGoalState state = ac.getState();
	    ROS_INFO("Action finished: %s",state.toString().c_str());
	}
	else
	{
	    ROS_INFO("Action did not finish before the time out.");
	}

  	return 0;
}