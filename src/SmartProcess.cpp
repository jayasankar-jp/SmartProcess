#include "SmartProcess.h"

void SmartProcess::setTimer(const unsigned long &timer)
{
    this->timer = timer;
}
unsigned long SmartProcess::getTimer()
{
    return initialTime;
}

void SmartProcess::TriggerDelay(void (*callback)(void), unsigned long delayTime)
{
    timer = delayTime;
    if (!FunEn)
        return;
    else if (!isCalled)
    {

        if (millis() - initialTime >= timer)
        {
            initialTime = millis();
            callback();
            isCalled = true;
        }
    }
}
void SmartProcess::triggerContinuously(unsigned long time2, unsigned long time1, void (*callback_1)(void), void (*callback_2)(void) = nullptr)
{
#ifdef __DEBUG_E__
    Serial.print("Initial Time fun start : ");
    Serial.println(initialTime);
#endif
    if (!FunEn)
        return;
    if ((selector == 0 ? time1 : time2) == 0)
    {
#ifdef __DEBUG_E__
        Serial.println("Call 1");
#endif
        selector == 0 ? callback_1() : callback_2 ? callback_2()
                                                  : callback_1();
        selector = (selector + 1) % 2;
    }
    else if (initialTime == 0)
    {
        delay(10);
        // callback();
        selector == 0 ? callback_1() : callback_2 ? callback_2()
                                                  : callback_1();
        selector = (selector + 1) % 2;
        initialTime = millis();

#ifdef __DEBUG_E__
        Serial.println("Call 2");
        Serial.print("Initial Time : ");
        Serial.println(initialTime);

#endif
    }
    else if (millis() - initialTime >= (selector == 0 ? time1 : time2))
    {
#ifdef __DEBUG_E__
        Serial.println("Call 3");
#endif
        // callback();
        selector == 0 ? callback_1() : callback_2 ? callback_2()
                                                  : callback_1();
        selector = (selector + 1) % 2;
        initialTime = millis();
    }
}

void SmartProcess::triggerContinuously(void (*callback_1)(void), void (*callback_2)(void))
{
#ifdef __DEBUG_E__
    Serial.print("Initial Time fun start : ");
    Serial.println(initialTime);
#endif
    if (!FunEn)
        return;
    if (timer == 0)
    {
#ifdef __DEBUG_E__
        Serial.println("Call 1");
#endif
        selector == 0 ? callback_1() : callback_2();
        selector = (selector + 1) % 2;
    }
    else if (initialTime == 0)
    {
        delay(10);
        // callback();
        selector == 0 ? callback_1() : callback_2();
        selector = (selector + 1) % 2;
        initialTime = millis();

#ifdef __DEBUG_E__
        Serial.println("Call 2");
        Serial.print("Initial Time : ");
        Serial.println(initialTime);

#endif
    }
    else if (millis() - initialTime >= timer)
    {
#ifdef __DEBUG_E__
        Serial.println("Call 3");
#endif
        // callback();
        selector == 0 ? callback_1() : callback_2();
        selector = (selector + 1) % 2;
        initialTime = millis();
    }
}
void SmartProcess::triggerContinuously(void (*callback)(void))
{
#ifdef __DEBUG_E__
    Serial.print("Initial Time fun start : ");
    Serial.println(initialTime);
#endif
    if (!FunEn)
        return;
    if (timer == 0)
    {
#ifdef __DEBUG_E__
        Serial.println("Call 1");
#endif
        callback();
    }
    else if (initialTime == 0)
    {
        delay(10);
        callback();
        initialTime = millis();

#ifdef __DEBUG_E__
        Serial.println("Call 2");
        Serial.print("Initial Time : ");
        Serial.println(initialTime);

#endif
    }
    else if (millis() - initialTime >= timer)
    {
#ifdef __DEBUG_E__
        Serial.println("Call 3");
#endif
        callback();
        initialTime = millis();
    }
}
void SmartProcess::resetTimer()
{
    initialTime = millis();
    isCalled = false;
}
void SmartProcess::resetTimer(unsigned long time)
{
    initialTime = time;
}
void SmartProcess::disableFn()
{
    FunEn = false;
}
void SmartProcess::enableFn()
{
    FunEn = true;
}