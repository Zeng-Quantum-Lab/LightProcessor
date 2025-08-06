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
#include "usbsetup.hpp"
#include <stdio.h>


class Usb_Com{
public:
//Declaration
	Usb_Com(PCD_HandleTypeDef * hpcd_USB_FS) {usb_instance = hpcd_USB_FS;};

	typedef enum{
		OUT = 0x11,
		IN = 0x99,
		SOF = 0x55,
		SETUP = 0xDD,
		DATA0 = 0x33,
		DATA1 = 0xBB,
		DATA2 = 0x77,
		MDATA = 0xFF
	} PacketID;

	typedef struct{
		uint32_t Sync;
		uint8_t PID;
		unsigned int ADDR : 7;
		unsigned int ENDP : 4;
		unsigned int CRC_bits : 5;
		unsigned int EOP : 3;
	} TokenUsbPacket;

	typedef struct{
		uint32_t Sync;
		uint8_t PID;
		unsigned int ADDR : 7;
		unsigned int ENDP : 4;
		uint8_t Data[64];
		unsigned int  CRC_bits : 16;
		unsigned int EOP : 3;
	} DataUsbPacket;

	typedef struct{
		unsigned int Sync : 32;
		unsigned int PID : 8;
		unsigned int EOP : 3;
	} HandshakeUsbPacket;

	typedef struct{
		uint32_t Sync : 32;
		uint8_t PID = PacketID::SOF;
		unsigned int  CRC_bits : 16;
		unsigned int EOP : 3;
	} SOFUsbPacket;

//Variables
	constexpr static uint8_t INDEFAULT = 0x80;
	constexpr static uint8_t OUTDEFAULT = 0x00;
	uint8_t Receive_Buffer[64];
	uint8_t Transmit_Buffer[64];
	bool Transmitted = false;
	bool Received = false;
	PCD_HandleTypeDef * usb_instance;
//Functions
	HAL_StatusTypeDef Usb_Init();
	HAL_StatusTypeDef OpenEndpoint(uint8_t ep_num);
private:

//Functions



};




#endif /* INC_USBLIB_HPP_ */
