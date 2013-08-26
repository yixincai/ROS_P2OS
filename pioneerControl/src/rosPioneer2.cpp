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

#include <geometry_msgs/Twist.h>

using namespace std;

#define KEYCODE_A 0x61
#define KEYCODE_D 0x64
#define KEYCODE_S 0x73
#define KEYCODE_W 0x77 
#define KEYCODE_Q 0x71
#define KEYCODE_E 0x65

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

  ros::NodeHandle n_;
  ros::Publisher vel_pub_;

  public:
  void init()
  { 
    cmd.linear.x = cmd.linear.y = cmd.angular.z = 0;

    vel_pub_ = n_.advertise<geometry_msgs::Twist>("cmd_vel", 1);

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
  ros::init(argc, argv, "pioneer2_base_keyboard");

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
