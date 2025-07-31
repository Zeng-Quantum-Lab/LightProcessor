/*
 * usblib.cpp
 *
 *  Created on: Jul 29, 2025
 *      Author: Khoi Anh Nguyen
 */

#include "usblib.hpp"


HAL_StatusTypeDef Usb_Coms::Usb_Init(){
	HAL_PCD_MspInit(usb_instance);


	if (HAL_PCD_Start(usb_instance) != HAL_OK){
		fprintf(stderr, "Cannot Start USB Components\n");
		return HAL_ERROR;
	}

	HAL_Delay(25);

	if (HAL_PCD_DevConnect(usb_instance) != HAL_OK){
		fprintf(stderr, "Cannot Connect USB Components\n");
		return HAL_ERROR;
	}


	return HAL_OK;
}

void HAL_PCD_DataInStageCallback (PCD_HandleTypeDef * hpcd, uint8_t epnum){

}

void Usb_Coms::Usb_Send(){

}

void Usb_Coms::Usb_Recieve(){
}
