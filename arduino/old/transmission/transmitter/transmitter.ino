#include <Servo.h>
#define INTERVAL_TIME 10

Servo servoX;
Servo servoY;


const int buttonPin = 3; 
const int buttonPin2 = 4; 

const int signalPin = 5;
const int signalPin2 = 6;
const int signalPin3 = 7;
const int signalPin4 = 8;
int signalState = 0;
int signalState2 = 0;
int signalState3 = 0;
int signalState4 = 0;

int servoXpin = 13;
int servoYpin = 12;


int laser = 11;

boolean laserOn = true;

unsigned long then = 0;  
unsigned long then2 = 0;
unsigned long then3 = 0;
unsigned long then4 = 0;

int index = 0;

int whiteLed = 2;

int buttonState = 0;   
int buttonState2 = 0;    

int resetTrackerCounter = 0;

int xVal = 0;
int yVal = 20;
boolean turnBack = false;
boolean turning = true;


//henk
int bits[8] = {LOW, HIGH, HIGH, LOW, HIGH, HIGH, HIGH, LOW};
int bits2[8] = {HIGH, LOW, LOW, HIGH, HIGH, HIGH, HIGH, LOW};
int bits3[8] = {LOW, LOW, HIGH, LOW, HIGH, LOW, HIGH, LOW};
int bits4[8] = {HIGH, LOW, HIGH, LOW, HIGH, HIGH, HIGH, LOW};

//toto
/*
int bits[8] = {LOW, LOW, LOW, HIGH, HIGH, HIGH, HIGH, LOW};
int bits2[8] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW};
int bits3[8] = {LOW, LOW, LOW, HIGH, HIGH, HIGH, HIGH, LOW};
int bits4[8] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW};
*/

void setup() {

 
servoX.attach(servoXpin);
servoY.attach(servoYpin);


pinMode(buttonPin, INPUT);
pinMode(buttonPin2, INPUT);
pinMode(signalPin, INPUT);
pinMode(signalPin2, INPUT);
pinMode(signalPin3, INPUT);
pinMode(signalPin4, INPUT);

pinMode(whiteLed, OUTPUT);

pinMode(laser, OUTPUT);

servoY.write(5);
servoX.write(0);



  Serial.begin(9600); // open the serial port at 9600 bps:

}




void loop() {  
  
   unsigned long now = millis();
  
   if( now - then >= INTERVAL_TIME) {
  then = now;
  // 0, 1, 2, 3, 4, 5, 6, 7, 8 => 9 sequenzen HIGH
  if ( index < 8 ) {
       if ( index == 0 ){
         digitalWrite(laser, HIGH);
       }
       index ++;
   } 
    else if ( index >= 8 && index <= 15 ) {
     digitalWrite(laser, bits[index-8]);
     index ++;
   }
   else if ( index >= 16 && index <= 23 ) {
     digitalWrite(laser, bits2[index-16]);
     index ++;
   }
    else if ( index >= 24 && index <= 31 ) {
     digitalWrite(laser, bits3[index-24]);
     index ++;
   }
    else if ( index >= 32 && index <= 39 ) {
     digitalWrite(laser, bits4[index-32]);
     index ++;
   }
   else if ( index == 40 ) {
     digitalWrite(laser, LOW);
     index ++;
   } else if ( index < 90 ) {
    index ++;
   } else {
    index = 0;
   }
 }
}
