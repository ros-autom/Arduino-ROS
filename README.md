# Arduino-ROS
Controlling arduino motors using ROS Twist teleoperation keyboard and viewing Ultrasonic Range Data in a plot from a single ROS node.

Upload the desired code to your Arduino.
With arduino connected to your USB port,open a new terminal and run:

    rosrun rosserial_python serial_node.py /dev/ttyUSB0

While serial connection is achieved, open a new terminal and run:

    rqt_plot /ultrasound

This should give you the real time range values of the Ultrasonic sensor.

In order to control your arduino motors using ROS Twist keyboard, after you serially connect, open a new terminal and run:

    rosrun teleop_twist_keyboard teleop_twist_keyboard.py

You can now control your motors through ROS, in real time.


