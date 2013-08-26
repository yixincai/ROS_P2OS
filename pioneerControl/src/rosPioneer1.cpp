#include <ros/ros.h>
#include "ros/console.h"
#include <ros/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <fstream>
#include <iostream>
#include <cmath>
#include <p2os_driver/GripperState.h>

using namespace std;

// Main function
int main(int argc, char** argv)
{
	ros::init(argc, argv, "Gripper_controller");
	ros::NodeHandle n;
	
	ros::Publisher gripper_pub_ = n.advertise<p2os_driver::GripperState>("/gripper_control", 1, true);

  double start_time;
  char choice;
  p2os_driver::GripperState cmd;
  // Main loop
  while(ros::ok()){
	    printf("Enter 'c' to close the gripper,\n'o' to open the gripper,\n'u' to move the gripper up,\n'd' to move the gripper down,\nor 'q' to quit:\n");
	    cin>>choice;
	    if (choice == 'q')
	      return 0;
	    else if (choice == 'o'){
	      start_time = ros::Time::now().toSec();
	      cmd.grip.state = 2;
	      cmd.grip.dir = 1;
	      cmd.lift.state = 1;//open the gripper
	      while (ros::Time::now().toSec() < start_time + 7)
	        gripper_pub_.publish(cmd);
	    }
	    else if (choice == 'c'){
	      start_time = ros::Time::now().toSec();
	      cmd.grip.state = 2;//close the gripper
	      cmd.grip.dir = -1;
	      cmd.lift.state = 6;
	      while (ros::Time::now().toSec() < start_time + 3.5)
	        gripper_pub_.publish(cmd);
	    }
	    else if (choice == 'u'){
	      start_time = ros::Time::now().toSec();
	      cmd.grip.state = 0;
	      cmd.grip.dir = 0;
	      cmd.lift.state = 4;//lift the gripper
	      while (ros::Time::now().toSec() < start_time + 4)
	        gripper_pub_.publish(cmd);
	    }
	    else if (choice == 'd'){
	      start_time = ros::Time::now().toSec();
	      cmd.grip.state = 0;
	      cmd.grip.dir = 0;
	      cmd.lift.state = 5;//lower the gripper
	      while (ros::Time::now().toSec() < start_time + 4)
	        gripper_pub_.publish(cmd);
	    }
  	}
  	
	return 0;
}
