
#include "ux_api.h"

#include "ux_dcd_stm32.h"

#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_pcd.h"

#include "usb_app_setup.h"

PCD_HandleTypeDef  hpcd_USB_OTG_HS;

void usb_device_initialize()
{
UINT    status =  0;

  /* USER CODE END USB_OTG_HS_Init 1 */
  hpcd_USB_OTG_HS.Instance = USB_OTG_HS;
  hpcd_USB_OTG_HS.Init.dev_endpoints = 8;
  hpcd_USB_OTG_HS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_OTG_HS.Init.dma_enable = DISABLE;
  hpcd_USB_OTG_HS.Init.phy_itface = PCD_PHY_ULPI;
  hpcd_USB_OTG_HS.Init.Sof_enable = DISABLE;
  hpcd_USB_OTG_HS.Init.low_power_enable = DISABLE;
  hpcd_USB_OTG_HS.Init.lpm_enable = DISABLE;
  hpcd_USB_OTG_HS.Init.vbus_sensing_enable = DISABLE;
  hpcd_USB_OTG_HS.Init.use_dedicated_ep1 = DISABLE;
  hpcd_USB_OTG_HS.Init.use_external_vbus = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_OTG_HS) != HAL_OK)
   return;


  /* Register the STM32  USB device controllers available in this system */
  status =  ux_dcd_stm32_initialize((ULONG)USB_OTG_HS, (ULONG)&hpcd_USB_OTG_HS);

  if (status != UX_SUCCESS)
   return;


#ifdef DEMO_HID
  HAL_PCDEx_SetRxFiFo(&hpcd_USB_OTG_HS, 0x120);
  HAL_PCDEx_SetTxFiFo(&hpcd_USB_OTG_HS, 0, 0x80);
  HAL_PCDEx_SetTxFiFo(&hpcd_USB_OTG_HS, 1, 0x100);
#endif /* DEMO_HID */

  HAL_PCD_Start(&hpcd_USB_OTG_HS);
}
