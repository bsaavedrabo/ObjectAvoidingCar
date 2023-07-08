
// Object-avoiding car implemented in Arduino. 


#include <HCSR04.h>

// Ultrasonic sensor pins:
int TRIG = A0;
int ECHO = A1;

UltraSonicDistanceSensor ultrasonic(TRIG, ECHO);
float distance;

// Left motor
int LEFT_MOTOR_SPEED_PIN = 3; // enabler B
int LEFT_MOTOR_FORWARD_PIN = 4;
int LEFT_MOTOR_BACKWARD_PIN = 5;

// Right motor
int RIGHT_MOTOR_SPEED_PIN = 13; // enabler A
int RIGHT_MOTOR_FORWARD_PIN = 12;
int RIGHT_MOTOR_BACKWARD_PIN = 11;


void setup() {
    pinMode(LEFT_MOTOR_SPEED_PIN, OUTPUT);
    pinMode(LEFT_MOTOR_FORWARD_PIN, OUTPUT);
    pinMode(LEFT_MOTOR_BACKWARD_PIN, OUTPUT);
    pinMode(RIGHT_MOTOR_SPEED_PIN, OUTPUT);
    pinMode(RIGHT_MOTOR_FORWARD_PIN, OUTPUT);
    pinMode(RIGHT_MOTOR_BACKWARD_PIN, OUTPUT);

    Serial.begin(9600);

    digitalWrite(LEFT_MOTOR_SPEED_PIN, HIGH);
    digitalWrite(RIGHT_MOTOR_SPEED_PIN, HIGH);
}

void loop() {

    distance = ultrasonic.measureDistanceCm(); // Use 'CM' for centimeters or 'INC' for inches
    Serial.println(distance);

    if (distance > -1 && distance < 25) {
        stop();
        delay(1000);
        goBackward();
        delay(300);
        stop();
        delay(1000);
      // randomly decide to go left or right: 
        if (random(0, 2) == 0) {
            goLeft();
        } else {
            goRight();
        }

        delay(500);
        stop();
        delay(700);
    } else {
        goForward();
    }
}

void goForward() {
    digitalWrite(LEFT_MOTOR_FORWARD_PIN, HIGH);
    digitalWrite(LEFT_MOTOR_BACKWARD_PIN, LOW);
    digitalWrite(RIGHT_MOTOR_FORWARD_PIN, HIGH);
    digitalWrite(RIGHT_MOTOR_BACKWARD_PIN, LOW);
}

void goBackward() {
    digitalWrite(LEFT_MOTOR_FORWARD_PIN, LOW);
    digitalWrite(LEFT_MOTOR_BACKWARD_PIN, HIGH);
    digitalWrite(RIGHT_MOTOR_FORWARD_PIN, LOW);
    digitalWrite(RIGHT_MOTOR_BACKWARD_PIN, HIGH);
}

void stop() {
    digitalWrite(LEFT_MOTOR_FORWARD_PIN, LOW);
    digitalWrite(LEFT_MOTOR_BACKWARD_PIN, LOW);
    digitalWrite(RIGHT_MOTOR_FORWARD_PIN, LOW);
    digitalWrite(RIGHT_MOTOR_BACKWARD_PIN, LOW);
}

void goRight() {
    digitalWrite(LEFT_MOTOR_FORWARD_PIN, HIGH);
    digitalWrite(LEFT_MOTOR_BACKWARD_PIN, LOW);
    digitalWrite(RIGHT_MOTOR_FORWARD_PIN, LOW);
    digitalWrite(RIGHT_MOTOR_BACKWARD_PIN, LOW);
}

void goLeft() {
    digitalWrite(LEFT_MOTOR_FORWARD_PIN, LOW);
    digitalWrite(LEFT_MOTOR_BACKWARD_PIN, LOW);
    digitalWrite(RIGHT_MOTOR_FORWARD_PIN, HIGH);
    digitalWrite(RIGHT_MOTOR_BACKWARD_PIN, LOW);
}
