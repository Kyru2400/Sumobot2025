

void Border_Sensor_Setup() {
  pinMode(BorderSensor_Left_Pin, INPUT_PULLUP);
  pinMode(BorderSensor_Right_Pin, INPUT_PULLUP);
}

bool ReadBorderSensorLeft() {
  return !digitalRead(BorderSensor_Left_Pin);  //Reverse the reading because the sensor outputs LOW when it detects the White border
}

bool ReadBorderSensorRight() {
  return !digitalRead(BorderSensor_Right_Pin);  //Reverse the reading because the sensor outputs LOW when it detects the White border
}

void Border_Update() {
  if (ReadBorderSensorLeft() && !ReadBorderSensorRight()) {
    SensedBorder = 1;
  } else if (!ReadBorderSensorLeft() && ReadBorderSensorRight()) {
    SensedBorder = 2;
  } else if (ReadBorderSensorLeft() && ReadBorderSensorRight()) {
    SensedBorder = 3;
  } else {
    SensedBorder = 0;
  }
}