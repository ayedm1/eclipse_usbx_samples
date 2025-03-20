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

#ifndef UX_DEMO_DEVICE_HID_MOUSE_H
#define UX_DEMO_DEVICE_HID_MOUSE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "tx_api.h"
#include "ux_api.h"
#include "ux_device_class_hid.h"


#include "ux_demo_device_hid_descriptors.h"

#include "common_hardware_code.h"
#include "usb_app_setup.h"


#define DEMO_STACK_SIZE                         4*1024
#define UX_DEVICE_MEMORY_STACK_SIZE             4*1024


#ifdef __cplusplus
}
#endif
#endif /* UX_DEMO_DEVICE_HID_MOUSE_H */
