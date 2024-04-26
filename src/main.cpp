#include <Arduino.h>

byte getPWM(byte pin);

const byte pwmInputPin = 3;
const byte tachoInputPin = 2;

const byte pwmOutputPin = 6;
const byte tachoOutputPin = 5;

volatile unsigned long tachoInputCounter = 0;
volatile unsigned long lastMicrosTachoInput;

void countPulses() {
  tachoInputCounter ++;
}

void setup() {
    pinMode(pwmOutputPin, OUTPUT);
    pinMode(pwmInputPin, INPUT);

    pinMode(tachoOutputPin, OUTPUT);
    pinMode(tachoInputPin, INPUT);

    attachInterrupt(digitalPinToInterrupt(tachoInputPin), countPulses, RISING);
    Serial.begin(9600);

    lastMicrosTachoInput = micros();
}

void loop() {
    byte pwm = getPWM(pwmInputPin);

    //analogWrite(pwmOutputPin, pwm);

    unsigned long currentMicros = micros();
  
    // Calculate RPM
    if (currentMicros - lastMicrosTachoInput >= 1000000) {
        Serial.print("Input (PWM): ");
        Serial.print(pwm);
        Serial.print(" Input (Tacho): ");
        Serial.println((tachoInputCounter / 2) * 60);

        // Reset variables
        tachoInputCounter = 0;
        lastMicrosTachoInput = currentMicros;
    }
}

byte getPWM(byte pin)
{
    unsigned long highTime = pulseIn(pin, HIGH, 50000UL);  // 50 millisecond timeout
    unsigned long lowTime = pulseIn(pin, LOW, 50000UL);  // 50 millisecond timeout

    // pulseIn() returns zero on timeout
    if (highTime == 0 || lowTime == 0)
        return digitalRead(pin) ? 255 : 0;

    return (255 * highTime) / (highTime + lowTime);
}