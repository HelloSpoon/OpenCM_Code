/*
Code used to animate HelloSpoon robot
with HelloSpoon Animator Android app.
*/

#include <"HelloSpoon.h">

char data = 0;

int num_mot = 0;
int num_time = 0;
int num_vel = 50;

int times = 0;

int actual_Pos[60][8];
int fin_pos[60][8] = {};

boolean activate = false;

HelloSpoon robot;

void setup(){
  robot.begin();
  Serial2.begin(57600);
  delay(500);
  
  robot.activateTrunk();
  delay(100);
}

void loop(){
  if(Serial2.available()>0){
    data = Serial2.read();
    if(data!=0){
      
      if(data == 'a'){
        activate = true;
      }
      
      else if(data == 'b'){
        activate = false;
        data = 0;
        fin_pos[60][8] = actual_Pos[60][8];
      }
      
      else if(data == 'c'){
        robot.torqueOFF(num_mot);
        robot.LED(num_mot, "red");
      }
      
      else if(data == 'd'){
        robot.torqueON(num_mot);
        robot.LED(num_mot, "green");
      }
      
      else if(data == 'e'){
        for(int i = 1; i < 5; i++){
          actual_Pos[times][i] = robot.getJointPosition(i);
        }
        times+=1;
      }
      
      else if(data == 'f'){
        for(int a = 0; a < times; a++){
          for(int b = 1; b < 5; b++){
            robot.setJointVelocity(b, num_vel);
            robot.moveJoint(b, actual_Pos[a][b]);
            SerialUSB.println(actual_Pos[a][b]);
          }
          SerialUSB.println("NEXT");
          delay(num_time);
        }
      }
      
      else if(data == 'g'){
        num_mot = 1;
      }

      else if(data == 'h'){
        num_mot = 2;
      }
      
      else if(data == 'i'){
        num_mot = 3;
      }
      
      else if(data == 'j'){
        num_mot = 4;
      }
      
      else if(data == 'm'){
        num_vel = 50;
      }

      else if(data == 'n'){
        num_vel = 200;
      }
      
      else if(data == 'o'){
        num_vel = 400;
      }
      
      else if(data == 'p'){
        num_vel = 600;
      }
      
      else if(data == 'q'){
        num_time = 3000;
      }
      
      else if(data == 'r'){
        num_time = 1000;
      }
      
      else if(data == 's'){
        num_time = 500;
      }
      
    }
  }
}
