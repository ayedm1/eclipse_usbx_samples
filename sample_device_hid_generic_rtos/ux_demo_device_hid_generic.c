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

#include "ux_demo_device_hid_generic.h"

/**************************************************/
/**  usbx device hid demo callbacks               */
/**************************************************/
VOID ux_demo_device_hid_instance_activate(VOID *hid_instance);
VOID ux_demo_device_hid_instance_deactivate(VOID *hid_instance);
UINT ux_demo_device_hid_callback(UX_SLAVE_CLASS_HID *hid_instance, UX_SLAVE_CLASS_HID_EVENT *hid_event);
UINT ux_demo_device_hid_get_callback(UX_SLAVE_CLASS_HID *hid_instance, UX_SLAVE_CLASS_HID_EVENT *hid_event);
#ifdef UX_DEVICE_CLASS_HID_INTERRUPT_OUT_SUPPORT
VOID ux_demo_device_hid_receiver_event_callback(struct UX_SLAVE_CLASS_HID_STRUCT *hid);
#endif /* UX_DEVICE_CLASS_HID_INTERRUPT_OUT_SUPPORT */

/**************************************************/
/**  usbx device hid demo thread                  */
/**************************************************/
VOID ux_demo_device_hid_thread_entry(ULONG thread_input);

/**************************************************/
/**  usbx application initialization with RTOS    */
/**************************************************/
VOID tx_application_define(VOID *first_unused_memory);

/**************************************************/
/**  usbx device hid demo generic                 */
/**************************************************/

/**************************************************/
/**  usbx device hid generic instance             */
/**************************************************/
UX_SLAVE_CLASS_HID *hid_generic;

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
UX_SLAVE_CLASS_HID_PARAMETER    hid_generic_parameter;

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

    /* Initialize the hid generic class parameters for the device */
    hid_generic_parameter.ux_slave_class_hid_instance_activate         = ux_demo_device_hid_instance_activate;
    hid_generic_parameter.ux_slave_class_hid_instance_deactivate       = ux_demo_device_hid_instance_deactivate;
    hid_generic_parameter.ux_device_class_hid_parameter_report_address = ux_demo_device_hid_get_report();
    hid_generic_parameter.ux_device_class_hid_parameter_report_length  = ux_demo_device_hid_get_report_length();
    hid_generic_parameter.ux_device_class_hid_parameter_report_id      = UX_FALSE;
    hid_generic_parameter.ux_device_class_hid_parameter_callback       = ux_demo_device_hid_callback;
    hid_generic_parameter.ux_device_class_hid_parameter_get_callback   = ux_demo_device_hid_get_callback;
#ifdef UX_DEVICE_CLASS_HID_INTERRUPT_OUT_SUPPORT
    hid_generic_parameter.ux_device_class_hid_parameter_receiver_initialize = ux_device_class_hid_receiver_initialize;
    hid_generic_parameter.ux_device_class_hid_parameter_receiver_event_max_number = 16;
    hid_generic_parameter.ux_device_class_hid_parameter_receiver_event_max_length = 64;
    hid_generic_parameter.ux_device_class_hid_parameter_receiver_event_callback = ux_demo_device_hid_receiver_event_callback;
#endif /* UX_DEVICE_CLASS_HID_INTERRUPT_OUT_SUPPORT */

    /* Initialize the device storage class. The class is connected with interface 0 on configuration 1. */
    status = ux_device_stack_class_register(_ux_system_slave_class_hid_name, ux_device_class_hid_entry,
                                            1, 0, (VOID *)&hid_generic_parameter);

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
    if (hid_generic == UX_NULL)
        hid_generic = (UX_SLAVE_CLASS_HID*) hid_instance;
}

/********************************************************************/
/**  ux_demo_device_hid_instance_deactivate                         */
/********************************************************************/
VOID ux_demo_device_hid_instance_deactivate(VOID *hid_instance)
{
    if (hid_instance == (VOID *)hid_generic)
        hid_generic = UX_NULL;
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

    UX_PARAMETER_NOT_USED(thread_input);

    usb_device_initialize();
}

#ifdef UX_DEVICE_CLASS_HID_INTERRUPT_OUT_SUPPORT

VOID ux_demo_device_hid_receiver_event_callback(struct UX_SLAVE_CLASS_HID_STRUCT *hid)
{

}
#endif /* UX_DEVICE_CLASS_HID_INTERRUPT_OUT_SUPPORT */
