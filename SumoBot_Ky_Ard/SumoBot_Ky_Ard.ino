
#include <SharpIR.h>

#define SharpIR_Center_Pin A0
#define SharpIR_Left_Pin A1
#define SharpIR_Right_Pin A2

#define MotorLeft_EnablePin 6
#define MotorLeft_DirPin1 7
#define MotorLeft_DirPin2 8

#define MotorRight_EnablePin 9
#define MotorRight_DirPin1 10
#define MotorRight_DirPin2 11

#define Button_Calibration_Pin 4
#define Default_LED_Pin 13

SharpIR DistanceSensor_Center(SharpIR::GP2Y0A21YK0F, SharpIR_Center_Pin);
SharpIR DistanceSensor_Left(SharpIR::GP2Y0A21YK0F, SharpIR_Left_Pin);
SharpIR DistanceSensor_Right(SharpIR::GP2Y0A21YK0F, SharpIR_Right_Pin);

int Distance_Center = 0;
int Distance_Left = 0;
int Distance_Right = 0;

#define BorderSensor_Left_Pin 2
#define BorderSensor_Right_Pin 3

bool BorderReached = false;
bool EnemyFound = false;
bool Attacking = false;

uint8_t AttackingDistance = 20;

uint8_t SensedBorder = 0;  //0=Null 1=Left 2=Right 3=both

uint32_t AttackingInterval = 1200;
uint32_t LastAttack = 0;

void setup() {
  Serial.begin(9600);  //Enable the serial comunication
  Serial.println("SumoBot Start...");
  Border_Sensor_Setup();

  Motor_Setup();

  pinMode(Button_Calibration_Pin, INPUT_PULLUP);
  pinMode(Default_LED_Pin, OUTPUT);
  digitalWrite(Default_LED_Pin, LOW);

  if (!digitalRead(Button_Calibration_Pin)) {
    while (1) {
      digitalWrite(Default_LED_Pin, HIGH);
      delay(100);
      digitalWrite(Default_LED_Pin, LOW);
      delay(100);
    }
  }

  for (int i = 0; i < 2; i++) {
    digitalWrite(Default_LED_Pin, HIGH);
    delay(500);
    digitalWrite(Default_LED_Pin, LOW);
    delay(500);
  }

  // ISR_Setup();
}

void loop() {


  Update_Distance();
  if (Distance_Center < AttackingDistance && !Attacking && SensedBorder == 0) {
    Robot_Forward(200);
    Attacking = true;
  }

  if (Distance_Left < AttackingDistance && !Attacking && SensedBorder == 0) {
    Robot_TurnLeft(200);
    delay(30);
  }

  if (Distance_Right < AttackingDistance && !Attacking && SensedBorder == 0) {
    Robot_TurnRight(200);
    delay(30);
  }


  Border_Update();

  switch (SensedBorder) {
    case 1:
      Robot_TurnLeft(200);
      delay(360);
      Robot_Stop();
      LastAttack = millis();
      break;

    case 2:
      Robot_TurnRight(200);
      delay(360);
      Robot_Stop();
      LastAttack = millis();
      break;
    case 3:
      Robot_Backward(200);
      delay(300);
      Robot_Stop();
      LastAttack = millis();
      break;
  }

  if (Attacking) {
    if ((millis() - LastAttack) >= AttackingInterval) {
      Attacking = false;
    }
  }
}
