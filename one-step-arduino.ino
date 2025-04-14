// Written by: Christopher Gholmieh
// Include:

// Library:
#include <stdlib.h>

// Constants:
const int input_pins[] = {13, 12, 11, 10, 9, 8, 7, 6};
const int motor_pin = 5;

const int motor_direction_one = 40;
const int motor_direction_two = 42;

const int stop_pin = 4;

// Prone:
int input_representation[] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};

// Methods:
/**
    @param binary_bits An array of bits representing 8-bit binary.
      @example: [0,   0,  0,  0,  0, 0, 0, 0]
      @example  [128, 64, 32, 16, 8, 4, 2, 1]
*/
int calculate_number_from_binary_bits(int* binary_bits) {
    // Variables (Assignments):
    // Representations:
    const int representations[] = {128, 64, 32, 16, 8, 4, 2, 1};

    // Number:
    int number = 0;

    // Logic:
    for (int iteration = 0; iteration < 8; iteration++) {
        number += representations[iteration] * binary_bits[iteration];
    }

    return number;
}

int* transform_representations_into_bits() {
    // Variables (Assignment):
    // Bits:
    static int bits[8];

    // Logic:
    for (int iteration = 0; iteration < 8; iteration++) {
        if (input_representation[iteration] == LOW) {
            bits[iteration] = 0;
        } else {
            bits[iteration] = 1;
        }
    }

    return bits;
}


// Setup:
void setup() {
    // Initialization:
    Serial.begin(9600);

    // GPIO:
    for (int iteration = 0; iteration < 8; iteration++) {
        pinMode(input_pins[iteration], INPUT);
    }

    // Motor:
    pinMode(motor_pin, OUTPUT);

    // Stop:
    pinMode(stop_pin, INPUT);
}


// Loop:
void loop() {
    // Logic:
    for (int iteration = 0; iteration < 8; iteration++) {
        input_representation[iteration] = digitalRead(input_pins[iteration]);
    }

    // Variables (Assignment):
    // Bits:
    int* bits = transform_representations_into_bits();

    Serial.print("Binary: ");

    for (int iteration = 0; iteration < 8; iteration++) {
        Serial.print(bits[iteration]);
    }

    // PWM:
    int PWM = calculate_number_from_binary_bits(bits);

    // Logic:
    if (digitalRead(stop_pin) == LOW) {
        analogWrite(motor_pin, 0);
        digitalWrite(motor_direction_one, LOW);

        return;
    }

    digitalWrite(motor_direction_one, HIGH);
    digitalWrite(motor_direction_two, LOW);
    analogWrite(motor_pin, PWM);
    
    // Logic:
    delay(500);
}
