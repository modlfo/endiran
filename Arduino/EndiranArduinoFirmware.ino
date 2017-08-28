#include <TimerOne.h>
#include "vultin.h"
#include "control.h"

/* The one an only context of the program */
Control_loop_type context;

void setup()
{

   /*   Initialize encoders */
   pinMode(22, INPUT);
   pinMode(24, INPUT);
   pinMode(2, INPUT);
   digitalWrite(22, HIGH); // turn on pullup resistor
   digitalWrite(24, HIGH); // turn on pullup resistor
   digitalWrite(2, HIGH);  // turn on pullup resistor

   pinMode(26, INPUT);
   pinMode(28, INPUT);
   pinMode(3, INPUT);
   digitalWrite(26, HIGH); // turn on pullup resistor
   digitalWrite(28, HIGH); // turn on pullup resistor
   digitalWrite(3, HIGH);  // turn on pullup resistor

   pinMode(17, INPUT);
   pinMode(16, INPUT);
   pinMode(18, INPUT);
   digitalWrite(17, HIGH); // turn on pullup resistor
   digitalWrite(16, HIGH); // turn on pullup resistor
   digitalWrite(18, HIGH); // turn on pullup resistor

   pinMode(21, INPUT);
   pinMode(20, INPUT);
   pinMode(19, INPUT);
   digitalWrite(21, HIGH); // turn on pullup resistor
   digitalWrite(20, HIGH); // turn on pullup resistor
   digitalWrite(19, HIGH); // turn on pullup resistor

   attachInterrupt(digitalPinToInterrupt(2), processEncoder1, CHANGE);
   attachInterrupt(digitalPinToInterrupt(3), processEncoder2, CHANGE);
   attachInterrupt(digitalPinToInterrupt(18), processEncoder3, CHANGE);
   attachInterrupt(digitalPinToInterrupt(19), processEncoder4, CHANGE);

   /*   Initialize motors   */

   pinMode(5, OUTPUT);
   pinMode(4, OUTPUT);

   pinMode(7, OUTPUT);
   pinMode(6, OUTPUT);

   pinMode(9, OUTPUT);
   pinMode(8, OUTPUT);

   pinMode(11, OUTPUT);
   pinMode(10, OUTPUT);

   Timer1.initialize(10000);
   Timer1.attachInterrupt(actuate); // attach the service routine here

   TCCR0B = (TCCR0B & 0xF8) | 2;
   TCCR2B = (TCCR2B & 0xF8) | 2;
   TCCR4B = (TCCR4B & 0xF8) | 2;

   Serial.begin(115200);
}

void loop()
{
   Control_loop(context);
}

/* Interrupt handler to perform control operations */
void actuate()
{
   Control_actuate(context);
}

/* Interrupt handler to process the encoders */
void processEncoder1()
{
   Control_encoder1(context);
}

void processEncoder2()
{
   Control_encoder2(context);
}

void processEncoder3()
{
   Control_encoder3(context);
}

void processEncoder4()
{
   Control_encoder4(context);
}

/*  External functions called from Vult */
int Serial_available()
{
   return Serial.available();
}
int Serial_read()
{
   return Serial.read();
}
void Serial_write(int byte)
{
   Serial.write(byte);
}
void IO_digitalWrite(int pin, uint8_t value)
{
   digitalWrite(pin, value);
}
uint8_t IO_digitalRead(int pin)
{
   return digitalRead(pin);
}
void IO_analogWrite(int pin, int value)
{
   analogWrite(pin, value);
}
