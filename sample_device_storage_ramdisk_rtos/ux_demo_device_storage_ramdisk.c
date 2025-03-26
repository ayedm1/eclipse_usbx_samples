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

#include "ux_demo_device_storage_ramdisk.h"

/**************************************************/
/**  usbx device storage demo callbacks           */
/**************************************************/
VOID ux_demo_device_storage_instance_activate(VOID *storage_instance);
VOID ux_demo_device_storage_instance_deactivate(VOID *storage_instance);
UINT ux_demo_storage_media_read(VOID *storage, ULONG lun, UCHAR * data_pointer, ULONG number_blocks,
                                ULONG lba, ULONG *media_status);
UINT ux_demo_storage_media_write(VOID *storage, ULONG lun, UCHAR * data_pointer, ULONG number_blocks,
                                 ULONG lba, ULONG *media_status);
UINT ux_demo_storage_media_status(VOID *storage, ULONG lun, ULONG media_id, ULONG *media_status);
UINT ux_demo_storage_media_flush(VOID *storage, ULONG lun, ULONG number_blocks, ULONG lba, ULONG *media_status);

/**************************************************/
/**  usbx device storage demo thread              */
/**************************************************/
VOID ux_demo_device_storage_thread_entry(ULONG thread_input);

/**************************************************/
/**  usbx application initialization with RTOS    */
/**************************************************/
VOID tx_application_define(VOID *first_unused_memory);

/**************************************************/
/**  usbx device storage demo                     */
/**************************************************/
VOID usbx_storage_disk_init(VOID);
static VOID ux_demo_error_callback(UINT system_level, UINT system_context, UINT error_code);

/**************************************************/
/**  usbx device storage instance                 */
/**************************************************/
UX_SLAVE_CLASS_STORAGE *storage_ramdisk;

/**************************************************/
/**  thread object                                */
/**************************************************/
static TX_THREAD ux_storage_thread;

VOID usbx_storage_disk_init(VOID);

UCHAR ram_disk_memory[RAM_DISK_SIZE];

int main(void)
{
    /* Initialize the board.  */
    board_setup();

    printf("USBX Device mass storage example\r\n");

    /* Enter the ThreadX kernel.  */
    tx_kernel_enter();
}

VOID tx_application_define(VOID *first_unused_memory)
{
CHAR                              *stack_pointer;
CHAR                              *memory_pointer;
UINT                              status;
UX_SLAVE_CLASS_STORAGE_PARAMETER  storage_ramdisk_parameter;
UX_SLAVE_CLASS_STORAGE_LUN        *lun;

    /* Initialize the free memory pointer.  */
    stack_pointer =  (CHAR *) first_unused_memory;

    /* Initialize the RAM disk memory. */
    memory_pointer =  stack_pointer +  DEMO_STACK_SIZE;

    usbx_storage_disk_init();

    /* Initialize USBX Memory */
    status = ux_system_initialize(memory_pointer, UX_DEVICE_MEMORY_STACK_SIZE, UX_NULL, 0);

    if(status != UX_SUCCESS)
        goto error;

    printf("USBX System initialized successfully\r\n");

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
        goto error;

    printf("USBX Device stack initialized successfully\r\n");;

    /* Initialize the storage class parameters for the device */
    storage_ramdisk_parameter.ux_slave_class_storage_instance_activate = ux_demo_device_storage_instance_activate;
    storage_ramdisk_parameter.ux_slave_class_storage_instance_deactivate = ux_demo_device_storage_instance_deactivate;
    storage_ramdisk_parameter.ux_slave_class_storage_parameter_number_lun = 1;
//    storage_ramdisk_parameter.ux_slave_class_storage_parameter_product_id = (UCHAR*) UX_DEMO_STORAGE_DEVICE_PID;
//    storage_ramdisk_parameter.ux_slave_class_storage_parameter_product_rev = "001";
//    storage_ramdisk_parameter.ux_slave_class_storage_parameter_product_serial = "123456789";
//    storage_ramdisk_parameter.ux_slave_class_storage_parameter_vendor_id = (UCHAR*) UX_DEMO_STORAGE_DEVICE_VID;

    lun = &storage_ramdisk_parameter.ux_slave_class_storage_parameter_lun[0];

    /* Initialize the storage class parameters for reading/writing to the Flash Disk.  */
    lun -> ux_slave_class_storage_media_last_lba = RAM_DISK_LAST_LBA;
    lun -> ux_slave_class_storage_media_block_length = 512;
    lun -> ux_slave_class_storage_media_type = 0;
    lun -> ux_slave_class_storage_media_removable_flag = 0x80;
    lun -> ux_slave_class_storage_media_read_only_flag = RAM_DISK_WRITE_PROTECT;
    lun -> ux_slave_class_storage_media_read = ux_demo_storage_media_read;
    lun -> ux_slave_class_storage_media_write = ux_demo_storage_media_write;
    lun -> ux_slave_class_storage_media_status = ux_demo_storage_media_status;
    lun -> ux_slave_class_storage_media_flush = RAM_DISK_WRITE_CACHING ? ux_demo_storage_media_flush : UX_NULL;

    /* Initialize the device storage class. The class is connected with interface 0 on configuration 1. */
    status = ux_device_stack_class_register(_ux_system_slave_class_storage_name, _ux_device_class_storage_entry,
                                            1, 0, (VOID *)&storage_ramdisk_parameter);

    if(status != UX_SUCCESS)
        goto error;

    /* error callback */
    ux_utility_error_callback_register(ux_demo_error_callback);

    /* Create the main demo thread.  */
    status = ux_utility_thread_create(&ux_storage_thread, "storage_usbx_app_thread_entry",
                                      ux_demo_device_storage_thread_entry, 0, stack_pointer,
                                      512, 20, 20, 1, TX_AUTO_START);

    if(status != UX_SUCCESS)
        goto error;

    return;

error:
    printf("tx_application_define: ERROR 0x%x\r\n", status);
    while(1)
    {
    }
}

