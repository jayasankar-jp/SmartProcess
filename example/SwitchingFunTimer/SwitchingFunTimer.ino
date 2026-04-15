
#include <SmartProcess.h>
SmartProcess Timer1, Timer2;
void function1()
{
  Serial.println("Function 1 trigger");
}
void function2()
{
  Serial.println("Function 2 trigger");
}
void function3()
{
  Serial.println("Function 3 trigger");
}
void setup()
{
  Serial.begin(9600);
}

int number = 1;
void loop()
{
  Timer1.triggerContinuously(5000, 2000, function1, function2);
  // Timer2.triggerContinuously(10000,3000,function3);
  Serial.println(number++);
  delay(1000);
}
