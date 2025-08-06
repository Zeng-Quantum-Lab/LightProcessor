/*
 * usblib.cpp
 *
 *  Created on: Jul 29, 2025
 *      Author: Khoi Anh Nguyen
 */

#include "usblib.hpp"

HAL_StatusTypeDef Usb_Com::Usb_Init(){
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

HAL_StatusTypeDef Usb_Com::OpenEndpoint(uint8_t ep_num){
	uint8_t tracked_IN_ep = INDEFAULT + ep_num;
	uint8_t tracked_OUT_ep = OUTDEFAULT + ep_num;

	if (HAL_PCD_EP_Open(usb_instance, tracked_IN_ep, 64, EP_TYPE_CTRL) != HAL_OK){ //Open IN endpoint
		fprintf(stderr, "Fail to open IN%d\n", ep_num);
		return HAL_ERROR;
	}
	if (HAL_PCD_EP_Open(usb_instance, tracked_OUT_ep, 64, EP_TYPE_CTRL) != HAL_OK){ //Open Out endpoint
		fprintf(stderr, "Fail to open OUT%d\n", ep_num);
		return HAL_ERROR;
	}
	if (HAL_PCD_EP_Receive(usb_instance, tracked_IN_ep, Receive_Buffer, 64) != HAL_OK){ //Open endpoint to listen to
		fprintf(stderr, "Fail to listen to IN%d\n", ep_num);
		return HAL_ERROR;
	}

	return HAL_OK;
}
