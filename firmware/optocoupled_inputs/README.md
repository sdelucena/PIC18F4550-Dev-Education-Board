# LV62 Optocoupled Inputs Example

This firmware example demonstrates the two isolated optocoupled digital inputs provided on the LV62 PIC18F4550 Dev-Education Board.

## Purpose

The example demonstrates how a 12/24 Vdc field signal can be safely interfaced to the PIC18F4550 through an optocoupler.

The PIC monitors the two optocoupled inputs by polling and uses the two onboard relays to indicate the corresponding input states.

## Hardware

- Microcontroller: PIC18F4550
- Optocoupled Input 1: RB0 / INT0
- Optocoupled Input 2: RB2 / INT2
- Relay 1: RB3
- Relay 2: RC0
- Optocoupled inputs: isolated 12/24 Vdc field signals
- Each optocoupled input has an associated LED indicator.

## Operation

The optocoupled inputs are active LOW.

When a field signal is applied to an optocoupler input, its phototransistor conducts and the corresponding PIC input becomes LOW.

The firmware continuously polls both inputs:

- Input 1 active → Relay 1 ON
- Input 1 inactive → Relay 1 OFF
- Input 2 active → Relay 2 ON
- Input 2 inactive → Relay 2 OFF

No interrupts are used in this example. The purpose is to demonstrate simple polling of isolated digital inputs.

## Software

- MPLAB X IDE
- XC8 compiler v3.10
- System clock: 48 MHz

The source code is contained in `optocoupled_inputs.c`.

## Bootloader Warning

The LV62 uses a HID bootloader occupying the lower area of program memory.

Before building the project, set:

**Project Properties → XC8 Linker → Code Offset = `0x1000`**

This prevents the application from being linked into the bootloader area.

## Tested Configuration

The optocoupled inputs were tested using an external 12/24 Vdc field supply and an industrial pushbutton.

The input indicator LEDs illuminate when the corresponding field input is activated.

The relay outputs are used as visual/functional indication of the detected input states.

## Connection Diagram and Test Setup

The following document shows the connection of two industrial
pushbuttons to the LV62 optocoupled inputs and a photograph of
the actual test setup.

[Connection Diagram and Test Setup](LV62_Optocouplers_with_Two_Industrial_Pushbuttons_Diagram_and_Picture_v1.0.pdf)
