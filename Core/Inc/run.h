/*
 * run.hpp
 *
 *  Created on: Jul 31, 2025
 *      Author: Admin
 */

#ifndef INC_RUN_H_
#define INC_RUN_H_

#ifdef __cplusplus
extern "C"{
#endif
#include "stm32g4xx_hal.h"
#include <stdbool.h>

#define ADC1_IN3_Pin GPIO_PIN_2
#define ADC1_IN3_GPIO_Port GPIOA
#define ADC2_IN3_Pin GPIO_PIN_6
#define ADC2_IN3_GPIO_Port GPIOA
#define ADC3_IN1_Pin GPIO_PIN_1
#define ADC3_IN1_GPIO_Port GPIOB
#define ADC4_IN5_Pin GPIO_PIN_15
#define ADC4_IN5_GPIO_Port GPIOB

void run();
void ProcessSetup(PCD_HandleTypeDef *hpcd);
void Usb_Transmitted(PCD_HandleTypeDef *hpcd, uint8_t epnum);
void Usb_Received(PCD_HandleTypeDef *hpcd, uint8_t epnum);
void SineWaveInit();
void SquareWaveInit();

#ifdef __cplusplus
}
#endif

#endif /* INC_RUN_H_ */
