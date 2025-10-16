
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

SharpIR DistanceSensor_Center( SharpIR::GP2Y0A21YK0F, SharpIR_Center_Pin );
SharpIR DistanceSensor_Left( SharpIR::GP2Y0A21YK0F, SharpIR_Left_Pin );
SharpIR DistanceSensor_Right( SharpIR::GP2Y0A21YK0F, SharpIR_Right_Pin );

int Distance_Center = 0;
int Distance_Left = 0;
int Distance_Right = 0;

#define BorderSensor_Left_Pin 2
#define BorderSensor_Right_Pin 3

void setup()
{
  Serial.begin( 9600 ); //Enable the serial comunication
  Serial.println("SumoBot Start...");
  Border_Sensor_Setup();

  Motor_Setup();

  pinMode(Button_Calibration_Pin, INPUT_PULLUP);
  pinMode(Default_LED_Pin, OUTPUT);
  digitalWrite(Default_LED_Pin, LOW);

  if(!digitalRead(Button_Calibration_Pin)){
    while(1){
    digitalWrite(Default_LED_Pin, HIGH);
    delay(100);
    digitalWrite(Default_LED_Pin, LOW);
    delay(100);
    }
  }

  for(int i=0; i<10; i++){
    digitalWrite(Default_LED_Pin, HIGH);
    delay(500);
    digitalWrite(Default_LED_Pin, LOW);
    delay(500);
  }


}

void loop(){
    MotorLeft_Forward(255);
  MotorRight_Forward(255);

  delay(2000);
  Robot_Stop();
  delay(1000);

  MotorLeft_Backward(255);
  MotorRight_Backward(255);
  delay(2000);
  Robot_Stop();
  delay(1000);

  // Update_Distance();
  // Serial.print("Center: ");
  // Serial.print(Distance_Center);
  // Serial.print(" cm, Left: ");
  // Serial.print(Distance_Left);
  // Serial.print(" cm, Right: ");
  // Serial.print(Distance_Right);
  // Serial.println(" cm");

  // Serial.print("Border Left: ");
  // Serial.print(ReadBorderSensorLeft());
  // Serial.print(", Border Right: ");
  // Serial.println(ReadBorderSensorRight());

  // delay(500); //Wait 500 milliseconds before the next reading
}
