/***************************************************************************
 * Copyright (c) 2024 Microsoft Corporation
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

#ifndef UX_DEMO_DEVICE_DESCRIPTORS_H
#define UX_DEMO_DEVICE_DESCRIPTORS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ux_api.h"

//#define UX_DEMO_MOUSE_ABSOLUTE

#define UX_DEMO_HID_DEVICE_VID                  0x070A
#define UX_DEMO_HID_DEVICE_PID                  0x4030

#define UX_DEMO_BCD_USB                         0x0200

#define UX_DEMO_BCD_HID                         0x0110

#define UX_DEMO_HID_DEVICE_MAX_PACKET_SIZE      0x08U

#define UX_DEMO_HID_ENDPOINT_ADDRESS            USB_ENDPOINT_1 | USB_ENDPOINT_IN

#define UX_DEMO_HID_ENDPOINT_FS_SIZE            0x08U
#define UX_DEMO_HID_ENDPOINT_HS_SIZE            0x08U

#define UX_DEMO_HID_ENDPOINT_FS_BINTERVAL       0x08U
#define UX_DEMO_HID_ENDPOINT_HS_BINTERVAL       0x08U

#define UX_DEMO_HID_SUBCLASS                    USB_INTERFACE_SUBCLASS_NOBOOT

#define UX_DEMO_BATTRIBUTES                     USB_BMATTRIBUTE_SELFP | USB_BMATTRIBUTE_RESERVED
#define UX_DEMO_MAX_POWER                       50

#define UX_DEMO_HID_DEVICE_TOTAL_LENGTH         USB_CONFIGURATION_DESCRIPTOR_LENGTH + \
                                                USB_INTERFACE_DESCRIPTOR_LENGTH     + \
                                                USB_HID_DESCRIPTOR_LENGTH           + \
                                                USB_ENDPOINT_DESCRIPTOR_LENGTH


#define USB_ENDPOINT_0                          0x00U   /* End Point Number 0  */
#define USB_ENDPOINT_1                          0x01U   /* End Point Number 1  */
#define USB_ENDPOINT_2                          0x02U   /* End Point Number 2  */
#define USB_ENDPOINT_3                          0x03U   /* End Point Number 3  */
#define USB_ENDPOINT_4                          0x04U   /* End Point Number 4  */
#define USB_ENDPOINT_5                          0x05U   /* End Point Number 5  */
#define USB_ENDPOINT_6                          0x06U   /* End Point Number 6  */
#define USB_ENDPOINT_7                          0x07U   /* End Point Number 7  */
#define USB_ENDPOINT_8                          0x08U   /* End Point Number 8  */
#define USB_ENDPOINT_9                          0x09U   /* End Point Number 9  */
#define USB_ENDPOINT_10                         0x0AU   /* End Point Number 10 */
#define USB_ENDPOINT_11                         0x0BU   /* End Point Number 11 */
#define USB_ENDPOINT_12                         0x0CU   /* End Point Number 12 */
#define USB_ENDPOINT_13                         0x0DU   /* End Point Number 13 */
#define USB_ENDPOINT_14                         0x0EU   /* End Point Number 14 */
#define USB_ENDPOINT_15                         0x0FU   /* End Point Number 15 */


/* Endpoint Descriptor define */
#define USB_ENDPOINT_IN                         0x80U   /* IN Endpoint */
#define USB_ENDPOINT_OUT                        0x00U   /* OUT Endpoint */

#define USB_ENDPOINT_ISO                        0x01U   /* Isochronous Transfer */
#define USB_ENDPOINT_BULK                       0x02U   /* Bulk Transfer */
#define USB_ENDPOINT_INT                        0x03U   /* Interrupt Transfer */

/* Descriptor length define */
#define USB_DEVICE_DESCRIPTOR_LENGTH            0x12U   /* Device Descriptor Length             */
#define USB_CONFIGURATION_DESCRIPTOR_LENGTH     0x09U   /* Configuration Descriptor Length      */
#define USB_INTERFACE_DESCRIPTOR_LENGTH         0x09U   /* Interface Descriptor Length          */
#define USB_ENDPOINT_DESCRIPTOR_LENGTH          0x07U   /* Endpoint Descriptor Length           */
#define USB_HID_DESCRIPTOR_LENGTH               0x09U   /* HID Descriptor Length                */
#define USB_DEVICE_QUALIFIER_DESCRIPTOR_LENGTH  0x0AU   /* Device Qualifier Descriptor Length   */

