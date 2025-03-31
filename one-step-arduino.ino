// Written by: Christopher Gholmieh
// Include:

// Library:
#include <stdlib.h>

// Constants:
const int input_pins[] = {1, 2, 3, 4, 5, 6, 7, 8};

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

    for (int iteration = 0; iteration < 8; iteration++) {
        pinMode(input_pins[iteration], INPUT);
    }
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

    Serial.print(" -> Decimal: ");
    Serial.println(PWM);

    // Logic:
    delay(500);
}
