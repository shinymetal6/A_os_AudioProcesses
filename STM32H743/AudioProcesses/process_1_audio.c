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

#include "A_os_includes.h"
#include "A_os_AudioInclude.h"

//#define	LOOPBACK_TEST
#define	OSCILLATORS_TEST

#ifdef	OSCILLATORS_TEST
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
#endif

int16_t	audio_in_buf[AUDIO_BUF_SIZE*2],audio_out_buf[AUDIO_BUF_SIZE*2];
extern	void Iir_S_configure(uint8_t Type, uint16_t Frequency, float iir_Q);

#ifdef	OSCILLATORS_TEST

uint8_t	state = 0;
void do_err()
{
	__disable_irq();
	while(1);
}

void process_1_audio(uint32_t process_id)
{
uint32_t	wakeup,flags;
uint16_t	freq=90;

uint16_t	iir_freq=100;
uint8_t		type=BIQUAD_HIGH_PASS;
float		iirQ=0.6f;
float		resonance=2.5f;

uint8_t		volume=100;

	if ( allocate_hw(HW_I2C1,HWMAN_STD_IRQ) == HW_I2C1 )
		Nau88c22_Init();

	InitEffectsSequencer();

	InitOscillators();
	SetGeneratorMode();

	PassThrough_init();
	PassThrough_enable();

	Iir_init(type, iir_freq, iirQ);
	Iir_enable();

	Vca_init(volume);
	Vca_enable();

	InsertBlockEffect(Do_PassThrough,0,EFFECT_ENABLED);
	InsertBlockEffect(Do_iir,1,EFFECT_ENABLED);
	InsertBlockEffect(Do_PassThrough,2,EFFECT_ENABLED);
	InsertBlockEffect(Do_Vca,3,EFFECT_ENABLED);

	StartAudioBuffers(audio_in_buf,audio_out_buf);

	EnableOscillator(0,freq,0);

	create_timer(TIMER_ID_0,300,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);

	while(1)
	{
		wait_event(EVENT_TIMER);
		get_wakeup_flags(&wakeup,&flags);
		if ( wakeup == 0 )
			do_err();
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
			/*
			DisableOscillator(0,freq,0);
			freq++;
			if ( freq > 100 )
				freq = 10;
			EnableOscillator(0,freq,0);
			*/
			iir_freq += 100;
			if ( iir_freq > 4000 )
			{
				iir_freq = 100;
			}
			Iir_configure(type, iir_freq, iirQ);
			if ( volume == 100 )
				volume /= 2;
			else
				volume = 100;

			Vca_setMasterVolume(volume);

			/*
			if ( state == 0 )
				EnableOscillator(0,freq,0);
			else
				DisableOscillator(0,freq,0);
			state++;
			state &= 1;
			*/
		}
	}
}
#endif
#ifdef	LOOPBACK_TEST

int16_t	audio_in_buf[AUDIO_BUF_SIZE*2],audio_out_buf[AUDIO_BUF_SIZE*2];

void process_1_audio(uint32_t process_id)
{
	uint32_t	wakeup,flags;

	SetEffectMode();
	SetMasterVolume(75);
	iir_set_params(1,1000,0.7F);
	StartAudioBuffers(audio_in_buf,audio_out_buf);
	create_timer(TIMER_ID_0,200,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED );
	while(1)
	{
		wait_event(EVENT_TIMER | EVENT_EXT_INT_IRQ);
		get_wakeup_flags(&wakeup,&flags);

		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
		}
	}
}
#endif
