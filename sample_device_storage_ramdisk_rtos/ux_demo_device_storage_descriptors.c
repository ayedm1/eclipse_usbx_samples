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

#include "ux_demo_device_storage_descriptors.h"


UCHAR ux_demo_device_framework_full_speed[] = {
    /* Device descriptor */
    0x12,                       /* bLength */
    0x01,                       /* bDescriptorType */
    UX_W0(UX_DEMO_BCD_USB), UX_W1(UX_DEMO_BCD_USB), /* bcdUSB : 0x0200 : USB 2.0 */
    0x00,                       /* bDeviceClass : 0x00 : Interface-defined */
    0x00,                       /* bDeviceSubClass : 0x00 : Reset */
    0x00,                       /* bDeviceProtocol : 0x00 : Reset */
    UX_DEMO_MAX_EP0_SIZE,       /* bMaxPacketSize0 */
    UX_W0(UX_DEMO_STORAGE_DEVICE_VID), UX_W1(UX_DEMO_STORAGE_DEVICE_VID), /* idVendor */
    UX_W0(UX_DEMO_STORAGE_DEVICE_PID), UX_W1(UX_DEMO_STORAGE_DEVICE_PID), /* idProduct */
    0x00, 0x00,                 /* bcdDevice */
    0x01,                       /* iManufacturer */
    0x02,                       /* iProduct */
    0x03,                       /* iSerialNumber */
    0x01,                       /* bNumConfigurations */

    /* Configuration descriptor */
    0x09,                       /* bLength */
    0x02,                       /* bDescriptorType */
    UX_W0(UX_DEMO_STORAGE_CONFIG_DESC_SIZE), UX_W1(UX_DEMO_STORAGE_CONFIG_DESC_SIZE), /* wTotalLength */
    0x01,                       /* bNumInterfaces */
    0x01,                       /* bConfigurationValue */
    0x04,                       /* iConfiguration */
    0xC0,                       /* bmAttributes */
                                /* D6 : 0x1 : Self-powered */
                                /* D5, Remote Wakeup : 0x0 : Not supported */
    0x32,                       /* bMaxPower : 50 : 100mA */

    /* Interface descriptor */
    0x09,                       /* bLength */
    0x04,                       /* bDescriptorType */
    0x00,                       /* bInterfaceNumber */
    0x00,                       /* bAlternateSetting */
    0x02,                       /* bNumEndpoints */
    0x08,                       /* bInterfaceClass : 0x08 : Mass Storage */
    0x06,                       /* bInterfaceSubClass : SCSI transparent*/
    0x50,                       /* nInterfaceProtocol */
    0x06,                       /* iInterface */

    /* Endpoint descriptor (Bulk In) */
    0x07,                       /* bLength */
    0x05,                       /* bDescriptorType */
    UX_DEMO_STORAGE_EPIN_ADDR,  /* bEndpointAddress */
    0x02,                       /* bmAttributes */
                                  /* D1..0, Transfer Type : 0x2 : Bulk */
                                  /* D3..2, Synchronization Type : 0x0 : No Synchronization */
                                  /* D5..4, Usage Type : 0x0 : Data endpoint */
    UX_W0(UX_DEMO_STORAGE_FS_EPIN_SIZE), UX_W1(UX_DEMO_STORAGE_FS_EPIN_SIZE),  /* wMaxPacketSize */
                                  /* D10..0, Max Packet Size */
                                  /* D12..11, Additional transactions : 0x00 */
    0x00,                        /* bInterval */

    /* Endpoint descriptor (Bulk Out) */
    0x07,                       /* bLength */
    0x05,                       /* bDescriptorType */
    UX_DEMO_STORAGE_EPOUT_ADDR, /* bEndpointAddress */
    0x02,                       /* bmAttributes */
                                  /* D1..0, Transfer Type : 0x2 : Bulk */
                                  /* D3..2, Synchronization Type : 0x0 : No Synchronization */
                                  /* D5..4, Usage Type : 0x0 : Data endpoint */
    UX_W0(UX_DEMO_STORAGE_FS_EPOUT_SIZE), UX_W1(UX_DEMO_STORAGE_FS_EPOUT_SIZE),  /* wMaxPacketSize */
                                  /* D10..0, Max Packet Size */
                                  /* D12..11, Additional transactions : 0x00 */
    0x00                        /* bInterval */
};


