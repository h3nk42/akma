#include <Servo.h>

float period_micros = 2500;
int input = A0;
int inputBuffers[5] = {NULL, NULL, NULL, NULL, NULL};
int lastExtremum;
boolean firstLoop = true;
boolean printed = false;


// SERVO VARS

Servo servoX;
Servo servoY;

int servoXpin = 13;
int servoYpin = 12;

int servoXVal = 0;
int servoYVal = 0;
// ------------

boolean checkIfLow() {
    if(inputBuffers[0] >= inputBuffers[1] && inputBuffers[1] >= inputBuffers[2] &&  inputBuffers[2] <= inputBuffers[3] && inputBuffers[3] <= inputBuffers[4] ){
        return checkDoubleExtremum(inputBuffers[2]);
    }
    return false;
}

boolean checkIfHigh() {
    if (inputBuffers[0] <= inputBuffers[1] && inputBuffers[1] <= inputBuffers[2] &&  inputBuffers[2] >= inputBuffers[3] && inputBuffers[3] >= inputBuffers[4] ){
        return checkDoubleExtremum(inputBuffers[2]);
    }
    return false;
}

boolean checkDoubleExtremum(int currentExtremum) {
    if(lastExtremum != NULL ) {
        if(lastExtremum == currentExtremum) {
            return false;
        } else {
            lastExtremum = currentExtremum;
            return true;
        }
    } else {
        lastExtremum = currentExtremum;
        return true;
    }
}

boolean periodToPulseWidthRatio_toBoolean(float ratio) {
    if (ratio < 0.6) {
        return true;
    } else {
        return false;
    }
}

// TIMESTAMPS 
unsigned long lowTime;
unsigned long highTime;


// FRAMEBUFFER
uint8_t frameSize = 27;
boolean frame[27];
uint8_t frameIterator = 0;

// STARTBYTE9
bool startByte9[9] =  {1,1,1,1,1,1,1,1,0}; //510

// RECEIVED PAYLOAD
boolean payload[9];

float currentAngle = 0;


int8_t moduloFrameSize(uint8_t index) {
    return(index % frameSize);
}

int8_t findLastIndexOfStartByte9InFrame () {
    uint8_t startByteFoundIterator = 0;
    int8_t lastIndexOfStartByte = -1;
    for(int i = 0; i<= 34; i++) {
        if (frame[moduloFrameSize(i)] == startByte9[startByteFoundIterator]) {
            startByteFoundIterator++;
        } else {
            startByteFoundIterator = 0;
        }
        if(startByteFoundIterator == 9 ) {
            lastIndexOfStartByte = moduloFrameSize(i);
        } 
    }
    return lastIndexOfStartByte;
}

bool checkPayloadAndParity (uint8_t lastIndexOfStartByte9) {
    uint8_t onesCounter = 0 ;
    for (int i = 0; i<9; i++) {
        if( frame[ moduloFrameSize( lastIndexOfStartByte9+1 + i ) ] == 1 ) {onesCounter ++;}
        if( frame[ moduloFrameSize( lastIndexOfStartByte9+1 + i ) ] !=  frame[ moduloFrameSize(lastIndexOfStartByte9+1 + i + 9)] ) {
            return false;
        }
    }
    return onesCounter != 9;
}

void retrievePayload(uint8_t lastIndexOfStartByte9) {
     for (int i = 0; i<9; i++) {
         payload[i] = frame[moduloFrameSize(lastIndexOfStartByte9+1+i)];
     }
}

float convertByte9ToFloat () {
    float payloadInDec = 0;
    for (uint8_t i = 0; i<9; i++) {
         payloadInDec += payload[i] ? 1 * pow(2,8-i) : 0;
    }
     return payloadInDec;
}


void writeAngleToServos(float angle) {
    if(angle > 180) {
        servoX.write(180);
        servoY.write(angle-180);
    } else {
        servoX.write(0);
        servoY.write(angle);
    }
}




void resetToInitialState() {
    lowTime = NULL;
    highTime = NULL;
    frameIterator = 0;

    inputBuffers[0] = NULL;
    inputBuffers[1] = NULL;
    inputBuffers[2] = NULL;
    inputBuffers[3] = NULL;
    inputBuffers[4] = NULL;

    //firstLoop = true;
    printed = false;
    //delay(100);
}


void setup() {
    pinMode(input, INPUT);
    Serial.begin(115200);

    servoX.attach(servoXpin);
    servoY.attach(servoYpin);

    servoY.write(servoYVal);
    servoX.write(servoXVal);

}

void loop() { 
   
    if(printed) {
        resetToInitialState();
    }
    else {
        inputBuffers[4] = 1024 - analogRead(input);
        if ( inputBuffers[0] != NULL ) {
            if( frameIterator < frameSize ) {
                if ( checkIfLow()) {
                    // low
                    if(highTime != NULL) {
                        lowTime = micros();
                        frame[frameIterator] = periodToPulseWidthRatio_toBoolean(((float)lowTime - (float)highTime) / period_micros);
                        frameIterator ++;
                    } 
                }
                else if ( checkIfHigh() ) {
                    // high
                    highTime = micros();
                }
            } else {    
                        int8_t lastIndexOfStartByte = findLastIndexOfStartByte9InFrame();
                        if(lastIndexOfStartByte == -1) {
                        } else {
                            if(checkPayloadAndParity(lastIndexOfStartByte)){
                                retrievePayload(lastIndexOfStartByte);
                                float angleToWrite = convertByte9ToFloat();
                                if (currentAngle == angleToWrite) {
                                } else {
                                    if (angleToWrite <= 360 && angleToWrite >= 0) {
                                        writeAngleToServos(angleToWrite);
                                        currentAngle = angleToWrite;
                                    }
                                }
                            }
                        }
                    printed = true;
                }
        }
    }

    inputBuffers[0] = inputBuffers[1];
    inputBuffers[1] = inputBuffers[2];
    inputBuffers[2] = inputBuffers[3];
    inputBuffers[3] = inputBuffers[4];
}