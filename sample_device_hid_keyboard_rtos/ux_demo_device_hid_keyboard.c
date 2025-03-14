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

#include "ux_demo_device_hid_keyboard.h"

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
/**  usbx device hid demo keyboard                */
/**************************************************/
UINT ux_demo_hid_keyboard_send_lowercase_character(UX_SLAVE_CLASS_HID *device_hid);
UINT ux_demo_hid_keyboard_send_uppercase_character(UX_SLAVE_CLASS_HID *device_hid);
UINT ux_demo_hid_keyboard_send_number(UX_SLAVE_CLASS_HID *device_hid);
UINT ux_demo_hid_keyboard_send_special_character(UX_SLAVE_CLASS_HID *device_hid);
UINT ux_demo_hid_keyboard_send_enter(UX_SLAVE_CLASS_HID *device_hid);

/**************************************************/
/**  usbx device hid keyboard instance            */
/**************************************************/
UX_SLAVE_CLASS_HID *hid_keyboard;

/**************************************************/
/**  usbx device hid keyboard                     */
/**************************************************/
ULONG num_lock_flag  = UX_FALSE;
ULONG caps_lock_flag = UX_FALSE;

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
UX_SLAVE_CLASS_HID_PARAMETER    hid_keyboard_parameter;

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

    /* Initialize the hid keyboard class parameters for the device */
    hid_keyboard_parameter.ux_slave_class_hid_instance_activate         = ux_demo_device_hid_instance_activate;
    hid_keyboard_parameter.ux_slave_class_hid_instance_deactivate       = ux_demo_device_hid_instance_deactivate;
    hid_keyboard_parameter.ux_device_class_hid_parameter_report_address = ux_demo_device_hid_get_report();
    hid_keyboard_parameter.ux_device_class_hid_parameter_report_length  = ux_demo_device_hid_get_report_length();
    hid_keyboard_parameter.ux_device_class_hid_parameter_report_id      = UX_FALSE;
    hid_keyboard_parameter.ux_device_class_hid_parameter_callback       = ux_demo_device_hid_callback;
    hid_keyboard_parameter.ux_device_class_hid_parameter_get_callback   = ux_demo_device_hid_get_callback;

    /* Initialize the device storage class. The class is connected with interface 0 on configuration 1. */
    status = ux_device_stack_class_register(_ux_system_slave_class_hid_name, ux_device_class_hid_entry,
                                            1, 0, (VOID *)&hid_keyboard_parameter);

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
    if (hid_keyboard == UX_NULL)
        hid_keyboard = (UX_SLAVE_CLASS_HID*) hid_instance;
}

/********************************************************************/
/**  ux_demo_device_hid_instance_deactivate                         */
/********************************************************************/
VOID ux_demo_device_hid_instance_deactivate(VOID *hid_instance)
{
    if (hid_instance == (VOID *)hid_keyboard)
        hid_keyboard = UX_NULL;
}

