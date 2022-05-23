/* int input = A0;
int inputBuffer[5] = {NULL, NULL, NULL, NULL, NULL};

boolean checkIfLow() {
    return (inputBuffer[0] >= inputBuffer[1] && inputBuffer[1] >= inputBuffer[2] &&  inputBuffer[2] <= inputBuffer[3] && inputBuffer[3] <= inputBuffer[4] );
}

boolean checkIfHigh() {
    return (inputBuffer[0] <= inputBuffer[1] && inputBuffer[1] <= inputBuffer[2] &&  inputBuffer[2] >= inputBuffer[3] && inputBuffer[3] >= inputBuffer[4] );
}


void setup() {
  pinMode(input, INPUT);
  Serial.begin(115200);
}

void loop() { 
    inputBuffer[4] = 1024 - analogRead(input);
    if ( inputBuffer[0] != NULL ) {
        if ( checkIfLow()) {
            // low
           
        }
        else if ( checkIfHigh() ) {
            // high
             Serial.print("CurrentReads: ");
            for(int i = 0; i < 5; i++) {
                Serial.print(inputBuffer[i]);Serial.print(", ");
            }
            Serial.println("----");
        } else {
            // increment counters;
        }
    }

    inputBuffer[0] = inputBuffer[1];
    inputBuffer[1] = inputBuffer[2];
    inputBuffer[2] = inputBuffer[3];
    inputBuffer[3] = inputBuffer[4];
  
} */