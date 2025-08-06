/*
 * usbsetup.hpp
 *
 *  Created on: Aug 5, 2025
 *      Author: Admin
 */

#ifndef INC_USBSETUP_HPP_
#define INC_USBSETUP_HPP_
#include "stm32g4xx_hal.h"

class Usb_Setup{
public:
	Usb_Setup(PCD_HandleTypeDef * hpcd_USB_FS) {usb_instance = hpcd_USB_FS;}
	typedef enum {
		Standard = 0,
		Class = 1,
		Vendor = 2
	} RequestTypes;

	typedef enum{
		GET_STATUS = 0,
		CLEAR_FEATURE = 1,
		SET_FEATURE = 3,
		SET_ADDRESS = 5,
		GET_DESCRIPTOR = 6,
		SET_DESCRIPTOR = 7,
		GET_CONFIGURATION = 8,
		SET_CONFIGURATION = 9
	} DeviceRequest;

	typedef enum{
		GET_INTERFACE = 0xA,
		SET_INTERFACE = 0x11
	} InterfaceRequest;

	typedef enum{
		SYNCH_FRAME = 0x12
	} EndpointRequest;

	typedef struct{
		uint8_t Direction : 1;
		uint8_t Request_Type : 2;
		uint8_t Recipient : 5;
	} USBRequestType;

	typedef struct{
		uint8_t bLength = 18;
		uint8_t BDescriptorType = 0x01;
		uint16_t bcdUSB;
		uint8_t bDeviceClass;
		uint8_t bDeviceSubClass;
		uint8_t bDeviceProtocol;
		uint8_t bMaxPacketSize = 64;
		uint16_t idVendor;
		uint16_t idProduct;
		uint16_t bcdDevice;
		uint8_t iManufacturer;
		uint8_t iProduct;
		uint8_t iSerialNumber;
		uint8_t bNumConfigurations;
	} DeviceDescriptor;

	typedef struct{
		USBRequestType bmRequestType; 	//Direction, Type, Recipient
		uint8_t bRequest;      			//Specific Request
		uint16_t wValue;       			//Request-Specific parameter
		uint16_t wIndex;       			//Endpoint Index
		uint16_t wLength;      			//Number of bytes in Data Stage
	} SetupUsbPacket;

	PCD_HandleTypeDef * usb_instance;
};



#endif /* INC_USBSETUP_HPP_ */
