/*
 * usblib.hpp
 *
 *  Created on: Jul 29, 2025
 *      Author: Khoi Anh Nguyen
 */

#ifndef INC_USBLIB_HPP_
#define INC_USBLIB_HPP_

class Usb_Coms{
public:
//Declaration
	Usb_Coms(PCD_HandleTypeDef * hpcd_USB_FS) {usb_instance = hpcd_USB_FS;};

//Functions
	bool Usb_Init();
	bool Usb_Send();
	bool Usb_Recieve();

private:
//Variables
	PCD_HandleTypeDef * usb_instance;

};

#endif /* INC_USBLIB_HPP_ */
