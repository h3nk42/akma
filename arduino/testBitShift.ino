

int number = 255;
void setup(){


    Serial.begin(115200);
}

void loop() {
    Serial.println("---");
for (uint8_t i =0; i<8; i++) {
    Serial.print((number & ( 1 << i )) >> i);
}
delay(500);
}