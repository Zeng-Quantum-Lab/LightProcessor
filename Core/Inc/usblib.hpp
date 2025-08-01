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

class Usb_Coms{
public:
//Declaration
	Usb_Coms(PCD_HandleTypeDef * hpcd_USB_FS) {usb_instance = hpcd_USB_FS;};

//Variables
	constexpr static uint8_t IN1EP = 0x81;
	constexpr static uint8_t OUT1EP = 0x01;
	uint8_t Data_Out_Buffer[64];
	uint8_t Data_In_Buffer[64];

//Functions
	HAL_StatusTypeDef Usb_Init();
	void ProcessSetupStage(PCD_HandleTypeDef *hpcd);
	void Usb_Send(PCD_HandleTypeDef *hpcd, uint8_t epnum);
	void Usb_Recieve(PCD_HandleTypeDef *hpcd, uint8_t epnum);

private:
//Variables
	PCD_HandleTypeDef * usb_instance;

};




#endif /* INC_USBLIB_HPP_ */
