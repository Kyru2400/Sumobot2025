/*
Project: Sumobot for NRC
Author: Keith Kyru D. Tuscano
Date: 10/09/25
Version: 1.0
*/


void setup() {
  Serial.begin(115200);
  Serial.println("Sumobot Start...");
  Motor_Setup();
  IR_Setup();

  delay(3000);
}

void loop() {
  while (Status_IR_Right() && Status_IR_Left()) {
    Robot_Forward();
  }

  Robot_Stop();
  delay(100);
  Robot_Backward();
  delay(300);
  Robot_Stop();
  delay(2000);
  Robot_TurnRight();
  delay(300);


  delay(1000);
}