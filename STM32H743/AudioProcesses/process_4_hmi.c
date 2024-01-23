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

#ifdef SDCARD_ENABLED
#include "microsd_op.h"
#endif

MenuStruct_t	MenuStruct;
SDcard_t		SDcard;

extern	TIM_HandleTypeDef htim17;

extern	char 	SDPath[4];   /* SD logical drive path */
extern	FATFS 	SDFatFS;    /* File system object for SD logical drive */
extern	FIL 	SDFile;       /* File object for SD */

void encoder_button_irq_callback(void)
{
	MenuStruct.inputs |= ENCODER_BUTTON;
}

void encoder_clock_irq_callback(uint16_t GPIO_Pin)
{
	if ( (MenuStruct.inputs & ENCODER_CLK ) == 0 )
		MenuStruct.inputs = (HAL_GPIO_ReadPin(ENCODER1_DATA_GPIO_Port, ENCODER1_DATA_Pin)<<1 ) | ENCODER_CLK;
}


uint32_t	wk1err=0,splash_duration_timticks;

void process4_menus(void)
{
uint16_t	logo_brightness=FULL_BRIGHTNESS;

	switch(MenuStruct.menu_state)
	{
	case	MENU_SPLASH:
		if ( splash_duration_timticks > 0)
		{
			splash_duration_timticks--;
			LcdSetBrightness(logo_brightness);
		}
		else
		{

			LcdSetBrightness(ZERO_BRIGHTNESS);
			MenuStruct.menu_state = MENU_STATE_TOP;
			Menus_Init(ZERO_BRIGHTNESS);
			LcdSetBrightness(FULL_BRIGHTNESS);
			MenuStruct.inputs = 0;
			DoMenus();
		}
		break;
	default:
		if ( MenuStruct.inputs)
		{
			DoMenus();
		}
		break;
	}
}

uint8_t process4_sdcard(void)
{
uint8_t	ret_val = 1;
	if ( microsd_detect() )
	{
		if (( SDcard.card_status & CARD_MOUNTED) == CARD_MOUNTED )
			ret_val = 0;
		else
		{
			if(f_mount(&SDFatFS, (TCHAR const*)SDPath, 0) == FR_OK)
			{
				SDcard.card_status |= CARD_MOUNTED;
				ret_val = 0;
			}
		}
	}
	else
		SDcard.card_status &= ~( CARD_DETECTED | CARD_MOUNTED);
	return ret_val;
}

void process_4_hmi(void)
{
uint32_t	wakeup;

	allocate_hw(HW_EXT_INT,HWMAN_SINGLE_IRQ);
	allocate_hw(HW_ADC1,HWMAN_STD_IRQ);
	allocate_hw(HW_ADC2,HWMAN_STD_IRQ);
	allocate_hw(HW_SPI1,HWMAN_STD_IRQ);
	HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);
	IntAdc_Start();
	LcdInit();
	splash_duration_timticks = 5;
	Draw_Logo(logo);
	MenuStruct.menu_state = MENU_SPLASH;

	create_timer(TIMER_ID_0,200,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED );
	while(1)
	{
		wakeup = wait_event(EVENT_TIMER | EVENT_EXT_INT_IRQ);
		if ( wakeup == 0 )
			wk1err++;
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			process4_menus();
			process4_sdcard();
		}
	}
}
