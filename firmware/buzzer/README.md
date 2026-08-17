# LV62 Buzzer Example

This is the first firmware example for the LV62 PIC18F4550 Dev-Education Board.

## Purpose

This example demonstrates how to configure and control the LV62 on-board buzzer using a PIC18F4550 digital I/O pin.

## Hardware

- Microcontroller: PIC18F4550
- Buzzer control: RB4
- RB4 is configured as a digital output.
- The buzzer is active-low.

## Software

- MPLAB X IDE
- XC8 compiler
- System clock: 48 MHz

## Operation

After initialization, the program repeatedly calls `beep()`. The function generates a short audible tone by changing RB4 between its active and inactive states with software delays.

The source code is contained in `buzzer.c`.
