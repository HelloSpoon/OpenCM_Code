/*
HelloSpoon Factory Reset Code.

This is code is loaded on the OpenCM-9.04 provided with HelloSpoon robot.

If for any reason you download a different code 
and want to return your HelloSpoon to its factory state
you MUST load this code using CM9 IDE or HelloSpoon IDE
to your OpenCM-9.04 board.

For more information about HelloSpoon IDE:
https://github.com/HelloSpoon/HelloSpoon_OpenCMLib

Trunk design:
 
ID 1: XL-320 2.0 -------- base
ID 2: XL-320 2.0 -------- strong elbow (right)
ID 3: XL-320 2.0 -------- strong elbow (left)
ID 4: XL-320 2.0 -------- elbow near spoon 
ID 5: XL-320 2.0 -------- spoon 
*/

#include <HelloSpoon.h>

char data[2] = 0;

HelloSpoon robot;

/*
Randomly generated motion with random LED routine.
*/
void Dance(){
 int rand_pos[4] = {random(0,0), random(0,0), random(0,0), random(0,0)};
 //char rand_led[4] = {"pink", "white", "cyan", "magenta"};
 
 for(int i = 1; i < 5; i++){
  //robot.LED(i, rand_led[i-1]);
  robot.moveJoint(i, rand_pos[i-1]); 
  delay(10);
 }
 
}

/*
Turn ON blue LED tone, 
just as a reminder that HelloSpoon robot is ready to be used.
*/
void LEDS_on(){
 for(int led = 1; led < 5; led++){
  robot.LED(led,"blue");
  delay(10);
 }
}

/*
LED notification,
activated when a word is recognized by HelloSpoon app.
*/
void LED_notification(){
 for(int i = 1; i < 5; i++){
  robot.LED(i,"green");
  delay(10);
 }
 delay(500);
 for(int i = 1; i < 5; i++){
  robot.LED(i,"blue");
  delay(10);
 }
}

/*
It's possible to set individually the velocity of each actuator 
by modifying this function.
*/
void motionsVelocity(){
 for(int i = 1; i < 5; i++){
  robot.setJointVelocity(i, 80);
  delay(10);
 }
 delay(1000);
}

void setup(){
 
 robot.begin(); //Starts comm with HelloSpoon robot actuators and board.
 Serial2.begin(57600); //Starts Bluetooth comm.
 delay(500); 
 LEDS_on(); //Turns on LEDs.
 motionsVelocity(); // Sets velocity for motions.
 
}

void loop(){
 if(Serial2.available()){
  data = Serial2.read();
  if(data!=0){
   
  }
 }
}
