//activates the servo library
#include <Servo.h>

//gives our servo a name
Servo servo1;

int pos = 0; //variable to store the servo position

void setup() {
  //sets the pin to output and attaches servo to it
  pinMode(1, OUTPUT);
  servo1.attach(3); //attach the servo on pin 3 (orange pin)

  //attach red pin to 5V and brown pin to GND
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    servo1.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
