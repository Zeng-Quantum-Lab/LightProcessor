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

	struct{
		uint8_t bmRequestType; //Direction, Type, Recipient
		uint8_t bRequest;      //Specific Request
		uint16_t wValue;       //Request-Specific parameter
		uint16_t wIndex;       //Endpoint Index
		uint16_t wLength;      //Number of bytes in Data Stage
	} Usb_Packet;



//Variables
	constexpr static uint8_t IN1EP = 0x81;
	constexpr static uint8_t OUT1EP = 0x01;
	uint8_t Receive_Buffer[64];
	uint8_t Transmit_Buffer[64];
	PCD_HandleTypeDef * usb_instance;

//Functions
	HAL_StatusTypeDef Usb_Init();

private:
//Variables


};




#endif /* INC_USBLIB_HPP_ */
