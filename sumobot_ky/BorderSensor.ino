#define IR_Right_Pin 14
#define IR_Left_Pin 15

void IR_Setup() {
  pinMode(IR_Right_Pin, INPUT_PULLUP);
  pinMode(IR_Left_Pin, INPUT_PULLUP);

}

bool Status_IR_Right(){
  return digitalRead(IR_Right_Pin);
}

bool Status_IR_Left(){
  return digitalRead(IR_Left_Pin);
}

