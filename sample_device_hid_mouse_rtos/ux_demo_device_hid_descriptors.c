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
    0x05, 0x01,         // USAGE_PAGE (Generic Desktop)
    0x09, 0x02,         // USAGE (Mouse)
    0xa1, 0x01,         // COLLECTION (Application)

    /* Pointer and Physical are required by Apple Recovery */
    0x09, 0x01,         //   USAGE (Pointer)
    0xa1, 0x00,         //   COLLECTION (Physical)

    /* 3 Buttons */
    0x05, 0x09,         //     USAGE_PAGE (Button)
    0x19, 0x01,         //     USAGE_MINIMUM (Button 1)
    0x29, 0x03,         //     USAGE_MAXIMUM (Button 3)
    0x15, 0x00,         //     LOGICAL_MINIMUM (0)
    0x25, 0x01,         //     LOGICAL_MAXIMUM (1)
    0x75, 0x01,         //     REPORT_SIZE (1)
    0x95, 0x03,         //     REPORT_COUNT (3) -> 3 buttons
    0x81, 0x02,         //     INPUT (Data, Variable, Absolute) -> Buttons

    0x75, 0x05,         //     REPORT_SIZE (5)
    0x95, 0x01,         //     REPORT_COUNT (1)
    0x81, 0x03,         //     INPUT (Constant, Variable, Absolute) -> Padding bits

    /* X, Y */
    0x05, 0x01,         //     USAGE_PAGE (Generic Desktop)
    0x09, 0x30,         //     USAGE (X)
    0x09, 0x31,         //     USAGE (Y)
#ifdef UX_DEMO_MOUSE_ABSOLUTE
    0x16, 0x00, 0x00,   //     LOGICAL_MINIMUM (0)
    0x26, 0xFF, 0x7F,   //     LOGICAL_MAXIMUM (32767) (0x7FFF)
    0x75, 0x10,         //     REPORT_SIZE (16) (2 bytes per axis)
    0x95, 0x02,         //     REPORT_COUNT (2)  -> X, Y position
    0x81, 0x02,         //     INPUT (Data, Variable, Absolute) -> Absolute X, Y position
#else /* UX_DEMO_MOUSE_ABSOLUTE */
    0x15, 0x81,         //     LOGICAL_MINIMUM (-127)
    0x25, 0x7F,         //     LOGICAL_MAXIMUM (127)
    0x75, 0x08,         //     REPORT_SIZE (8)  (1 bytes per axis)
    0x95, 0x02,         //     REPORT_COUNT (2) -> X, Y movement
    0x81, 0x06,         //     INPUT (Data, Variable, Relative) -> X, Y are relative
#endif  /* UX_DEMO_MOUSE_ABSOLUTE */

    /* Wheel */
    0x09, 0x38,         //     USAGE (Mouse Wheel)
    0x15, 0x81,         //     LOGICAL_MINIMUM (-127)
    0x25, 0x7F,         //     LOGICAL_MAXIMUM (127)
    0x75, 0x08,         //     REPORT_SIZE (8)
    0x95, 0x01,         //     REPORT_COUNT (1) -> Wheel movement
    0x81, 0x06,         //     INPUT (Data, Variable, Relative) -> Wheel

    /* End */
    0xC0,               //   END_COLLECTION
    0xC0                // END_COLLECTION
};

#define UX_HID_MOUSE_REPORT_LENGTH (sizeof(hid_report)/sizeof(hid_report[0]))

