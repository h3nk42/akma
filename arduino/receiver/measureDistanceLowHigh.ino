/* int input = A0;
int currentReads[5] = {NULL, NULL, NULL, NULL, NULL};

int lastExtremum;

int firstLoop = true;


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

// low / high reads
int lowsHighsSize = 10;
unsigned long lowsHighs[10][3];
int lowsHighsCounter = 0;

float prevCurrentExtremum[4];



// loop values 
int loopDuration[100];
int loopCounter = 0;

unsigned long then;
unsigned long now;

unsigned long lowTime;
unsigned long highTime;


void setup() {
  pinMode(input, INPUT);
  Serial.begin(115200);
}

void loop() { 
    if(firstLoop) {
        delay(500);
        firstLoop = false;
    }

    currentReads[4] = 1024 - analogRead(input);
    now = micros();
    if(then != NULL) {
        //loopDuration[loopCounter] = now - then;
        loopDuration[loopCounter] = currentReads[2];
        loopCounter++;
    }
    then = now;
    if (lowsHighsCounter < lowsHighsSize) {
    if ( currentReads[0] != NULL ) {
        if ( checkIfLow()) {
            // low
            lowTime = micros();

            lowsHighs[lowsHighsCounter][0] = 0;
            if( highTime != NULL ) {lowsHighs[lowsHighsCounter][1] = lowTime - highTime;}
            lowsHighs[lowsHighsCounter][2] = currentReads[2];
            lowsHighsCounter++;
            
  
        }
        else if ( checkIfHigh() ) {
            // high
            prevCurrentExtremum[0] = highTime - lowTime;

            highTime = micros();

            lowsHighs[lowsHighsCounter][0] = 1;
            if(lowTime != NULL) {lowsHighs[lowsHighsCounter][1] = highTime - lowTime;}
            lowsHighs[lowsHighsCounter][2] = currentReads[2];
            lowsHighsCounter++;
           
        }
    }
    }
     else {
          Serial.println(" -- Loop Values -- ");
         for (int i = 0; i<100; i++) {
            Serial.print(loopDuration[i]);  Serial.print(", ");
            loopDuration[i] = 0;
         }
         Serial.println("");

        for(int i = 0; i<lowsHighsSize; i++) {
            Serial.print("{ extremum: ");
            Serial.print(lowsHighs[i][0]);
            Serial.print(", time: ");
            Serial.print(lowsHighs[i][1]);
             Serial.print(", val: ");
            Serial.print(lowsHighs[i][2]);
            Serial.print(" }, ");
            if(i>0 && lowsHighs[i-1][0] == lowsHighs[i][0]) {
             Serial.print("----------- DOUBLE ----------- ");    
            }
        }
         Serial.println(" -------- ");
         Serial.println("");
        lowsHighsCounter = 0;
        loopCounter= 0;
  }

    currentReads[0] = currentReads[1];
    currentReads[1] = currentReads[2];
    currentReads[2] = currentReads[3];
    currentReads[3] = currentReads[4];
  
} */