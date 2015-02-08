/*
HelloSpoon Factory Reset Code.

This code is loaded on the OpenCM-9.04 provided with HelloSpoon robot.

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

char data = 0;
boolean load_reader = true;
boolean wall = false;
boolean isFriend = true;

HelloSpoon robot;

/*
Reading load on spoon... needs modification!!
*/

void readLoad(){
 delay(1000);
 Serial2.write(1);
 old_ON_Position();
}

/*
Randomly generated motion with random LED routine.
*/
void Dance(){
 int rand_pos[4] = {random(250,550), random(250,650), random(250,750), random(150,800)};
 char rand_led[4] = {'p', 'w', 'c', 'm'};
 
 for(int i = 1; i < 5; i++){
  robot.LED(i, rand_led[i-1]);
  robot.moveJoint(i, rand_pos[i-1]); 
  delay(50);
 }
 
}

/*
LED notification,
activated when a word is recognized by HelloSpoon app.
*/
void LED_notification(){
 for(int i = 1; i < 5; i++){
  robot.LED(i,"green");
  delay(50);
 }
 delay(500);
 for(int i = 1; i < 5; i++){
  robot.LED(i,"blue");
  delay(50);
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

void old_ON_Position(){
 delay(500);
 robot.moveJoint(1, 512);
 robot.moveJoint(2, 312);
 robot.moveJoint(3, 750);
 robot.moveJoint(4, 402);
 delay(1500);
 ON_Position();
}

void ON_Position(){
 delay(500);
 robot.moveJoint(1, 512);
 robot.moveJoint(2, 612);
 robot.moveJoint(3, 750);
 robot.moveJoint(4, 202);
 delay(1500);
}

void Feeding_Init(){
 motionsVelocity();
 load_reader = true;
 
 robot.moveJoint(1, 679);
 robot.moveJoint(2, 347);
 robot.moveJoint(3, 810);
 robot.moveJoint(4, 295);
 delay(1000);
 robot.moveJoint(2, 559);
 robot.moveJoint(3, 810);
 robot.moveJoint(4, 295);
 delay(1000);
 robot.moveJoint(2, 562);
 robot.moveJoint(3, 616);
 robot.moveJoint(4, 454);
 delay(1000);
 robot.moveJoint(2, 649);
 robot.moveJoint(3, 370);
 robot.moveJoint(4, 562);
 delay(1000);
 robot.moveJoint(2, 749);
 robot.moveJoint(3, 270);
 robot.moveJoint(4, 585);
 delay(1000);
 
 Scoop_Motion_Bowl();
 
}

void Scoop_Motion_Bowl(){
 robot.setJointVelocity(1, 100);
 robot.setJointVelocity(2, 100);
 robot.setJointVelocity(3, 100);
 robot.setJointVelocity(4, 100);
 
 robot.moveJoint(2, 807);
 robot.moveJoint(3, 341);
 robot.moveJoint(4, 480);
 delay(500);
 robot.moveJoint(2, 821);
 robot.moveJoint(3, 227);
 robot.moveJoint(4, 430);
 delay(500);
 
 Scoop_Motion_Mouth_Modif();
}

void Scoop_Motion_Mouth_Modif(){
 
 robot.moveJoint(2, 473);
 robot.moveJoint(3, 523);
 robot.moveJoint(4, 400);
 delay(1000);
 robot.moveJoint(2, 453);
 robot.moveJoint(3, 540);
 robot.moveJoint(4, 450);
 delay(1000);
 robot.moveJoint(2, 453);
 robot.moveJoint(3, 540);
 robot.moveJoint(4, 490);
 delay(1000);
 
 Neutral();
 
}

void Neutral(){
 robot.moveJoint(1, 512);
 delay(3500);
 readLoad();
}

void Spoon_Out_Mouth(){
 robot.setJointVelocity(1, 50);
 robot.setJointVelocity(2, 50);
 robot.setJointVelocity(3, 50);
 robot.setJointVelocity(4, 50);
 
 robot.moveJoint(2, 373);
 robot.moveJoint(3, 770);
 robot.moveJoint(4, 302);
 delay(500);
 
}

void setup(){
 
 robot.begin(); //Starts comm with HelloSpoon robot actuators and board.
 Serial2.begin(57600); //Starts Bluetooth comm.
 delay(500);
 
 robot.activateTrunk();
 delay(500);
 
 ON_Position();
 
}

void loop(){
 
 if(wall){
  
 }
 else{
  if(Serial2.available()){
   data = Serial2.read();
   if(data!=0){
    if(data == 'w' && isFriend){
     for(int i = 0; i < 10; i++){
      Dance();
      delay(350);
     }
     ON_Position();
    }
    else if(data == 'c' && isFriend){
     Feeding_Init();
    }
    
   }
  }
 }
}
