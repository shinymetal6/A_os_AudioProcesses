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

uint32_t	activation_flag,wk1err=0,tim0=0,tim1=0;
void process_4(void)
{
uint32_t	wakeup;

	create_timer(TIMER_ID_0,50,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED );
	create_timer(TIMER_ID_1,200,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED );
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);

	while(1)
	{
		wakeup = wait_event(EVENT_TIMER);
		if ( wakeup == 0 )
			wk1err++;
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			activation_flag = get_activation_flags();
			if ((activation_flag & TIMER_ID_0) == TIMER_ID_0)
			{
				tim0++;
			}
			if ((activation_flag & TIMER_ID_1) == TIMER_ID_1)
			{
				tim1++;
			}
		}
	}
}
