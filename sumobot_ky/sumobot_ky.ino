/*
Project: Sumobot for NRC
Author: Keith Kyru D. Tuscano
Date: 10/09/25
Version: 1.0
*/

#define Calibration_Button_Pin 22


void setup() {
  Serial.begin(115200);
  Serial.println("Sumobot Start...");
  Motor_Setup();
  IR_Setup();

  pinMode(Calibration_Button_Pin, INPUT_PULLUP);

  if (!digitalRead(Calibration_Button_Pin)) {
    while (1)
      ;
  }

  delay(5000);


}

void loop() {
      Robot_Forward();
  while (Status_IR_Right() && Status_IR_Left()) {

  }

  Robot_Backward();
  delay(300);
  Robot_Stop();
  delay(100);
  Robot_TurnRight();
  delay(150);

}