/* Descriptor type define */
#define USB_DESCRIPTOR_TYPE_DEVICE              0x01U   /* Device Descriptor                    */
#define USB_DESCRIPTOR_TYPE_CONFIGURATION       0x02U   /* Configuration Descriptor             */
#define USB_DESCRIPTOR_TYPE_STRING              0x03U   /* String Descriptor                    */
#define USB_DESCRIPTOR_TYPE_INTERFACE           0x04U   /* Interface Descriptor                 */
#define USB_DESCRIPTOR_TYPE_ENDPOINT            0x05U   /* Endpoint Descriptor                  */
#define USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER    0x06U   /* Device Qualifier Descriptor          */
#define USB_DESCRIPTOR_TYPE_OTHER_SPEED_CONF    0x07U   /* Other Speed Configuration Descriptor */
#define USB_DESCRIPTOR_TYPE_INTERFACE_POWER     0x08U   /* Interface Power Descriptor           */
#define USB_DESCRIPTOR_TYPE_OTG_DESCRIPTOR      0x09U   /* OTG Descriptor                       */
#define USB_DESCRIPTOR_TYPE_HUB_DESCRIPTOR      0x29U   /* HUB descriptor                       */
#define USB_DESCRIPTOR_TYPE_HID_DESCRIPTOR      0x21U   /* HID descriptor                       */

/* Configuration descriptor bmAttributes define */
#define USB_BMATTRIBUTE_RESERVED                0x80U   /* Reserved(set to 1)   */
#define USB_BMATTRIBUTE_SELFP                   0x40U   /* Self Powered         */
#define USB_BMATTRIBUTE_BUSP                    0x00U   /* Bus Powered          */
#define USB_BMATTRIBUTE_REMOTE_WAKEUP_ON        0x20U   /* Remote Wake up ON    */
#define USB_BMATTRIBUTE_REMOTE_WAKEUP_OFF       0x00U   /* Remote Wake up OFF   */

/* Interface class define */
#define USB_INTERFACE_NOT                       0x00U   /* Un corresponding Class */
#define USB_INTERFACE_AUDIO                     0x01U   /* Audio Class            */
#define USB_INTERFACE_CDC                       0x02U   /* CDC Class              */
#define USB_INTERFACE_CDCC                      0x02U   /* CDC-Control Class      */
#define USB_INTERFACE_HID                       0x03U   /* HID Class              */
#define USB_INTERFACE_PHY                       0x05U   /* Physical Class         */
#define USB_INTERFACE_IMG                       0x06U   /* Image Class            */
#define USB_INTERFACE_PRN                       0x07U   /* Printer Class          */
#define USB_INTERFACE_MAS                       0x08U   /* Mass Storage Class     */
#define USB_INTERFACE_HUB                       0x09U   /* HUB Class              */
#define USB_INTERFACE_CDCD                      0x0AU   /* CDC-Data Class         */
#define USB_INTERFACE_CHIP                      0x0BU   /* Chip/Smart Card Class  */
#define USB_INTERFACE_CNT                       0x0CU   /* Content-Security Class */
#define USB_INTERFACE_VID                       0x0EU   /* Video Class            */
#define USB_INTERFACE_DIAG                      0xDCU   /* Diagnostic Device      */
#define USB_INTERFACE_WIRE                      0xE0U   /* Wireless Controller    */
#define USB_INTERFACE_APL                       0xFEU   /* Application-Specific   */
#define USB_INTERFACE_VEN                       0xFFU   /* Vendor-Specific Class  */

#define USB_BCDNUM_2000                         0x0200U

/* HID Subclass define */
#define USB_INTERFACE_SUBCLASS_NOBOOT           0x00U   /* No Subclass             */
#define USB_INTERFACE_SUBCLASS_BOOT             0x01U   /* Boot Interface Subclass */

/* HID Protocol define */
#define USB_INTERFACE_PROTOCOL_NONE             0x00U  /* Demonstration         */
#define USB_INTERFACE_PROTOCOL_KEYBOARD         0x01U  /* Keyboard              */
#define USB_INTERFACE_PROTOCOL_MOUSE            0x02U  /* Mouse                 */

UCHAR*  ux_demo_get_high_speed_framework(VOID);
ULONG   ux_demo_get_high_speed_framework_length(VOID);
UCHAR*  ux_demo_get_full_speed_framework(VOID);
ULONG   ux_demo_get_full_speed_framework_length(VOID);
UCHAR*  ux_demo_get_string_framework(VOID);
ULONG   ux_demo_get_string_framework_length(VOID);
UCHAR*  ux_demo_get_language_framework(VOID);
ULONG   ux_demo_get_language_framework_length(VOID);

UCHAR*  ux_demo_device_hid_get_report(VOID);
ULONG   ux_demo_device_hid_get_report_length(VOID);

#ifdef __cplusplus
}
#endif
#endif  /* UX_DEMO_DEVICE_DESCRIPTORS_H */
