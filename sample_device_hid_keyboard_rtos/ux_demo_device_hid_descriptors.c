/***************************************************************************
 * Copyright (c) 2025-present Eclipse ThreadX Contributors
 *
 * This program and the accompanying materials are made available under the
 * terms of the MIT License which is available at
 * https://opensource.org/licenses/MIT.
 *
 *
 * SPDX-License-Identifier: MIT
 **************************************************************************/
#include "ux_demo_device_hid_descriptors.h"

UCHAR hid_report[] = {
    0x05, 0x01,         // USAGE_PAGE (Generic Desktop)
    0x09, 0x06,         // USAGE (Keyboard)
    0xa1, 0x01,         // COLLECTION (Application)

    /* Modifier Keys (Shift, Ctrl, Alt, GUI) */
    0x05, 0x07,         //     USAGE_PAGE (Key Codes)
    0x19, 0xE0,         //     USAGE_MINIMUM (Left Control)
    0x29, 0xE7,         //     USAGE_MAXIMUM (Right GUI)
    0x15, 0x00,         //     LOGICAL_MINIMUM (0)
    0x25, 0x01,         //     LOGICAL_MAXIMUM (1)
    0x75, 0x01,         //     REPORT_SIZE (1)
    0x95, 0x08,         //     REPORT_COUNT (8)
    0x81, 0x02,         //     INPUT (Data, Variable, Absolute)

    /* Reserved byte */
    0x75, 0x08,         //     REPORT_SIZE (8)
    0x95, 0x01,         //     REPORT_COUNT (1)
    0x81, 0x01,         //     INPUT (Constant)

    /* Key Array (6-Key Rollover) */
    0x05, 0x07,         //     USAGE_PAGE (Key Codes)
    0x19, 0x00,         //     USAGE_MINIMUM (0)
    0x29, 0x65,         //     USAGE_MAXIMUM (101)
    0x15, 0x00,         //     LOGICAL_MINIMUM (0)
    0x25, 0x65,         //     LOGICAL_MAXIMUM (101)
    0x75, 0x08,         //     REPORT_SIZE (8)
    0x95, 0x06,         //     REPORT_COUNT (6)
    0x81, 0x00,         //     INPUT (Data, Array) - Key array

    /* LED Output (Caps Lock, Num Lock, etc.) */
    0x05, 0x08,         //     Usage Page (LEDs)
    0x19, 0x01,         //     Usage Minimum (Num Lock)
    0x29, 0x05,         //     Usage Maximum (Kana)
    0x15, 0x00,         //     Logical Minimum (0)
    0x25, 0x01,         //     Logical Maximum (1)
    0x75, 0x01,         //     Report Size (1)
    0x95, 0x05,         //     Report Count (5)
    0x91, 0x02,         //     OUTPUT (Data, Variable, Absolute)

    /* Padding to make LED section byte-aligned */
    0x75, 0x03,         //     Report Size (3)
    0x95, 0x01,         //     Report Count (1)
    0x91, 0x01,         //     OUTPUT (Constant, Array, Absolute)

    0xc0                // End Collection
};

#define UX_HID_KEYBOARD_REPORT_LENGTH (sizeof(hid_report)/sizeof(hid_report[0]))

