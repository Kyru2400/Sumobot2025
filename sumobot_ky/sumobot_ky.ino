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
#define NUM_SAMPLES 16

uint16_t score = 0;

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

  // float LeftDistance = getSharpIR_Distance(SharpIR_Left_Pin);
  // float RightDistance = getSharpIR_Distance(SharpIR_Right_Pin);
  // float CenterDistance = getSharpIR_Distance(SharpIR_Center_Pin);

  // if (isnan(LeftDistance)) {
  //   Serial.println(F("Distance Left: ---"));
  // } else {
  //   Serial.print(F("Distance Left: "));
  //   Serial.print(LeftDistance, 1);
  //   Serial.println(F(" cm"));
  // }

  // if (isnan(RightDistance)) {
  //   Serial.println(F("Distance Right: ---"));
  // } else {
  //   Serial.print(F("Distance Right: "));
  //   Serial.print(RightDistance, 1);
  //   Serial.println(F(" cm"));
  // }

  // if (isnan(CenterDistance)) {
  //   Serial.println(F("Distance Right: ---"));
  // } else {
  //   Serial.print(F("Distance Center: "));
  //   Serial.print(CenterDistance, 1);
  //   Serial.println(F(" cm"));
  // }

  Robot_Forward();
  while (1) {
    if (!Status_IR_Right() && !Status_IR_Left()) {
      score++;
    }

    if (Status_IR_Right() && Status_IR_Left()) {
      score = 0;
    }

    if (score > 10) {
      goto exit_forward_loop;
    }
    delay(5);
  }
exit_forward_loop:

  Robot_Backward();
  delay(600);
  Robot_Stop();
  delay(100);
  Robot_TurnRight();
  delay(150);
}