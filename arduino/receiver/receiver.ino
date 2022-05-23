/* int input = A0;


int ARRAYLENGTH = 200;
int reads[200][2] = {};
int counter = 0;

int lineCounter = 1;

int now;
int then = micros();


void setup() {
  
  pinMode(input, INPUT);
  Serial.begin(115200); // open the serial port at 9600 bps:
  
}


void loop() { 
  if(counter < ARRAYLENGTH) {
  now = micros();
  reads[counter][0] = 1024 - analogRead(input);
  reads[counter][1] = now - then;
  then = now;

  counter++;
  //delayMicroseconds(120);
  }else { 
    Serial.print("LINE "); Serial.print(lineCounter);  Serial.print(": ");
  for(int i = 0; i<ARRAYLENGTH; i++) {
    Serial.print("{ val: ");
    Serial.print(reads[i][0]);
    Serial.print(", time: ");
    Serial.print(reads[i][1]);
    Serial.print(" }, ");
  }
  Serial.println("RESET");
  Serial.println("----");
  lineCounter ++;
   counter = 0;
  }
  
} */