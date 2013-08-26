#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <termios.h>
#include <signal.h>
#include <math.h>

#include <ros/ros.h>
#include "ros/console.h"
#include <ros/time.h>
#include <p2os_driver/GripperState.h>
#include <geometry_msgs/Twist.h>

using namespace std;

#define KEYCODE_A 0x61
#define KEYCODE_D 0x64
#define KEYCODE_S 0x73
#define KEYCODE_W 0x77 
#define KEYCODE_Q 0x71
#define KEYCODE_E 0x65
#define KEYCODE_I 0x69
#define KEYCODE_K 0x6B
#define KEYCODE_J 0x6A
#define KEYCODE_L 0x6C
#define KEYCODE_F 0x66
#define KEYCODE_G 0x67
#define KEYCODE_H 0x68

#define KEYCODE_A_CAP 0x41
#define KEYCODE_D_CAP 0x44
#define KEYCODE_S_CAP 0x53
#define KEYCODE_W_CAP 0x57
#define KEYCODE_Q_CAP 0x51
#define KEYCODE_E_CAP 0x45

class TeleopP2Keyboard
{
  private:
  double walk_vel, run_vel, yaw_rate, yaw_rate_run;
  geometry_msgs::Twist cmd;
  double start_time;
  p2os_driver::GripperState g_cmd;
  
  ros::NodeHandle n_;
  ros::Publisher vel_pub_;
	ros::Publisher gripper_pub_;

  public:
  void init()
  { 
    cmd.linear.x = cmd.linear.y = cmd.angular.z = 0;

    vel_pub_ = n_.advertise<geometry_msgs::Twist>("cmd_vel", 1);
    gripper_pub_ = n_.advertise<p2os_driver::GripperState>("/gripper_control", 1, true);
    ros::NodeHandle n_private("~");
    n_private.param("walk_vel", walk_vel, 0.1);
    n_private.param("run_vel", run_vel, 0.4);
    n_private.param("yaw_rate", yaw_rate, 0.2);
    n_private.param("yaw_run_rate", yaw_rate_run, 0.4);
  }
  
  ~TeleopP2Keyboard()   { }
  void keyboardLoop();

};

int kfd = 0;
struct termios cooked, raw;

void quit(int sig)
{
  tcsetattr(kfd, TCSANOW, &cooked);
  exit(0);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "pioneer2_control_keyboard");

  TeleopP2Keyboard tpk;
  tpk.init();

  signal(SIGINT,quit);

  tpk.keyboardLoop();

  return(0);
}

