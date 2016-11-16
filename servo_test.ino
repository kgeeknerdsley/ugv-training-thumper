//activates the servo library
#include <Servo.h>

//gives our servo a name
Servo servo1;

void setup() {
  //sets the pin to output and attaches servo to it
  pinMode(1, OUTPUT);
  servo1.attach(3);
}

void loop() {
  //moves servo 75 deg clockwise
  servo1.write(75);
  delay(50);
  
  //TODO: Add a loop in here to make the servo continuously rotate?

}
