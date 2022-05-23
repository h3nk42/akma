int solar = A0;
int solar2 = A1;

int diode = 7;

int lastDiff = 0;

int THRESHHOLD = 30;



int now = micros()*62.5;
int numbers[100] {0};
int iterator = 0; 


void setup(){
 
 Serial.begin(9600);
 pinMode(solar, INPUT); 
  pinMode(solar2, INPUT); 
  pinMode(diode, OUTPUT); 
}

void loop(){
  digitalWrite(diode, HIGH);
  int diff = analogRead(solar) - analogRead(solar2);
  //Serial.println(diff);
  if(diff-lastDiff > THRESHHOLD | diff-lastDiff < -THRESHHOLD) {
     //Serial.println("laser on");
     lastDiff = 0;
  } else {
    lastDiff = diff;
  }
  
  
    int eben = now;
   now = micros()*62.5;
   int difference = now - eben;
   if ( iterator < 100  ) {
   numbers[iterator] = difference;
   iterator++;
   }
     if(iterator == 99 ) {
       for (int i=0; i<100; i++) {
         Serial.print(numbers[i]);
         Serial.print("  , ");
       }
     Serial.println("  , ");
     iterator = 0;
     now = micros()*62.5;
   }  
   
 
 //delay(250);
}