UCHAR ux_demo_device_framework_full_speed[] = {
    /* Device Descriptor */
    USB_DEVICE_DESCRIPTOR_LENGTH,               /* bLength                */
    USB_DESCRIPTOR_TYPE_DEVICE,                 /* bDescriptorType        */
    UX_W0(USB_BCDNUM_2000),                     /* bcdUSB                 */
    UX_W1(USB_BCDNUM_2000),
    0x00,                                       /* bDeviceClass           */
    0x00,                                       /* bDeviceSubClass        */
    0x00,                                       /* bDeviceProtocol        */
    UX_DEMO_HID_DEVICE_MAX_PACKET_SIZE,         /* bMaxPacketSize0        */
    UX_W0(UX_DEMO_HID_DEVICE_VID),              /* idVendor               */
    UX_W1(UX_DEMO_HID_DEVICE_VID),
    UX_W0(UX_DEMO_HID_DEVICE_PID),              /* idProduct              */
    UX_W1(UX_DEMO_HID_DEVICE_PID),
    0x00, 0x00,                                 /* bcdDevice              */
    0x01,                                       /* iManufacturer          */
    0x02,                                       /* iProduct               */
    0x03,                                       /* iSerialNumber          */
    0x01,                                       /* bNumConfigurations     */

    /* Configuration Descriptor, total */
    USB_CONFIGURATION_DESCRIPTOR_LENGTH,        /* bLength                */
    USB_DESCRIPTOR_TYPE_CONFIGURATION,          /* bDescriptorType        */
    UX_W0(UX_DEMO_HID_DEVICE_TOTAL_LENGTH),     /* wTotalLength           */
    UX_W1(UX_DEMO_HID_DEVICE_TOTAL_LENGTH),
    0x01,                                       /* bNumInterfaces         */
    0x01,                                       /* bConfigurationValue    */
    0x04,                                       /* iConfiguration         */
    UX_DEMO_BATTRIBUTES,                        /* bmAttributes           */
    UX_DEMO_MAX_POWER,                          /* bMaxPower              */

    /* Interface Descriptor */
    USB_INTERFACE_DESCRIPTOR_LENGTH,            /* bLength                */
    USB_DESCRIPTOR_TYPE_INTERFACE,              /* bDescriptorType        */
    0x00,                                       /* bInterfaceNumber       */
    0x00,                                       /* bAlternateSetting      */
    0x01,                                       /* bNumEndpoints          */
    USB_INTERFACE_HID,                          /* bInterfaceClass        */
    UX_DEMO_HID_SUBCLASS,                       /* bInterfaceSubClass     */
    USB_INTERFACE_PROTOCOL_MOUSE,               /* bInterfaceProtocol     */
    0x00,                                       /* iInterface             */

    /* HID Descriptor */
    USB_HID_DESCRIPTOR_LENGTH,                  /* bLength                */
    USB_DESCRIPTOR_TYPE_HID_DESCRIPTOR,         /* bDescriptorType        */
    UX_W0(UX_DEMO_BCD_HID),                     /* bcdHID                 */
    UX_W1(UX_DEMO_BCD_HID),
    0x21,                                       /* bCountryCode           */
    0x01,                                       /* bNumDescriptors        */
    0x22,                                       /* bReportDescriptorType1 */
    UX_W0(UX_HID_MOUSE_REPORT_LENGTH),          /* wDescriptorLength1     */
    UX_W1(UX_HID_MOUSE_REPORT_LENGTH),

    /* Endpoint Descriptor */
    USB_ENDPOINT_DESCRIPTOR_LENGTH,             /* bLength                */
    USB_DESCRIPTOR_TYPE_ENDPOINT,               /* bDescriptorType        */
    UX_DEMO_HID_ENDPOINT_ADDRESS,               /* bEndpointAddress       */
    USB_ENDPOINT_INT,                           /* bmAttributes           */
    UX_W0(UX_DEMO_HID_ENDPOINT_FS_SIZE),        /* wMaxPacketSize         */
    UX_W1(UX_DEMO_HID_ENDPOINT_FS_SIZE),
    UX_DEMO_HID_ENDPOINT_FS_BINTERVAL,          /* bInterval              */
};


