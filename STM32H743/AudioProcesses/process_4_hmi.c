/* 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Project : bb1xx_743_00 
*/
/*
 * process_4_hmi.c
 *
 *  Created on: Jan 3, 2024
 *      Author: fil
 */

#include "main.h"
#include "A_os_includes.h"
#include "A_os_AudioInclude.h"

uint8_t	button=0,clock=0;
extern	uint16_t logo[];
extern	TIM_HandleTypeDef htim17;

void encoder_button_irq_callback(void)
{
	button++;
}

void encoder_clock_irq_callback(void)
{
	clock++;
}

void process_4_hmi(uint32_t process_id)
{
	/*
	while(1)
	{
		task_delay(200);
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

	}
	*/
/**/
	uint32_t	wakeup;
	uint8_t		led_cntr=0;
	uint16_t	logo_brightness=ZERO_BRIGHTNESS;

	HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);
	IntAdc_Start();
	LcdInit();
	Draw_Logo(logo);
	create_timer(TIMER_ID_0,50,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED );
	while(1)
	{
		wakeup = wait_event(EVENT_TIMER);
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			if ( logo_brightness < FULL_BRIGHTNESS )
			{
				logo_brightness +=20;
				LcdSetBrightness(logo_brightness);
			}


			led_cntr++;
			if ( led_cntr == 20)
			{
				//HAL_GPIO_WritePin(LED_1_GPIOPORT, LED_1_GPIOBIT,GPIO_PIN_RESET);
				led_cntr = 0;
			}
			/*
			else
				HAL_GPIO_WritePin(LED_1_GPIOPORT, LED_1_GPIOBIT,GPIO_PIN_SET);
				*/
		}
	}
	/**/
}
