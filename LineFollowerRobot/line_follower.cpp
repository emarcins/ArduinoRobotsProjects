// --- Speed Settings ---
int forwardSpeed = 100;
int turnSpeed = 110;

// Sensor Pins
const int leftSensor = 2;
const int midSensor = 3;
const int rightSensor = 4;

// Motor Pins(PWM Capable)
const int leftMotorForward = 9;
const int leftMotorBackward = 10;
const int rightMotorForward = 6;
const int rightMotorBackward = 5;

void setup() {
    pinMode(leftSensor, INPUT);
    pinMode(midSensor, INPUT);
    pinMode(rightSensor, INPUT);
    
    pinMode(leftMotorForward, OUTPUT);
    pinMode(leftMotorBackward, OUTPUT);
    pinMode(rightMotorForward, OUTPUT);
    pinMode(rightMotorBackward, OUTPUT);

    moveForward();
}


void loop() {
    int L = digitalRear(leftSensor);
    int M = digitalRear(midSensor);
    int R = digitalRear(rightSensor);


// Logic: 0 = Line Detected(Black), 1 = Floor (White)
    if (M == 0) {
        moveForward();
    }
    else if (L == 0) {
        turnLeft();
    }
    else if (R == 0) {
        turnRight();
    }
}

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