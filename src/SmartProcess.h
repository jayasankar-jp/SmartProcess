#ifndef __SMART_PROCESS_H__
#define __SMART_PROCESS_H__

#include "Defines.h"
#include "string.h"
#include <Arduino.h>
// template <typename T>
class SmartProcess
{

private:
    unsigned long timer;
    unsigned long initialTime;
    bool FunEn;
    bool isCalled = 0;
    int selector;

public:
    SmartProcess() : FunEn(true), isCalled(false), initialTime(0), selector(0) {};
    void setTimer(const unsigned long &timer);
    void resetTimer();
    unsigned long getTimer();
    void resetTimer(unsigned long time);
    void triggerContinuously(void (*callback)(void));
    void triggerContinuously(void (*callback_1)(void), void (*callback_2)(void));
    void triggerContinuously(unsigned long time2, unsigned long time1, void (*callback_1)(void), void (*callback_2)(void) = nullptr);
    void TriggerDelay(void (*callback)(void), unsigned long delayTime);
    void disableFn();
    void enableFn();
};
#endif