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


/**************************************************************************/
/**************************************************************************/
/**                                                                       */
/**  AUTHOR                                                               */
/**                                                                       */
/**   Mohamed AYED                                                        */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#include "ux_demo_device_hid_descriptors.h"

UCHAR hid_report[] = {
    0x05, 0x81,         // USAGE_PAGE (Vendor defined)
    0x09, 0x82,         // USAGE (Vendor defined)
    0xA1, 0x01,         // COLLECTION (Application)
    0x09, 0x83,         // USAGE (Vendor defined)

    0x09, 0x84,         //     USAGE (Vendor defined)
    0x15, 0x80,         //     LOGICAL_MINIMUM (-128)
    0x25, 0x7F,         //     LOGICAL_MAXIMUM(127)
    0x75, 0x08,         //     REPORT_SIZE (8U)
    0x95, 0x08,         //     REPORT_COUNT (8U)
    0x81, 0x02,         //     INPUT (Data, Variable, Absolute)

    0x09, 0x84,         //     USAGE (Vendor defined)
    0x15, 0x80,         //     LOGICAL_MINIMUM (-128)
    0x25, 0x7F,         //     LOGICAL_MAXIMUM (127)
    0x75, 0x08,         //     REPORT_SIZE (8U)
    0x95, 0x08,         //     REPORT_COUNT (8U)
    0x91, 0x02,         //     OUTPUT (Data, Variable, Absolute)

    0xC0U               // End collection
};

#define UX_HID_GENERIC_REPORT_LENGTH (sizeof(hid_report)/sizeof(hid_report[0]))

