
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
void setup()
{
  Serial.begin(9600);
  Timer1.setTimer(2000);
  Timer2.setTimer(5000);
}

void loop()
{
  if (Serial.available())
  {
    char c = Serial.read();
    if (c == '1')
    {
      Timer1.resetTimer();
    }
    else if (c == '2')
    {
      Timer2.resetTimer();
    }
  }
  Timer1.TriggerDelay(function1, 5000);
  Timer2.TriggerDelay(function2, 2500);
  Serial.println("Running....");
  delay(250);
}