UCHAR ux_demo_device_framework_high_speed[] = {
   /* Device Descriptor */
    USB_DEVICE_DESCRIPTOR_LENGTH,               /* bLength                */
    USB_DESCRIPTOR_TYPE_DEVICE,                 /* bDescriptorType        */
    UX_W0(UX_DEMO_BCD_USB),
    UX_W1(UX_DEMO_BCD_USB),                     /* bcdUSB                 */
    0x00,                                       /* bDeviceClass           */
    0x00,                                       /* bDeviceSubClass        */
    0x00,                                       /* bDeviceProtocol        */
    0x40,                                       /* bMaxPacketSize0        */
    UX_W0(UX_DEMO_HID_DEVICE_VID),
    UX_W1(UX_DEMO_HID_DEVICE_VID),              /* idVendor               */
    UX_W0(UX_DEMO_HID_DEVICE_PID),
    UX_W1(UX_DEMO_HID_DEVICE_PID),              /* idProduct              */
    0x01, 0x00,                                 /* bcdDevice              */
    0x01,                                       /* iManufacturer          */
    0x02,                                       /* iProduct               */
    0x03,                                       /* iSerialNumber          */
    0x01,                                       /* bNumConfigurations     */

    /* Device Qualifier Descriptor */
    USB_DEVICE_QUALIFIER_DESCRIPTOR_LENGTH,     /* bLength                */
    USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER,       /* bDescriptorType        */
    UX_W0(UX_DEMO_BCD_USB),                     /* bcdUSB                 */
    UX_W1(UX_DEMO_BCD_USB),
    0x00,                                       /* bDeviceClass           */
    0x00,                                       /* bDeviceSubClass        */
    0x00,                                       /* bDeviceProtocol        */
    0x40,                                       /* bMaxPacketSize0        */
    0x01,                                       /* bNumConfigurations     */
    0x00,                                       /* bReserved              */

    /* Configuration Descriptor */
    USB_CONFIGURATION_DESCRIPTOR_LENGTH,        /* bLength                */
    USB_DESCRIPTOR_TYPE_CONFIGURATION,          /* bDescriptorType        */
    UX_W0(UX_DEMO_HID_DEVICE_TOTAL_LENGTH),     /* wTotalLength           */
    UX_W1(UX_DEMO_HID_DEVICE_TOTAL_LENGTH),
    0x01,                                       /* bNumInterfaces         */
    0x01,                                       /* bConfigurationValue    */
    0x05,                                       /* iConfiguration         */
    UX_DEMO_BATTRIBUTES,                        /* bmAttributes           */
    UX_DEMO_MAX_POWER,                          /* bMaxPower              */

    /* Interface Descriptor */
    USB_INTERFACE_DESCRIPTOR_LENGTH,            /* bLength                */
    USB_DESCRIPTOR_TYPE_INTERFACE,              /* bDescriptorType        */
    0x00,                                       /* bInterfaceNumber       */
    0x00,                                       /* bAlternateSetting      */
    0x01,                                       /* bNumEndpoints          */
    USB_INTERFACE_HID,                          /* bInterfaceClass        */
    UX_DEMO_HID_SUBCLASS,                       /* bInterfaceSubClass     */
    USB_INTERFACE_PROTOCOL_MOUSE,               /* bInterfaceProtocol     */
    0x00,                                       /* iInterface             */

    /* HID Descriptor */
    USB_HID_DESCRIPTOR_LENGTH,                  /* bLength                */
    USB_DESCRIPTOR_TYPE_HID_DESCRIPTOR,         /* bDescriptorType        */
    UX_W0(UX_DEMO_BCD_HID),                     /* bcdHID                 */
    UX_W1(UX_DEMO_BCD_HID),
    0x21,                                       /* bCountryCode           */
    0x01,                                       /* bNumDescriptors        */
    0x22,                                       /* bReportDescriptorType1 */
    UX_W0(UX_HID_MOUSE_REPORT_LENGTH),          /* wDescriptorLength1     */
    UX_W1(UX_HID_MOUSE_REPORT_LENGTH),

    /* Endpoint Descriptor */
    USB_ENDPOINT_DESCRIPTOR_LENGTH,             /* bLength                */
    USB_DESCRIPTOR_TYPE_ENDPOINT,               /* bDescriptorType        */
    UX_DEMO_HID_ENDPOINT_ADDRESS,               /* bEndpointAddress       */
    USB_ENDPOINT_INT,                           /* bmAttributes           */
    UX_W0(UX_DEMO_HID_ENDPOINT_HS_SIZE),        /* wMaxPacketSize         */
    UX_W1(UX_DEMO_HID_ENDPOINT_HS_SIZE),
    UX_DEMO_HID_ENDPOINT_HS_BINTERVAL,          /* bInterval              */
};


/* String Device Framework :
   Byte 0 and 1 : Word containing the language ID : 0x0904 for US
   Byte 2       : Byte containing the index of the descriptor
   Byte 3       : Byte containing the length of the descriptor string
*/
UCHAR ux_demo_string_framework[] = {

    /* iManufacturer string descriptor : Index 1 */
    0x09, 0x04, 0x01, 12,
    'U', 'S', 'B', 'X', ' ', 'e', 'c', 'l', 'i', 'p', 's', 'e',

    /* iProduct string descriptor : Index 2 */
    0x09, 0x04, 0x02, 14,
    'H', 'I', 'D', ' ', 'M', 'o', 'u', 's', 'e', ' ', 'D', 'e', 'm', 'o',

    /* iSerialNumber Number string descriptor : Index 3 */
    0x09, 0x04, 0x03, 13,
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1',

    /* iConfiguration string descriptor : Index 4 */
    0x09, 0x04, 0x04, 10,
    'F', 'u', 'l', 'l', ' ', 'S', 'p', 'e', 'e', 'd',

    /* iConfiguration string descriptor : Index 5 */
    0x09, 0x04, 0x05, 10,
    'H', 'i', 'G', 'H', ' ', 'S', 'p', 'e', 'e', 'd',
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
