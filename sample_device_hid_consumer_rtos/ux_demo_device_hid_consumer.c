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


#include "ux_demo_device_hid_consumer.h"

/**************************************************/
/**  usbx device hid demo callbacks               */
/**************************************************/
VOID ux_demo_device_hid_instance_activate(VOID *hid_instance);
VOID ux_demo_device_hid_instance_deactivate(VOID *hid_instance);
UINT ux_demo_device_hid_callback(UX_SLAVE_CLASS_HID *hid_instance, UX_SLAVE_CLASS_HID_EVENT *hid_event);
UINT ux_demo_device_hid_get_callback(UX_SLAVE_CLASS_HID *hid_instance, UX_SLAVE_CLASS_HID_EVENT *hid_event);

/**************************************************/
/**  usbx device hid demo thread                  */
/**************************************************/
VOID ux_demo_device_hid_thread_entry(ULONG thread_input);

/**************************************************/
/**  usbx application initialization with RTOS    */
/**************************************************/
VOID tx_application_define(VOID *first_unused_memory);

/**************************************************/
/**  usbx device hid demo consumer                */
/**************************************************/
UINT ux_demo_hid_consumer_media_control(UX_SLAVE_CLASS_HID *device_hid);
UINT ux_demo_hid_consumer_brightness_control(UX_SLAVE_CLASS_HID *device_hid);

/**************************************************/
/**  usbx device hid consumer instance            */
/**************************************************/
UX_SLAVE_CLASS_HID *hid_consumer;

/**************************************************/
/**  thread object                                */
/**************************************************/
static TX_THREAD ux_hid_thread;

int main(void)
{
    /* Initialize the board.  */
    board_setup();

    /* Enter the ThreadX kernel.  */
    tx_kernel_enter();

    while (1)
    {
    }

}

VOID tx_application_define(VOID *first_unused_memory)
{
CHAR                            *stack_pointer;
CHAR                            *memory_pointer;
UINT                            status;
UX_SLAVE_CLASS_HID_PARAMETER    hid_consumer_parameter;

    /* Initialize the free memory pointer.  */
    stack_pointer =  (CHAR *) first_unused_memory;

    /* Initialize the RAM disk memory. */
    memory_pointer =  stack_pointer +  DEMO_STACK_SIZE;

    /* Initialize USBX Memory */
    status = ux_system_initialize(memory_pointer, UX_DEVICE_MEMORY_STACK_SIZE, UX_NULL, 0);

    if(status != UX_SUCCESS)
        return;

    /* Install the device portion of USBX */
    status = ux_device_stack_initialize(ux_demo_get_high_speed_framework(),
                                        ux_demo_get_high_speed_framework_length(),
                                        ux_demo_get_full_speed_framework(),
                                        ux_demo_get_full_speed_framework_length(),
                                        ux_demo_get_string_framework(),
                                        ux_demo_get_string_framework_length(),
                                        ux_demo_get_language_framework(),
                                        ux_demo_get_language_framework_length(),
                                        UX_NULL);

    if(status != UX_SUCCESS)
        return;

    /* Initialize the hid consumer class parameters for the device */
    hid_consumer_parameter.ux_slave_class_hid_instance_activate         = ux_demo_device_hid_instance_activate;
    hid_consumer_parameter.ux_slave_class_hid_instance_deactivate       = ux_demo_device_hid_instance_deactivate;
    hid_consumer_parameter.ux_device_class_hid_parameter_report_address = ux_demo_device_hid_get_report();
    hid_consumer_parameter.ux_device_class_hid_parameter_report_length  = ux_demo_device_hid_get_report_length();
    hid_consumer_parameter.ux_device_class_hid_parameter_report_id      = UX_FALSE;
    hid_consumer_parameter.ux_device_class_hid_parameter_callback       = ux_demo_device_hid_callback;
    hid_consumer_parameter.ux_device_class_hid_parameter_get_callback   = ux_demo_device_hid_get_callback;

    /* Initialize the device storage class. The class is connected with interface 0 on configuration 1. */
    status = ux_device_stack_class_register(_ux_system_slave_class_hid_name, ux_device_class_hid_entry,
                                            1, 0, (VOID *)&hid_consumer_parameter);

    if(status != UX_SUCCESS)
        return;

    /* Create the main demo thread.  */
    status = ux_utility_thread_create(&ux_hid_thread, "hid_usbx_app_thread_entry",
                                      ux_demo_device_hid_thread_entry, 0, stack_pointer,
                                      512, 20, 20, 1, TX_AUTO_START);

    if(status != UX_SUCCESS)
        return;
}

