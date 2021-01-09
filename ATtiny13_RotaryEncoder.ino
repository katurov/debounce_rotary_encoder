/*
 * Okay, things I would like to do: make something VERY stable to determine
 *  is Encoder moved LEFT or RIGHT so stable that I can use it on Raspberry
 *  
 *  Problem is: Rotary Encoders on Raspberry generated a lot l|r wrong 
 *  signals, so lots and lots methods are writen to avoid it. In one of my
 *  projects I using ESP8266 (with lots of pin ready for interrrups).
 *  
 *  Here I'm trying to make a solution with cheap ATtiny13A 
 *  
 *                      +-\/-+
 *            RST PB5  1|°   |8  Vcc
 * --- RIGHT MOVE PB3  2|    |7  PB2 
 * ---  LEFT MOVE PB4  3|    |6  PB1 ------------ CLK on Encoder
 *                GND  4|    |5  PB0 (PCINT0) --- DT  on Encoder
 *                      +----+  
 * 
 * 
 *  Great help found here:
 *    * David Johnson-Davies - http://www.technoblogy.com/list?1YVE
 *    * A guy named http://noiseislife.tumblr.com - https://forums.adafruit.com/viewtopic.php?f=24&p=69110
 *    
 *  About the ATtiny13A
 *    * MicroCore 
 *    * ATtiny13
 *    * EEPROM retained
 *    * Clock: 9.6MHz internal oscilator
 *    * BOD 4.3 (use 2.7 for Raspberry)
 *    * Micros disabled
 *    * 202 bytes (19% of storage), 2 bytes out of 64 (3%) of dynamic memory
 *    * Code in Arduino IDE (why not)
 *    
 *  WHAT by Paul Katurov <katurov@gmail.com>
 */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
 
#define LEFT_LED PB4
#define RIGH_LED PB3

volatile bool s_pb0        = 0;
volatile bool s_pb1        = 0;

 
int main(void) {
  GIMSK = _BV (PCIE);           // Pin Change Interrupt Enable
  PCMSK = _BV (PCINT0);         // Enable external interrupts PCINT0
  MCUCR = _BV (ISC00);          // PCINT0 is triggered on any change
  sei();                        // int - Global enable interrupts

  pinMode(PB0, INPUT_PULLUP);   //  DT pin of the Encoder
  pinMode(PB1, INPUT_PULLUP);   // CLK pin of the Encoder
  pinMode(LEFT_LED, OUTPUT);    // Set direction register output
  pinMode(RIGH_LED, OUTPUT);    // Set direction register output
  digitalWrite(LEFT_LED, LOW);  // Make initial state LOW
  digitalWrite(RIGH_LED, LOW);  // Make initial state LOW

  for (;;) {
    asm("NOP");                 // loop (endless)
  }
 
  return 0;
}
 
ISR (PCINT0_vect) {             // Interrupt on PCINT0 vector
  bool m_pb0 = digitalRead(PB0);
  bool m_pb1 = digitalRead(PB1);

  if ( m_pb0 != s_pb0 ) {
    s_pb0 = m_pb0;
    if (m_pb1 != s_pb1) {
      s_pb1 = m_pb1;
      indicateRotation ( m_pb0 == m_pb1 );
    }
  }

}

/*
 * Okay, how IT works: if both are in one state, this is RIGHT move
 *  this is why we just use one already compared variable.
 */
void indicateRotation ( bool side ) {
  if ( side ) {
    digitalWrite( RIGH_LED, HIGH );
    _delay_ms (50);
    digitalWrite( RIGH_LED, LOW );
  } else {
    digitalWrite( LEFT_LED, HIGH );
    _delay_ms (50);
    digitalWrite( LEFT_LED, LOW );
  }  
}
