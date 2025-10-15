/*
Project: Sumobot for NRC
Author: Keith Kyru D. Tuscano
Date: 10/09/25
Version: 1.0
*/
#include <Arduino.h>
#include "ESP32SharpIR.h"

#define Calibration_Button_Pin 22

uint16_t score = 0;
unsigned int Motor_Speed = 160;

bool Attack_Center = false;
bool Attack_Left = false;
bool Attack_Right = false;

uint8_t Attack_Score=0;

void setup() {
  Serial.begin(115200);
  Serial.println("Sumobot Start...");

  Motor_Setup();

  DistanceSensor_setup();

  pinMode(Calibration_Button_Pin, INPUT_PULLUP);

  if (!digitalRead(Calibration_Button_Pin)) {
    while (1)
      ;
  }

  delay(5000);
  Serial.println("GO!");
}



void loop() {
  DistanceSensor_Updated();

  // if (Attack_Left && !Attack_Right && !Attack_Center) {
  //   Serial.println("Turn Left");
  // }else if( Attack_Right && !Attack_Left && !Attack_Center) {
  //   Serial.println("Turn Right");
  // }else if( Attack_Center && !Attack_Left && !Attack_Right) {
  //   Serial.println("Attack");
  //   // Robot_Attack();
  // }
}



void Robot_Attack() {
  Motor_Speed = 160;
  score = 0;
  Robot_Forward();
  while (1) {
    if (!Status_IR_Right() || !Status_IR_Left()) {
      score++;
    }

    if (Status_IR_Right() || Status_IR_Left()) {
      score = 0;
    }

    if (score > 6) {
      goto exit_forward_loop;
    }
    delay(5);
  }
exit_forward_loop:
  delay(10);
  Robot_Stop();
  delay(100);
  Robot_Retreat();
}

void Robot_Retreat() {
  Motor_Speed = 120;
  score = 0;
  Robot_Backward();
  delay(300);
  while(1){
    if(Status_IR_Right() || Status_IR_Left()){
      score++;
    }

    if(!Status_IR_Right() || !Status_IR_Left()){
      score = 0;
    }

    if(score > 6){
      goto exit_backward_loop;
    }
  }
exit_backward_loop:
  delay(10);
  Robot_Stop();
  delay(100);
  
}