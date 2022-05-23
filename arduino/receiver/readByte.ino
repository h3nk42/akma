/* float period_micros = 2500;


int input = A0;
int currentReads[5] = {NULL, NULL, NULL, NULL, NULL};

int lastExtremum;

boolean firstLoop = true;

boolean printed = false;



boolean checkIfLow() {
    if(currentReads[0] >= currentReads[1] && currentReads[1] >= currentReads[2] &&  currentReads[2] <= currentReads[3] && currentReads[3] <= currentReads[4] ){
        return checkDoubleExtremum(currentReads[2]);
    }
    return false;
}

boolean checkIfHigh() {
    if (currentReads[0] <= currentReads[1] && currentReads[1] <= currentReads[2] &&  currentReads[2] >= currentReads[3] && currentReads[3] >= currentReads[4] ){
        return checkDoubleExtremum(currentReads[2]);
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

int highToLowRatioSize = 16;
int highToLowRatioOuterSize = 10;
boolean highToLowRatio[10][16];
int iterator = 0;
int iteratorOuter = 0;


unsigned long lowTime;
unsigned long highTime;

void resetMemory() {
    lowTime = NULL;
    highTime = NULL;
    iterator = 0;
    iteratorOuter = 0;

    currentReads[0] = NULL;
    currentReads[1] = NULL;
    currentReads[2] = NULL;
    currentReads[3] = NULL;
    currentReads[4] = NULL;

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
        resetMemory();
    }
    else {
        currentReads[4] = 1024 - analogRead(input);
        if ( currentReads[0] != NULL ) {
            if( iterator < highToLowRatioSize ) {
                if ( checkIfLow()) {
                    // low
                    if(highTime != NULL) {
                        lowTime = micros();
                        highToLowRatio[iteratorOuter][iterator] = periodToPulseWidthRatio_toBoolean (((float)lowTime - (float)highTime) / period_micros);
                        iterator ++;
                    } 
                }
                else if ( checkIfHigh() ) {
                    // high
                    highTime = micros();
                }
            } else {
                if (iteratorOuter < highToLowRatioOuterSize-1 ) 
                {
                    iteratorOuter ++;
                    iterator = 0;
                } else {
                    for (int i = 0; i < highToLowRatioOuterSize; i++) {
                        Serial.print("Read ");Serial.println(i+1);
                        Serial.print("  ----> [");
                        for (int j = 0; j < highToLowRatioSize; j++) {
                            Serial.print(highToLowRatio[i][j]); Serial.print(", ");
                        }
                       Serial.println("] <---- ");
                    }
                    Serial.println("----------- end -----------"); Serial.println("");

                    printed = true;
                }
            }
        }

        currentReads[0] = currentReads[1];
        currentReads[1] = currentReads[2];
        currentReads[2] = currentReads[3];
        currentReads[3] = currentReads[4];
    }
  
} */