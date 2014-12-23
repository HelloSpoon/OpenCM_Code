/*
HelloSpoon Factory Reset Code.

This is code is loaded on the OpenCM-9.04 inside HelloSpoon robot.

If for any reason you download a different code 
and want to return your HelloSpoon as its factory state
you MUST load this code using CM9 IDE or HelloSpoon IDE.

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

char Data_Received = 0;

HelloSpoon robot;

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
 }
 delay(500);
 for(int i = 1; i < 5; i++){
  robot.LED(i,"blue");
 }
}

void setup(){
 robot.begin(); //Starts comm with HelloSpoon robot actuators and board.
 Serial2.begin(57600); //Starts Bluetooth comm.
 delay(500); 
 LEDS_on();
}

void loop(){
 if(Serial2.available()){
  Data_Received = Serial2.read();
  if(Data_Received!=0){
   
  }
 }
}
