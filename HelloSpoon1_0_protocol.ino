/*
  HelloSpoon sketch
 
 MODIFIED FOR DXL 2.0 and 1.0 protocol and NEW 5 DOF trunk
 EEPROM support REMOVED for CM9 IDE issues...
 MAIN_PROGRAM
 
 Trunk design:
 
 ID 1: XL-320 2.0 -------- base
 ID 4: XL-320 2.0 -------- elbow near spoon 
 ID 1: XL-320 1.0 -------- strong elbow (right)
 ID 2: XL-320 1.0 -------- strong elbow (left)
 ID 4: XL-320 1.0 -------- spoon 
 */
#include <DynamixelPro.h>

char Data_Received = 0;

char IMEI = 0;

long var = 0;
long password = 0;

int char_counter = 0;
int real_var = 0;
float carga = 0;
int thrash = 0;

boolean isFriend = true;
boolean wall = false;
boolean load_reader = true;

int var_bowl1 = 679;
int var_bowl2 = 649;
int var_bowl3 = 370;
int var_bowl4 = 562;

int var_mouth2 = 453;
int var_mouth3 = 580;
int var_mouth4 = 540;

int init_feeding[5][4] = {{347, 678, 810, 295}, // 679                          
                          {559, 466, 811, 296}, // 679
                          {562, 461, 616, 454}, // 679
                          {649, 370, 562, 512}, // 679
                          {749, 267, 418, 584}}; // 681

int scoop_motion[2][4] = {{807, 207, 341, 480}, //671
                          {821, 188, 227, 430}}; //671

int shake_scoop[2][4] = {{821, 188, 227, 430}, //693
                         {821, 188, 227, 430}}; //673

int init_mouth[3][4] = {{473, 560, 523, 480}, //512
                        {453, 580, 550, 480}, //512
                        {421, 613, 659, }};  //512

int init_mouth_modif[3][4] = {{473, 560, 523, 400}, //671
                              {453, 580, 540, 450}, //671
                              {453, 580, 540, 490}}; //671

int spoon_out[1][4] = {{372, 654, 770, 302}}; //512                        

DynamixelPro DxlEx;


void readLoad(){
  //SerialUSB.println("[DEBUG] estoy aqui tio");
  //while(load_reader){
    //if(DxlEx.readWord(1,37) > 500 && DxlEx.readWord(1,37) < 550){
      //carga = Dxl.readByte(4,40);
    //  SerialUSB.println("El valor de la carga:");
      //SerialUSB.println("Carga: ");
      //SerialUSB.print(carga);
      //if(carga>=80 || (carga>=30 && carga <=43)){
        //load_reader = false;
        delay(1000);
        Serial2.write(1);
        old_ON_Position();
      //}
    //}
    //else{
    //}
  //}
}

void DanceMotions(){
  int Random_Pos[4] = {
    random(250,550),random(250,650),random(250,750),random(150,800)  };
  int Random_LED[5] = {
    random(0,6), random(0,6), random(0,6), random(0,6), random(0,6)  };
  SLOW_velocity();
  for(int i=0;i<5;i++){
    DxlEx.writeWord(1, 25, Random_LED[0]);
    Dxl.writeWord(i+1, 25, Random_LED[i+1]);
    delay(50);
  }
  DxlEx.writeWord(1,30,Random_Pos[0]);
  Dxl.writeWord(1,30,Random_Pos[1]);
  Dxl.writeWord(2,30,1024-Random_Pos[1]);
  Dxl.writeWord(3,30,Random_Pos[2]);
  Dxl.writeWord(4,30,Random_Pos[3]);
  delay(50);
}

void LEDS_off(){
  for(int led=0;led<5;led++){
    DxlEx.writeWord(1,25,4);
    DxlEx.writeWord(4,25,4);
    Dxl.writeWord(led+1,25,4);
  }
  delay(500);
}

void LED_notification(int led){
  for(int i=0;i<5;i++){
    DxlEx.writeWord(1,25,led);
    DxlEx.writeWord(i+1,25,led);
  }
  delay(100);
  for(int j=0;j<5;j++){
    DxlEx.writeWord(1,25,0);
    DxlEx.writeWord(j+1,25,0);
  }  
}

void SLOW_velocity(){
  DxlEx.writeWord(1,32,80);
  DxlEx.writeWord(4,32,80);
  Dxl.writeWord(1,32,80);
  Dxl.writeWord(2,32,80);
  Dxl.writeWord(4,32,80); 
  delay(1000); 
}

