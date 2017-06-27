#include <TimerOne.h>
#include "vultin.h"

/*     ENCODERS      */
#define encoder1IntPin 2
#define encoder1Enc1  22
#define encoder1Enc2  24

#define encoder2IntPin 3
#define encoder2Enc1  26
#define encoder2Enc2  28

#define encoder3IntPin 18
#define encoder3Enc1  17
#define encoder3Enc2  16

#define encoder4IntPin 19
#define encoder4Enc1  21
#define encoder4Enc2  20

int16_t encoder1Pos = 0;
uint8_t encoder1State;
int16_t encoder2Pos = 0;
uint8_t encoder2State;
int16_t encoder3Pos = 0;
uint8_t encoder3State;
int16_t encoder4Pos = 0;
uint8_t encoder4State;


/*    MOTORS    */
#define motor1DirPin 5
#define motor1PWMPin 4
fix16_t motor1Current;
#define motor1CurentPin 12

#define motor2DirPin 7
#define motor2PWMPin 6
fix16_t motor2Current;
#define motor2CurentPin 13

#define motor3DirPin 9
#define motor3PWMPin 8
fix16_t motor3Current;
#define motor3CurentPin 14

#define motor4DirPin 11
#define motor4PWMPin 10
fix16_t motor4Current;
#define motor4CurentPin 15

#define MAX_SPEED 4194304

fix16_t target_speed_left;
fix16_t target_speed_right;
fix16_t speed1,speed2,speed3,speed4;
fix16_t motor1state,motor2state,motor3state,motor4state;
uint8_t trigger;
uint8_t moving;

  uint8_t inByte;
  uint8_t ctrl,val,midi_state;
  int16_t sval;
  fix16_t abs_vel1,abs_vel2;
  fix16_t error_left;
  fix16_t error_left_pre;
  fix16_t signal_left;
  fix16_t signal_left_pre;
  fix16_t error_right;
  fix16_t error_right_pre;
  fix16_t signal_right;
  fix16_t signal_right_pre;

/* Ultra Sonic Sensors */
#define rightUltrasonicSensorEnchoPin 50
#define rightUltrasonicSensorTrigPin 52
#define leftUltrasonicSensorEnchoPin 12
#define leftUltrasonicSensorTrigPin 13

fix16_t durationRight;
uint16_t distanceRight;
fix16_t durationLeft;
uint16_t distanceLeft;


/*    LINE SENSORS    */
#define sensor1Pin 0
uint16_t sensor1val;
#define sensor2Pin 1
uint16_t sensor2val;
#define sensor3Pin 2
uint16_t sensor3val;


void processEncoder(uint8_t &state, uint8_t enc1_pin, uint8_t enc2_pin, int16_t &pos);
void moveMotor(uint8_t motor, fix16_t vel);
void sendControl(uint8_t ctrl, uint8_t value);

