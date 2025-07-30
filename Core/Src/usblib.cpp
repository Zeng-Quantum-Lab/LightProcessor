/*
 * usblib.cpp
 *
 *  Created on: Jul 29, 2025
 *      Author: Khoi Anh Nguyen
 */

#include "usblib.hpp"


HAL_StatusTypeDef Usb_Coms::Usb_Init(){
	HAL_PCD_MspInit(usb_instance);

	usb_instance->pData = pdev;
	if (!(HAL_PCD_Start(usb_instance) == HAL_OK)){
		fprintf(stderr, "Cannot Start USB peripheral\n");
		return HAL_ERROR;
	}
	HAL_Delay();

	return HAL_OK;
}

HAL_StatusTypeDef Usb_Coms::Usb_Send(){

	return True;
}

HAL_StatusTypeDef Usb_Coms::Usb_Recieve(){

}
