#include <Servo.h>

// --- Speed Settings ---
int forwardSpeed = 140;
int turnSpeed = 130;
int stopDistance = 25; //Stop if obstacle is closer than 25cm

// Pins
const int servoPin = 4;
const int trigPin = 12;
const int echoPin = 13;

// Motor Pins(PWM Capable)
const int leftMotorForward = 3;
const int leftMotorBackward = 11;
const int rightMotorForward = 6;
const int rightMotorBackward = 5;

void setup() {
Serial.begin(9600);

    pinMode(trigPin, INPUT);
    pinMode(echoPin, INPUT); 
    
    pinMode(leftMotorForward, OUTPUT);
    pinMode(leftMotorBackward, OUTPUT);
    pinMode(rightMotorForward, OUTPUT);
    pinMode(rightMotorBackward, OUTPUT);

    myServo.attach(servoPin);
    myServo.write(90); // look straight ahead
    delay(1000);
}


void loop() {
    int distanceFront = getDistance();

    if(distanceFront > stopDistance) {
        moveForward();
    }
    else {
        stopRobot();
        delay(500);

        // look around
        int distanceLeft = lookLeft();
        delay(300);
        int distanceRight = lookRight();
        delay(300);

        if (distanceLeft >= distanceRight) {
            turnLeft();
            delay(800); // spin for a half a second (adjust based on your battery/motors)
        }
        else {
            turnRight();
            delay(800);
        }
        stopRobot(); // re-center and check again in the next loop
    }
}


int getDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH);
    int distance = duration * 0.034 / 2;

    if (distance == 0) distance = 400; // pulseIn timeout or out of range
    return distance;
}

int lookLeft() {
    myServo.write(150);
    delay(500);
    int dist = getDistance();
    myServo.write(90); // return tgo center
    return dist;
}

int lookRight() {
    myServo.write(30);
    delay(500);
    int dist = getDistance();
    myServo.write(90); // return tgo center
    return dist;
}

// movement functions (robot turns)

void moveForward() {
    analogWrite(leftMotorForward, forwardSpeed);
    analogWrite(leftMotorBackward, 0);
    analogWrite(rightMotorForward, forwardSpeed);
    analogWrite(rightMotorBackward, 0);
}

void turnLeft() {
    analogWrite(leftMotorForward, 0);
    analogWrite(leftMotorBackward, turnSpeed);
    analogWrite(rightMotorForward, turnSpeed);
    analogWrite(rightMotorBackward, 0);
}

void turnRight() {
    analogWrite(leftMotorForward, turnSpeed);
    analogWrite(leftMotorBackward, 0);
    analogWrite(rightMotorForward, forwardSpeed);
    analogWrite(rightMotorBackward, turnSpeed);
}

void turnRight() {
    analogWrite(leftMotorForward, 0);
    analogWrite(leftMotorBackward, 0);
    analogWrite(rightMotorForward, 0);
    analogWrite(rightMotorBackward, 0);
}