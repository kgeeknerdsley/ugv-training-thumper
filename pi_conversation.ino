byte incoming = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()) {
    incoming = Serial.read();
    Serial.print("Number received: ");
    Serial.println(incoming ,DEC);
  }
}
