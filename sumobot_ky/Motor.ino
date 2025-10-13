
#define Left_Enable 23
#define Left_Input1 25
#define Left_Input2 26

#define Right_Enable 27
#define Right_Input1 18
#define Right_Input2 19

void RightMotor_Stop() {
  analogWrite(Right_Enable, 0);
  digitalWrite(Right_Input1, 0);
  digitalWrite(Right_Input2, 0);
}

void LeftMotor_Stop() {
  analogWrite(Left_Enable, 0);
  digitalWrite(Left_Input1, 0);
  digitalWrite(Left_Input2, 0);
}


void RightMotor_Backward() {
  analogWrite(Right_Enable, Motor_Speed);
  digitalWrite(Right_Input1, 1);
  digitalWrite(Right_Input2, 0);
}

void LeftMotor_Backward() {
  analogWrite(Left_Enable, Motor_Speed);
  digitalWrite(Left_Input1, 0);
  digitalWrite(Left_Input2, 1);
}

void LeftMotor_Forward() {
  analogWrite(Left_Enable, Motor_Speed);
  digitalWrite(Left_Input1, 1);
  digitalWrite(Left_Input2, 0);
}

void RightMotor_Forward() {
  analogWrite(Right_Enable, Motor_Speed);
  digitalWrite(Right_Input1, 0);
  digitalWrite(Right_Input2, 1);
}

void Robot_TurnLeft() {
  RightMotor_Forward();
  LeftMotor_Backward();
}

void Robot_TurnRight() {
  LeftMotor_Forward();
  RightMotor_Backward();
}

void Robot_Forward() {
  LeftMotor_Forward();
  RightMotor_Forward();
}

void Robot_Backward() {
  LeftMotor_Backward();
  RightMotor_Backward();
}

void Robot_Stop() {
  LeftMotor_Stop();
  RightMotor_Stop();
}

void Motor_Setup() {
  pinMode(Left_Enable, OUTPUT);
  pinMode(Left_Input1, OUTPUT);
  pinMode(Left_Input2, OUTPUT);

  pinMode(Right_Enable, OUTPUT);
  pinMode(Right_Input1, OUTPUT);
  pinMode(Right_Input2, OUTPUT);

  analogWrite(Left_Enable, 0);
  digitalWrite(Left_Input1, 0);
  digitalWrite(Left_Input2, 0);
  analogWrite(Right_Enable, 0);
  digitalWrite(Right_Input1, 0);
  digitalWrite(Right_Input2, 0);
}