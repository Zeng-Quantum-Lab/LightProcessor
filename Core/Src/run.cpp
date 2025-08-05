/*
 * run.cpp
 *
 *  Created on: Jul 31, 2025
 *      Author: Admin
 */

#include "run.hpp"

extern "C"{
	extern PCD_HandleTypeDef hpcd_USB_FS;
}

Usb_Coms usb = Usb_Coms(&hpcd_USB_FS);

int run(){

	//USB Config
//	if (usb.Usb_Init() != HAL_OK){
//		fprintf(stderr, "Cannot Initialize USB Components\n");
//		break;
//	}

	(*usb.usb_instance).SetupStageCallback = ProcessSetup;
	(*usb.usb_instance).DataInStageCallback = Usb_Send;
	(*usb.usb_instance).DataOutStageCallback = Usb_Receive;

	if (HAL_PCD_Start(usb.usb_instance) != HAL_OK){
		fprintf(stderr, "Cannot Start USB Components\n");
		break;
	}

	HAL_Delay(25);

	if (HAL_PCD_DevConnect(usb.usb_instance) != HAL_OK){
		fprintf(stderr, "Cannot Connect USB Components\n");
		break;
	}


}

void ProcessSetup(PCD_HandleTypeDef *hpcd){

}

void Usb_Send(PCD_HandleTypeDef *hpcd, uint8_t epnum){

}

void Usb_Receive(PCD_HandleTypeDef *hpcd, uint8_t epnum){

}
