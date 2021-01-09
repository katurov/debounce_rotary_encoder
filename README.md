# Debounce Rotary Encoder with ATtiny13A

## Main proconditions

[How to use ATtiny13A in Arduino IDE](https://github.com/MCUdude/MicroCore)

Please, double check VCC and BOD voltage on ATtiny before connect it to Raspberry or MCU.

In my case it was Rotary Encoder module with pull-up resistors, here are pins:
* \+ for VCC
* G for Ground
* SW for click (or tap?)
* DT for one direction
* CLK for other direction

very useful thing

## Connections

Here is main scheme, also described in program' listing, but here are commons:
* VCC on both have to be connected to VCC
* Grounds to Ground
* ATtiny13A pin 6 (PB1) to CLK pin of Encoder
* ATtiny13A pin 5 (PB0) to DT pin of Encoder
* ATtiny13A pin 2 (PB3) to pin of MCU which waits for signal about rotation on Right
* ATtiny13A pin 3 (PB4) to pin of MCU which waits for signal about rotation on Left
