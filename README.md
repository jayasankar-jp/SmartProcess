# SmartProcess

SmartProcess is a lightweight, non-blocking task scheduler for Arduino based on `millis()`.
It enables periodic and delayed execution of functions without using blocking delays.

---

## Overview

SmartProcess provides a simple abstraction to manage timed execution of functions in embedded systems.
It is designed to keep the `loop()` function responsive while handling multiple timed operations.

---

## Features

- Non-blocking execution using `millis()`
- Independent timers using multiple instances
- Continuous and delayed execution modes
- Support for multiple callbacks
- Lightweight and efficient for embedded systems

---

## Installation

### Manual Installation

Clone the repository and place it inside your Arduino libraries directory:

```bash
git clone https://github.com/jayasankar-jp/SmartProcess.git
mv SmartProcess ~/Arduino/libraries/
```

Restart the Arduino IDE after installation.

---

### Arduino CLI

```bash
arduino-cli lib install SmartProcess
```

---

## Basic Usage

```cpp
#include <SmartProcess.h>

SmartProcess Timer1, Timer2;

void function1() {
  Serial.println("Function 1 trigger");
}

void function2() {
  Serial.println("Function 2 trigger");
}

void setup() {
  Serial.begin(9600);
  Timer1.setTimer(2000);
  Timer2.setTimer(5000);
}

void loop() {
  Timer1.triggerContinuously(function1);
  Timer2.triggerContinuously(function2);
}
```

---

## API Reference

### setTimer

```cpp
void setTimer(unsigned long timer);
```

Sets the interval for the timer in milliseconds.

---

### getTimer

```cpp
unsigned long getTimer();
```

Returns the currently configured timer value.

---

### resetTimer

```cpp
void resetTimer();
void resetTimer(unsigned long time);
```

Resets the timer to the current time or a specified value.

---

### triggerContinuously

```cpp
void triggerContinuously(void (*callback)(void));
void triggerContinuously(void (*callback1)(void), void (*callback2)(void));
void triggerContinuously(unsigned long time2, unsigned long time1,
                         void (*callback1)(void),
                         void (*callback2)(void) = nullptr);
```

Executes one or more callbacks repeatedly based on the configured timer.

---

### TriggerDelay

```cpp
void TriggerDelay(void (*callback)(void), unsigned long delayTime);
```

Executes a callback once after a specified delay.

---

### enableFn / disableFn

```cpp
void enableFn();
void disableFn();
```

Enables or disables execution of callbacks.

---

## Usage Guidelines

### Avoid blocking operations

SmartProcess is designed for non-blocking execution. Avoid using `delay()` in your main loop unless absolutely necessary.

---

### Avoid loops inside callback functions

Callback functions must execute quickly and return immediately.

Incorrect usage:

```cpp
void function1() {
  for (int i = 0; i < 1000; i++) {
    Serial.println("Blocking");
  }
}
```

This blocks execution and affects timing accuracy.

Correct usage:

```cpp
void function1() {
  Serial.println("Non-blocking execution");
}
```

---

### Keep callbacks lightweight

Callbacks should:

- Execute quickly
- Avoid heavy computation
- Avoid blocking I/O where possible

---

## Example: Delay with Reset Control

```cpp
#include <SmartProcess.h>

SmartProcess Timer1, Timer2;

void function1() {
  Serial.println("Function 1 trigger");
}

void function2() {
  Serial.println("Function 2 trigger");
}

void setup() {
  Serial.begin(9600);
  Timer1.setTimer(2000);
  Timer2.setTimer(5000);
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();

    if (c == '1') {
      Timer1.resetTimer();
    } else if (c == '2') {
      Timer2.resetTimer();
    }
  }

  Timer1.TriggerDelay(function1, 5000);
  Timer2.TriggerDelay(function2, 2500);
}
```

---

## Testing

SmartProcess can be tested using `arduino-cli` and a Makefile.

### Prerequisites

Install required cores:

```bash
arduino-cli core update-index
arduino-cli core install arduino:avr
arduino-cli core install esp32:esp32
```

---

### Makefile

```makefile
LIB_NAME=SmartProcess
EXAMPLE=examples/BasicExample

BOARD_AVR=arduino:avr:uno
BOARD_ESP32=esp32:esp32:esp32

all: test-uno test-esp32

test-uno:
	arduino-cli compile --fqbn $(BOARD_AVR) $(EXAMPLE)

test-esp32:
	arduino-cli compile --fqbn $(BOARD_ESP32) $(EXAMPLE)

clean:
	rm -rf build
```

---

### Run Tests

```bash
make
```

This compiles the example for multiple boards to validate compatibility.

---

## Best Practices

- Keep `loop()` fast and responsive
- Use separate SmartProcess instances for independent tasks
- Use `resetTimer()` for dynamic control of execution
- Validate behavior across different boards

---

## License

This project is licensed under the MIT License.

```
MIT License

Copyright (c) 2026 Jayasankar JP

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction...

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
```

---

## Author

Jayasankar JP
https://github.com/jayasankar-jp

---

## Contribution

Contributions are welcome. Please open issues or submit pull requests for improvements, bug fixes, or new features.

---
