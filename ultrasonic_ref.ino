/* 
  THIS CODE IS REFERENCE MATERIAL AND SHOULD NOT BE MODIFIED WITHOUT GOOD REASON

  Datasheet for component:
   http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf 
 */
 
const int trigPin = 12;
const int echoPin = 13;
 
void setup() {
  // initialize serial communication:
  Serial.begin(9600);
}
 
void loop()
{
  //vars for calculations
  long duration, inches, cm;
 
  //send out the pulse from sensor, should be 10+ ms
  //setting to LOW before the HIGH makes signal cleaner
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  //reads the pulse that's come back
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  //print out data
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  //wait before starting over
  //can be as long as you want depending on how frequently the data is needed
  delay(100);
}
 
long microsecondsToInches(long microseconds)
{
  //calculation comes from Parallax's datasheet
  
  return microseconds / 74 / 2;
}
 
long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