UCHAR ux_demo_device_framework_full_speed[] = {
    /* Device Descriptor */
    0x12,                       /* bLength : 18 */
    0x01,                       /* bDescriptorType */
    0x10, 0x01,                 /* bcdUSB : 0x0110 : USB 1.1 */
    0x00,                       /* bDeviceClass : 0x00 : Interface-defined */
    0x00,                       /* bDeviceSubClass : 0x00 : Reset */
    0x00,                       /* bDeviceProtocol : 0x00 : Reset */
    0x08,                       /* bMaxPacketSize0 : 8 : 8 */
    UX_W0(UX_DEMO_HID_DEVICE_VID), UX_W1(UX_DEMO_HID_DEVICE_VID), /* idVendor : ... */
    UX_W0(UX_DEMO_HID_DEVICE_PID), UX_W1(UX_DEMO_HID_DEVICE_PID), /* idProduct */
    0x00, 0x00,                 /* bcdDevice */
    0x00,                       /* iManufacturer */
    0x00,                       /* iProduct */
    0x00,                       /* iSerialNumber */
    0x01,                       /* bNumConfigurations */

    /* Configuration Descriptor, total 34 */
    0x09,                       /* bLength */
    0x02,                       /* bDescriptorType */
    0x22, 0x00,                 /* wTotalLength : 34 */
    0x01,                       /* bNumInterfaces */
    0x01,                       /* bConfigurationValue */
    0x00,                       /* iConfiguration */
    0xc0,                       /* bmAttributes */
                                /* D6 : 0x1 : Self-powered */
                                /* D5, Remote Wakeup : 0x0 : Not supported */
    0x32,                       /* bMaxPower : 50 : 100mA */

    /* Interface Descriptor */
    0x09,                       /* bLength */
    0x04,                       /* bDescriptorType */
    0x00,                       /* bInterfaceNumber */
    0x00,                       /* bAlternateSetting */
    0x01,                       /* bNumEndpoints */
    0x03,                       /* bInterfaceClass : 0x03 : HID */
    UX_DEMO_HID_SUBCLASS,       /* bInterfaceSubClass : ... : Boot/non-boot Subclass */
    0x01,                       /* bInterfaceProtocol : 0x00 : Undefined */
    0x00,                       /* iInterface */

    /* HID Descriptor */
    0x09,                       /* bLength : 9 */
    0x21,                       /* bDescriptorType : 0x21 : HID descriptor */
    0x10, 0x01,                 /* bcdHID : 0x0110 */
    0x21,                       /* bCountryCode : 33 : US */
    0x01,                       /* bNumDescriptors */
    0x22,                       /* bReportDescriptorType1 : 0x22 : Report descriptor */
    UX_W0(UX_HID_KEYBOARD_REPORT_LENGTH), UX_W1(UX_HID_KEYBOARD_REPORT_LENGTH), /* wDescriptorLength1 */

    /* Endpoint Descriptor */
    0x07,                           /* bLength */
    0x05,                           /* bDescriptorType */
    UX_DEMO_HID_ENDPOINT_ADDRESS,   /* bEndpointAddress */
                                    /* D7, Direction : 0x01 */
                                    /* D3..0, Endpoint number : 2 */
    0x03,                           /* bmAttributes */
                                    /* D1..0, Transfer Type : 0x3 : Interrupt */
                                    /* D3..2, Synchronization Type : 0x0 : No Synchronization */
                                    /* D5..4, Usage Type : 0x0 : Data endpoint */
    UX_W0(UX_DEMO_HID_ENDPOINT_SIZE), UX_W1(UX_DEMO_HID_ENDPOINT_SIZE), /* wMaxPacketSize */
                                    /* D10..0, Max Packet Size */
                                    /* D12..11, Additional transactions : 0x00 */
    UX_DEMO_HID_ENDPOINT_BINTERVAL, /* bInterval : 8 : 8ms / x128 (FS 128ms/HS 16ms) */
};


UCHAR ux_demo_device_framework_high_speed[] = {
   /* Device Descriptor */
    0x12,                       /* bLength : 18 */
    0x01,                       /* bDescriptorType */
    UX_W0(UX_DEMO_BCD_USB), UX_W1(UX_DEMO_BCD_USB), /* bcdUSB : 0x0200 : USB 2.0 */
    0x00,                       /* bDeviceClass : 0x00 : Interface-defined */
    0x00,                       /* bDeviceSubClass : 0x00 : Reset */
    0x00,                       /* bDeviceProtocol : 0x00 : Reset */
    0x40,                       /* bMaxPacketSize0 : 64 : 64 */
    UX_W0(UX_DEMO_HID_DEVICE_VID), UX_W1(UX_DEMO_HID_DEVICE_VID), /* idVendor : ... */
    UX_W0(UX_DEMO_HID_DEVICE_PID), UX_W1(UX_DEMO_HID_DEVICE_PID), /* idProduct */
    0x01, 0x00,                 /* bcdDevice */
    0x01,                       /* iManufacturer */
    0x02,                       /* iProduct */
    0x03,                       /* iSerialNumber */
    0x01,                       /* bNumConfigurations */

    /* Device_Qualifier Descriptor */
    0x0a,                       /* bLength */
    0x06,                       /* bDescriptorType */
    UX_W0(UX_DEMO_BCD_USB), UX_W1(UX_DEMO_BCD_USB), /* bcdUSB : 0x0200 : USB 2.0 */
    0x00,                       /* bDeviceClass : 0x00 : Interface-defined */
    0x00,                       /* bDeviceSubClass : 0x00 : Reset */
    0x00,                       /* bDeviceProtocol : 0x00 : Reset */
    0x40,                       /* bMaxPacketSize0 : 64 : 64 */
    0x01,                       /* bNumConfigurations */
    0x00,                       /* bReserved */

    /* Configuration Descriptor, total 34 */
    0x09,                       /* bLength */
    0x02,                       /* bDescriptorType */
    0x22, 0x00,                 /* wTotalLength : 34 */
    0x01,                       /* bNumInterfaces */
    0x01,                       /* bConfigurationValue */
    0x00,                       /* iConfiguration */
    0xc0,                       /* bmAttributes */
                                /* D6 : 0x1 : Self-powered */
                                /* D5, Remote Wakeup : 0x0 : Not supported */
    0x32,                       /* bMaxPower : 50 : 100mA */

    /* Interface Descriptor */
    0x09,                       /* bLength */
    0x04,                       /* bDescriptorType */
    0x00,                       /* bInterfaceNumber */
    0x00,                       /* bAlternateSetting */
    0x01,                       /* bNumEndpoints */
    0x03,                       /* bInterfaceClass : 0x03 : HID */
    UX_DEMO_HID_SUBCLASS,       /* bInterfaceSubClass : ... : Boot/non-boot Subclass */
    0x01,                       /* bInterfaceProtocol : 0x00 : Undefined */
    0x00,                       /* iInterface */

    /* HID Descriptor */
    0x09,                       /* bLength : 9 */
    0x21,                       /* bDescriptorType : 0x21 : HID descriptor */
    UX_W0(UX_DEMO_BCD_HID), UX_W1(UX_DEMO_BCD_HID), /* bcdHID : 0x0110 */
    0x21,                       /* bCountryCode : 33 : US */
    0x01,                       /* bNumDescriptors */
    0x22,                       /* bReportDescriptorType1 : 0x22 : Report descriptor */
    UX_W0(UX_HID_KEYBOARD_REPORT_LENGTH), UX_W1(UX_HID_KEYBOARD_REPORT_LENGTH), /* wDescriptorLength1  */

    /* Endpoint Descriptor */
    0x07,                           /* bLength */
    0x05,                           /* bDescriptorType */
    UX_DEMO_HID_ENDPOINT_ADDRESS,   /* bEndpointAddress */
                                    /* D7, Direction : 0x01 */
                                    /* D3..0, Endpoint number : 2 */
    0x03,                           /* bmAttributes */
                                    /* D1..0, Transfer Type : 0x3 : Interrupt */
                                    /* D3..2, Synchronization Type : 0x0 : No Synchronization */
                                    /* D5..4, Usage Type : 0x0 : Data endpoint */
    UX_W0(UX_DEMO_HID_ENDPOINT_SIZE), UX_W1(UX_DEMO_HID_ENDPOINT_SIZE), /* wMaxPacketSize */
                                    /* D10..0, Max Packet Size */
                                    /* D12..11, Additional transactions : 0x00 */
    UX_DEMO_HID_ENDPOINT_BINTERVAL, /* bInterval : 8 : 8ms / x128 (FS 128ms/HS 16ms) */
};


