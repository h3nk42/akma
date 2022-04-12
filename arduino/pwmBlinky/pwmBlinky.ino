

int solar = A0;
int now = micros()*62.5;

int numbers[100] {0};
int iterator = 0; 

void setup() {
  pinMode(6, OUTPUT);
  Serial.begin(9600);
}
  void loop() {  
     
   digitalWrite(6, HIGH);
   digitalWrite(6, HIGH);
   digitalWrite(6, HIGH);

   
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
}

