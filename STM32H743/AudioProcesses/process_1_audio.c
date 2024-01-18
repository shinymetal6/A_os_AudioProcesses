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
 * process_1_audio.c
 *
 *  Created on: Jan 3, 2024
 *      Author: fil
 */
#include "main.h"

#include "../../../A_os/modules/audio/oscillator_core.h"
#include "../../../A_os/modules/audio/oscillators.h"
#include "A_os_includes.h"

void ena_osc(void)
{
	EnableOscillator(0,69,0);
	EnableOscillator(0,70,0);
	EnableOscillator(0,71,0);
	EnableOscillator(0,72,0);
	EnableOscillator(0,73,0);
	EnableOscillator(0,74,0);
	EnableOscillator(0,75,0);
	EnableOscillator(0,76,0);
	EnableOscillator(0,77,0);
	EnableOscillator(0,78,0);
	EnableOscillator(0,79,0);
	EnableOscillator(0,80,0);
	EnableOscillator(0,81,0);
	EnableOscillator(0,82,0);
	EnableOscillator(0,83,0);
	EnableOscillator(0,84,0);
}
void dis_osc(void)
{
	DisableOscillator(0,69,0);
	DisableOscillator(0,70,0);
	DisableOscillator(0,71,0);
	DisableOscillator(0,72,0);
	DisableOscillator(0,73,0);
	DisableOscillator(0,74,0);
	DisableOscillator(0,75,0);
	DisableOscillator(0,76,0);
	DisableOscillator(0,77,0);
	DisableOscillator(0,78,0);
	DisableOscillator(0,79,0);
	DisableOscillator(0,80,0);
	DisableOscillator(0,81,0);
	DisableOscillator(0,82,0);
	DisableOscillator(0,83,0);
	DisableOscillator(0,84,0);
}
void process_1_audio(uint32_t process_id)
{
uint32_t	wakeup;
uint8_t	dir = 1;
uint32_t	*audiobuf;

	audiobuf = InitOscillators();
	StartAudioBuffers(audiobuf);
	EnableOscillator(0,69,0);

	create_timer(TIMER_ID_0,100,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);

	while(1)
	{
		wakeup = wait_event(EVENT_TIMER);
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			if ( dir == 1 )
			{
				dir = 0;
				EnableOscillator(0,69,0);
				//ena_osc();
			}
			else
			{
				dir = 1;
				DisableOscillator(0,69,0);
				//dis_osc();
			}
		}
	}
}