/********************************************************************/
/**  ux_demo_device_hid_instance_activate                           */
/********************************************************************/
VOID ux_demo_device_hid_instance_activate(VOID *hid_instance)
{
    if (hid_consumer == UX_NULL)
        hid_consumer = (UX_SLAVE_CLASS_HID*) hid_instance;
}

/********************************************************************/
/**  ux_demo_device_hid_instance_deactivate                         */
/********************************************************************/
VOID ux_demo_device_hid_instance_deactivate(VOID *hid_instance)
{
    if (hid_instance == (VOID *)hid_consumer)
        hid_consumer = UX_NULL;
}

/********************************************************************/
/**  ux_demo_device_hid_callback                                    */
/********************************************************************/
UINT ux_demo_device_hid_callback(UX_SLAVE_CLASS_HID *hid_instance, UX_SLAVE_CLASS_HID_EVENT *hid_event)
{
    UX_PARAMETER_NOT_USED(hid_instance);
    UX_PARAMETER_NOT_USED(hid_event);

    return UX_SUCCESS;
}

/********************************************************************/
/**  ux_demo_device_hid_get_callback                                */
/********************************************************************/
UINT ux_demo_device_hid_get_callback(UX_SLAVE_CLASS_HID *hid_instance, UX_SLAVE_CLASS_HID_EVENT *hid_event)
{
    UX_PARAMETER_NOT_USED(hid_instance);
    UX_PARAMETER_NOT_USED(hid_event);

    return UX_SUCCESS;
}

/********************************************************************/
/**  ux_demo_device_hid_thread_entry: hid demo thread               */
/********************************************************************/
VOID ux_demo_device_hid_thread_entry(ULONG thread_input)
{
UINT            status;
UINT            demo_state = 0;

    UX_PARAMETER_NOT_USED(thread_input);

    usb_device_initialize();

    while (1)
    {
      /* Check if the device state already configured.  */
      if ((UX_SLAVE_DEVICE_CHECK_STATE(UX_DEVICE_CONFIGURED)) && (hid_consumer != UX_NULL))
      {
        switch(demo_state)
        {

        case UX_CONSUMER_MEDIA:

          /* Control media.  */
          status = ux_demo_hid_consumer_media_control(hid_consumer);

          if (status == UX_CONSUMER_MEDIA_DONE)
              demo_state = UX_CONSUMER_BRIGHTNESS;

          break;

        case UX_CONSUMER_BRIGHTNESS:

          /* Control brightness.  */
          status = ux_demo_hid_consumer_brightness_control(hid_consumer);

          if (status == UX_CONSUMER_BRIGHTNESS_DONE)
              demo_state = UX_CONSUMER_FINISH;

          break;

        default:

          ux_utility_delay_ms(MS_TO_TICK(10));

          break;
        }
      }
      else
      {
        /* Sleep thread for 10ms.  */
        ux_utility_delay_ms(MS_TO_TICK(10));
      }
    }
}

