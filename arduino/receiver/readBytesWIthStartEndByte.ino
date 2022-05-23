/* float period_micros = 2500;
int input = A0;
int inputBuffers[5] = {NULL, NULL, NULL, NULL, NULL};
int lastExtremum;
boolean firstLoop = true;
boolean printed = false;

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
bool startByte9[9] =  {1,1,1,1,1,1,1,1,0};

// RECEIVED PAYLOAD
boolean payload[9];


int8_t moduloFrameSize(uint8_t index) {
    return(index % frameSize);
}

int8_t findStartByte9InFrame () {
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
    for (int i = 0; i<9; i++) {
        if( frame[ moduloFrameSize( lastIndexOfStartByte9+1 + i ) ] !=  frame[ moduloFrameSize(lastIndexOfStartByte9+1 + i + 9)] ) {
            return false;
        }
    }
    return true;
}

void retrievePayload(uint8_t lastIndexOfStartByte9) {
     for (int i = 0; i<9; i++) {
         payload[i] = frame[moduloFrameSize(lastIndexOfStartByte9+1+i)];
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

    firstLoop = true;
    printed = false;
    delay(500);
}


void setup() {
  pinMode(input, INPUT);
  Serial.begin(115200);
}

void loop() { 
    if(firstLoop) {
        delay(100);
        Serial.println("----------- begin -----------"); 
        firstLoop = false;
    }
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
                        Serial.print("  ----> [");
                        for (int i = 0; i < frameSize; i++) {
                            Serial.print(frame[i]); Serial.print(", ");
                        }
                       Serial.println("] <---- ");

                        Serial.print("  ----> [ lastIndex of startByte9: ");
                        Serial.print(findStartByte9InFrame());
                       Serial.println("] <---- ");
                         Serial.print("  ----> [ parityCheck: ");
                        Serial.print(checkPayloadAndParity(findStartByte9InFrame()));
                       Serial.println("] <---- ");
                        Serial.print("  ----> [ extracted payload: ");
                        if(checkPayloadAndParity(findStartByte9InFrame())){
                            retrievePayload(findStartByte9InFrame());
                            for (int i = 0; i < 9; i++) {
                                Serial.print(payload[i]); Serial.print(", ");
                            }
                        }
                        
                       Serial.println("] <---- ");

                    Serial.println("----------- end -----------"); Serial.println("");

                    printed = true;
                }
        }

        inputBuffers[0] = inputBuffers[1];
        inputBuffers[1] = inputBuffers[2];
        inputBuffers[2] = inputBuffers[3];
        inputBuffers[3] = inputBuffers[4];
    }
  
} */