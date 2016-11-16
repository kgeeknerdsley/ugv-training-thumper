#define trigPin 0
#define echoPin 1

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  //sets up some dank math variables
  long duration;
  long distance;
  
  //sends out the wave pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  //math calc to find distance
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  pulseIn(echoPin, LOW);
  
  Serial.println(distance);
  
  //print out the data to monitor
//  if(distance >= 200 || distance <= 0) {
//    Serial.println("SHIT'S BROKE FAM");
//  } else {
//    Serial.println(distance);
//  }
}
