/*
 * usblib.hpp
 *
 *  Created on: Jul 30, 2025
 *      Author: Admin
 */

#ifndef INC_USBLIB_HPP_
#define INC_USBLIB_HPP_

#include "stm32g4xx_hal.h"
#include "stm32g4xx_hal_pcd.h"
#include <stdio.h>

void HAL_PCD_DataOutStageCallback (PCD_HandleTypeDef * hpcd, uint8_t epnum);

class Usb_Coms{
public:
//Declaration
	Usb_Coms(PCD_HandleTypeDef * hpcd_USB_FS) {usb_instance = hpcd_USB_FS;};

//Functions
	HAL_StatusTypeDef Usb_Init();
	void Usb_Send();
	void Usb_Recieve();

private:
//Variables
	PCD_HandleTypeDef * usb_instance;

};




#endif /* INC_USBLIB_HPP_ */
