/*
 * run.cpp
 *
 *  Created on: Jul 31, 2025
 *      Author: Admin
 */
//Good Study Ref:
//https://www.beyondlogic.org/usbnutshell/usb5.shtml

#include "run.h"
#include "usblib.hpp"
#include "usbsetup.hpp"

extern "C"{
	extern PCD_HandleTypeDef hpcd_USB_FS;
	extern ADC_HandleTypeDef hadc1;
	extern TIM_HandleTypeDef htim2;
	extern UART_HandleTypeDef huart5;
}

Usb_Com usb = Usb_Com(&hpcd_USB_FS);
Usb_Setup usb_setup = Usb_Setup(&hpcd_USB_FS);
Usb_Setup::DeviceDescriptor usb_descriptor;
bool isSquareMode = true;
uint32_t bytePointer = 0;
uint8_t bitPointer = 0;
uint8_t UartTransmitBuffer[64];

void ProcessSetup(PCD_HandleTypeDef *hpcd){
	Usb_Setup::SetupUsbPacket * setup_packet = (Usb_Setup::SetupUsbPacket *) (*usb_setup.usb_instance).Setup;

	switch (setup_packet->bRequest) {
		case Usb_Setup::SET_ADDRESS: {
			if (HAL_PCD_SetAddress(usb_setup.usb_instance, setup_packet->wValue) != HAL_OK){
				fprintf(stderr, "Cannot Setup Device Address\n");
				break;
			}
			fprintf(stdout, "Device Address Setup\n");
			break;
		}
		case Usb_Setup::SET_INTERFACE:{
			if (setup_packet->wValue == Usb_Setup::SineWave){
				SineWaveInit();
				fprintf(stdout, "Switiching to Sine Wave Mode\n");
				usb_setup.isSquareWave = false;
			}
			else{
				SquareWaveInit();
				fprintf(stdout, "Switching to Square Wave Mode\n");
				usb_setup.isSquareWave = true;
			}
			break;
		}
		case Usb_Setup::GET_INTERFACE:{
			uint8_t currentMode = (uint8_t) usb_setup.isSquareWave;
			if (HAL_PCD_EP_Transmit(usb_setup.usb_instance, Usb_Com::OUTDEFAULT + 1, &currentMode , 1) != HAL_OK){
				fprintf(stderr, "Cannot Send Device Configuration");
				break;
			}
			fprintf(stdout, "Device Configuration Sent\n");
			break;
		}
		case Usb_Setup::GET_DESCRIPTOR: {
			uint8_t * usb_descriptor_bytes = (uint8_t *)&usb_descriptor;
			if (HAL_PCD_EP_Transmit(usb_setup.usb_instance, Usb_Com::OUTDEFAULT + 1, usb_descriptor_bytes, usb_descriptor.bLength) != HAL_OK){
				fprintf(stderr, "Cannot Send Device Descriptor");
				break;
			}
			fprintf(stdout, "Device Descriptor Sent\n");
			break;
		}
		default:
			break;
	}
}

void Usb_Transmitted(PCD_HandleTypeDef *hpcd, uint8_t epnum){
	usb.Transmitted = true;
}

void Usb_Received(PCD_HandleTypeDef *hpcd, uint8_t epnum){
	usb.Received = true;
}

void ProcessEndOfSample(ADC_HandleTypeDef * hadc){

}

void SquareWaveInit(){
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = ADC1_IN3_Pin | ADC2_IN3_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(ADC1_IN3_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = ADC3_IN1_Pin | ADC4_IN5_Pin;
	HAL_GPIO_Init(ADC3_IN1_GPIO_Port, &GPIO_InitStruct);
}

void SineWaveInit(){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = ADC1_IN3_Pin | ADC2_IN3_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = ADC3_IN1_Pin | ADC4_IN5_Pin;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void CheckSquareVal(TIM_HandleTypeDef * htim2){
//	fprintf(stdout, "CV\n");
	GPIO_PinState PinState = HAL_GPIO_ReadPin(ADC1_IN3_GPIO_Port, ADC1_IN3_Pin);
	if (PinState == GPIO_PIN_SET){
		fprintf(stdout, "1\n");
		UartTransmitBuffer[bytePointer] |= 0x1 << bitPointer;
	}
	else{
		fprintf(stdout, "0\n");
		UartTransmitBuffer[bytePointer] &= ~(0x1 << bitPointer);
	}

	bitPointer += 1;

	//ADC1
	if ((bytePointer == 63) && (bitPointer == 7)){ //Sampling last bit of the packet
		bytePointer = 0; //Reset bit and byte pointer
		bitPointer = 0;

//		HAL_UART_Transmit(&huart5, UartTransmitBuffer, 64, 0);
		fprintf(stdout, "Data Transmitted\n");
	}
	else if (bitPointer == 7){ //Sampling last bit of each byte
		bytePointer += 1;
		bitPointer = 0;
	}
	//ADC2
	//ADC3
	//ADC4
}

void CheckSineVal(TIM_HandleTypeDef * htim2){
	fprintf(stdout, "CAV");
}

extern "C" void run(){
//USB Config
//	fprintf(stdout, "Started Usb Config\n");
//	uint8_t tracked_ep = 1;
//
//	if (usb.Usb_Init() != HAL_OK){
//		fprintf(stderr, "Cannot Initialize USB Components\n");
//		return;
//	}
//	fprintf(stdout, "USB Components Initialized\n");
//
//	(*usb_setup.usb_instance).SetupStageCallback = ProcessSetup;
//	(*usb.usb_instance).DataInStageCallback = Usb_Received;
//	(*usb.usb_instance).DataOutStageCallback = Usb_Transmitted;
//
//	if (usb.OpenEndpoint(tracked_ep) != HAL_OK){
//		fprintf(stderr, "Cannot Open Endpoint %d\n", tracked_ep);
//		return;
//	}
//	fprintf(stdout, "Endpoint %d Opened\n", tracked_ep);
//	fprintf(stdout, "Usb Config Finished\n");

//ADC Config
	fprintf(stdout, "Started ADC Config\n");
	SquareWaveInit();
	hadc1.EndOfSamplingCallback = ProcessEndOfSample;
	if (HAL_ADC_Start(&hadc1) != HAL_OK){
		fprintf(stdout, "Failed to Config ADC\n");
		return;
	}
	fprintf(stdout, "ADC Config Finished\n");

//Timer Config
	fprintf(stdout, "Started Timer Config\n");
	if (isSquareMode){
		htim2.PeriodElapsedCallback = CheckSquareVal;
	}
	else{
		htim2.PeriodElapsedCallback = CheckSineVal;
	}
//	if (HAL_TIM_Base_Start_IT(&htim2) != HAL_OK){     //Issue Enable it using HAL
//		fprintf(stdout, "Failed to config Timer\n");
//		return;
//	}

	//Manually Enable TIM2 Interrupt
	htim2.Instance->DIER = TIM_DIER_UIE;
	htim2.Instance->CR1 = TIM_CR1_CEN;

	fprintf(stdout, "Timer Config Finished\n");

	while (1){
		__WFI();
	}
}