void setup() {

  /*   Initialize encoders */
  pinMode(encoder1Enc1, INPUT);
  pinMode(encoder1Enc2, INPUT);
  pinMode(encoder1IntPin, INPUT);
  digitalWrite(encoder1Enc1, HIGH);       // turn on pullup resistor
  digitalWrite(encoder1Enc2, HIGH);       // turn on pullup resistor
  digitalWrite(encoder1IntPin, HIGH);       // turn on pullup resistor

  pinMode(encoder2Enc1, INPUT);
  pinMode(encoder2Enc2, INPUT);
  pinMode(encoder2IntPin, INPUT);
  digitalWrite(encoder2Enc1, HIGH);       // turn on pullup resistor
  digitalWrite(encoder2Enc2, HIGH);       // turn on pullup resistor
  digitalWrite(encoder2IntPin, HIGH);       // turn on pullup resistor

  pinMode(encoder3Enc1, INPUT);
  pinMode(encoder3Enc2, INPUT);
  pinMode(encoder3IntPin, INPUT);
  digitalWrite(encoder3Enc1, HIGH);       // turn on pullup resistor
  digitalWrite(encoder3Enc2, HIGH);       // turn on pullup resistor
  digitalWrite(encoder3IntPin, HIGH);       // turn on pullup resistor

  pinMode(encoder4Enc1, INPUT);
  pinMode(encoder4Enc2, INPUT);
  pinMode(encoder4IntPin, INPUT);
  digitalWrite(encoder4Enc1, HIGH);       // turn on pullup resistor
  digitalWrite(encoder4Enc2, HIGH);       // turn on pullup resistor
  digitalWrite(encoder4IntPin, HIGH);       // turn on pullup resistor

  encoder1State = digitalRead(encoder1Enc1)<<1|digitalRead(encoder1Enc2);
  encoder2State = digitalRead(encoder2Enc1)<<1|digitalRead(encoder2Enc2);
  encoder3State = digitalRead(encoder3Enc1)<<1|digitalRead(encoder3Enc2);
  encoder4State = digitalRead(encoder4Enc1)<<1|digitalRead(encoder4Enc2);

  attachInterrupt(0, processEncoder1, CHANGE);
  attachInterrupt(1, processEncoder2, CHANGE);
  attachInterrupt(5, processEncoder3, CHANGE);
  attachInterrupt(4, processEncoder4, CHANGE);


  /*   Initialize motors   */

  pinMode(motor1DirPin, OUTPUT);
  pinMode(motor1PWMPin, OUTPUT);

  pinMode(motor2DirPin, OUTPUT);
  pinMode(motor2PWMPin, OUTPUT);

  pinMode(motor3DirPin, OUTPUT);
  pinMode(motor3PWMPin, OUTPUT);

  pinMode(motor4DirPin, OUTPUT);
  pinMode(motor4PWMPin, OUTPUT);

  Timer1.initialize(100000);
  Timer1.attachInterrupt( timerIsr ); // attach the service routine here

  motor1state = 0;
  motor2state = 0;
  motor3state = 0;
  motor4state = 0;

  TCCR0B = (TCCR0B & 0xF8) | 2;
  TCCR2B = (TCCR2B & 0xF8) | 2 ;
  TCCR4B = (TCCR4B & 0xF8) | 2 ;

  target_speed_left = 0;
  target_speed_right = 0;
  
  
    /* Initialize ultrasonic sensors */

  pinMode(rightUltrasonicSensorTrigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(rightUltrasonicSensorEnchoPin, INPUT); // Sets the echoPin as an Input
  pinMode(leftUltrasonicSensorTrigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(leftUltrasonicSensorEnchoPin, INPUT); // Sets the echoPin as an Input
  
  
  
  Serial.begin (115200);
  
     inByte;
   ctrl,val,midi_state=0;
   sval=0;
   abs_vel1,abs_vel2=0;
   error_left = 0;
   error_left_pre = 0;
   signal_left = 0;
   signal_left_pre = 0;
   error_right = 0;
   signal_right = 0;
   signal_right_pre = 0;
  
  
}

void saturate(fix16_t &v){
  v = v>MAX_SPEED?MAX_SPEED:(v< -MAX_SPEED? -MAX_SPEED:v);
}

void loop(){



  while(1)
  {
    if(Serial.available()>0)
    {
      inByte = Serial.read();
      if(midi_state==0 && inByte==0xB0)
      {
        midi_state = 1;
      }
      else if(midi_state==1){
        ctrl = inByte;
        midi_state = 2;
      }
      else if(midi_state==2){
        val = inByte;
        sval = val;
        sval = sval-64;
        midi_state = 0;
        if(ctrl==0x50){
          target_speed_left = int_to_fix(sval);
        }
        if(ctrl==0x51){
          target_speed_right = int_to_fix(sval);
        }
      }
      else
        midi_state = 0;
    }

    abs_vel1 = target_speed_left>0?target_speed_left:-target_speed_left;
    abs_vel2 = target_speed_right>0?target_speed_right:-target_speed_right;
    if(abs_vel1>int_to_fix(1) || abs_vel2>int_to_fix(1))
      moving = 1;
    else
      moving = 0;

    if(trigger!=0){

       trigger = 0;




      #define P_left float_to_fix(2)
       #define I_left float_to_fix(1)
       
       #define P_right float_to_fix(2)
       #define I_right float_to_fix(1)


       error_left = target_speed_left-speed3;
       signal_left = signal_left_pre + fix_mul((P_left+I_left),error_left)+fix_mul(-P_left+I_left,error_left_pre); 
       signal_left_pre = signal_left;
       error_left_pre = error_left;
       moveMotor(1,signal_left);
       moveMotor(3,signal_left);

       error_right = target_speed_right-speed2;
       signal_right = signal_right_pre + fix_mul((P_right+I_right),error_right)+fix_mul(-P_right+I_right,error_right_pre); 
       signal_right_pre = signal_right;
       error_right_pre = error_right;
       moveMotor(2,signal_right);
       moveMotor(4,signal_right);



       // Send information
       sendControl(0x20,abs(fix_to_int(speed1)));
       sendControl(0x21,abs(fix_to_int(speed2)));
       sendControl(0x22,abs(fix_to_int(speed3)));
       sendControl(0x23,abs(fix_to_int(speed4)));

       sendControl(0x30,fix_to_int(abs(error_left)));
       sendControl(0x31,fix_to_int(abs(error_right)));
       sendControl(0x32,fix_to_int(abs(target_speed_left)));
       sendControl(0x33,fix_to_int(abs(target_speed_right)));
       
       
       /* Ultra Sonic Sensors */
         
       digitalWrite(rightUltrasonicSensorTrigPin, LOW);
       delayMicroseconds(2);
       // Sets the trigPin on HIGH state for 10 micro seconds
       digitalWrite(rightUltrasonicSensorTrigPin, HIGH);
       delayMicroseconds(10);
       digitalWrite(rightUltrasonicSensorTrigPin, LOW);
       // Reads the echoPin, returns the sound wave travel time in microseconds
       durationRight = float_to_fix(pulseIn(rightUltrasonicSensorEnchoPin, HIGH));
       // Calculating the distance
       distanceRight= fix_to_int(fix_mul(fix_mul(durationRight,float_to_fix(0.034)),float_to_fix(0.5)));
       
       digitalWrite(leftUltrasonicSensorTrigPin, LOW);
       delayMicroseconds(2);
       // Sets the trigPin on HIGH state for 10 micro seconds
       digitalWrite(leftUltrasonicSensorTrigPin, HIGH);
       delayMicroseconds(10);
       digitalWrite(leftUltrasonicSensorTrigPin, LOW);
       // Reads the echoPin, returns the sound wave travel time in microseconds
       durationLeft = float_to_fix(pulseIn(leftUltrasonicSensorEnchoPin, HIGH));
       // Calculating the distance
       distanceLeft= fix_to_int(fix_mul(fix_mul(durationLeft,float_to_fix(0.034)),float_to_fix(0.5)));

/*
       Serial.print("Distance Right: ");
       Serial.println(distanceRight);
       
       Serial.print("Distance Left: ");
       Serial.println(distanceLeft);
  */     
       if (distanceLeft >= 127){
           distanceLeft = 127;
       }
    
       if (distanceLeft <= 0){
        distanceLeft = 0;
       }
    
    if (distanceRight >= 127){
           distanceRight = 127;
       }
    
       if (distanceRight <= 0){
        distanceRight = 0;
       }
       
       sendControl(0x40,distanceLeft);
       sendControl(0x41,distanceRight);
    
       sendControl(0x42,sensor3val);

    }
  }
}

void timerIsr()
{
    int v;
    speed1 = -int_to_fix(encoder1Pos);
    v = analogRead(motor1CurentPin);
    delayMicroseconds(20);

    motor1Current = int_to_fix(v);
    speed2 = -int_to_fix(encoder2Pos);
    v = analogRead(motor2CurentPin);
    delayMicroseconds(20);

    motor2Current = int_to_fix(v);
    speed3 = -int_to_fix(encoder3Pos);
    v = analogRead(motor3CurentPin);
    delayMicroseconds(20);


    motor3Current = int_to_fix(v);
    speed4 = -int_to_fix(encoder4Pos);
    v = analogRead(motor4CurentPin);
    motor4Current = int_to_fix(v);


    sensor1val = analogRead(sensor1Pin) >> 2;delayMicroseconds(20);
    sensor2val = analogRead(sensor2Pin) >> 2;delayMicroseconds(20);
    sensor3val = analogRead(sensor3Pin) >> 2;delayMicroseconds(20);


    encoder1Pos=0;
    encoder2Pos=0;
    encoder3Pos=0;
    encoder4Pos=0;

    trigger=1;
}

void moveMotor(uint8_t motor, fix16_t vel)
{
  uint8_t dir,dir_fixed;
  uint8_t vel_int;
  fix16_t fixed_vel;
  dir = vel>0?1:0;
  fixed_vel = vel>0?vel:fix_sub(0,vel);
  vel_int = fix_to_int(fixed_vel);

  if(moving==0) vel_int = 0;
  if(motor==1 || motor==2)
    dir_fixed = dir;
  else
    dir_fixed = dir!=0?0:1;
  switch(motor)
  {
    case 1:
      digitalWrite(motor1DirPin,dir_fixed);
      analogWrite(motor1PWMPin,vel_int);
      break;
    case 2:
      digitalWrite(motor2DirPin,dir_fixed);
      analogWrite(motor2PWMPin,vel_int);
      break;
    case 3:
      digitalWrite(motor3DirPin,dir_fixed);
      analogWrite(motor3PWMPin,vel_int);
      break;
    case 4:
      digitalWrite(motor4DirPin,dir_fixed);
      analogWrite(motor4PWMPin,vel_int);
      break;
  }
}

void processEncoder1() {
  processEncoder(encoder1State,encoder1Enc1,encoder1Enc2,encoder1Pos);
}

void processEncoder2() {
  processEncoder(encoder2State,encoder2Enc1,encoder2Enc2,encoder2Pos);
}

void processEncoder3() {
  processEncoder(encoder3State,encoder3Enc1,encoder3Enc2,encoder3Pos);
}

void processEncoder4() {
  processEncoder(encoder4State,encoder4Enc1,encoder4Enc2,encoder4Pos);
}



void processEncoder(uint8_t &state, uint8_t enc1_pin, uint8_t enc2_pin, int16_t &pos) {

  uint8_t enc1 = digitalRead(enc1_pin);
  uint8_t enc2 = digitalRead(enc2_pin);
  switch(state)
  {
    case 0:
      if(enc2!=0){
         pos++;
         state = 1;
       }
      else {
        pos--;
        state = 2;
      }
      break;
     case 1:
      if(enc1!=0){
         pos++;
         state = 3;
       }
      else {
        pos--;
        state = 0;
      }
      break;
     case 2:
      if(enc2!=0){
         pos--;
         state = 3;
       }
      else {
        pos++;
        state = 0;
      }
      break;
     case 3:
      if(enc1==0){
         pos--;
         state = 1;
       }
      else {
        pos++;
        state = 2;
      }
      break;
  }
}

void sendControl(uint8_t ctrl, uint8_t value)
{
  Serial.write(0xB0);
  Serial.write(ctrl);
  Serial.write(value);
}


