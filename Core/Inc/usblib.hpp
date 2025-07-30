/*
 * usblib.hpp
 *
 *  Created on: Jul 29, 2025
 *      Author: Khoi Anh Nguyen
 */
#ifndef INC_USBLIB_HPP_
#define INC_USBLIB_HPP_
extern "C"{
	#include "stm32g4xx_hal_pcd.h"
	#include "stm32g4xx_hal.h"
}

class Usb_Coms{
public:
//Declaration
	Usb_Coms(PCD_HandleTypeDef * hpcd_USB_FS) {usb_instance = hpcd_USB_FS;};

//Functions
	HAL_StatusTypeDef Usb_Init();
	HAL_StatusTypeDef Usb_Send();
	HAL_StatusTypeDef Usb_Recieve();

private:
//Variables
	PCD_HandleTypeDef * usb_instance;

};

#endif /* INC_USBLIB_HPP_ */
