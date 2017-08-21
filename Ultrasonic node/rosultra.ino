//rosrun rosserial_python serial_node.py /dev/ttyUSB0
//rqt_plot /ultrasound

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include <WProgram.h>
#endif
#include <stdlib.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/String.h>
#include <ros/time.h>
#include <sensor_msgs/Range.h>
#define USE_USBCON

ros::NodeHandle  nh;

sensor_msgs::Range range_msg;
geometry_msgs::Twist msg;

float move1;
float move2;

ros::Publisher pub_range( "/ultrasound", &range_msg);

int pingPin = 12;
int inPin = 13;
int ledPin = 11;
long range_time;
char frameid[] = "/ultrasound";

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
  nh.initNode();
  nh.advertise(pub_range);
  nh.subscribe(sub);
  range_msg.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg.header.frame_id =  frameid;
  range_msg.field_of_view = 0.1;  // fake
  range_msg.min_range = 0.0;
  range_msg.max_range = 4.47;
  pinMode(leftforw, OUTPUT);
  pinMode(leftback, OUTPUT);
  pinMode(rightforw, OUTPUT);
  pinMode(rightback, OUTPUT); 
}

void loop()
{
  if ( millis() >= range_time ){
      int r =0;  
      range_msg.range = getRange() / 100;
      range_msg.header.stamp = nh.now();
      pub_range.publish(&range_msg);
      range_time =  millis() + 50;
    }    
    nh.spinOnce();
    delay(1);
}


long microsecondsToCentimeters(long microseconds)
{
// The speed of sound is 340 m/s or 29 microseconds per centimeter.
// The ping travels out and back, so to find the distance of the
// object we take half of the distance travelled.
return microseconds / 29.1 / 2;
}

float getRange()
{
    
    // establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  long duration, cm;
  
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(3);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  
  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(inPin, INPUT);
  duration = pulseIn(inPin, HIGH);
  
  // convert the time into a distance
  return microsecondsToCentimeters(duration);
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
