/*
 * usblib.cpp
 *
 *  Created on: Jul 29, 2025
 *      Author: Khoi Anh Nguyen
 */

#include "usblib.hpp"

HAL_StatusTypeDef Usb_Coms::Usb_Init(){
	HAL_PCD_MspInit(usb_instance);

	(*usb_instance).IN_ep[0].xfer_buff = Receive_Buffer; //Link Receive Buffer
	(*usb_instance).OUT_ep[0].xfer_buff = Transmit_Buffer; //Link Transmit Buffer

	HAL_PCD_EP_Open(usb_instance, IN1EP, 64, EP_TYPE_CTRL); //Open IN endpoint
	HAL_PCD_EP_Open(usb_instance, OUT1EP, 64, EP_TYPE_CTRL); //Open Out endpoint

	return HAL_OK;
}

