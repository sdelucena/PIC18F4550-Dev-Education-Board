# LV62 — 6-Key ADC Keyboard

## Overview

This firmware example demonstrates the six-key ADC keyboard on the LV62 PIC18F4550 Dev-Education Board.

Six pushbuttons share a resistor-divider network connected to one analog input. The firmware identifies the pressed key from the ADC reading and provides audible confirmation using the onboard active-low buzzer.

## Hardware Connections

| Function | PIC18F4550 pin |
|---|---|
| ADC keyboard input | RA2 / AN2 |
| Active-low buzzer | RB4 |

## Supported Keys

- **Enter** — accept or confirm
- **Escape** — cancel or return
- **Up** — move up
- **Down** — move down
- **Right** — move right
- **Left** — move left

The ADC thresholds are based on measurements from the actual LV62 keyboard circuit.

## Source Files

- `6_key_adc_keyboard.c` — demonstration application.
- `keyboard_6key.c` — keyboard driver implementation.
- `keyboard_6key.h` — public key identifiers and function declarations.

## Driver Interface

Initialize the keyboard:

```c
keyboardInit();
```

Read the current key identifier:

```c
unsigned char key = keyboardRead();
```

The returned value is one of these constants:

- `KEY_NONE`
- `KEY_ENTER`
- `KEY_ESCAPE`
- `KEY_UP`
- `KEY_DOWN`
- `KEY_RIGHT`
- `KEY_LEFT`

The buzzer sounds once when a new key press is confirmed. Holding a key does not generate repeated beeps, and releasing a key does not generate a beep.

## MPLAB X Configuration

- **Target device:** PIC18F4550
- **Compiler:** MPLAB XC8
- **System clock:** 48 MHz
- **Linker Code Offset:** `0x1000`, to preserve the LV62 HID bootloader.

Set the Code Offset under **Project Properties → XC8 Linker → Code Offset**.

## Notes

This example provides a starting point for implementing menu navigation and other user-interface functions using the LV62 six-key ADC keyboard.
