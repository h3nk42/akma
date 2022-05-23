#include <Servo.h>

Servo servoX;
Servo servoY;


int servoXpin = 13;
int servoYpin = 12;

int servoXVal = 0;
int servoYVal = 0;

int input = A0;









void setup() {
    servoX.attach(servoXpin);
    servoY.attach(servoYpin);


    pinMode(input, INPUT);
    Serial.begin(115200); // open the serial port at 9600 bps:


}


void loop() {
    
    servoY.write(servoXVal);
    servoX.write(servoYVal);

    servoXVal++;
    servoYVal++;

    delay(100);

    Serial.println(analogRead(input));
}