/********************************************************************/
/**  ux_demo_hid_consumer_media_control:                            */
/**             mute, unmute, volume up/down, play/pause,           */
/**             next/previous Track                                 */
/********************************************************************/
UINT ux_demo_hid_consumer_media_control(UX_SLAVE_CLASS_HID *device_hid)
{
UCHAR                     status;
UX_SLAVE_CLASS_HID_EVENT  device_hid_event;
static UCHAR              media_event;
static UCHAR              volume_level = 100;


    /* Initialize mouse event.  */
    device_hid_event.ux_device_class_hid_event_report_id = 0;
    device_hid_event.ux_device_class_hid_event_report_type = UX_DEVICE_CLASS_HID_REPORT_TYPE_INPUT;
    device_hid_event.ux_device_class_hid_event_length = 2;


    switch(media_event)
    {
    case UX_CONSUMER_MEDIA_VOLUME_DOWN:

        /* Sleep thread for 50ms.  */
        ux_utility_delay_ms(MS_TO_TICK(50));

        device_hid_event.ux_device_class_hid_event_buffer[0] = 0x04;
        device_hid_event.ux_device_class_hid_event_buffer[1] = 0;

        status = ux_device_class_hid_event_set(device_hid, &device_hid_event);

        if(status != UX_SUCCESS)
            return UX_ERROR;

        /* Send release event */
        device_hid_event.ux_device_class_hid_event_buffer[0] = 0;
        device_hid_event.ux_device_class_hid_event_buffer[1] = 0;

        /* Sleep thread for 10ms.  */
        ux_utility_delay_ms(MS_TO_TICK(10));

        status = ux_device_class_hid_event_set(device_hid, &device_hid_event);

        if(status != UX_SUCCESS)
            return UX_ERROR;

        volume_level -= 2;

        if (volume_level == 0)
            media_event = UX_CONSUMER_MEDIA_VOLUME_UP;

        break;

    case UX_CONSUMER_MEDIA_VOLUME_UP:

        /* Sleep thread for 50ms.  */
        ux_utility_delay_ms(MS_TO_TICK(50));

        device_hid_event.ux_device_class_hid_event_buffer[0] = 0x03;
        device_hid_event.ux_device_class_hid_event_buffer[1] = 0;

        status = ux_device_class_hid_event_set(device_hid, &device_hid_event);

        if(status != UX_SUCCESS)
            return UX_ERROR;

        /* Send release event */
        device_hid_event.ux_device_class_hid_event_buffer[0] = 0;
        device_hid_event.ux_device_class_hid_event_buffer[1] = 0;

        /* Sleep thread for 10ms.  */
        ux_utility_delay_ms(MS_TO_TICK(10));

        status = ux_device_class_hid_event_set(device_hid, &device_hid_event);

        if(status != UX_SUCCESS)
            return UX_ERROR;

        volume_level += 2;

        if (volume_level == 100)
            media_event = UX_CONSUMER_MEDIA_MUTE;

        break;

    case UX_CONSUMER_MEDIA_MUTE:

        /* Sleep thread for 10ms.  */
        ux_utility_delay_ms(MS_TO_TICK(10));

        device_hid_event.ux_device_class_hid_event_buffer[0] = 0x05;
        device_hid_event.ux_device_class_hid_event_buffer[1] = 0;

        status = ux_device_class_hid_event_set(device_hid, &device_hid_event);

        if(status != UX_SUCCESS)
            return UX_ERROR;

        /* Send release event */
        device_hid_event.ux_device_class_hid_event_buffer[0] = 0;
        device_hid_event.ux_device_class_hid_event_buffer[1] = 0;

        /* Sleep thread for 10ms.  */
        ux_utility_delay_ms(MS_TO_TICK(10));

        status = ux_device_class_hid_event_set(device_hid, &device_hid_event);

        if(status != UX_SUCCESS)
            return UX_ERROR;

        media_event = UX_CONSUMER_MEDIA_UNMUTE;

        break;

    case UX_CONSUMER_MEDIA_UNMUTE:

        /* Sleep thread for 100ms.  */
        ux_utility_delay_ms(MS_TO_TICK(100));

        device_hid_event.ux_device_class_hid_event_buffer[0] = 0x05;
        device_hid_event.ux_device_class_hid_event_buffer[1] = 0;

        status = ux_device_class_hid_event_set(device_hid, &device_hid_event);

        if(status != UX_SUCCESS)
            return UX_ERROR;

        /* Send release event */
        device_hid_event.ux_device_class_hid_event_buffer[0] = 0;
        device_hid_event.ux_device_class_hid_event_buffer[1] = 0;

        /* Sleep thread for 10ms.  */
        ux_utility_delay_ms(MS_TO_TICK(10));

        status = ux_device_class_hid_event_set(device_hid, &device_hid_event);

        if(status != UX_SUCCESS)
            return UX_ERROR;

        media_event = UX_CONSUMER_MEDIA_PLAY;

        break;

    case UX_CONSUMER_MEDIA_PLAY:

        /* Sleep thread for 10ms.  */
        ux_utility_delay_ms(MS_TO_TICK(10));

        device_hid_event.ux_device_class_hid_event_buffer[0] = 0x06;
        device_hid_event.ux_device_class_hid_event_buffer[1] = 0;

        status = ux_device_class_hid_event_set(device_hid, &device_hid_event);

        if(status != UX_SUCCESS)
            return UX_ERROR;

        /* Send release event */
        device_hid_event.ux_device_class_hid_event_buffer[0] = 0;
        device_hid_event.ux_device_class_hid_event_buffer[1] = 0;

        /* Sleep thread for 10ms.  */
        ux_utility_delay_ms(MS_TO_TICK(10));

        status = ux_device_class_hid_event_set(device_hid, &device_hid_event);

        if(status != UX_SUCCESS)
            return UX_ERROR;

        media_event = UX_CONSUMER_MEDIA_PAUSE;

        break;

    case UX_CONSUMER_MEDIA_PAUSE:

        /* Sleep thread for 10ms.  */
        ux_utility_delay_ms(MS_TO_TICK(10));

        device_hid_event.ux_device_class_hid_event_buffer[0] = 0x06;
        device_hid_event.ux_device_class_hid_event_buffer[1] = 0;

        status = ux_device_class_hid_event_set(device_hid, &device_hid_event);

        if(status != UX_SUCCESS)
            return UX_ERROR;

        /* Send release event */
        device_hid_event.ux_device_class_hid_event_buffer[0] = 0;
        device_hid_event.ux_device_class_hid_event_buffer[1] = 0;

        /* Sleep thread for 10ms.  */
        ux_utility_delay_ms(MS_TO_TICK(10));

        status = ux_device_class_hid_event_set(device_hid, &device_hid_event);

        if(status != UX_SUCCESS)
            return UX_ERROR;

        media_event = UX_CONSUMER_MEDIA_NEXT_TRACK;

        break;

    case UX_CONSUMER_MEDIA_NEXT_TRACK:

        /* Sleep thread for 10ms.  */
        ux_utility_delay_ms(MS_TO_TICK(10));

        device_hid_event.ux_device_class_hid_event_buffer[0] = 0x07;
        device_hid_event.ux_device_class_hid_event_buffer[1] = 0;

        status = ux_device_class_hid_event_set(device_hid, &device_hid_event);

        if(status != UX_SUCCESS)
            return UX_ERROR;

        /* Send release event */
        device_hid_event.ux_device_class_hid_event_buffer[0] = 0;
        device_hid_event.ux_device_class_hid_event_buffer[1] = 0;

        /* Sleep thread for 10ms.  */
        ux_utility_delay_ms(MS_TO_TICK(10));

        status = ux_device_class_hid_event_set(device_hid, &device_hid_event);

        if(status != UX_SUCCESS)
            return UX_ERROR;

        media_event = UX_CONSUMER_MEDIA_PREVIOUS_TRACK;

        break;

    case UX_CONSUMER_MEDIA_PREVIOUS_TRACK:

        /* Sleep thread for 2s.  */
        ux_utility_delay_ms(MS_TO_TICK(2000));

        device_hid_event.ux_device_class_hid_event_buffer[0] = 0x08;
        device_hid_event.ux_device_class_hid_event_buffer[1] = 0;

        status = ux_device_class_hid_event_set(device_hid, &device_hid_event);

        if(status != UX_SUCCESS)
            return UX_ERROR;

        /* Send release event */
        device_hid_event.ux_device_class_hid_event_buffer[0] = 0;
        device_hid_event.ux_device_class_hid_event_buffer[1] = 0;

        /* Sleep thread for 10ms.  */
        ux_utility_delay_ms(MS_TO_TICK(10));

        status = ux_device_class_hid_event_set(device_hid, &device_hid_event);

        if(status != UX_SUCCESS)
            return UX_ERROR;

        media_event = UX_CONSUMER_MEDIA_DONE;

        break;

    default:

        ux_utility_memory_set(&device_hid_event, 0, sizeof(UX_SLAVE_CLASS_HID_EVENT));

        break;
    }

    return media_event;
}

