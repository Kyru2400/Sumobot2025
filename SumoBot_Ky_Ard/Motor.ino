void Motor_Setup(){
  pinMode(MotorLeft_EnablePin, OUTPUT);
  pinMode(MotorLeft_DirPin1, OUTPUT);
  pinMode(MotorLeft_DirPin2, OUTPUT);

  pinMode(MotorRight_EnablePin, OUTPUT);
  pinMode(MotorRight_DirPin1, OUTPUT);
  pinMode(MotorRight_DirPin2, OUTPUT);

  Robot_Stop(); //Make sure the robot is stopped when the motors are initialized
}

void MotorLeft_Stop(){
  analogWrite(MotorLeft_EnablePin, 0);
  digitalWrite(MotorLeft_DirPin1, 0);
  digitalWrite(MotorLeft_DirPin2, 0);
}

void MotorRight_Stop(){
  analogWrite(MotorRight_EnablePin, 0);
  digitalWrite(MotorRight_DirPin1, 0);
  digitalWrite(MotorRight_DirPin2, 0);
}

void Robot_Stop(){
  MotorLeft_Stop();
  MotorRight_Stop();
}

void MotorLeft_Forward(int speed){
  if(speed < 0) speed = 0;
  if(speed > 255) speed = 255;
  analogWrite(MotorLeft_EnablePin, speed);
  digitalWrite(MotorLeft_DirPin1, 0);
  digitalWrite(MotorLeft_DirPin2, 1);
}

void MotorLeft_Backward(int speed){
  if(speed < 0) speed = 0;
  if(speed > 255) speed = 255;
  analogWrite(MotorLeft_EnablePin, speed);
  digitalWrite(MotorLeft_DirPin1, 1);
  digitalWrite(MotorLeft_DirPin2, 0);
}

void MotorRight_Forward(int speed){
  if(speed < 0) speed = 0;
  if(speed > 255) speed = 255;
  analogWrite(MotorRight_EnablePin, speed);
  digitalWrite(MotorRight_DirPin1, 0);
  digitalWrite(MotorRight_DirPin2, 1);
}

void MotorRight_Backward(int speed){
  if(speed < 0) speed = 0;
  if(speed > 255) speed = 255;
  analogWrite(MotorRight_EnablePin, speed);
  digitalWrite(MotorRight_DirPin1, 1);
  digitalWrite(MotorRight_DirPin2, 0);
}