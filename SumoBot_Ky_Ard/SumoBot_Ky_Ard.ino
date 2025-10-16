
#include <SharpIR.h>

#define SharpIR_Center_Pin A0
#define SharpIR_Left_Pin A1
#define SharpIR_Right_Pin A2

SharpIR DistanceSensor_Center( SharpIR::GP2Y0A21YK0F, SharpIR_Center_Pin );
SharpIR DistanceSensor_Left( SharpIR::GP2Y0A21YK0F, SharpIR_Left_Pin );
SharpIR DistanceSensor_Right( SharpIR::GP2Y0A21YK0F, SharpIR_Right_Pin );

void setup()
{
  Serial.begin( 9600 ); //Enable the serial comunication
}

void loop()
{
  int distance_center = DistanceSensor_Center.getDistance(); //Calculate the distance in centimeters and store the value in a variable
  int distance_left = DistanceSensor_Left.getDistance();
  int distance_right = DistanceSensor_Right.getDistance();

  Serial.print("Center: ");
  Serial.print(distance_center);
  Serial.print(" cm, Left: ");
  Serial.print(distance_left);
  Serial.print(" cm, Right: ");
  Serial.print(distance_right);
  Serial.println(" cm");

  delay(500); //Wait 500 milliseconds before the next reading
}
