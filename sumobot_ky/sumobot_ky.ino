/*
Project: Sumobot for NRC
Author: Keith Kyru D. Tuscano
Date: 10/09/25
Version: 1.0
*/

#include <math.h>

#define Calibration_Button_Pin 22

#define SharpIR_Left_Pin 36
#define SharpIR_Right_Pin 39
#define SharpIR_Center_Pin 33
// #define NUM_SAMPLES 16

uint16_t score = 0;
unsigned int Motor_Speed = 160;

void setup() {
  Serial.begin(115200);
  Serial.println("Sumobot Start...");
  Motor_Setup();
  IR_Setup();
  DistanceSensor_Setup();

  pinMode(Calibration_Button_Pin, INPUT_PULLUP);

  if (!digitalRead(Calibration_Button_Pin)) {
    while (1)
      ;
  }

  delay(5000);
}

void loop() {

  if (isnan(getSharpIR_Distance(SharpIR_Left_Pin, true))) {
    Serial.println(F("Distance Left: ---"));
  } else {
    Serial.print(F("Distance Left: "));
    Serial.print(getSharpIR_Distance(SharpIR_Left_Pin, true), 1);
    Serial.println(F(" cm"));
  }

  if (isnan(getSharpIR_Distance(SharpIR_Right_Pin, true))) {
    Serial.println(F("Distance Right: ---"));
  } else {
    Serial.print(F("Distance Right: "));
    Serial.print(getSharpIR_Distance(SharpIR_Right_Pin, true), 1);
    Serial.println(F(" cm"));
  }

  if (isnan(getSharpIR_Distance(SharpIR_Center_Pin, false))) {
    Serial.println(F("Distance Right: ---"));
  } else {
    Serial.print(F("Distance Center: "));
    Serial.print(getSharpIR_Distance(SharpIR_Center_Pin, false), 1);
    Serial.println(F(" cm"));
  }

  if (getSharpIR_Distance(SharpIR_Right_Pin, true) < 15.0) {
    while (getSharpIR_Distance(SharpIR_Center_Pin, false) > 30.0) {
      Robot_TurnRight();
    }
    Robot_Attack();
    Robot_Retreat();
  } else if (getSharpIR_Distance(SharpIR_Left_Pin, true) < 15.0) {
    while (getSharpIR_Distance(SharpIR_Center_Pin, false) > 30.0) {
      Robot_TurnLeft();
    }
    Robot_Attack();
    Robot_Retreat();
  } else if (getSharpIR_Distance(SharpIR_Center_Pin, false) > 30.0) {
    Robot_Attack();
    Robot_Retreat();
  } else {
    Robot_TurnRight();
  }
}

void Robot_Attack() {
  Motor_Speed = 255;
  Robot_Forward();
  while (1) {
    if (!Status_IR_Right() || !Status_IR_Left()) {
      score++;
    }

    if (Status_IR_Right() || Status_IR_Left()) {
      score = 0;
    }

    if (score > 3) {
      goto exit_forward_loop;
    }
    delay(5);
  }
exit_forward_loop:
  delay(10);
}

void Robot_Retreat() {
  Motor_Speed = 180;
  Robot_Backward();
  delay(1000);
}