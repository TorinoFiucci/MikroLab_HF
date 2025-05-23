#ifndef __BACKLIGHT_PWM_H
#define __BACKLIGHT_PWM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f0xx_hal.h"

/**
  * @brief  Initializes and starts the backlight PWM.
  * @param  htim: pointer to a TIM_HandleTypeDef structure that contains
  * the configuration information for TIM1.
  * @retval None
  */
void backlight_init(TIM_HandleTypeDef *htim);

/**
  * @brief  Sets the brightness of the LCD backlight.
  * @param  htim: pointer to a TIM_HandleTypeDef structure that contains
  * the configuration information for TIM1.
  * @param  percentage: Brightness level from 0 (off) to 100 (full brightness).
  * @retval None
  */
void backlight_set_brightness(TIM_HandleTypeDef *htim, uint8_t percentage);

#ifdef __cplusplus
}
#endif

#endif /* __BACKLIGHT_PWM_H */
