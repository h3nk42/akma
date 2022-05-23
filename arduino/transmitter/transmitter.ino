/* uint8_t laser = 11;

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

void setup() {
  fillFrame();

  pinMode(laser, OUTPUT);
}

void writeBit(boolean bit) {
  digitalWrite(laser, HIGH);
  bit ? delayMicroseconds(pulseWidthHigh) : delayMicroseconds(pulseWidthLow);
  digitalWrite(laser, LOW);
  bit ? delayMicroseconds(period -  pulseWidthHigh) : delayMicroseconds(period -  pulseWidthLow);
}

void loop() {
  writeBit(frame[frameIterator][byte9Iterator]);
  byte9Iterator++;
  if(byte9Iterator == byte9Size ) {
    byte9Iterator = 0;
    frameIterator ++;
  }
  if(frameIterator == frameSize){
    frameIterator = 0;
  }
} */