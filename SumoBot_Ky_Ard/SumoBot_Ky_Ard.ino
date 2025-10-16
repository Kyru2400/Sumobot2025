
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

  for (int i = 0; i < 5; i++) {
    digitalWrite(Default_LED_Pin, HIGH);
    delay(500);
    digitalWrite(Default_LED_Pin, LOW);
    delay(500);
  }

  ISR_Setup();
}

void loop() {

  if (BorderReached) {
    Robot_Stop();
    delay(600);
    Robot_Backward(255);
    delay(500);
    uint8_t check = 0;
    while (ReadBorderSensorLeft() || ReadBorderSensorRight()) {
      delay(100);
      check++;
      if(check>=15){
        break;
      }
    }
    Robot_Stop();
    delay(300);
    BorderReached = false;
    Robot_TurnRight(255);
    delay(600);
    Robot_Stop();
    Attacking = false;
  } else {
    Update_Distance();
    if (Distance_Left < 30 && Distance_Right > 30 && Distance_Center > 30 && !Attacking && !BorderReached) {
      //Serial.println("Enemy to the Left");
      Robot_TurnLeft(180);
      while (Distance_Center > 30) {
        Update_Distance();
      }
      Robot_Stop();
      EnemyFound = true;
      Robot_Forward(255);
      Attacking = true;
    } else if (Distance_Right < 30 && Distance_Left > 30 && Distance_Center > 30 && !Attacking && !BorderReached) {
      //Serial.println("Enemy to the Right");
      Robot_TurnRight(180);
      while (Distance_Center > 30) {
        Update_Distance();
      }
      Robot_Stop();
      EnemyFound = true;
      Robot_Forward(255);
      Attacking = true;
    } else if (Distance_Center < 30 && !Attacking && !BorderReached) {
      EnemyFound = true;
      Robot_Forward(255);
      Attacking = true;
    } else if (Distance_Center > 30 && Distance_Left > 30 && Distance_Right > 30 && !Attacking && !BorderReached) {
      EnemyFound = false;
      Robot_TurnRight(180);
    }
  }
}
