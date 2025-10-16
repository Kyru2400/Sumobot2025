
#include <SharpIR.h>

#define SharpIR_Center_Pin A0
#define SharpIR_Left_Pin A1
#define SharpIR_Right_Pin A2

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
  Border_Sensor_Setup();
}

void loop()
{
  Update_Distance();
  Serial.print("Center: ");
  Serial.print(Distance_Center);
  Serial.print(" cm, Left: ");
  Serial.print(Distance_Left);
  Serial.print(" cm, Right: ");
  Serial.print(Distance_Right);
  Serial.println(" cm");

  Serial.print("Border Left: ");
  Serial.print(ReadBorderSensorLeft());
  Serial.print(", Border Right: ");
  Serial.println(ReadBorderSensorRight());

  delay(500); //Wait 500 milliseconds before the next reading
}
