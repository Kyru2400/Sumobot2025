// void ISR_Setup() {

//   cli();  // Disable global interrupts

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

//   sei();  // enable interrupts
// }


// ISR(TIMER2_COMPA_vect) {
//   // timer2 interrupt 8kHz

//   cli();  //disable all interrupts

//   sei();  //enable all interrupts
// }