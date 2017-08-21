//Controlling arduino motors using ROS Twist keyboard
//rosrun rosserial_python serial_node.py /dev/ttyUSB0
//rosrun teleop_twist_keyboard teleop_twist_keyboard.py


#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif
#include <stdlib.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/String.h>
ros::NodeHandle nh;
geometry_msgs::Twist msg;

float move1;
float move2;


void callback(const geometry_msgs::Twist& cmd_vel)
{
  move1 = cmd_vel.linear.x;
  move2 = cmd_vel.angular.z;
  if (move1 > 0 && move2 == 0)
  {
    front();
  }
  else if (move1 > 0 && move2 > 0 )
  {
    left();
  }
  else if (move1 > 0 && move2 < 0 )
  {
    right();
  }
  else if (move1 < 0)
  {
    back();
  }
  else
  {
    die();
  }
}

ros::Subscriber <geometry_msgs::Twist> sub("/cmd_vel", callback);

const int rightforw = 2;
const int leftback = 3;
const int leftforw = 4;
const int rightback = 5;

void setup() {
pinMode(leftforw, OUTPUT);
pinMode(leftback, OUTPUT);
pinMode(rightforw, OUTPUT);
pinMode(rightback, OUTPUT);

nh.initNode();
nh.subscribe(sub);
}

void loop() {
nh.spinOnce();
delay(1);
}

void front()
{
    digitalWrite(leftforw, HIGH);
    digitalWrite(rightforw, HIGH);
    digitalWrite(leftback, LOW);
    digitalWrite(rightback, LOW);
    delay(100);
    die(); 
    
}
void back()
{
    digitalWrite(leftforw, LOW);
    digitalWrite(rightforw, LOW);
    digitalWrite(leftback, HIGH);
    digitalWrite(rightback, HIGH);
    delay(100);
    die();   
}
void left()
{
    digitalWrite(leftforw, LOW);
    digitalWrite(rightforw, HIGH);
    digitalWrite(leftback, LOW);
    digitalWrite(rightback, LOW);
    delay(100);
    die(); 

}
void right()
{
    digitalWrite(leftforw, HIGH);
    digitalWrite(rightforw, LOW);
    digitalWrite(leftback, LOW);
    digitalWrite(rightback, LOW);
    delay(100);
    die(); 
}
void die()
{
    digitalWrite(leftforw, LOW);
    digitalWrite(rightforw, LOW);
    digitalWrite(leftback, LOW);
    digitalWrite(rightback, LOW);
}

