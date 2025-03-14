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

#ifndef UX_DEMO_DEVICE_HID_CONSUMER_H
#define UX_DEMO_DEVICE_HID_CONSUMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ux_api.h"
#include "ux_device_class_hid.h"


#include "ux_demo_device_hid_descriptors.h"

#include "common_hardware_code.h"
#include "usb_app_setup.h"


#define DEMO_STACK_SIZE                         2*1024
#define UX_DEVICE_MEMORY_STACK_SIZE             2*1024

#define UX_CONSUMER_MEDIA                       0x00
#define UX_CONSUMER_BRIGHTNESS                  0x01

/******************************/
/**  Screen Brightness event  */
/******************************/
#define UX_CONSUMER_BRIGHTNESS_DOWN             0x00
#define UX_CONSUMER_BRIGHTNESS_UP               0x01

#define UX_CONSUMER_BRIGHTNESS_DONE             0x10

/******************************/
/**  Media Control event      */
/******************************/

#define UX_CONSUMER_MEDIA_VOLUME_DOWN           0x00
#define UX_CONSUMER_MEDIA_VOLUME_UP             0x01
#define UX_CONSUMER_MEDIA_MUTE                  0x02
#define UX_CONSUMER_MEDIA_UNMUTE                0x03
#define UX_CONSUMER_MEDIA_PLAY                  0x04
#define UX_CONSUMER_MEDIA_PAUSE                 0x05
#define UX_CONSUMER_MEDIA_NEXT_TRACK            0x06
#define UX_CONSUMER_MEDIA_PREVIOUS_TRACK        0x07

#define UX_CONSUMER_MEDIA_DONE                  0x10

#define UX_CONSUMER_FINISH                      0x10

#ifdef __cplusplus
}
#endif
#endif /* UX_DEMO_DEVICE_HID_CONSUMER_H */
