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
#define SharpIR_Center_Pin 34
// #define NUM_SAMPLES 16

uint16_t score = 0;
unsigned int Motor_Speed = 160;

void setup() {
  Serial.begin(115200);
  Serial.println("Sumobot Start...");
  Motor_Setup();
  IR_Setup();
  // DistanceSensor_Setup();

  pinMode(Calibration_Button_Pin, INPUT_PULLUP);

  if (!digitalRead(Calibration_Button_Pin)) {
    while (1)
      ;
  }

  delay(5000);
}

unsigned int Dist_Mid = 0;
unsigned int Dist_Right = 0;
unsigned int Dist_Left = 0;

void loop() {
  //   Serial.println("SharpIR Mid:" + String(getSharpIR_Analog(SharpIR_Center_Pin)));
  //   Serial.println("SharpIR Right:" + String(getSharpIR_Analog(SharpIR_Right_Pin)));
  //   Serial.println("SharpIR Left:" + String(getSharpIR_Analog(SharpIR_Left_Pin)));
  //   delay (1000);
  Dist_Mid = get_This_Distance(SharpIR_Center_Pin);
  Dist_Right = get_This_Distance(SharpIR_Right_Pin);
  Dist_Left = get_This_Distance(SharpIR_Left_Pin);

    Serial.println("SharpIR Mid:" + String(Dist_Mid));
    delay (1000);


  if (Dist_Mid > 450 && Dist_Mid != 0) {
    Serial.println("Attack Mid!");
  }

  if (Dist_Right > 1650 && Dist_Right != 0) {
    Serial.println("Attack Right!");
  }

  if (Dist_Left > 1450 && Dist_Left != 0) {
    Serial.println("Attack Left!");
  }
}

unsigned int get_This_Distance(int ThisPin) {
  uint32_t ThisDistance = 0;
  for (int i = 0; i < 3; i++) {
    ThisDistance = ThisDistance + getSharpIR_Analog(ThisPin);
  }
  return ThisDistance / 3;
}


void Robot_Attack() {
  Motor_Speed = 200;
  Robot_Forward();
  while (1) {
    if (!Status_IR_Right() && !Status_IR_Left()) {
      score++;
    }

    if (Status_IR_Right() && Status_IR_Left()) {
      score = 0;
    }

    if (score > 6) {
      goto exit_forward_loop;
    }
    delay(5);
  }
exit_forward_loop:
  delay(10);
  Robot_Retreat();
}

void Robot_Retreat() {
  Motor_Speed = 180;
  Robot_Backward();
  delay(600);
}