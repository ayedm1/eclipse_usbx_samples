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


#define UX_DEMO_STORAGE_DEVICE_VID              0x070A
#define UX_DEMO_STORAGE_DEVICE_PID              0x4030

#define UX_DEMO_BCD_USB                         0x0200

#define UX_DEMO_MAX_EP0_SIZE                    0x40U

#define UX_DEMO_STORAGE_CONFIG_DESC_SIZE        0x20U

#define UX_DEMO_STORAGE_EPIN_ADDR               0x81U
#define UX_DEMO_STORAGE_EPOUT_ADDR              0x01U

#define UX_DEMO_STORAGE_FS_EPIN_SIZE            0x40U
#define UX_DEMO_STORAGE_FS_EPOUT_SIZE           0x40U

#define UX_DEMO_STORAGE_HS_EPIN_SIZE            0x200U
#define UX_DEMO_STORAGE_HS_EPOUT_SIZE           0x200U

UCHAR*  ux_demo_get_high_speed_framework(VOID);
ULONG   ux_demo_get_high_speed_framework_length(VOID);
UCHAR*  ux_demo_get_full_speed_framework(VOID);
ULONG   ux_demo_get_full_speed_framework_length(VOID);
UCHAR*  ux_demo_get_string_framework(VOID);
ULONG   ux_demo_get_string_framework_length(VOID);
UCHAR*  ux_demo_get_language_framework(VOID);
ULONG   ux_demo_get_language_framework_length(VOID);

#ifdef __cplusplus
}
#endif
#endif  /* UX_DEMO_DEVICE_DESCRIPTORS_H */