void old_ON_Position(){
  delay(500);
  DxlEx.writeWord(1,30,512);
  DxlEx.writeWord(4,30,750);
  Dxl.writeWord(1,30,312);
  Dxl.writeWord(2,30,712);
  Dxl.writeWord(4,30,402);
  delay(1500);
  ON_Position();
}

void ON_Position(){
  delay(500);
  DxlEx.writeWord(1,30,512);
  DxlEx.writeWord(4,30,750);
  Dxl.writeWord(1,30,612);
  Dxl.writeWord(2,30,412);
  Dxl.writeWord(4,30,202);
  delay(1500);
}

void Feeding_Init(){
  SLOW_velocity();
  load_reader = true;
 
      DxlEx.writeWord(1, 30, var_bowl1);
      Dxl.writeWord(1,30,347);
      Dxl.writeWord(2,30,678);
      DxlEx.writeWord(4,30,810);
      Dxl.writeWord(4,30,295);
      delay(1000);  
      Dxl.writeWord(1,30,559);
      Dxl.writeWord(2,30,466);
      DxlEx.writeWord(4,30,810);
      Dxl.writeWord(4,30,295);
      delay(1000); 
      Dxl.writeWord(1,30,562);
      Dxl.writeWord(2,30,461);
      DxlEx.writeWord(4,30,616);
      Dxl.writeWord(4,30,454);
      delay(1000); 
      /*From here you start to use the saved values*/
      Dxl.writeWord(1,30,var_bowl2); //649
      Dxl.writeWord(2,30,var_bowl3); //370
      DxlEx.writeWord(4,30,var_bowl4); //562
      Dxl.writeWord(4,30,512);
      delay(1000); 
      Dxl.writeWord(1,30,var_bowl2+100);
      Dxl.writeWord(2,30,var_bowl3-100);
      DxlEx.writeWord(4,30,var_bowl4-140);
      Dxl.writeWord(4,30,585);
      delay(1000); 
  
  Scoop_Motion_Bowl();
}

void Scoop_Motion_Bowl(){

      DxlEx.writeWord(1,32,100);
      DxlEx.writeWord(4,32,100);
      Dxl.writeWord(1,32,100);
      Dxl.writeWord(2,32,100);
      Dxl.writeWord(4,32,100);
      
      //DxlEx.writeWord(1,30,671);
      Dxl.writeWord(1,30,807);
      Dxl.writeWord(2,30,207);
      DxlEx.writeWord(4,30,341);
      Dxl.writeWord(4,30,480);
      delay(500);
      Dxl.writeWord(1,30,821);
      Dxl.writeWord(2,30,188);
      DxlEx.writeWord(4,30,227);
      Dxl.writeWord(4,30,430); 
      delay(500); 
      
      Scoop_Motion_Mouth_Modif();
}

void Scoop_Motion_Mouth_Modif(){
      Dxl.writeWord(1,30,473);
      Dxl.writeWord(2,30,560);
      DxlEx.writeWord(4,30,523);
      Dxl.writeWord(4,30,400); 
    delay(1000);  
    Dxl.writeWord(1,30,453);
      Dxl.writeWord(2,30,560);
      DxlEx.writeWord(4,30,540);
      Dxl.writeWord(4,30,450); 
    delay(1000);  
    Dxl.writeWord(1,30,var_mouth2); //453
      Dxl.writeWord(2,30,var_mouth3); //580
      DxlEx.writeWord(4,30,var_mouth4); //540
      Dxl.writeWord(4,30,490); //490
    delay(1000);  
  
  Neutral();
}

void Neutral(){
  DxlEx.writeWord(1, 30, 512);
  delay(3500);
  readLoad();
//normal_boot();
}


void Spoon_Out_Mouth(){
  
  DxlEx.writeWord(1,32,50);
      DxlEx.writeWord(4,32,50);
      Dxl.writeWord(1,32,50);
      Dxl.writeWord(2,32,50);
      Dxl.writeWord(4,32,50);

  Dxl.writeWord(1,30,var_mouth2-80);
      Dxl.writeWord(2,30,var_mouth3+70);
      DxlEx.writeWord(4,30,var_mouth4+230);
      Dxl.writeWord(4,30,302);
    delay(500);  
  
}

void MakerFaire_Demo(){
  for(int i=0;i<10;i++){
    DanceMotions();
    delay(350);
  }
  ON_Position();
}

void bowl_process(){
  var_bowl1 = DxlEx.readWord(1,37);
  var_bowl2 = Dxl.readWord(1,36);
  var_bowl3 = Dxl.readWord(2,36);
  var_bowl4 = DxlEx.readWord(4,37);
  delay(300);
  turnON_torque();
  delay(1000);
  ON_Position();
  delay(2000);
  turnOFF_torque(2);
}