/********************************************************************/
/**  ux_demo_device_storage_instance_activate                       */
/********************************************************************/
VOID ux_demo_device_storage_instance_activate(VOID *storage_instance)
{
    if (storage_ramdisk == UX_NULL)
    {
        storage_ramdisk = (UX_SLAVE_CLASS_STORAGE*) storage_instance;

        printf("USBX Device mass storage activate\r\n");
    }
}

/********************************************************************/
/**  ux_demo_device_storage_instance_deactivate                     */
/********************************************************************/
VOID ux_demo_device_storage_instance_deactivate(VOID *storage_instance)
{
    if (storage_instance == (VOID *)storage_ramdisk)
    {
        storage_ramdisk = UX_NULL;

        printf("USBX device mass storage deactivate\r\n");
    }
}


UINT ux_demo_storage_media_read(VOID *storage, ULONG lun, UCHAR *data_pointer, ULONG number_blocks,
                                ULONG lba, ULONG *media_status)
{
UINT status =  UX_SUCCESS;

    UX_PARAMETER_NOT_USED(storage);
    UX_PARAMETER_NOT_USED(media_status);

    ux_utility_memory_copy(data_pointer, ram_disk_memory + lba * 512, number_blocks * 512);

    return(status);
}

UINT ux_demo_storage_media_write(VOID *storage, ULONG lun, UCHAR *data_pointer, ULONG number_blocks,
                                 ULONG lba, ULONG *media_status)
{
UINT status =  UX_SUCCESS;

    UX_PARAMETER_NOT_USED(storage);
    UX_PARAMETER_NOT_USED(media_status);

    ux_utility_memory_copy(ram_disk_memory + lba * 512, data_pointer, number_blocks * 512);

    return(status);
}

UINT ux_demo_storage_media_status(VOID *storage, ULONG lun, ULONG media_id, ULONG *media_status)
{
    UX_PARAMETER_NOT_USED(storage);
    UX_PARAMETER_NOT_USED(lun);
    UX_PARAMETER_NOT_USED(media_id);
    UX_PARAMETER_NOT_USED(media_status);

    return(UX_SUCCESS);
}

UINT ux_demo_storage_media_flush(VOID *storage, ULONG lun, ULONG number_blocks, ULONG lba, ULONG *media_status)
{
    UX_PARAMETER_NOT_USED(storage);
    UX_PARAMETER_NOT_USED(lun);
    UX_PARAMETER_NOT_USED(number_blocks);
    UX_PARAMETER_NOT_USED(lba);
    UX_PARAMETER_NOT_USED(media_status);

    return(UX_SUCCESS);
}

/********************************************************************/
/**  ux_demo_device_storage_thread_entry: storage demo thread       */
/********************************************************************/
VOID ux_demo_device_storage_thread_entry(ULONG thread_input)
{

    UX_PARAMETER_NOT_USED(thread_input);

    usb_device_initialize();
}

VOID usbx_storage_disk_init(VOID)
{
    ux_utility_memory_set(ram_disk_memory, 0, RAM_DISK_SIZE);

#ifdef BUILD_FILE_SYSTEM

    ux_utility_memory_copy(ram_disk_memory + 0 * 512, (void*)sector_0, sizeof(sector_0));

    /* Update number of sectors.  */
    if (RAM_DISK_N_LBA >= 0x100)
    {
        ux_utility_short_put(ram_disk_memory + 0x13, 0);
        ux_utility_long_put(ram_disk_memory + 0x20, RAM_DISK_N_LBA);
    }
    else
    {
        ux_utility_short_put(ram_disk_memory + 0x13, RAM_DISK_N_LBA);
        ux_utility_long_put(ram_disk_memory + 0x20, 0);
    }

    ux_utility_memory_copy(ram_disk_memory + 6 * 512, (void*)sector_6_7, sizeof(sector_6_7));
    ux_utility_memory_copy(ram_disk_memory + 7 * 512, (void*)sector_6_7, sizeof(sector_6_7));
    ux_utility_memory_copy(ram_disk_memory + 8 * 512, (void*)sector_8, sizeof(sector_8));

#endif /* BUILD_FILE_SYSTEM */
}

static VOID ux_demo_error_callback(UINT system_level, UINT system_context, UINT error_code)
{
    /*
     * Refer to ux_api.h. For example,
     * UX_SYSTEM_LEVEL_INTERRUPT, UX_SYSTEM_CONTEXT_DCD, UX_DEVICE_HANDLE_UNKNOWN
     */
    printf("USBX error: system level(%d), context(%d), error code(0x%x)\r\n", system_level, system_context, error_code);
}