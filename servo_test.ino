#include <Servo.h>

Servo servo1;

void setup() {
  pinMode(1, OUTPUT);
  servo1.attach(3);
}

void loop() {
  servo1.write(75);
  delay(50);
  
  

}
