uint8_t laser = 11;
uint8_t poti = A0;


bool transmitting = false;
uint8_t transmittingCounter = 0;


//@400Hz
uint16_t period = 2500;
uint16_t pulseWidthHigh = period/2;
uint16_t pulseWidthLow = period/4;


uint16_t startByte9 =  510;
int16_t currentDegree = 0;

uint16_t potiBuffer[3] = {0};


uint8_t byte9Size = 9;
uint8_t frameSize = 3;

uint8_t frameIterator = 0;
uint8_t byte9Iterator = 0;

int mapInputToDegree(int input) {
    return input / (341.00/120.00);
}

int getBitFromIntAtIndex(int number, uint8_t index) {
    return (number & ( 1 << index )) >> index;
}


void setup() {

    pinMode(laser, OUTPUT);
    pinMode(poti, INPUT);

    Serial.begin(115200); // open the serial port at 9600 bps:

}

void transmitBit(boolean bit) {
  digitalWrite(laser, HIGH);
  bit ? delayMicroseconds(pulseWidthHigh) : delayMicroseconds(pulseWidthLow);
  digitalWrite(laser, LOW);
  bit ? delayMicroseconds(period -  pulseWidthHigh) : delayMicroseconds(period -  pulseWidthLow);
}

void loop() {
    if(transmitting) {
        if(frameIterator == 0) {
            transmitBit(getBitFromIntAtIndex(startByte9,  8 - byte9Iterator));
            //Serial.print(getBitFromIntAtIndex(startByte9,  8 - byte9Iterator));
        } else {
            transmitBit(getBitFromIntAtIndex(currentDegree, 8 - byte9Iterator));
            //Serial.print(getBitFromIntAtIndex(currentDegree, 8 - byte9Iterator));
        }
        byte9Iterator++;
        if(byte9Iterator == byte9Size ) {
            byte9Iterator = 0;
            frameIterator ++;
            //Serial.print("   |   ");
        }
        if(frameIterator == frameSize){
            frameIterator = 0;
            transmittingCounter ++;
            //Serial.println("--------"); 
            //Serial.println("");
            if(transmittingCounter > 5) {
                transmitting = false;
                transmittingCounter = 0;
               
            }
        }
    } else {
        uint16_t potiRead = analogRead(poti);
        Serial.println(potiRead);
        Serial.println("---------");
        int16_t newDegree = mapInputToDegree(potiRead);
        if( currentDegree - 1 <= newDegree && currentDegree + 1 >=  newDegree ) {
        }else {
            currentDegree = newDegree;
        }

        transmitting = true;

    }
}