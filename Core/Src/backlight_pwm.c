#include "backlight_pwm.h"

/**
  * @brief  Initializes and starts the backlight PWM.
  * @param  htim: pointer to a TIM_HandleTypeDef structure that contains
  * the configuration information for TIM1.
  * @retval None
  */
void backlight_init(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM1)
  {
    // Start PWM on TIM1 Channel 1
    HAL_TIM_PWM_Start(htim, TIM_CHANNEL_1);
  }
}

/**
  * @brief  Sets the brightness of the LCD backlight.
  * @param  htim: pointer to a TIM_HandleTypeDef structure that contains
  * the configuration information for TIM1.
  * @param  percentage: Brightness level from 0 (off) to 100 (full brightness).
  * @retval None
  */
void backlight_set_brightness(TIM_HandleTypeDef *htim, uint8_t percentage)
{
  if (htim->Instance == TIM1)
  {
    uint32_t pulse_value = 0;
    uint32_t period_value = __HAL_TIM_GET_AUTORELOAD(htim); // Get the Period (ARR value)

    if (percentage > 100)
    {
      percentage = 100;
    }

    // Calculate pulse value based on percentage of the period
    // Note: period_value is ARR, so for 100% duty cycle, CCR should be ARR+1 if period is ARR.
    // However, it's common to set CCR from 0 to ARR.
    // If period is 65535, then pulse = (65535 * percentage) / 100
    pulse_value = (period_value * percentage) / 100;

    __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, pulse_value);
  }
}