UINT ux_demo_hid_consumer_brightness_control(UX_SLAVE_CLASS_HID *device_hid)
{
UCHAR                     status;
UX_SLAVE_CLASS_HID_EVENT  device_hid_event;
static UCHAR              brightness_event;
static UCHAR              brightness_level = 100;


    /* Initialize mouse event.  */
    device_hid_event.ux_device_class_hid_event_report_id = 0;
    device_hid_event.ux_device_class_hid_event_report_type = UX_DEVICE_CLASS_HID_REPORT_TYPE_INPUT;
    device_hid_event.ux_device_class_hid_event_length = 2;


    switch(brightness_event)
    {
    case UX_CONSUMER_BRIGHTNESS_DOWN:

        /* Sleep thread for 500ms.  */
        ux_utility_delay_ms(MS_TO_TICK(500));

        device_hid_event.ux_device_class_hid_event_buffer[0] = 0x02;
        device_hid_event.ux_device_class_hid_event_buffer[1] = 0;

        status = ux_device_class_hid_event_set(device_hid, &device_hid_event);

        if(status != UX_SUCCESS)
            return UX_ERROR;

        /* Send release event */
        device_hid_event.ux_device_class_hid_event_buffer[0] = 0;
        device_hid_event.ux_device_class_hid_event_buffer[1] = 0;

        /* Sleep thread for 10ms.  */
        ux_utility_delay_ms(MS_TO_TICK(10));

        status = ux_device_class_hid_event_set(device_hid, &device_hid_event);

        if(status != UX_SUCCESS)
            return UX_ERROR;

        brightness_level -= 2;

        if (brightness_level == 0)
            brightness_event = UX_CONSUMER_BRIGHTNESS_UP;

        break;

    case UX_CONSUMER_BRIGHTNESS_UP:

        /* Sleep thread for 500ms.  */
        ux_utility_delay_ms(MS_TO_TICK(500));

        device_hid_event.ux_device_class_hid_event_buffer[0] = 0x01;
        device_hid_event.ux_device_class_hid_event_buffer[1] = 0;

        status = ux_device_class_hid_event_set(device_hid, &device_hid_event);

        if(status != UX_SUCCESS)
            return UX_ERROR;

        /* Send release event */
        device_hid_event.ux_device_class_hid_event_buffer[0] = 0;
        device_hid_event.ux_device_class_hid_event_buffer[1] = 0;

        /* Sleep thread for 10ms.  */
        ux_utility_delay_ms(MS_TO_TICK(10));

        status = ux_device_class_hid_event_set(device_hid, &device_hid_event);

        if(status != UX_SUCCESS)
            return UX_ERROR;

        brightness_level += 2;

        if (brightness_level == 100)
            brightness_event = UX_CONSUMER_BRIGHTNESS_DONE;

        break;

    default:

        ux_utility_memory_set(&device_hid_event, 0, sizeof(UX_SLAVE_CLASS_HID_EVENT));

        break;
    }

    return brightness_event;
}