UCHAR ux_demo_device_framework_high_speed[] = {
    /* Device descriptor */
    0x12,                       /* bLength */
    0x01,                       /* bDescriptorType */
    UX_W0(UX_DEMO_BCD_USB), UX_W1(UX_DEMO_BCD_USB), /* bcdUSB : 0x0200 : USB 2.0 */
    0x00,                       /* bDeviceClass : 0x00 : Interface-defined */
    0x00,                       /* bDeviceSubClass : 0x00 : Reset */
    0x00,                       /* bDeviceProtocol : 0x00 : Reset */
    UX_DEMO_MAX_EP0_SIZE,       /* bMaxPacketSize0 */
    UX_W0(UX_DEMO_STORAGE_DEVICE_VID), UX_W1(UX_DEMO_STORAGE_DEVICE_VID), /* idVendor */
    UX_W0(UX_DEMO_STORAGE_DEVICE_PID), UX_W1(UX_DEMO_STORAGE_DEVICE_PID), /* idProduct */
    0x01, 0x00,                 /* bcdDevice */
    0x01,                       /* iManufacturer */
    0x02,                       /* iProduct */
    0x03,                       /* iSerialNumber */
    0x01,                       /* bNumConfigurations */

    /* Device qualifier descriptor */
    0x0A,                       /* bLength */
    0x06,                       /* bDescriptorType */
    UX_W0(UX_DEMO_BCD_USB), UX_W1(UX_DEMO_BCD_USB), /* bcdUSB : 0x0200 : USB 2.0 */
    0x00,                       /* bDeviceClass : 0x00 : Interface-defined */
    0x00,                       /* bDeviceSubClass : 0x00 : Reset */
    0x00,                       /* bDeviceProtocol : 0x00 : Reset */
    0x40,                       /* bMaxPacketSize0 */
    0x01,                       /* bNumConfigurations */
    0x00,                       /* bReserved */

    /* Configuration descriptor */
    0x09,                       /* bLength */
    0x02,                       /* bDescriptorType */
    UX_W0(UX_DEMO_STORAGE_CONFIG_DESC_SIZE), UX_W1(UX_DEMO_STORAGE_CONFIG_DESC_SIZE), /* wTotalLength */
    0x01,                       /* bNumInterfaces */
    0x01,                       /* bConfigurationValue */
    0x05,                       /* iConfiguration */
    0xC0,                       /* bmAttributes */
                                /* D6 : 0x1 : Self-powered */
                                /* D5, Remote Wakeup : 0x0 : Not supported */
    0x32,                       /* bMaxPower : 50 : 100mA */

    /* Interface descriptor */
    0x09,                       /* bLength */
    0x04,                       /* bDescriptorType */
    0x00,                       /* bInterfaceNumber */
    0x00,                       /* bAlternateSetting */
    0x02,                       /* bNumEndpoints */
    0x08,                       /* bInterfaceClass : 0x08 : Mass Storage */
    0x06,                       /* bInterfaceSubClass : SCSI transparent*/
    0x50,                       /* nInterfaceProtocol */
    0x06,                       /* iInterface */

    /* Endpoint descriptor (Bulk In) */
    0x07,                       /* bLength */
    0x05,                       /* bDescriptorType */
    UX_DEMO_STORAGE_EPIN_ADDR,  /* bEndpointAddress */
    0x02,                       /* bmAttributes */
                                  /* D1..0, Transfer Type : 0x2 : Bulk */
                                  /* D3..2, Synchronization Type : 0x0 : No Synchronization */
                                  /* D5..4, Usage Type : 0x0 : Data endpoint */
    UX_W0(UX_DEMO_STORAGE_HS_EPIN_SIZE), UX_W1(UX_DEMO_STORAGE_HS_EPIN_SIZE),  /* wMaxPacketSize */
                                  /* D10..0, Max Packet Size */
                                  /* D12..11, Additional transactions : 0x00 */
    0x00,                        /* bInterval */

    /* Endpoint descriptor (Bulk Out) */
    0x07,                       /* bLength */
    0x05,                       /* bDescriptorType */
    UX_DEMO_STORAGE_EPOUT_ADDR, /* bEndpointAddress */
    0x02,                       /* bmAttributes */
                                  /* D1..0, Transfer Type : 0x2 : Bulk */
                                  /* D3..2, Synchronization Type : 0x0 : No Synchronization */
                                  /* D5..4, Usage Type : 0x0 : Data endpoint */
    UX_W0(UX_DEMO_STORAGE_HS_EPOUT_SIZE), UX_W1(UX_DEMO_STORAGE_HS_EPOUT_SIZE),  /* wMaxPacketSize */
                                  /* D10..0, Max Packet Size */
                                  /* D12..11, Additional transactions : 0x00 */
    0x00                        /* bInterval */
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
    0x09, 0x04, 0x02, 20,
    'S', 'T', 'O', 'R', 'A', 'G', 'E', ' ', 'R', 'A', 'M', 'D', 'I', 'S', 'K', ' ', 'D', 'e', 'm', 'o',

    /* iSerialNumber Number string descriptor : Index 3 */
    0x09, 0x04, 0x03, 13,
    '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1',

    /* iConfiguration string descriptor : Index 4 */
    0x09, 0x04, 0x04, 10,
    'F', 'u', 'l', 'l', ' ', 'S', 'p', 'e', 'e', 'd',

    /* iConfiguration string descriptor : Index 5 */
    0x09, 0x04, 0x05, 10,
    'H', 'i', 'G', 'H', ' ', 'S', 'p', 'e', 'e', 'd',

    /* iInterface string descriptor : Index 6 */
    0x09, 0x04, 0x06, 15,
    'R', 'e', 'm', 'o', 'v', 'a', 'b', 'l', 'e', ' ', 'D', 'r', 'i', 'v', 'e'
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