UCHAR ux_demo_device_framework_full_speed[] = {
    /* Device Descriptor */
    0x12,                       /* bLength : 18 */
    0x01,                       /* bDescriptorType */
    0x10, 0x01,                 /* bcdUSB : 0x0110 : USB 1.1 */
    0x00,                       /* bDeviceClass : 0x00 : Interface-defined */
    0x00,                       /* bDeviceSubClass : 0x00 : Reset */
    0x00,                       /* bDeviceProtocol : 0x00 : Reset */
    0x40,                       /* bMaxPacketSize0 : 64 */
    UX_W0(UX_DEMO_HID_DEVICE_VID), UX_W1(UX_DEMO_HID_DEVICE_VID), /* idVendor : ... */
    UX_W0(UX_DEMO_HID_DEVICE_PID), UX_W1(UX_DEMO_HID_DEVICE_PID), /* idProduct */
    UX_W0(UX_DEMO_BCD_HID), UX_W1(UX_DEMO_BCD_HID), /* bcdDevice */
    0x01,                       /* iManufacturer */
    0x02,                       /* iProduct */
    0x03,                       /* iSerialNumber */
    0x01,                       /* bNumConfigurations */

    /* Configuration Descriptor */
    0x09,                       /* bLength */
    0x02,                       /* bDescriptorType */
    0x29, 0x00,                 /* wTotalLength */
    0x01,                       /* bNumInterfaces */
    0x01,                       /* bConfigurationValue */
    0x00,                       /* iConfiguration */
    0xC0,                       /* bmAttributes */
                                /* D6 : 0x1 : Self-powered */
                                /* D5, Remote Wakeup : 0x0 : Not supported */
    0x32,                       /* bMaxPower : 50 : 100mA */

    /* Interface Descriptor */
    0x09,                       /* bLength */
    0x04,                       /* bDescriptorType */
    0x00,                       /* bInterfaceNumber */
    0x00,                       /* bAlternateSetting */
    0x02,                       /* bNumEndpoints */
    0x03,                       /* bInterfaceClass : 0x03 : HID */
    UX_DEMO_HID_SUBCLASS,       /* bInterfaceSubClass : ... : Boot/non-boot Subclass */
    0x00,                       /* bInterfaceProtocol : 0x00 : Undefined */
    0x00,                       /* iInterface */

    /* HID Descriptor */
    0x09,                       /* bLength */
    0x21,                       /* bDescriptorType : 0x21 : HID descriptor */
    0x10, 0x01,                 /* bcdHID : 0x0110 */
    0x21,                       /* bCountryCode : 33 : US */
    0x01,                       /* bNumDescriptors */
    0x22,                       /* bReportDescriptorType1 : 0x22 : Report descriptor */
    UX_W0(UX_HID_GENERIC_REPORT_LENGTH), UX_W1(UX_HID_GENERIC_REPORT_LENGTH), /* wDescriptorLength1 */

    /* Endpoint Descriptor IN */
    0x07,                           /* bLength */
    0x05,                           /* bDescriptorType */
    UX_DEMO_HID_ENDPOINT_IN_ADDRESS,/* bEndpointAddress */
                                    /* D7, Direction : 0x01 */
                                    /* D3..0, Endpoint number : 2 */
    0x03,                           /* bmAttributes */
                                    /* D1..0, Transfer Type : 0x3 : Interrupt */
                                    /* D3..2, Synchronization Type : 0x0 : No Synchronization */
                                    /* D5..4, Usage Type : 0x0 : Data endpoint */
    UX_W0(UX_DEMO_HID_ENDPOINT_IN_SIZE), UX_W1(UX_DEMO_HID_ENDPOINT_IN_SIZE), /* wMaxPacketSize */
                                    /* D10..0, Max Packet Size */
                                    /* D12..11, Additional transactions : 0x00 */
    UX_DEMO_HID_ENDPOINT_IN_BINTERVAL_FS, /* bInterval : 8 : 8ms / x128 (FS 128ms/HS 16ms) */

    /* Endpoint Descriptor OUT */
    0x07,                            /* bLength */
    0x05,                            /* bDescriptorType */
    UX_DEMO_HID_ENDPOINT_OUT_ADDRESS,/* bEndpointAddress */
                                     /* D7, Direction : 0x01 */
                                     /* D3..0, Endpoint number : 2 */
    0x03,                            /* bmAttributes */
                                     /* D1..0, Transfer Type : 0x3 : Interrupt */
                                     /* D3..2, Synchronization Type : 0x0 : No Synchronization */
                                     /* D5..4, Usage Type : 0x0 : Data endpoint */
    UX_W0(UX_DEMO_HID_ENDPOINT_OUT_SIZE), UX_W1(UX_DEMO_HID_ENDPOINT_OUT_SIZE), /* wMaxPacketSize */
                                     /* D10..0, Max Packet Size */
                                     /* D12..11, Additional transactions : 0x00 */
    UX_DEMO_HID_ENDPOINT_OUT_BINTERVAL_FS, /* bInterval : 8 : 8ms / x128 (FS 128ms/HS 16ms) */
};


