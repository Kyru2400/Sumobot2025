#include <Arduino.h>
#include "ESP32SharpIR.h"

// Pins (ADC1)
#define PIN_LEFT    36
#define PIN_RIGHT   39
#define PIN_CENTER  33

// Models (change if your hardware differs)
ESP32SharpIR irLeft  (ESP32SharpIR::GP2Y0A21YK0F, PIN_LEFT);   // 10–80 cm
ESP32SharpIR irRight (ESP32SharpIR::GP2Y0A21YK0F, PIN_RIGHT);  // 10–80 cm
ESP32SharpIR irCenter(ESP32SharpIR::GP2Y0A41SK0F, PIN_CENTER); // 4–30 cm

void setup() {
  Serial.begin(115200);
  delay(200);

  // Init ADC & pins (0–3.3 V span)
  irLeft.begin(ADC_11db);
  irRight.begin(ADC_11db);
  irCenter.begin(ADC_11db);

  // Pace & smoothing (tweak as needed)
  irLeft.setMinInterval(30);
  irRight.setMinInterval(30);
  irCenter.setMinInterval(30);

  irLeft.setSamples(4, 3);
  irRight.setSamples(4, 3);
  irCenter.setSamples(4, 3);

  irLeft.setFilterRate(0.25f);
  irRight.setFilterRate(0.25f);
  irCenter.setFilterRate(0.25f);

  Serial.println(F("ESP32 + 3x Sharp IR (simple poll/print)"));
}

static inline void printIfUpdated(const char* tag, ESP32SharpIR& s) {
  if (!s.poll()) return;              // no new sample yet
  uint8_t u = s.lastRaw();
  float   f = s.last();

  // Unified out-of-range messages
  if (u < 20) {
    Serial.printf("%s: TOO NEAR  [%.1f cm]\n", tag, f);
  } else if (u == 31 || u == 81 || u == 151) {
    Serial.printf("%s: TOO FAR   [%.1f cm]\n", tag, f);
  } else {
    Serial.printf("%s: %u cm  (%.1f)\n", tag, u, f);
  }
}

void loop() {
  printIfUpdated("Left  ",  irLeft);
  printIfUpdated("Right ",  irRight);
  printIfUpdated("Center",  irCenter);
  delay(2); // tiny breather
}
