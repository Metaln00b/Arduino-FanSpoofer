#include <Arduino.h>

byte getPWM(byte pin);
byte getTacho(byte pin);

const byte pwmInputPin = 3;
const byte tachoInputPin = 9;

const byte pwmOutputPin = 6;
const byte tachoOutputPin = 5;

void setup() {
    pinMode(pwmOutputPin, OUTPUT);
    pinMode(pwmInputPin, INPUT);

    pinMode(tachoOutputPin, OUTPUT);
    pinMode(tachoInputPin, INPUT);
    Serial.begin(9600);
}

void loop() {
    byte pwm = getPWM(pwmInputPin);
    byte tacho = getTacho(tachoInputPin);

    analogWrite(pwmOutputPin, pwm);
    analogWrite(tachoOutputPin, tacho);

    Serial.print("Input (PWM): ");
    Serial.print(pwm);
    Serial.print(" Input (Tacho): ");
    Serial.println(tacho);
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

byte getTacho(byte pin)
{
    unsigned long highTime = pulseIn(pin, HIGH, 5000000UL);
    unsigned long lowTime = pulseIn(pin, LOW, 5000000UL);

    // pulseIn() returns zero on timeout
    if (highTime == 0 || lowTime == 0)
        return digitalRead(pin) ? 255 : 0;

    return (255 * highTime) / (highTime + lowTime);
}