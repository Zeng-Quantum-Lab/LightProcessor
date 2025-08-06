/*
 * run.cpp
 *
 *  Created on: Jul 31, 2025
 *      Author: Admin
 */
//Good Study Ref:
//https://www.beyondlogic.org/usbnutshell/usb5.shtml

#include "run.hpp"

extern "C"{
	extern PCD_HandleTypeDef hpcd_USB_FS;
}

Usb_Com usb = Usb_Com(&hpcd_USB_FS);
Usb_Setup usb_setup = Usb_Setup(&hpcd_USB_FS);
Usb_Setup::DeviceDescriptor usb_descriptor;

void ProcessSetup(PCD_HandleTypeDef *hpcd){
	Usb_Setup::SetupUsbPacket * setup_packet = (Usb_Setup::SetupUsbPacket *) (*usb_setup.usb_instance).Setup;

	switch (setup_packet->bRequest) {
		case Usb_Setup::DeviceRequest::SET_ADDRESS: {
			if (HAL_PCD_SetAddress(usb_setup.usb_instance, setup_packet->wValue) != HAL_OK){
				fprintf(stderr, "Cannot Setup Device Address\n");
				break;
			}
				break;
		}

		case Usb_Setup::DeviceRequest::GET_DESCRIPTOR: {
			uint8_t * usb_descriptor_bytes = (uint8_t *)&usb_descriptor;
			if (HAL_PCD_EP_Transmit(usb_setup.usb_instance, Usb_Com::OUTDEFAULT + 1, usb_descriptor_bytes, usb_descriptor.bLength) != HAL_OK){
				fprintf(stderr, "Cannot Send Device Descriptor");
			}
			break;
		}
		default:
			break;
	}

}

void Usb_Send(PCD_HandleTypeDef *hpcd, uint8_t epnum){
	usb.Transmitted = true;
}

void Usb_Receive(PCD_HandleTypeDef *hpcd, uint8_t epnum){
	usb.Received = true;
}

void run(){
//USB Config
	uint8_t tracked_ep = 1;

	if (usb.Usb_Init() != HAL_OK){
		fprintf(stderr, "Cannot Initialize USB Components\n");
		return;
	}

	(*usb_setup.usb_instance).SetupStageCallback = ProcessSetup;
	(*usb.usb_instance).DataInStageCallback = Usb_Send;
	(*usb.usb_instance).DataOutStageCallback = Usb_Receive;

	if (usb.OpenEndpoint(tracked_ep) != HAL_OK){
		fprintf(stderr, "Cannot Open Endpoint %d\n", tracked_ep);
		return;
	}


}
