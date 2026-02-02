#include <Servo.h>

Servo myServo;

const int TOO_CLOSE = 20;     // Threshold distance
const int greenPin = 5;      // Green LED (far)
const int redPin   = 7;      // Red LED (close)
const int servoPin = 6;      // Servo signal
const int trigPin  = 10;     // Ultrasonic trig
const int echoPin  = 9;      // Ultrasonic echo

long duration;
int distance;

void setup() {
  myServo.attach(servoPin);

  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);   
}

void loop() {

  //Sweep 
  for (int angle = 15; angle <= 165; angle++) {
    myServo.write(angle);
    delay(15);

    distance = measureDistance();
    sendToProcessing(angle, distance);
    updateLED(distance);
  }

  // Sweep backward
  for (int angle = 165; angle >= 15; angle--) {
    myServo.write(angle);
    delay(15);

    distance = measureDistance();
    sendToProcessing(angle, distance);
    updateLED(distance);
  }
}

int measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;  
}

void sendToProcessing(int angle, int distance) {
  Serial.print(angle);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");
}

void updateLED(int distance) {
  if (distance <= TOO_CLOSE) {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
  } else {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
  }
}