/********************************************************************/
/**  ux_demo_device_hid_callback                                    */
/********************************************************************/
UINT ux_demo_device_hid_callback(UX_SLAVE_CLASS_HID *hid_instance, UX_SLAVE_CLASS_HID_EVENT *hid_event)
{
    UX_PARAMETER_NOT_USED(hid_instance);

    /* There was an event.  Analyze it.  Is it NUM LOCK ? */
    if ((hid_event -> ux_device_class_hid_event_buffer[0] & UX_HID_NUM_LOCK_MASK) &&
        (hid_event -> ux_device_class_hid_event_report_type == UX_DEVICE_CLASS_HID_REPORT_TYPE_OUTPUT))

        /* Set the Num lock flag.  */
        num_lock_flag = UX_TRUE;
    else
        /* Reset the Num lock flag.  */
        num_lock_flag = UX_FALSE;

    /* There was an event.  Analyze it.  Is it CAPS LOCK ? */
    if ((hid_event -> ux_device_class_hid_event_buffer[0] & UX_HID_CAPS_LOCK_MASK) &&
        (hid_event -> ux_device_class_hid_event_report_type == UX_DEVICE_CLASS_HID_REPORT_TYPE_OUTPUT))
        /* Set the Caps lock flag.  */
        caps_lock_flag = UX_TRUE;
    else
        /* Reset the Caps lock flag.  */
        caps_lock_flag = UX_FALSE;

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
      if ((UX_SLAVE_DEVICE_CHECK_STATE(UX_DEVICE_CONFIGURED)) && (hid_keyboard != UX_NULL))
      {
        switch(demo_state)
        {

        case UX_DEMO_HID_KEYBOARD_SEND_LOWCASE_CHARATER:

          /* keyboard send lowercase character */
          status = ux_demo_hid_keyboard_send_lowercase_character(hid_keyboard);

          if (status == UX_DEMO_HID_KEYBOARD_SEND_EVENT_DONE)
          {
              status = ux_demo_hid_keyboard_send_enter(hid_keyboard);

              if (status == UX_DEMO_HID_KEYBOARD_SEND_EVENT_DONE)
                  demo_state = UX_DEMO_HID_KEYBOARD_SEND_UPPERCASE_CHARATER;
          }

          break;


        case UX_DEMO_HID_KEYBOARD_SEND_UPPERCASE_CHARATER:

          /* keyboard send uppercase character */
          status = ux_demo_hid_keyboard_send_uppercase_character(hid_keyboard);

          if (status == UX_DEMO_HID_KEYBOARD_SEND_EVENT_DONE)
          {
              status = ux_demo_hid_keyboard_send_enter(hid_keyboard);

              if (status == UX_DEMO_HID_KEYBOARD_SEND_EVENT_DONE)
                  demo_state = UX_DEMO_HID_KEYBOARD_SEND_NUMBER;
          }

          break;


        case UX_DEMO_HID_KEYBOARD_SEND_NUMBER:

          /* keyboard send number */
          status = ux_demo_hid_keyboard_send_number(hid_keyboard);

          if (status == UX_DEMO_HID_KEYBOARD_SEND_EVENT_DONE)
          {
              status = ux_demo_hid_keyboard_send_enter(hid_keyboard);

              if (status == UX_DEMO_HID_KEYBOARD_SEND_EVENT_DONE)
                  demo_state = UX_DEMO_HID_KEYBOARD_SENLD_SPECIAL_CHARATER;
          }

          break;


        case UX_DEMO_HID_KEYBOARD_SENLD_SPECIAL_CHARATER:

          /* keyboard send special character */
          status = ux_demo_hid_keyboard_send_special_character(hid_keyboard);

          if (status == UX_DEMO_HID_KEYBOARD_SEND_EVENT_DONE)
              demo_state = UX_DEMO_HID_KEYBOARD_SEND_EVENT_FINISH;

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
/**  ux_demo_hid_keyboard_send_lowercaser_character:                */
/**          send lowercase character (a -> z)                      */
/********************************************************************/
UINT ux_demo_hid_keyboard_send_lowercase_character(UX_SLAVE_CLASS_HID *device_hid)
{
UCHAR                    status;
UCHAR                    key;
UX_SLAVE_CLASS_HID_EVENT device_hid_event;
static UCHAR             index;

    /* Wait for 10 seconds. */
    ux_utility_thread_sleep(MS_TO_TICK(50));

    key = keys_alphanumeric[index];

    /* Insert a key into the keyboard event.  */
    device_hid_event.ux_device_class_hid_event_report_id = 0;
    device_hid_event.ux_device_class_hid_event_report_type = UX_DEVICE_CLASS_HID_REPORT_TYPE_INPUT;
    device_hid_event.ux_device_class_hid_event_length = 8;
    device_hid_event.ux_device_class_hid_event_buffer[0] = 0;
    device_hid_event.ux_device_class_hid_event_buffer[1] = 0;
    device_hid_event.ux_device_class_hid_event_buffer[2] = key;   /* key */
    device_hid_event.ux_device_class_hid_event_buffer[3] = 0;
    device_hid_event.ux_device_class_hid_event_buffer[4] = 0;
    device_hid_event.ux_device_class_hid_event_buffer[5] = 0;
    device_hid_event.ux_device_class_hid_event_buffer[6] = 0;
    device_hid_event.ux_device_class_hid_event_buffer[7] = 0;

    /* Set the keyboard event.  */
    status = ux_device_class_hid_event_set(hid_keyboard, &device_hid_event);

    if (status != UX_SUCCESS)
        return status;

    /* Next event has the key depressed.  */
    device_hid_event.ux_device_class_hid_event_buffer[2] = 0;

    /* Set the keyboard event.  */
    status = ux_device_class_hid_event_set(hid_keyboard, &device_hid_event);

    if (status != UX_SUCCESS)
        return status;

    /* Are we at the end of alphabet ?  */
    if (index < sizeof(keys_alphanumeric))
        /* Next key.  */
        index++;
    else
    {
        ux_utility_memory_set(&device_hid_event, 0, sizeof(UX_SLAVE_CLASS_HID_EVENT));

        status = UX_DEMO_HID_KEYBOARD_SEND_EVENT_DONE;
    }

    return status;
}

/********************************************************************/
/**  ux_demo_hid_keyboard_send_uppercase_character:                 */
/**          send uppercase character (A -> Z)                      */
/********************************************************************/
UINT ux_demo_hid_keyboard_send_uppercase_character(UX_SLAVE_CLASS_HID *device_hid)
{
UCHAR                    status;
UCHAR                    key;
UX_SLAVE_CLASS_HID_EVENT device_hid_event;
static UCHAR             index;


    /* Wait for 20 seconds. */
    ux_utility_thread_sleep(MS_TO_TICK(50));

    key = keys_alphanumeric[index];

    /* Insert a key into the keyboard event.  */
    device_hid_event.ux_device_class_hid_event_report_id = 0;
    device_hid_event.ux_device_class_hid_event_report_type = UX_DEVICE_CLASS_HID_REPORT_TYPE_INPUT;
    device_hid_event.ux_device_class_hid_event_length = 8;
    device_hid_event.ux_device_class_hid_event_buffer[0] = 0x02;  /* Left Shift modifier */
    device_hid_event.ux_device_class_hid_event_buffer[1] = 0;
    device_hid_event.ux_device_class_hid_event_buffer[2] = key;   /* key */
    device_hid_event.ux_device_class_hid_event_buffer[3] = 0;
    device_hid_event.ux_device_class_hid_event_buffer[4] = 0;
    device_hid_event.ux_device_class_hid_event_buffer[5] = 0;
    device_hid_event.ux_device_class_hid_event_buffer[6] = 0;
    device_hid_event.ux_device_class_hid_event_buffer[7] = 0;

    /* Set the keyboard event.  */
    status = ux_device_class_hid_event_set(hid_keyboard, &device_hid_event);

    if (status != UX_SUCCESS)
        return status;

    /* Next event has the key depressed.  */
    device_hid_event.ux_device_class_hid_event_buffer[0] = 0;
    device_hid_event.ux_device_class_hid_event_buffer[2] = 0;

    /* Set the keyboard event.  */
    status = ux_device_class_hid_event_set(hid_keyboard, &device_hid_event);

    if (status != UX_SUCCESS)
        return status;

    /* Are we at the end of alphabet ?  */
    if (index < sizeof(keys_alphanumeric))
        /* Next key.  */
        index++;
    else
    {
        ux_utility_memory_set(&device_hid_event, 0, sizeof(UX_SLAVE_CLASS_HID_EVENT));

        status = UX_DEMO_HID_KEYBOARD_SEND_EVENT_DONE;
    }

   return status;
}

/********************************************************************/
/**  ux_demo_hid_keyboard_send_number:                              */
/**          send number (0 -> 9)                                   */
/********************************************************************/
UINT ux_demo_hid_keyboard_send_number(UX_SLAVE_CLASS_HID *device_hid)
{
UCHAR                    status;
UCHAR                    number;
UX_SLAVE_CLASS_HID_EVENT device_hid_event;
static UCHAR             index;


    /* Wait for 20 seconds. */
    ux_utility_thread_sleep(MS_TO_TICK(50));

    number = keys_numeric[index];

    /* Insert a key into the keyboard event.  */
    device_hid_event.ux_device_class_hid_event_report_id = 0;
    device_hid_event.ux_device_class_hid_event_report_type = UX_DEVICE_CLASS_HID_REPORT_TYPE_INPUT;
    device_hid_event.ux_device_class_hid_event_length = 8;
    device_hid_event.ux_device_class_hid_event_buffer[0] = 0;
    device_hid_event.ux_device_class_hid_event_buffer[1] = 0;
    device_hid_event.ux_device_class_hid_event_buffer[2] = number;   /* key */
    device_hid_event.ux_device_class_hid_event_buffer[3] = 0;
    device_hid_event.ux_device_class_hid_event_buffer[4] = 0;
    device_hid_event.ux_device_class_hid_event_buffer[5] = 0;
    device_hid_event.ux_device_class_hid_event_buffer[6] = 0;
    device_hid_event.ux_device_class_hid_event_buffer[7] = 0;

    /* Set the keyboard event.  */
    status = ux_device_class_hid_event_set(hid_keyboard, &device_hid_event);

    if (status != UX_SUCCESS)
        return status;

    /* Next event has the key depressed.  */
    device_hid_event.ux_device_class_hid_event_buffer[2] = 0;

    /* Set the keyboard event.  */
    status = ux_device_class_hid_event_set(hid_keyboard, &device_hid_event);

    if (status != UX_SUCCESS)
        return status;

    /* Are we at the end of numeric ?  */
    if (index < sizeof(keys_numeric))
        /* Next key.  */
        index++;
    else
    {
        ux_utility_memory_set(&device_hid_event, 0, sizeof(UX_SLAVE_CLASS_HID_EVENT));

        status = UX_DEMO_HID_KEYBOARD_SEND_EVENT_DONE;
    }

   return status;
}

/********************************************************************/
/**  ux_demo_hid_keyboard_send_special_character:                   */
/**          send number (!, @, #, $, %, ^, &, *, (, ))             */
/********************************************************************/
UINT ux_demo_hid_keyboard_send_special_character(UX_SLAVE_CLASS_HID *device_hid)
{
UCHAR                    status;
UCHAR                    key;
UX_SLAVE_CLASS_HID_EVENT device_hid_event;
static UCHAR             index;


    /* Wait for 20 seconds. */
    ux_utility_thread_sleep(MS_TO_TICK(50));

    key = keys_numeric[index];

    /* Insert a key into the keyboard event.  */
    device_hid_event.ux_device_class_hid_event_report_id = 0;
    device_hid_event.ux_device_class_hid_event_report_type = UX_DEVICE_CLASS_HID_REPORT_TYPE_INPUT;
    device_hid_event.ux_device_class_hid_event_length = 8;
    device_hid_event.ux_device_class_hid_event_buffer[0] = 0x02;  /* Left Shift modifier */
    device_hid_event.ux_device_class_hid_event_buffer[1] = 0;
    device_hid_event.ux_device_class_hid_event_buffer[2] = key;   /* key */
    device_hid_event.ux_device_class_hid_event_buffer[3] = 0;
    device_hid_event.ux_device_class_hid_event_buffer[4] = 0;
    device_hid_event.ux_device_class_hid_event_buffer[5] = 0;
    device_hid_event.ux_device_class_hid_event_buffer[6] = 0;
    device_hid_event.ux_device_class_hid_event_buffer[7] = 0;

    /* Set the keyboard event.  */
    status = ux_device_class_hid_event_set(hid_keyboard, &device_hid_event);

    if (status != UX_SUCCESS)
        return status;

    /* Next event has the key depressed.  */
    device_hid_event.ux_device_class_hid_event_buffer[0] = 0;
    device_hid_event.ux_device_class_hid_event_buffer[2] = 0;

    /* Set the keyboard event.  */
    status = ux_device_class_hid_event_set(hid_keyboard, &device_hid_event);

    if (status != UX_SUCCESS)
        return status;

    /* Are we at the end of alphabet ?  */
    if (index < sizeof(keys_numeric))
        /* Next key.  */
        index++;
    else
    {
        ux_utility_memory_set(&device_hid_event, 0, sizeof(UX_SLAVE_CLASS_HID_EVENT));

        status = UX_DEMO_HID_KEYBOARD_SEND_EVENT_DONE;
    }

   return status;
}

/********************************************************************/
/**  ux_demo_hid_keyboard_send_enter:                               */
/**          send enter (\r)                                        */
/********************************************************************/
UINT ux_demo_hid_keyboard_send_enter(UX_SLAVE_CLASS_HID *device_hid)
{
UCHAR                    status;
UX_SLAVE_CLASS_HID_EVENT device_hid_event;


    /* Wait for 20 seconds. */
    ux_utility_thread_sleep(MS_TO_TICK(50));

    /* Insert a key into the keyboard event.  */
    device_hid_event.ux_device_class_hid_event_report_id = 0;
    device_hid_event.ux_device_class_hid_event_report_type = UX_DEVICE_CLASS_HID_REPORT_TYPE_INPUT;
    device_hid_event.ux_device_class_hid_event_length = 8;
    device_hid_event.ux_device_class_hid_event_buffer[0] = 0;
    device_hid_event.ux_device_class_hid_event_buffer[1] = 0;
    device_hid_event.ux_device_class_hid_event_buffer[2] = 0x28; /* ENTER key */
    device_hid_event.ux_device_class_hid_event_buffer[3] = 0;
    device_hid_event.ux_device_class_hid_event_buffer[4] = 0;
    device_hid_event.ux_device_class_hid_event_buffer[5] = 0;
    device_hid_event.ux_device_class_hid_event_buffer[6] = 0;
    device_hid_event.ux_device_class_hid_event_buffer[7] = 0;

    /* Set the keyboard event.  */
    status = ux_device_class_hid_event_set(hid_keyboard, &device_hid_event);

    if (status != UX_SUCCESS)
        return status;

    /* Next event has the key depressed.  */
    device_hid_event.ux_device_class_hid_event_buffer[2] = 0;

    /* Set the keyboard event.  */
    status = ux_device_class_hid_event_set(hid_keyboard, &device_hid_event);

    if (status != UX_SUCCESS)
        return status;

    ux_utility_memory_set(&device_hid_event, 0, sizeof(UX_SLAVE_CLASS_HID_EVENT));

    status = UX_DEMO_HID_KEYBOARD_SEND_EVENT_DONE;

    return status;
}
