# LV62 4-Digit 7-Segment Display Example

Purpose
Hardware
Display Interface
Operation
Software
Bootloader Warning
Tested Configuration

RD3..RD0   BCD data
RD7        Thousands latch
RD6        Hundreds latch
RD5        Tens latch
RD4        Units latch

Latch Disable = 0 → normal state

To update a digit:

1. Put the BCD value on RD3..RD0.
2. Set the corresponding latch control HIGH.
3. Wait 100 µs.
4. Return the latch control LOW.

# LV62 4-Digit 7-Segment Display Example

![LV62 4-Digit 7-Segment Display showing 3092 mV](LV62_4_digit_7seg_display_3092mV.png)

This firmware example demonstrates the 4-digit 7-segment LED display provided on the LV62 PIC18F4550 Dev-Education Board.

## Purpose

The example demonstrates how to control a 4-digit red, common-cathode 7-segment LED display using four HEF4543 BCD-to-7-segment latch/decoder/drivers.

The firmware implements a four-digit counter with a resolution of 1/4 second.

The counter runs from:

    0000 → 0001 → 0002 → ... → 9999 → 0000

## Hardware

- Microcontroller: PIC18F4550
- Display: 4-digit red, common-cathode 7-segment LED display
- BCD-to-7-segment devices: 4 × HEF4543
- BCD data bus: RD3..RD0
- Thousands latch control: RD7
- Hundreds latch control: RD6
- Tens latch control: RD5
- Units latch control: RD4

Each display digit has its own HEF4543 latch/decoder/driver.

No display multiplexing is required.

## Display Interface

The four BCD data lines are shared by all four HEF4543 devices.

| PIC18F4550 | Function |
|------------|----------|
| RD3 | BCD D |
| RD2 | BCD C |
| RD1 | BCD B |
| RD0 | BCD A |
| RD7 | Thousands latch |
| RD6 | Hundreds latch |
| RD5 | Tens latch |
| RD4 | Units latch |

The BCD value of only one digit at a time is placed on RD3..RD0.

## Latch Operation

The latch control inputs are normally LOW.

To write a new digit:

1. Put the BCD value on RD3..RD0.
2. Set the corresponding latch control HIGH.
3. Keep it HIGH for 100 µs.
4. Return the latch control LOW.

The selected HEF4543 then retains the new BCD value.

## Operation

After initialization, the display starts at 0000.

The counter is incremented every 250 ms:

    0000
    0001
    0002
    ...
    9999
    0000

The four decimal digits are extracted from the counter value and written individually to the four HEF4543 latches.

## Software

- MPLAB X IDE
- XC8 compiler v3.10
- System clock: 48 MHz

The source code is contained in `4_digit_7seg_display.c`.

## Bootloader Warning

The LV62 uses a HID bootloader occupying the lower area of program memory.

Before building the project, set:

**Project Properties → XC8 Linker → Code Offset = `0x1000`**

This prevents the application from being linked into the bootloader area.

## Tested Configuration

The firmware was programmed into the LV62 PIC18F4550 Dev-Education Board and tested using the onboard 4-digit 7-segment LED display.

The counter operated correctly from 0000 through 9999 and returned to 0000 after 9999.
