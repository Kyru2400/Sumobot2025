

void SharpIR_Setup() {
  // Prefer per-pin attenuation if present in your core:
#if defined(ARDUINO_ARCH_ESP32)
  // Try per-pin API; if your core lacks it, comment the next line and
  // keep the global analogSetAttenuation call below.
  analogSetPinAttenuation(SharpIR_Left_Pin, ADC_11db);
  analogSetPinAttenuation (SharpIR_Right_Pin, ADC_11db);
#endif

  // Global fallback (safe even if per-pin is used above)
  analogSetAttenuation(ADC_11db);

  // Default width is 12 bits on ESP32; keep it unless you changed it elsewhere.
  // analogSetWidth(12);

  Serial.println(F("ESP32 + GP2Y0A21YK0F distance (cm)"));
}

float getSharpIR_Distance(int PinToUse) {
  // Average a handful of mV readings for stability
  uint32_t sum_mV = 0;
  for (int i = 0; i < NUM_SAMPLES; ++i) {
    sum_mV += analogReadMilliVolts(PinToUse);  // ESP32 API
    delayMicroseconds(500);
  }
  const float mv = sum_mV * 1.0f / NUM_SAMPLES;
  const float v = mv / 1000.0f;

  const float cm = voltsToCm(v);

  delay(100);

  return cm;
}

static inline float voltsToCm(float v) {
  if (v < 0.05f) return NAN;  // ignore near-zero
  const float k = 27.728f;
  const float n = -1.2045f;  // d ≈ 27.728 * v^-1.2045
  float d = k * powf(v, n);
  if (d < 10.0f) d = 10.0f;  // clamp to usable range
  if (d > 80.0f) d = 80.0f;
  return d;
}