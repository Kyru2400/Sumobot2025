void Update_Distance() {
  Distance_Center = DistanceSensor_Center.getDistance();  //Calculate the distance in centimeters and store the value in a variable
  Distance_Left = DistanceSensor_Left.getDistance();
  Distance_Right = DistanceSensor_Right.getDistance();
}