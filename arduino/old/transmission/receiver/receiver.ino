#define THRESHOLD 50
#define INTERVAL_TIME 10

int solarRead;
int index = 0;
int startBitIndex = 0;

int solar = A0;
int ambientRead = 1020;


int pinA = 3;
int pinB = 2;
int pinC = 4;
int pinD = 5;
int pinDot = 6;
int pinE = 7;
int pinF = 8;
int pinG = 9;
int D1 = 10;
int D2 = 11;
int D3 = 12;
int D4 = 13;

unsigned long then = 0;
unsigned long then2 = 0;
unsigned long then3 = 0;
unsigned long now;

boolean reading = false;
boolean printReading = false;
boolean expectingTransmission = false;

int rBits[32];
int bits[8];

void setup() {

  Serial.begin(9600);

  pinMode(solar, INPUT);

  // initialize the digital pins as outputs.
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  
   digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  
  
}

void loop() {
      unsigned long now = millis();

      if (now - then >= INTERVAL_TIME) {
      then = now;
      solarRead = analogRead(solar);
      if( solarRead < 950 ) {
        
        if (reading) {
          rBits[index] = HIGH;
          index ++;
        } else {
          startBitIndex++;
        }
      } else {
        if (reading) {
          rBits[index] = LOW;
          index ++;
        } else {
          startBitIndex = 0;
        }
      }
      if (startBitIndex == 8) {
        //Serial.print("8");
        startBitIndex = 0;
        //expectingTransmission = true;
        reading = true;
        //return 0;
      }
      if (index == 32) {
        reading = false;
        printReading = true;
        index = 0;
        then2 = now;
        for (int i = 0; i < 32; i++) {
          Serial.print(rBits[i]);
        }
        Serial.println(" ");
      }
        
    } 
}
