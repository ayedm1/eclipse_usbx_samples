
## Overview

This example works as a USB HID device. It will appear as a USB keyboard device on PC.

  - Write lowercase character.
  - Write uppercase character.
  - Write number.
  - Write special character.

This application demo is running in standalone mode (without RTOS).

## USB Specification

- USB 2.0 Universal Serial BUS : https://www.usb.org/document-library/usb-20-specification
- USB HID Class : https://www.usb.org/document-library/device-class-definition-hid-111
- USB HID Usage Tables : https://usb.org/document-library/hid-usage-tables-16

## Report Descriptor

A HID (Human Interface Device) mouse report descriptor defines how data is sent from the device (mouse) to the host (computer). Below is a standard USB HID mouse report descriptor for a 3-button mouse with X and Y movement and wheel.

### Report Format

This descriptor defines a 4-byte report format:

|Byte |	Description                       | Example |
| --- | --------------------------------- | ------- |
|0    | Modifier Keys (Shift, Ctrl, etc.) | 0x02 (Left Shift) |
|1    | Reserved (0x00)                   | 0x00 |
|2-7  | Keycodes (Up to 6 keys)	          | 0x04, 0x05, 0x00 (A, B) |

## Run the example

  - Run application.
  - Open new text file.
  - Plug-in the device, which is running HID keyboard example, into the PC. A HID-compliant keyboard is enumerated in the Device Manager.