UCHAR ux_demo_device_framework_high_speed[] = {
   /* Device Descriptor */
    0x12,                       /* bLength : 18 */
    0x01,                       /* bDescriptorType */
    UX_W0(UX_DEMO_BCD_USB), UX_W1(UX_DEMO_BCD_USB), /* bcdUSB : 0x0200 : USB 2.0 */
    0x00,                       /* bDeviceClass : 0x00 : Interface-defined */
    0x00,                       /* bDeviceSubClass : 0x00 : Reset */
    0x00,                       /* bDeviceProtocol : 0x00 : Reset */
    0x40,                       /* bMaxPacketSize0 : 64 */
    UX_W0(UX_DEMO_HID_DEVICE_VID), UX_W1(UX_DEMO_HID_DEVICE_VID), /* idVendor  */
    UX_W0(UX_DEMO_HID_DEVICE_PID), UX_W1(UX_DEMO_HID_DEVICE_PID), /* idProduct */
    UX_W0(UX_DEMO_BCD_HID), UX_W1(UX_DEMO_BCD_HID), /* bcdDevice */
    0x01,                       /* iManufacturer */
    0x02,                       /* iProduct */
    0x03,                       /* iSerialNumber */
    0x01,                       /* bNumConfigurations */

    /* Device_Qualifier Descriptor */
    0x0A,                       /* bLength */
    0x06,                       /* bDescriptorType */
    UX_W0(UX_DEMO_BCD_USB), UX_W1(UX_DEMO_BCD_USB), /* bcdUSB : 0x0200 : USB 2.0 */
    0x00,                       /* bDeviceClass : 0x00 : Interface-defined */
    0x00,                       /* bDeviceSubClass : 0x00 : Reset */
    0x00,                       /* bDeviceProtocol : 0x00 : Reset */
    0x40,                       /* bMaxPacketSize0 : 64 */
    0x01,                       /* bNumConfigurations */
    0x00,                       /* bReserved */

    /* Configuration Descriptor */
    0x09,                       /* bLength */
    0x02,                       /* bDescriptorType */
    0x29, 0x00,                 /* wTotalLength */
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
    0x03,                       /* bInterfaceClass */
    UX_DEMO_HID_SUBCLASS,       /* bInterfaceSubClass : ... : Boot/non-boot Subclass */
    0x02,                       /* bInterfaceProtocol : 0x00 : Undefined */
    0x00,                       /* iInterface */

    /* HID Descriptor */
    0x09,                       /* bLength */
    0x21,                       /* bDescriptorType : 0x21 : HID descriptor */
    UX_W0(UX_DEMO_BCD_HID), UX_W1(UX_DEMO_BCD_HID), /* bcdHID : 0x0110 */
    0x21,                       /* bCountryCode : 33 : US */
    0x01,                       /* bNumDescriptors */
    0x22,                       /* bReportDescriptorType1 : 0x22 : Report descriptor */
    UX_W0(UX_HID_GENERIC_REPORT_LENGTH), UX_W1(UX_HID_GENERIC_REPORT_LENGTH), /* wDescriptorLength1  */

    /* Endpoint Descriptor */
    0x07,                           /* bLength */
    0x05,                           /* bDescriptorType */
    UX_DEMO_HID_ENDPOINT_IN_ADDRESS,/* bEndpointAddress */
                                    /* D7, Direction : 0x01 */
                                    /* D3..0, Endpoint number : 2 */
    0x03,                           /* bmAttributes */
                                    /* D1..0, Transfer Type : 0x3 : Interrupt */
                                    /* D3..2, Synchronization Type : 0x0 : No Synchronization */
                                    /* D5..4, Usage Type : 0x0 : Data endpoint */
    UX_W0(UX_DEMO_HID_ENDPOINT_IN_SIZE), UX_W1(UX_DEMO_HID_ENDPOINT_IN_SIZE), /* wMaxPacketSize */
                                    /* D10..0, Max Packet Size */
                                    /* D12..11, Additional transactions : 0x00 */
    UX_DEMO_HID_ENDPOINT_IN_BINTERVAL_HS, /* bInterval : 8 : 8ms / x128 (FS 128ms/HS 16ms) */

    /* Endpoint Descriptor OUT */
    0x07,                            /* bLength */
    0x05,                            /* bDescriptorType */
    UX_DEMO_HID_ENDPOINT_OUT_ADDRESS,/* bEndpointAddress */
                                     /* D7, Direction : 0x01 */
                                     /* D3..0, Endpoint number : 2 */
    0x03,                            /* bmAttributes */
                                     /* D1..0, Transfer Type : 0x3 : Interrupt */
                                     /* D3..2, Synchronization Type : 0x0 : No Synchronization */
                                     /* D5..4, Usage Type : 0x0 : Data endpoint */
    UX_W0(UX_DEMO_HID_ENDPOINT_OUT_SIZE), UX_W1(UX_DEMO_HID_ENDPOINT_OUT_SIZE), /* wMaxPacketSize */
                                     /* D10..0, Max Packet Size */
                                     /* D12..11, Additional transactions : 0x00 */
    UX_DEMO_HID_ENDPOINT_OUT_BINTERVAL_HS, /* bInterval : 8 : 8ms / x128 (FS 128ms/HS 16ms) */
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
    0x09, 0x04, 0x02, 16,
    'H', 'I', 'D', ' ', 'G', 'e', 'n', 'e', 'r', 'i', 'c', ' ', 'D', 'e', 'm', 'o',

    /* Serial Number string descriptor : Index 3 */
    0x09, 0x04, 0x03, 0x04, 0x30, 0x30, 0x30, 0x31
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
