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
#include "menus.h"

extern	MenuStruct_t	MenuStruct;

extern	TIM_HandleTypeDef htim17;
uint8_t	valenc[256] , validx=0;

uint16_t	counterhi=0,counterlo=0;
void encoder_debouncer(void)
{
	MenuStruct.inputs |= ENCODER_BUTTON;
}

void encoder_clock_irq_callback(uint16_t GPIO_Pin)
{
	if ( GPIO_Pin == ENCODER1_PHASE_Pin )
	{
		if ( (MenuStruct.inputs & ENCODER_CLK ) == 0 )
		{
			HAL_NVIC_DisableIRQ(EXTI0_IRQn);
			MenuStruct.inputs |= ENCODER_CLK;
			MenuStruct.inputs |= HAL_GPIO_ReadPin(ENCODER1_DATA_GPIO_Port, ENCODER1_DATA_Pin)<<1;
		}
	}
}

uint32_t	activation_flag,wk1err=0,tim0=0,tim1=0;
void process_4_hmi(void)
{
uint32_t	wakeup;
uint32_t	flags_from_tim = 0;
uint16_t	logo_brightness=ZERO_BRIGHTNESS;
	allocate_hw(HW_EXT_INT,HWMAN_SINGLE_IRQ);
	allocate_hw(HW_ADC1,HWMAN_STD_IRQ);
	allocate_hw(HW_ADC2,HWMAN_STD_IRQ);
	allocate_hw(HW_SPI1,HWMAN_STD_IRQ);
	HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);
	IntAdc_Start();
	LcdInit();
	Draw_Logo(logo);
	MenuStruct.menu_state = MENU_SPLASH;

	create_timer(TIMER_ID_0,50,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED );
	create_timer(TIMER_ID_1,200,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED );
	while(1)
	{
		wakeup = wait_event(EVENT_TIMER | EVENT_EXT_INT_IRQ);
		if ( wakeup == 0 )
			wk1err++;
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			activation_flag = get_activation_flags();
			if ((activation_flag & TIMER_ID_0) == TIMER_ID_0)
			{
				switch(MenuStruct.menu_state)
				{
				case	MENU_SPLASH:
					if ( logo_brightness < FULL_BRIGHTNESS )
					{
						logo_brightness +=20;
						LcdSetBrightness(logo_brightness);
					}
					else
					{
						MenuStruct.menu_state = MENU_STATE_TOP;
						Menus_Init(FULL_BRIGHTNESS);
						DoMenus(MENU_DRAW_ONLY);
					}
					break;
				case	MENU_STATE_TOP:
					break;
				}
			}
			if ((activation_flag & TIMER_ID_1) == TIMER_ID_1)
			{
				if ( flags_from_tim)
					DoMenus(flags_from_tim);
				flags_from_tim = 0;
				MenuStruct.inputs = 0;
				HAL_NVIC_EnableIRQ(EXTI0_IRQn);
			}
		}
		if (( wakeup & WAKEUP_FROM_EXT_INT_IRQ) == WAKEUP_FROM_EXT_INT_IRQ)
			flags_from_tim = get_activation_flags();
	}


}