/* String Device Framework :
   Byte 0 and 1 : Word containing the language ID : 0x0904 for US
   Byte 2       : Byte containing the index of the descriptor
   Byte 3       : Byte containing the length of the descriptor string
*/
UCHAR ux_demo_string_framework[] = {

    /* Manufacturer string descriptor : Index 1 */
    0x09, 0x04, 0x01, 12,
    'U', 'S', 'B', 'X', ' ', 'e', 'c', 'l', 'i', 'p', 's', 'e',

    /* Product string descriptor : Index 2 */
    0x09, 0x04, 0x02, 17,
    'H', 'I', 'D', ' ', 'K', 'e', 'y', 'b', 'o', 'a', 'r', 'd', ' ', 'D', 'e', 'm', 'o',

    /* Serial Number string descriptor : Index 3 */
    0x09, 0x04, 0x03, 0x04,
    0x30, 0x30, 0x30, 0x31
};


/* Multiple languages are supported on the device, to add
   a language besides english, the unicode language code must
   be appended to the language_id_framework array and the length
   adjusted accordingly. */
UCHAR ux_demo_language_id_framework[] = {
    /* English. */
    0x09, 0x04
};


UCHAR* ux_demo_get_high_speed_framework(VOID)
{
    return ux_demo_device_framework_high_speed;
}

ULONG ux_demo_get_high_speed_framework_length(VOID)
{
    return sizeof(ux_demo_device_framework_high_speed);
}

UCHAR* ux_demo_get_full_speed_framework(VOID)
{
    return ux_demo_device_framework_full_speed;
}

ULONG ux_demo_get_full_speed_framework_length(VOID)
{
    return sizeof(ux_demo_device_framework_full_speed);
}

UCHAR* ux_demo_get_string_framework(VOID)
{
    return ux_demo_string_framework;
}

ULONG ux_demo_get_string_framework_length(VOID)
{
    return sizeof(ux_demo_string_framework);
}

UCHAR* ux_demo_get_language_framework(VOID)
{
    return ux_demo_language_id_framework;
}

ULONG ux_demo_get_language_framework_length(VOID)
{
    return sizeof(ux_demo_language_id_framework);
}

UCHAR* ux_demo_device_hid_get_report(VOID)
{
    return hid_report;
}

ULONG ux_demo_device_hid_get_report_length(VOID)
{
    return (sizeof(hid_report)/sizeof(hid_report[0]));
}