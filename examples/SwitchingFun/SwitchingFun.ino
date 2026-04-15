
#include <SmartProcess.h>
SmartProcess Timer1,Timer2;
void function1(){
  Serial.println("Function 1 trigger");
}
void function2(){
  Serial.println("Function 2 trigger");
}
void setup() {
  Serial.begin(9600);
  Timer1.setTimer(2000);
  Timer2.setTimer(5000);
}

void loop() {
  Timer1.triggerContinuously(function1,function2);
//   Timer2.triggerContinuously();
  Serial.println("Running....");
  delay(250);
}

