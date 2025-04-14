# One-Step-Arduino
The official source code repository connecting binary signals from a raspberry pi to an arduino circuit.

## Installation
To install this project, simply create a arduino sketch and paste the one-step-arduino.ino code. Subsequently, press the upload button once your arduino unit is connected to your computer, and ensure that the pin mappings correspond to the constants in the code.
**Change the constants if necessary to fit your specific needs.**
```c
// Constants:
const int input_pins[] = {13, 12, 11, 10, 9, 8, 7, 6};
const int motor_pin = 5;

const int motor_direction_one = 40;
const int motor_direction_two = 42;

const int stop_pin = 4;
```

## Bits
Through the utilization of the Arduino input pins, LOW signals are converted to zeroes while HIGH signals are converted to ones.
- Notice that the **static** keyword was used to prevent memory leaks as overwriting memory was more efficient than constantly creating memory for non-dynamic arrays.

```c
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
```

## Circuit
The Raspberry Pi transmits binary signals using eight output pins, with LOW representing off and HIGH representing on.
- Using a logic level shifter, the 3.3V signals from the Raspberry Pi are converted into 5V signals and are transmitted to the Arduino pins.
- Utilizing a bit to binary conversion function, the value sent from the Raspberry Pi was succesfully transferred.

```c
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
```

## Perpetual Motion
A huge problem encountered during the project was the motor continously moving in perpetual motion. To combat this, our **one-step-learner** detects whether a person is walking forwards or backwards, and updates a **STOP** pin, as well as clearing the other bits to zeroes.
- Once a **STOP** bit has been activated, the Arduino circuit will prevent writing power to the motor until the **STOP** bit has been cleared.

```c
if (digitalRead(stop_pin) == LOW) {
    analogWrite(motor_pin, 0);
    digitalWrite(motor_direction_one, LOW);

    return;
}

digitalWrite(motor_direction_one, HIGH);
digitalWrite(motor_direction_two, LOW);
analogWrite(motor_pin, PWM);
```
