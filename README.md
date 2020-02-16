# Mini-forklift project
Idea was to create platform having similar capabilities to full-sized forklift.

Project contained the making of physical structure as well as programming and electronics.

## Construction
In the lower front part of the vehicle DC motors which, are located responsible for vehicle movement, while in the rear part a rotary wheel is placed. Such kinematics enable, with a large wheelbase, dynamic rotation almost in place.

Lifting mechanism was created using drylin linear guide with bar screw ([igus](https://www.igus.eu/drylin/linear-guide)).

Most of the structure was made using wood. But all assembly components and forks were made usind 3-d printing technology.

## Electronics
All project consinst of:
* 2 x L298 Drive Module
* Arduino Uno
* HC-06 bluetooth module
* Battery

## Control
![Blue Dot App](/images/blue_dot.png)
Robot is controlled using blue dot app, which sends message to arduino about location of the finger on touch screen.

Blue dot circle was split into outer and inner circle. Inner was controling the lift, outer was controling movement of the robot.

Speed of the motors was controlled using PWM.

## Thougts
Blue dot app wasnt the best choice. Similar funcionality could be achieved using better control system.

