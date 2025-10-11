// GP2Y0A21YK0F (10–80 cm) -> ESP32 GPIO36 (ADC1_CH0)
// Arduino-ESP32 3.x compatible (no adcAttachPin)

#include <math.h>

#define SharpIR_Left_Pin 36  // GPIO36 / VP (input-only)
#define SharpIR_Right_Pin 39
#define NUM_SAMPLES 16

// Convert sensor voltage (V) to distance (cm) via empirical fit.
// Calibrate k, n for your exact unit if you want tighter accuracy.


void setup() {
  Serial.begin(115200);
  delay(200);

  SharpIR_Setup();
}

void loop() {
  float LeftDistance = getSharpIR_Distance(SharpIR_Left_Pin);
  float RightDistance = getSharpIR_Distance(SharpIR_Right_Pin);

  if (isnan(LeftDistance)) {
    Serial.println(F("Distance Left: ---"));
  } else {
    Serial.print(F("Distance Left: "));
    Serial.print(LeftDistance, 1);
    Serial.println(F(" cm"));
  }

  if (isnan(RightDistance)){
    Serial.println(F("Distance Right: ---"));
  } else {
    Serial.print(F("Distance Right: "));
    Serial.print (RightDistance, 1);
    Serial.println(F(" cm"));
  }
}
