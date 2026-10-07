# PIC18F4550 Dev-Education Board

![LV62 PIC18F4550 Dev-Education Board](hardware/board_photos/LV62_Overview_Multiple_Boards.jpg)

This project is a development and education board based on the Microchip PIC18F4550,
designed for both teaching and real firmware development using MPLAB X and the XC8 compiler.

The board provides access to the main peripherals of the PIC18 architecture and is intended
for hands-on learning at register level, without hiding details behind high-level libraries.

## Main Features

- Microcontroller: PIC18F4550
- USB interface (CDC / HID capable)
- Analog-to-Digital Converter (ADC)
- Timers and interrupts
- PWM outputs
- Digital I/O
- On-board clock circuitry
- Regulated power supply
- ICSP programming/debug support

## Firmware

All firmware examples are written in:
- MPLAB X IDE
- XC8 compiler

Each peripheral has a dedicated test project, focused on clarity and didactic value.

## Firmware Examples

The repository currently includes the following independent firmware examples:

- [Buzzer](firmware/buzzer/) — simple active-low buzzer control.
- [Relays](firmware/relays/) — control of two onboard relays.
- [Optocoupled Inputs](firmware/optocoupled_inputs/) — isolated 12/24 Vdc digital inputs.
- [4-Digit 7-Segment Display](firmware/4_digit_7seg_display/) — 4-digit display control using four HEF4543 BCD-to-7-segment latch/decoder/drivers.

Each example is a self-contained MPLAB X / XC8 project and is intended to demonstrate one hardware function of the LV62 board.

## Hardware Documentation

- **Block Diagram**
  [LV62_Block_Diagram_v1.0.pdf](hardware/block_diagram/LV62_Block_Diagram_v1.0.pdf)

- **Schematics and Board Functional Diagram**  
  [LV62_Schematics_and_Board_Functional_Diagram_v1.0.pdf](hardware/schematics/LV62_Schematics_and_Board_Functional_Diagram_v1.0.pdf)

## Target Audience

- Engineering and technical students
- Educators
- Embedded systems developers and hobbyists
- Anyone interested in low-level PIC microcontroller programming

## Status

Documentation and firmware examples are being progressively organized and published.

## Author

Samuel Euzedice de Lucena

