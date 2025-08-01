/*
 * usblib.cpp
 *
 *  Created on: Jul 29, 2025
 *      Author: Khoi Anh Nguyen
 */

#include "usblib.hpp"


HAL_StatusTypeDef Usb_Coms::Usb_Init(){
	HAL_PCD_MspInit(usb_instance);

	(*usb_instance).SetupStageCallback = ProcessSetupStage;
	(*usb_instance).DataInStageCallback = Usb_Send;
	(*usb_instance).DataOutStageCallback = Usb_Recieve;


	HAL_PCD_EP_Open(usb_instance, IN1EP, 64, EP_TYPE_CTRL);
	HAL_PCD_EP_Open(usb_instance, OUT1EP, 64, EP_TYPE_CTRL);

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

void Usb_Coms::ProcessSetupStage(PCD_HandleTypeDef *hpcd){

}

void Usb_Coms::Usb_Send(PCD_HandleTypeDef *hpcd, uint8_t epnum){

}

void Usb_Coms::Usb_Recieve(PCD_HandleTypeDef *hpcd, uint8_t epnum){

}
