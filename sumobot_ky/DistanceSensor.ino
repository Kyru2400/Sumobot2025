

void DistanceSensor_Setup() {
  // Prefer per-pin attenuation if present in your core:
#if defined(ARDUINO_ARCH_ESP32)
  // Try per-pin API; if your core lacks it, comment the next line and
  // keep the global analogSetAttenuation call below.
  analogSetPinAttenuation(SharpIR_Left_Pin, ADC_11db);
  analogSetPinAttenuation (SharpIR_Right_Pin, ADC_11db);
  analogSetPinAttenuation (SharpIR_Center_Pin, ADC_11db);
#endif

  // Global fallback (safe even if per-pin is used above)
  analogSetAttenuation(ADC_11db);

  // Default width is 12 bits on ESP32; keep it unless you changed it elsewhere.
  // analogSetWidth(12);

  Serial.println(F("ESP32 + GP2Y0A21YK0F distance (cm)"));
}

float getSharpIR_Distance(int PinToUse, bool SharpIR_Variant) {
  const int NUM_SAMPLES = 16;
  uint32_t sum = 0;

  for (int i = 0; i < NUM_SAMPLES; i++) {
    sum += analogReadMilliVolts(PinToUse);
    delayMicroseconds(300);
  }

  float mv = sum / (float)NUM_SAMPLES;
  float v  = mv / 1000.0f;

  float cm = voltsToCm(v, SharpIR_Variant);
  if (isnan(cm)) return -1.0f;   // return -1 if invalid reading
  return cm;
}


// Converts voltage (in V) to distance (in cm) for 30 cm or 80 cm Sharp IR
static inline float voltsToCm(float v, bool WhichVariant) {
  // LUT for GP2Y0A41SK0F (4–30 cm)
  static const float lut30_v[]  = {3.10, 2.50, 1.95, 1.60, 1.30, 1.05, 0.90, 0.78, 0.70, 0.62, 0.56, 0.50, 0.45};
  static const float lut30_cm[] = {4.0,  5.0,  7.0,  9.0, 10.0, 12.0, 15.0, 18.0, 20.0, 22.0, 25.0, 27.0, 30.0};
  const int LUT30_LEN = sizeof(lut30_v)/sizeof(lut30_v[0]);

  // LUT for GP2Y0A21YK0F (10–80 cm)
  static const float lut80_v[]  = {3.00, 2.40, 1.85, 1.50, 1.20, 1.00, 0.86, 0.80, 0.72, 0.66, 0.60, 0.55, 0.51, 0.48, 0.46, 0.44};
  static const float lut80_cm[] = {10.0, 12.0, 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0, 50.0, 55.0, 60.0, 65.0, 70.0, 75.0, 80.0};
  const int LUT80_LEN = sizeof(lut80_v)/sizeof(lut80_v[0]);

  // Select which model you're using:
  const bool use30cm = WhichVariant;  // <-- set to true for 30 cm variant, false for 80 cm variant

  const float* lut_v  = use30cm ? lut30_v  : lut80_v;
  const float* lut_cm = use30cm ? lut30_cm : lut80_cm;
  const int n = use30cm ? LUT30_LEN : LUT80_LEN;

  if (v < 0.05f) return NAN;
  if (v >= lut_v[0])   return lut_cm[0];
  if (v <= lut_v[n - 1]) return lut_cm[n - 1];

  // Find where voltage fits and interpolate
  for (int i = 0; i < n - 1; i++) {
    if (v <= lut_v[i] && v >= lut_v[i + 1]) {
      float t = (v - lut_v[i + 1]) / (lut_v[i] - lut_v[i + 1]);
      return lut_cm[i + 1] + t * (lut_cm[i] - lut_cm[i + 1]);
    }
  }
  return NAN;
}
