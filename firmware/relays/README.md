# LV62 Relay Example

This is the second firmware example for the LV62 PIC18F4550 Dev-Education Board.

## Purpose

This example demonstrates how to control the two electromechanical relays provided on the LV62 board using PIC18F4550 digital I/O pins.

## Hardware

- Microcontroller: PIC18F4550
- Relay 1 control: RB3
- Relay 2 control: RC0
- Each relay has an associated LED indicator.
- The relay contacts are currently operated without an external load.

## Software

- MPLAB X IDE
- XC8 compiler
- System clock: 48 MHz

## Operation

The program alternately activates Relay 1 and Relay 2.

Only one relay is activated at a time. Each relay remains activated for approximately 1.5 seconds, while its corresponding LED indicator is illuminated.

The source code is contained in `relays.c`.

## Future Application

The relay outputs will subsequently be tested with external loads, including a lamp and an AC asynchronous motor.