void TeleopP2Keyboard::keyboardLoop()
{
  char c;
  bool dirty=false;

  // get the console in raw mode
  tcgetattr(kfd, &cooked);
  memcpy(&raw, &cooked, sizeof(struct termios));
  raw.c_lflag &=~ (ICANON | ECHO);
  // Setting a new line, then end of file
  raw.c_cc[VEOL] = 1;
  raw.c_cc[VEOF] = 2;
  tcsetattr(kfd, TCSANOW, &raw);

  puts("Reading from keyboard");
  puts("---------------------------");
  puts("Use 'WASD' to translate");
  puts("Use 'QE' to yaw");
  puts("Press 'Shift' to run");
	puts("Use 'J' to open the gripper");
	puts("Use 'L' to close the gripper");
	puts("Use 'I' to move the gripper up");
	puts("Use 'K' to move the gripper down");
	puts("Use 'G' to disable the gripper");
	puts("Use 'F' to disable the lift");
	puts("Use 'H' to disable all the movements");
  ros::Rate r(1000);
  for(;;)
  {
    // get the next event from the keyboard
    if(read(kfd, &c, 1) < 0)
    {
      perror("read():");
      exit(-1);
    }

    cmd.linear.x = cmd.linear.y = cmd.angular.z = 0;

    switch(c)
    {
      // Walking
    case KEYCODE_W:
      cmd.linear.x = walk_vel;
      dirty = true;
      break;
    case KEYCODE_S:
      cmd.linear.x = - walk_vel;
      dirty = true;
      break;
    case KEYCODE_A:
      cmd.linear.y = walk_vel;
      dirty = true;
      break;
    case KEYCODE_D:
      cmd.linear.y = - walk_vel;
      dirty = true;
      break;
    case KEYCODE_Q:
      cmd.angular.z = yaw_rate;
      dirty = true;
      break;
    case KEYCODE_E:
      cmd.angular.z = - yaw_rate;
      dirty = true;
      break;
      
      //gripper control
    case KEYCODE_J:
      start_time = ros::Time::now().toSec();
      g_cmd.grip.state = 1;
      g_cmd.grip.dir = 0;
      g_cmd.lift.state = 0;//open the gripper
      gripper_pub_.publish(g_cmd);
      ros::Duration(2).sleep();
      g_cmd.grip.state = 5;
      g_cmd.grip.dir = 0;
      g_cmd.lift.state = 0;//stop the gripper
      gripper_pub_.publish(g_cmd);
      break;
    case KEYCODE_L:
      start_time = ros::Time::now().toSec();
      g_cmd.grip.state = 2;//close the gripper
      g_cmd.grip.dir = 0;
      g_cmd.lift.state = 0;
      gripper_pub_.publish(g_cmd);
      ros::Duration(2.3).sleep();
      g_cmd.grip.state = 5;
      g_cmd.grip.dir = 0;
      g_cmd.lift.state = 0;//stop the gripper
      gripper_pub_.publish(g_cmd);
      break;
    case KEYCODE_I:
      start_time = ros::Time::now().toSec();
      g_cmd.grip.state = 3;
      g_cmd.grip.dir = 0;
      g_cmd.lift.state = 0;//lift the gripper
      gripper_pub_.publish(g_cmd);
      ros::Duration(3).sleep();
      g_cmd.grip.state = 6;
      g_cmd.grip.dir = 0;
      g_cmd.lift.state = 0;//stop the lift
      gripper_pub_.publish(g_cmd);
      break;
    case KEYCODE_K:
      start_time = ros::Time::now().toSec();
      g_cmd.grip.state = 4;
      g_cmd.grip.dir = 0;
      g_cmd.lift.state = 0;//lower the gripper
      gripper_pub_.publish(g_cmd);
      ros::Duration(3).sleep();
      g_cmd.grip.state = 6;
      g_cmd.grip.dir = 0;
      g_cmd.lift.state = 0;//stop the lift
      gripper_pub_.publish(g_cmd);
      break;
    case KEYCODE_F:
      start_time = ros::Time::now().toSec();
      g_cmd.grip.state = 6;
      g_cmd.grip.dir = 0;
      g_cmd.lift.state = 0;//stop the lift
      gripper_pub_.publish(g_cmd);
      break;
    case KEYCODE_G:
      start_time = ros::Time::now().toSec();
      g_cmd.grip.state = 5;
      g_cmd.grip.dir = 0;
      g_cmd.lift.state = 0;//stop the gripper
      gripper_pub_.publish(g_cmd);
      break;
    case KEYCODE_H:
      start_time = ros::Time::now().toSec();
      g_cmd.grip.state = 7;
      g_cmd.grip.dir = 0;
      g_cmd.lift.state = 0;//stop all
      gripper_pub_.publish(g_cmd);
      break;

    // Running 
    case KEYCODE_W_CAP:
      cmd.linear.x = run_vel;
      dirty = true;
      break;
    case KEYCODE_S_CAP:
      cmd.linear.x = - run_vel;
      dirty = true;
      break;
    case KEYCODE_A_CAP:
      cmd.linear.y = run_vel;
      dirty = true;
      break;
    case KEYCODE_D_CAP:
      cmd.linear.y = - run_vel;
      dirty = true;
      break;
    case KEYCODE_Q_CAP:
      cmd.angular.z = yaw_rate_run;
      dirty = true;
      break;
    case KEYCODE_E_CAP:
      cmd.angular.z = - yaw_rate_run;
      dirty = true;
      break;
    }

    if (dirty == true)
    {
      vel_pub_.publish(cmd);
    }

  }
}
