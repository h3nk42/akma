uint8_t laser = 11;
uint8_t poti = A0;


bool transmitting = false;
int transmittingCounter = 0;

//@400Hz
int period = 2500;
int pulseWidthHigh = period/2;
int pulseWidthLow = period/4;


bool startByte9[9] =  {1,1,1,1,1,1,1,1,0};
bool payLoad[9] = {0,1,0,1,1,0,1,0,0};
//bool payLoad[9] = {0,0,0,0,0,0,0,0,0};

uint8_t byte9Size = 9;
uint8_t frameSize = 3;
bool frame[3][9] = {{0}};

uint8_t frameIterator = 0;
uint8_t byte9Iterator = 0;

void fillFrame(){
  for(int i = 0; i<byte9Size; i++) {
      frame[0][i] = startByte9[i];
  }
   for(int i = 0; i<byte9Size; i++) {
      frame[1][i] = payLoad[i];
  }
   for(int i = 0; i<byte9Size; i++) {
      frame[2][i] = payLoad[i];
  }
}

int mapInputToDegree(int input) {
    return input / (341.00/120.00);
}

void writeDegreeToPayloadAndThenTransmit(int degree) {
    int a[9] = { 0,0,0, 0,0,0, 0,0,0  };
    int decimal = degree; 
    for(int i = 0;decimal>0;i++){    
        a[i] = decimal%2;    
        decimal = decimal/2;    
    }    
    for(int i = 8 ;i >= 0 ;i--){
        frame[1][8-i] = a[i];
        frame[2][8-i] = a[i];
    } 
}


void setup() {
    fillFrame();

    pinMode(laser, OUTPUT);
    pinMode(poti, INPUT);

    Serial.begin(115200); // open the serial port at 9600 bps:

}

void writeBit(boolean bit) {
  digitalWrite(laser, HIGH);
  bit ? delayMicroseconds(pulseWidthHigh) : delayMicroseconds(pulseWidthLow);
  digitalWrite(laser, LOW);
  bit ? delayMicroseconds(period -  pulseWidthHigh) : delayMicroseconds(period -  pulseWidthLow);
}

void loop() {
    if(transmitting) {
        writeBit(frame[frameIterator][byte9Iterator]);
        byte9Iterator++;
        if(byte9Iterator == byte9Size ) {
            byte9Iterator = 0;
            frameIterator ++;
        }
        if(frameIterator == frameSize){
            frameIterator = 0;
            transmittingCounter ++;
            if(transmittingCounter > 1) {
                transmitting = false;
                transmittingCounter = 0;
            }
        }
    } else {
        writeDegreeToPayloadAndThenTransmit(mapInputToDegree(analogRead(poti)));
        /* for(int i =0; i<9;i++) {
            Serial.print(frame[1][i]);
        }
        Serial.println("---"); */
        Serial.println(mapInputToDegree(analogRead(poti)));
        transmitting = true;
    }
}