# One-Step-Arduino
The official source code repository connecting binary signals from a raspberry pi to an arduino circuit.

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
switch (digitalRead(stop_pin)) {
    case LOW:
        {
            digitalWrite(motor_direction_one, HIGH);
            analogWrite(motor_pin, PWM);

            break;
        }

    case HIGH:
        {
            digitalWrite(motor_direction_one, LOW);
            analogWrite(motor_pin, 0);

            break;
        }
}
```
