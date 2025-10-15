void SharpIR_Setup() {
  pinMode(SharpIR_Center_Pin, INPUT_PULLUP);
  pinMode(SharpIR_Right_Pin, INPUT);
  pinMode(SharpIR_Left_Pin, INPUT);
}

unsigned int getSharpIR_Analog(int PinToUse) {
  uint32_t SharpIR_Analog_Now = 0;
  for (uint8_t a = 0; a < 30; a++) {
    // Serial.println("Acount" + String(a));
    SharpIR_Analog_Now = SharpIR_Analog_Now + analogRead(PinToUse);
    delayMicroseconds(90);
  }

  return SharpIR_Analog_Now / 30;
}
