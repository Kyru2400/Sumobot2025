void ISR_Setup() {

  cli();  // Disable global interrupts

  //############# SET TIMER1 to 8kHz ############
  //Reset Timer1 registers
  TCCR1A = 0;  // Clear Timer1 Control Registers
  TCCR1B = 0;
  TCNT1 = 0;  // Reset counter

  OCR1A = 1999;             // Set compare match register for 8kHz
  TCCR1B |= (1 << WGM12);   // Enable CTC mode
  TCCR1B |= (1 << CS10);    // Prescaler = 1
  TIMSK1 |= (1 << OCIE1A);  // Enable Timer1 compare A match interrupt
  //############### END TIMER2 ##################

//   //############# SET TIMER2 to 8kHz ############
//   //Reset Timer2 registers
//   TCCR2A = 0;
//   TCCR2B = 0;
//   TCNT2 = 0;
//   OCR2A = 249;
//   TCCR2A |= (1 << WGM21);
//   TCCR2B |= (1 << CS21);
//   TIMSK2 |= (1 << OCIE2A);
//   //############### END TIMER2 ##################

  sei();  // enable interrupts
}



//Interrupt for Border Sensor
ISR(TIMER1_COMPA_vect) {
  cli();  //disable all interrupts
  if (ReadBorderSensorLeft() && ReadBorderSensorRight() &&  !BorderReached) {
    BorderReached = true;
    EnemyFound = false;
    Robot_Backward(255);
    Robot_Stop();
  }
  sei();  //enable all interrupts
}

// // Interrupt for Distance Sensor
// ISR(TIMER2_COMPA_vect) {
//   // timer2 interrupt 8kHz

// //   cli();  //disable all interrupts
//   Update_Distance();
//   if (Distance_Left < 30 && Distance_Right > 30 && Distance_Center > 30 && !Attacking && !BorderReached) {
// //Serial.println("Enemy to the Left");
//     Robot_TurnLeft(255);
//     while (Distance_Center > 30) {
//       Update_Distance();
//     }
//     Robot_Stop();
//     EnemyFound = true;
//     Robot_Forward(255);
//   } else if (Distance_Right < 30 && Distance_Left > 30 && Distance_Center > 30 && !Attacking && !BorderReached) {
//     //Serial.println("Enemy to the Right");
//     Robot_TurnRight(255);
//     while (Distance_Center > 30) {
//       Update_Distance();
//     }
//     Robot_Stop();
//     EnemyFound = true;
//     Robot_Forward(255);
//   }else if(Distance_Center <30 && !Attacking && !BorderReached){
//     EnemyFound = true;
//     Robot_Forward(255);
//   }else if(Distance_Center >30 && Distance_Left >30 && Distance_Right >30 && !Attacking){
//     EnemyFound = false;
//   }
// //   sei();  //enable all interrupts
// }