void mouth_process(){
  Dxl.writeWord(4,25,5);
}

void turnON_torque(){
  Dxl.writeWord(1,24,1);
  Dxl.writeWord(2,24,1);
  DxlEx.writeWord(1,24,1);
  DxlEx.writeWord(4,24,1);
  delay(1000);
}

void turnOFF_torque(int id){
  
  Dxl.writeWord(1,24,0);
  Dxl.writeWord(2,24,0);
  DxlEx.writeWord(1,24,0);
  DxlEx.writeWord(4,24,0);
  delay(200);
  if(id == 1){
    Dxl.writeWord(4,30,512);
  }
  else if(id == 2){
    Dxl.writeWord(4,30,490); 
  }
  
}

void setup(){
  DxlEx.begin(3);
  Dxl.begin(1);
  pinMode(BOARD_LED_PIN,OUTPUT);
  digitalWrite(BOARD_LED_PIN,1);
  Serial2.begin(57600);
  delay(500);
  LEDS_off();
  SLOW_velocity();
  ON_Position();
  delay(2000);
  /*Experimental*/
  //turnOFF_torque(1);
  
}

void loop(){

  if(wall){
    SerialUSB.print("Enter to new loop!");
    //password_wall();
  }
  else{
    if(Serial2.available()){
      Data_Received = Serial2.read();
      if(Data_Received!=0){
        if(Data_Received=='2'){
        }
        else if(Data_Received=='w' && isFriend == true){
          MakerFaire_Demo();
          delay(350);
        }
        else if(Data_Received=='a'&& isFriend == true){
        }  
        else if(Data_Received=='b'&& isFriend == true){
        }
        else if(Data_Received=='c'&& isFriend == true){
          Feeding_Init();
        }
        else if(Data_Received=='t'&& isFriend == true){
        }
        else if(Data_Received=='o'&& isFriend == true){
        }
        else if(Data_Received=='y'&& isFriend == true){
          DxlEx.writeWord(1,25,2);
          delay(100);
          DxlEx.writeWord(1,25,0);
          int pos = DxlEx.readWord(1,36);
          if(pos<=300){
            DxlEx.writeWord(1,30,300);
          }
          else{
            DxlEx.writeWord(1,30,pos-50);
          }
        }
        else if(Data_Received=='z'&& isFriend == true){
          DxlEx.writeWord(4,25,2);
          delay(100);
          DxlEx.writeWord(4,25,0);
          int pos = DxlEx.readWord(4,36);
          if(pos<=250){
            DxlEx.writeWord(4,30,250);
          }
          else{
            DxlEx.writeWord(4,30,pos-50);
          }

        }
        else if(Data_Received=='f'&& isFriend == true){
          DxlEx.writeWord(4,25,2);
          delay(100);
          DxlEx.writeWord(4,25,0);
          int pos = DxlEx.readWord(4,36);
          if(pos>=500){
            DxlEx.writeWord(4,30,500);
          }
          else{
            DxlEx.writeWord(4,30,pos+50);
          }
        }
        else if(Data_Received=='g'&& isFriend == true){
          DxlEx.writeWord(1,25,2);
          delay(100);
          DxlEx.writeWord(1,25,0);
          int pos = DxlEx.readWord(1,36);
          if(pos>=700){
            DxlEx.writeWord(1,30,700);
          }
          else{
            DxlEx.writeWord(1,30,pos+50);
          }
        }
        else if(Data_Received=='p'&& isFriend == true){
          //bowl_process();
        }
        else if(Data_Received=='q'&& isFriend == true){
          //mouth_process();
        }
        else if(Data_Received=='m'&& isFriend == true){

        }
        else if(Data_Received=='h'&& isFriend == true){
          DxlEx.writeWord(2,25,2);
          delay(100);
          DxlEx.writeWord(2,25,0);
          int pos = DxlEx.readWord(2,36);
          if(pos>=500){
            DxlEx.writeWord(2,30,500);
          }
          else{
            DxlEx.writeWord(2,30,pos+50);
          }
        }
        else if(Data_Received=='n'&& isFriend == true){
          DxlEx.writeWord(2,25,2);
          delay(100);
          DxlEx.writeWord(2,25,0);
          int pos = DxlEx.readWord(2,36);
          if(pos<=50){
            DxlEx.writeWord(2,30,50);
          }
          else{
            DxlEx.writeWord(2,30,pos-50);
          }
        }
        else if(Data_Received=='x'&& isFriend == true){
        }

      }
    }
  }
}

