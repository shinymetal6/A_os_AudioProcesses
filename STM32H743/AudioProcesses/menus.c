/*
 * menus.c
 *
 *  Created on: Jul 16, 2021
 *      Author: fil
 */


#include "main.h"
#include "A_os_includes.h"
#include "A_os_AudioInclude.h"
#include "menus.h"
MenuStruct_t	MenuStruct;
uint16_t		line_ptr = 0;
__attribute__((section(".table"))) static const ScreenTypeDef	Main_Menu_Screen[] = {
		{
				"bB101",
				MENU_X_TITLE,
				MENU_Y_TITLE,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"OSCs",
				LINE1_X,
				LINE1_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"AFX",
				LINE2_X,
				LINE2_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Delay",
				LINE3_X,
				LINE3_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"System",
				LINE4_X,
				LINE4_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				" ",
		},
};

__attribute__((section(".table"))) static const ScreenTypeDef	Osc_Menu_Screen[] = {
		{
				"OSCs",
				MENU_X_TITLE,
				MENU_Y_TITLE,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Wave",
				LINE1_X,
				LINE1_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Duty",
				LINE2_X,
				LINE2_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"deTune",
				LINE3_X,
				LINE3_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Volume",
				LINE4_X,
				LINE4_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"ADSR",
				LINE5_X,
				LINE5_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Return",
				LINE6_X,
				LINE6_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				" ",
		},
};
__attribute__((section(".table"))) static const ScreenTypeDef	Osc_WaveMenu_Screen[] = {
		{
				"Waves",
				MENU_X_TITLE,
				MENU_Y_TITLE,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Wave 1",
				LINE1_X,
				LINE1_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Wave 2",
				LINE2_X,
				LINE2_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Wave 3",
				LINE3_X,
				LINE3_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Wave 4",
				LINE4_X,
				LINE4_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Return",
				LINE5_X,
				LINE5_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				" ",
		},
};
__attribute__((section(".table"))) static const ScreenTypeDef	Osc_DutyMenu_Screen[] = {
		{
				"Duty",
				MENU_X_TITLE,
				MENU_Y_TITLE,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Duty 1",
				LINE1_X,
				LINE1_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Duty 2",
				LINE2_X,
				LINE2_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Duty 3",
				LINE3_X,
				LINE3_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Duty 4",
				LINE4_X,
				LINE4_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Return",
				LINE5_X,
				LINE5_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				" ",
		},
};

__attribute__((section(".table"))) static const ScreenTypeDef	Osc_DeTuneMenu_Screen[] = {
		{
				"dTune",
				MENU_X_TITLE,
				MENU_Y_TITLE,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"deTune 1",
				LINE1_X,
				LINE1_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"deTune 2",
				LINE2_X,
				LINE2_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"deTune 3",
				LINE3_X,
				LINE3_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"deTune 4",
				LINE4_X,
				LINE4_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Return",
				LINE5_X,
				LINE5_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				" ",
		},
};

__attribute__((section(".table"))) static const ScreenTypeDef	Osc_VolumeMenu_Screen[] = {
		{
				"Vol",
				MENU_X_TITLE,
				MENU_Y_TITLE,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Volume 1",
				LINE1_X,
				LINE1_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Volume 2",
				LINE2_X,
				LINE2_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Volume 3",
				LINE3_X,
				LINE3_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Volume 4",
				LINE4_X,
				LINE4_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Return",
				LINE5_X,
				LINE5_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				" ",
		},
};

__attribute__((section(".table"))) static const ScreenTypeDef	Osc_ADSRMenu_Screen[] = {
		{
				"ADSR",
				MENU_X_TITLE,
				MENU_Y_TITLE,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"A Time",
				LINE1_X,
				LINE1_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"D Time",
				LINE2_X,
				LINE2_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"S Val",
				LINE3_X,
				LINE3_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"R Time",
				LINE4_X,
				LINE4_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Return",
				LINE5_X,
				LINE5_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				" ",
		},
};

__attribute__((section(".table"))) static const ScreenTypeDef	AFX_Menu_Screen[] = {
		{
				"AFX",
				MENU_X_TITLE,
				MENU_Y_TITLE,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Type",
				LINE1_X,
				LINE1_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Band",
				LINE2_X,
				LINE2_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Control",
				LINE3_X,
				LINE3_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Enable",
				LINE4_X,
				LINE4_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Return",
				LINE5_X,
				LINE5_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				" ",
		},
};


__attribute__((section(".table"))) static const ScreenTypeDef	Delay_Menu_Screen[] = {
		{
				"Delay",
				MENU_X_TITLE,
				MENU_Y_TITLE,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Increment",
				LINE1_X,
				LINE1_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Decrement",
				LINE2_X,
				LINE2_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Type",
				LINE3_X,
				LINE3_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Enable",
				LINE4_X,
				LINE4_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Return",
				LINE5_X,
				LINE5_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				" ",
		},
};

__attribute__((section(".table"))) static const ScreenTypeDef	System_Menu_Screen[] = {
		{
				"Sys",
				MENU_X_TITLE,
				MENU_Y_TITLE,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Input",
				LINE1_X,
				LINE1_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"VCA",
				LINE2_X,
				LINE2_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"FM",
				LINE3_X,
				LINE3_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Seq",
				LINE4_X,
				LINE4_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Memory",
				LINE5_X,
				LINE5_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Return",
				LINE6_X,
				LINE6_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				" ",
		},
};

__attribute__((section(".table"))) static const ScreenTypeDef	System_PGM_Menu_Screen[] = {
		{
				"Mem",
				MENU_X_TITLE,
				MENU_Y_TITLE,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"PGM num",
				LINE1_X,
				LINE1_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"LOAD",
				LINE3_X,
				LINE3_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"STORE",
				LINE4_X,
				LINE4_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				"Return",
				LINE5_X,
				LINE5_Y,
				ST7735_BLUE,
				ST7735_BLACK
		},
		{
				" ",
		},
};
#ifdef NOTYET
void Menus_Hilight_Line(ScreenTypeDef *screen, uint16_t old_line_number, uint16_t new_line_number)
{
	ST7735_WriteString(screen[old_line_number].x,screen[old_line_number].y,screen[old_line_number].line, Font_7x10, screen[old_line_number].fcolor, screen[old_line_number].bcolor);
	ST7735_WriteString(screen[new_line_number].x,screen[new_line_number].y,screen[new_line_number].line, Font_7x10, ST7735_BLACK, ST7735_BLACK);
	ST7735_WriteString(screen[new_line_number].x,screen[new_line_number].y,screen[new_line_number].line, Font_7x10, screen[new_line_number].bcolor, screen[new_line_number].fcolor);
}


void Osc_Menu(void)
{
	ST7735_FillScreen(ST7735_BLACK);
	Draw_Menu((ScreenTypeDef *)&Osc_Menu_Screen);
}

void Osc_WaveMenu(void)
{
	ST7735_FillScreen(ST7735_BLACK);
	Draw_Menu((ScreenTypeDef *)&Osc_WaveMenu_Screen);
}

void Delay_Menu(void)
{
	ST7735_FillScreen(ST7735_BLACK);
	Draw_Menu((ScreenTypeDef *)&Delay_Menu_Screen);
}

void move_menu(ScreenTypeDef *screen, uint16_t old_line_number, uint16_t new_line_number, uint16_t max_line_number)
{
	if (( MenuStruct.buttons_flag & BUTTON_TACT0) == BUTTON_TACT0)
	{
		if ( MenuStruct.menu_line_counter == 1 )
			MenuStruct.menu_line_counter = max_line_number;
		else
			MenuStruct.menu_line_counter --;
		MenuStruct.buttons_flag &= ~BUTTON_TACT0;
	}
	if (( MenuStruct.buttons_flag & BUTTON_TACT1) == BUTTON_TACT1)
	{
		if ( MenuStruct.menu_line_counter >= max_line_number )
			MenuStruct.menu_line_counter = 1;
		else
			MenuStruct.menu_line_counter ++;
		MenuStruct.buttons_flag &= ~BUTTON_TACT1;
	}
	Menus_Hilight_Line(screen,old_line_number,MenuStruct.menu_line_counter);
}

void change_menu(ScreenTypeDef *new_screen,ScreenTypeDef *old_screen)
{
#ifdef	SLOW_FILL
	ST7735_FillScreen(ST7735_BLACK);
#else
uint8_t	i=0;
	MenuStruct.menu_line_counter = 1;
	while(old_screen[i].line[0] != 0x20 )
	{
		ST7735_WriteString(old_screen[i].x,old_screen[i].y,old_screen[i].line, Font_7x10, ST7735_BLACK, ST7735_BLACK);
		i++;
	}
#endif
	Draw_Menu(new_screen);
}

void Draw_Waveform(uint8_t oscillator_offset,uint8_t waveform)
{
	switch (waveform)
	{
	case	SQUARE		:	ST7735_DrawImage(LINE_X_OSC1W+oscillator_offset*16,LINE_Y_OSCW+1, 14, 14, sqrw); break;
	case	TRIANGLE	:	ST7735_DrawImage(LINE_X_OSC1W+oscillator_offset*16,LINE_Y_OSCW+1, 14, 14, tria); break;
	case	NOISE		:	ST7735_DrawImage(LINE_X_OSC1W+oscillator_offset*16,LINE_Y_OSCW+1, 14, 14, noise); break;
	default				:	ST7735_DrawImage(LINE_X_OSC1W+oscillator_offset*16,LINE_Y_OSCW+1, 14, 14, sine); break; // 's' case
	}
}

uint8_t change_oscillator_waveform(uint8_t oscillator_offset )
{
uint8_t	i;

	MenuStruct.osc_waves[oscillator_offset]++;
	if ( MenuStruct.osc_waves[oscillator_offset] > NOISE)
		MenuStruct.osc_waves[oscillator_offset] = SINE;

	for(i=0;i<NUMOSCILLATORS;i+=VOICES)
	{
		Oscillator[i+oscillator_offset].waveform = MenuStruct.osc_waves[oscillator_offset];
	}
	Draw_Waveform(oscillator_offset , MenuStruct.osc_waves[oscillator_offset] );
	return Oscillator[oscillator_offset].waveform;
}

void DisplayDuty(void)
{
uint8_t	i,k;
char 	tmp_buf[16];
	DisplayClearADSR();
	k = LINE_X_DUTY;
	ST7735_WriteString(k,LINE_Y_TDUTY,"Duty", Font_7x10, ST7735_DARKGREEN, ST7735_BLACK);
	for(i=0;i<4;i++)
	{
		sprintf(tmp_buf,"%d",MenuStruct.osc_duty_percent[i]);
		ST7735_WriteString(k,LINE_Y_DUTY,"  ", Font_7x10, ST7735_DARKGREEN, ST7735_BLACK);
		ST7735_WriteString(k,LINE_Y_DUTY,tmp_buf, Font_7x10, ST7735_DARKGREEN, ST7735_BLACK);
		k += LINE_X_DUTY_DELTA;
	}
}

void DisplayDetune(void)
{
uint8_t	i,k;
char 	tmp_buf[16];
	DisplayClearADSR();
	k = LINE_X_DETUNE;
	ST7735_WriteString(k,LINE_Y_TDETUNE,"Detune", Font_7x10, ST7735_DARKGREEN, ST7735_BLACK);
	for(i=0;i<4;i++)
	{
		sprintf(tmp_buf,"%d",MenuStruct.osc_detune[i]);
		ST7735_WriteString(k,LINE_Y_DETUNE,"  ", Font_7x10, ST7735_DARKGREEN, ST7735_BLACK);
		ST7735_WriteString(k,LINE_Y_DETUNE,tmp_buf, Font_7x10, ST7735_DARKGREEN, ST7735_BLACK);
		k += LINE_X_DETUNE_DELTA;
	}
}

void DisplayVolume(void)
{
uint8_t	i,k;
char 	tmp_buf[16];
	DisplayClearADSR();
	k = LINE_X_VOLUME;
	ST7735_WriteString(k,LINE_Y_TVOLUME,"Volume", Font_7x10, ST7735_DARKGREEN, ST7735_BLACK);
	for(i=0;i<4;i++)
	{
		sprintf(tmp_buf,"%d",MenuStruct.osc_volume[i]);
		ST7735_WriteString(k,LINE_Y_VOLUME,"  ", Font_7x10, ST7735_DARKGREEN, ST7735_BLACK);
		ST7735_WriteString(k,LINE_Y_VOLUME,tmp_buf, Font_7x10, ST7735_DARKGREEN, ST7735_BLACK);
		k += LINE_X_DETUNE_DELTA;
	}
}

uint8_t ChangeOscillatorVolume(uint8_t oscillator_offset )
{
uint8_t	i;

	if ( MenuStruct.osc_volume[oscillator_offset] > 10 )
		MenuStruct.osc_volume[oscillator_offset] = 10;

	for(i=0;i<NUMOSCILLATORS;i+=VOICES)
	{
		Oscillator[i+oscillator_offset].volume = (float )MenuStruct.osc_volume[oscillator_offset] / 10.0F;
	}
	return 0;
}

uint8_t ChangeOscillatorDuty(uint8_t oscillator_offset , uint8_t duty)
{
uint8_t	i;
uint32_t	calc_duty;
	if ( duty > 99 )
		duty = 99;

	calc_duty = (uint32_t )((float )duty*DUTY_SCALE);
	for(i=0;i<NUMOSCILLATORS;i+=VOICES)
	{
		Oscillator[i+oscillator_offset].duty = (uint8_t )calc_duty;
		ChangeOscillatorWavePhase(i+oscillator_offset,Oscillator[i+oscillator_offset].waveform , Oscillator[i+oscillator_offset].duty );
	}
	return 0;
}

uint8_t ChangeOscillatorDetune(uint8_t oscillator_offset )
{
uint8_t	i;

	for(i=0;i<NUMOSCILLATORS;i+=VOICES)
	{
		if ( MenuStruct.osc_detune[oscillator_offset] < 50 )
		{
			Oscillator[i+oscillator_offset].detune = (50.0F - (float )MenuStruct.osc_detune[oscillator_offset]) / 10.0F;
		}
		else
		{
			Oscillator[i+oscillator_offset].detune = ((float )MenuStruct.osc_detune[oscillator_offset] - 50.0F) / 10.0F;
		}
		MenuStruct.oscillator_flags |= OSC_TUNE_PENDING;
	}
	return 0;
}

void View_Sequence(void)
{
	ST7735_WriteString(LINE_X_SEQUENCE,LINE_Y_SEQUENCE,"O", Font_7x10, ST7735_DARKGREEN, ST7735_BLACK);
	if (( MenuStruct.control_flags & CONTROL_OSC_VCF_DLY) == CONTROL_OSC_VCF_DLY)
	{
		if (( MenuStruct.afx_flags & AFX_ENABLED) == AFX_ENABLED)
			ST7735_WriteString(LINE_X_SEQUENCE+7,LINE_Y_SEQUENCE,"X", Font_7x10, ST7735_DARKGREEN, ST7735_BLACK);
		else
			ST7735_WriteString(LINE_X_SEQUENCE+7,LINE_Y_SEQUENCE,"X", Font_7x10, ST7735_GREY, ST7735_BLACK);

		if (( MenuStruct.delay_flags & DLY_ENABLED) == DLY_ENABLED)
			ST7735_WriteString(LINE_X_SEQUENCE+14,LINE_Y_SEQUENCE,"D", Font_7x10, ST7735_DARKGREEN, ST7735_BLACK);
		else
			ST7735_WriteString(LINE_X_SEQUENCE+14,LINE_Y_SEQUENCE,"D", Font_7x10, ST7735_GREY, ST7735_BLACK);
	}
	else
	{
		if (( MenuStruct.delay_flags & DLY_ENABLED) == DLY_ENABLED)
			ST7735_WriteString(LINE_X_SEQUENCE+7,LINE_Y_SEQUENCE,"D", Font_7x10, ST7735_DARKGREEN, ST7735_BLACK);
		else
			ST7735_WriteString(LINE_X_SEQUENCE+7,LINE_Y_SEQUENCE,"D", Font_7x10, ST7735_GREY, ST7735_BLACK);
		if (( MenuStruct.afx_flags & AFX_ENABLED) == AFX_ENABLED)
			ST7735_WriteString(LINE_X_SEQUENCE+14,LINE_Y_SEQUENCE,"X", Font_7x10, ST7735_DARKGREEN, ST7735_BLACK);
		else
			ST7735_WriteString(LINE_X_SEQUENCE+14,LINE_Y_SEQUENCE,"X", Font_7x10, ST7735_GREY, ST7735_BLACK);
	}
}

void View_Delay(void)
{
uint16_t	color;

	if (( MenuStruct.delay_flags & DLY_ENABLED) == DLY_ENABLED)
		color = ST7735_DARKGREEN;
	else
		color = ST7735_GREY;
	switch(MenuStruct.delay_flags & DLY_TYPE_MASK )
	{
	case	DLY_MIXER_FLANGER_POT :
		ST7735_WriteString(LINE_X_DELAYTYPE, LINE_Y_DELAYTYPE, "FP", Font_7x10, color, ST7735_BLACK);
		break;
	case	DLY_MIXER_REVERB_POT :
		ST7735_WriteString(LINE_X_DELAYTYPE, LINE_Y_DELAYTYPE, "RP", Font_7x10, color, ST7735_BLACK);
		break;
	case	DLY_MIXER_FLANGER_MIDI :
		ST7735_WriteString(LINE_X_DELAYTYPE, LINE_Y_DELAYTYPE, "FM", Font_7x10, color, ST7735_BLACK);
		break;
	case	DLY_MIXER_REVERB_MIDI :
		ST7735_WriteString(LINE_X_DELAYTYPE, LINE_Y_DELAYTYPE, "RM", Font_7x10, color, ST7735_BLACK);
		break;
	default :
		ST7735_WriteString(LINE_X_DELAYTYPE, LINE_Y_DELAYTYPE, "FP", Font_7x10, color, ST7735_BLACK);
		break;
	}
}

void View_Delay_Val(void)
{
uint16_t	color = ST7735_GREY;
char 	tmp_buf[16];
uint16_t	delay;

	if (( MenuStruct.delay_flags & DLY_MIXER_POT_MASK) == 0 )	// comes from prog
		delay = MenuStruct.delay_value_from_prog;
	else
		delay = MenuStruct.delay_value_from_midi;


	if ( delay < 10 )
		sprintf(tmp_buf,"  %d",delay);
	else if ( delay < 100 )
		sprintf(tmp_buf," %d",delay);
	else
		sprintf(tmp_buf,"%d",delay);
	if (( MenuStruct.delay_flags & DLY_ENABLED) == DLY_ENABLED)
		color = ST7735_DARKGREEN;
	ST7735_WriteString(LINE_X_DELAY,LINE_Y_DELAY,tmp_buf, Font_7x10, color, ST7735_BLACK);
}

void view_am(void)
{
uint16_t	color;

	if (( MenuStruct.control_flags & CONTROL_VCA) == CONTROL_VCA)
		color = ST7735_DARKGREEN;
	else
		color = ST7735_GREY;
	ST7735_WriteString(LINE_X_INPUT+14,LINE_Y_INPUT,"a", Font_7x10, color, ST7735_BLACK);
}

void view_fm(void)
{
uint16_t	color;

	if (( MenuStruct.control_flags & CONTROL_FM) == CONTROL_FM)
		color = ST7735_DARKGREEN;
	else
		color = ST7735_GREY;
	ST7735_WriteString(LINE_X_INPUT+21,LINE_Y_INPUT,"f", Font_7x10, color, ST7735_BLACK);
}


void Draw_AFX_Params(void)
{
uint16_t	color = ST7735_GREY;
	if (( MenuStruct.afx_flags & AFX_ENABLED) == AFX_ENABLED)
		color = ST7735_DARKGREEN;

	if (( MenuStruct.afx_flags & AFX_CONTROL_BP ) == AFX_CONTROL_BP)
		ST7735_WriteString(LINE_X_FILTER,LINE_Y_FILTER,"BP", Font_7x10, color, ST7735_BLACK);
	if (( MenuStruct.afx_flags & AFX_CONTROL_HP ) == AFX_CONTROL_HP)
		ST7735_WriteString(LINE_X_FILTER,LINE_Y_FILTER,"HP", Font_7x10, color, ST7735_BLACK);
	if (( MenuStruct.afx_flags & AFX_CONTROL_LP ) == AFX_CONTROL_LP)
		ST7735_WriteString(LINE_X_FILTER,LINE_Y_FILTER,"LP", Font_7x10, color, ST7735_BLACK);
	if (( MenuStruct.afx_flags & AFX_CONTROL_MIDI ) == AFX_CONTROL_MIDI)
		ST7735_WriteString(LINE_X_CONTROL,LINE_Y_CONTROL,"MIDI", Font_7x10, color, ST7735_BLACK);
	if (( MenuStruct.afx_flags & AFX_CONTROL_CV ) == AFX_CONTROL_CV)
		ST7735_WriteString(LINE_X_CONTROL,LINE_Y_CONTROL,"CV  ", Font_7x10, color, ST7735_BLACK);
	if (( MenuStruct.afx_flags & AFX_CONTROL_POT ) == AFX_CONTROL_POT)
		ST7735_WriteString(LINE_X_CONTROL,LINE_Y_CONTROL,"POT ", Font_7x10, color, ST7735_BLACK);
}

void Draw_Effects(void)
{
uint16_t	color = ST7735_GREY;
	if (( MenuStruct.afx_flags & AFX_ENABLED) == AFX_ENABLED)
		color = ST7735_DARKGREEN;

	if (( MenuStruct.afxtype_flags & AFXTYPE_MOOG1) == AFXTYPE_MOOG1)
		ST7735_WriteString(LINE_X_STATUS,LINE_Y_FILTER,"Moog1", Font_7x10, color, ST7735_BLACK);
	if (( MenuStruct.afxtype_flags & AFXTYPE_MOOG2) == AFXTYPE_MOOG2)
		ST7735_WriteString(LINE_X_STATUS,LINE_Y_FILTER,"Moog2", Font_7x10, color, ST7735_BLACK);
	if (( MenuStruct.afxtype_flags & AFXTYPE_PHASER) == AFXTYPE_PHASER)
		ST7735_WriteString(LINE_X_STATUS,LINE_Y_FILTER,"Phsr ", Font_7x10, color, ST7735_BLACK);
}

void DoMenus(void)
{
uint16_t	old_line_number;
ScreenTypeDef	*current_screen;

	switch ( MenuStruct.menu_state)
	{
	case	MENU_STATE_TOP:
		current_screen = (ScreenTypeDef *)&Main_Menu_Screen;
		if ((( MenuStruct.buttons_flag & BUTTON_TACT0) == BUTTON_TACT0) || (( MenuStruct.buttons_flag & BUTTON_TACT1) == BUTTON_TACT1))
		{
			old_line_number = MenuStruct.menu_line_counter;
			move_menu(current_screen,old_line_number,MenuStruct.menu_line_counter,MENU_MAX_TOP_LINE);
		}
		if (( MenuStruct.buttons_flag & BUTTON_TACT2) == BUTTON_TACT2)
		{
			if ( MenuStruct.menu_line_counter == 1)
			{
				MenuStruct.menu_state = MENU_STATE_OSC_TOP;
				change_menu((ScreenTypeDef *)&Osc_Menu_Screen,current_screen);
			}
			if ( MenuStruct.menu_line_counter == 2)
			{
				MenuStruct.menu_state = MENU_STATE_AFX;
				change_menu((ScreenTypeDef *)&AFX_Menu_Screen,current_screen);
			}
			if ( MenuStruct.menu_line_counter == 3)
			{
				MenuStruct.menu_state = MENU_STATE_DELAY;
				change_menu((ScreenTypeDef *)&Delay_Menu_Screen,current_screen);
			}
			if ( MenuStruct.menu_line_counter == MENU_MAX_TOP_LINE)
			{
				MenuStruct.menu_state = MENU_STATE_SYSTEM;
				change_menu((ScreenTypeDef *)&System_Menu_Screen,current_screen);
			}
		}
		break;
	case	MENU_STATE_OSC_TOP:
		current_screen = (ScreenTypeDef *)&Osc_Menu_Screen;
		if ((( MenuStruct.buttons_flag & BUTTON_TACT0) == BUTTON_TACT0) || (( MenuStruct.buttons_flag & BUTTON_TACT1) == BUTTON_TACT1))
		{
			old_line_number = MenuStruct.menu_line_counter;
			move_menu(current_screen,old_line_number,MenuStruct.menu_line_counter,MENU_MAX_OSC_LINE);
		}
		if (( MenuStruct.buttons_flag & BUTTON_TACT2) == BUTTON_TACT2)
		{
			if ( MenuStruct.menu_line_counter == MENU_MAX_OSC_LINE)
			{
				MenuStruct.menu_state = MENU_STATE_TOP;
				change_menu((ScreenTypeDef *)&Main_Menu_Screen,current_screen);
			}
			else
			{
				if ( MenuStruct.menu_line_counter == 1)
				{
					MenuStruct.menu_state = MENU_STATE_OSC_WAVE;
					change_menu((ScreenTypeDef *)&Osc_WaveMenu_Screen,current_screen);
				}
				if ( MenuStruct.menu_line_counter == 2)
				{
					MenuStruct.menu_state = MENU_STATE_OSC_DUTY;
					change_menu((ScreenTypeDef *)&Osc_DutyMenu_Screen,current_screen);
					DisplayDuty();
				}
				if ( MenuStruct.menu_line_counter == 3)
				{
					MenuStruct.menu_state = MENU_STATE_OSC_DETUNE;
					change_menu((ScreenTypeDef *)&Osc_DeTuneMenu_Screen,current_screen);
					DisplayDetune();
				}
				if ( MenuStruct.menu_line_counter == 4)
				{
					MenuStruct.menu_state = MENU_STATE_OSC_VOLUME;
					change_menu((ScreenTypeDef *)&Osc_VolumeMenu_Screen,current_screen);
					DisplayVolume();
				}
				if ( MenuStruct.menu_line_counter == 5)
				{
					MenuStruct.menu_state = MENU_STATE_ADSR;
					change_menu((ScreenTypeDef *)&Osc_ADSRMenu_Screen,current_screen);
					DisplayADSR();
				}
			}
		}
		break;
	case	MENU_STATE_OSC_WAVE:
		current_screen = (ScreenTypeDef *)&Osc_WaveMenu_Screen;
		if ((( MenuStruct.buttons_flag & BUTTON_TACT0) == BUTTON_TACT0) || (( MenuStruct.buttons_flag & BUTTON_TACT1) == BUTTON_TACT1))
		{
			old_line_number = MenuStruct.menu_line_counter;
			move_menu(current_screen,old_line_number,MenuStruct.menu_line_counter,MENU_MAX_OSC_WAVE_LINE);
			MenuStruct.buttons_flag &= ~( BUTTON_TACT0 | BUTTON_TACT1);
		}
		if (( MenuStruct.buttons_flag & BUTTON_TACT2) == BUTTON_TACT2)
		{
			if ( MenuStruct.menu_line_counter == MENU_MAX_OSC_WAVE_LINE)
			{
				MenuStruct.menu_state = MENU_STATE_OSC_TOP;
				change_menu((ScreenTypeDef *)&Osc_Menu_Screen,current_screen);
			}
			else
				change_oscillator_waveform(MenuStruct.menu_line_counter-1);
		}
		break;
	case	MENU_STATE_OSC_DUTY:
		current_screen = (ScreenTypeDef *)&Osc_DutyMenu_Screen;
		if ((( MenuStruct.buttons_flag & BUTTON_TACT0) == BUTTON_TACT0) || (( MenuStruct.buttons_flag & BUTTON_TACT1) == BUTTON_TACT1))
		{
			old_line_number = MenuStruct.menu_line_counter;
			move_menu(current_screen,old_line_number,MenuStruct.menu_line_counter,MENU_MAX_OSC_DUTY_LINE);
			MenuStruct.buttons_flag &= ~( BUTTON_TACT0 | BUTTON_TACT1);
		}
		if (( MenuStruct.buttons_flag & BUTTON_TACT2) == BUTTON_TACT2)
		{
			if ( MenuStruct.menu_line_counter == MENU_MAX_OSC_DUTY_LINE)
			{
				MenuStruct.menu_state = MENU_STATE_OSC_TOP;
				change_menu((ScreenTypeDef *)&Osc_Menu_Screen,current_screen);
				DisplayADSR();
			}
			else
			{
				if ( MenuStruct.osc_duty_percent[MenuStruct.menu_line_counter-1] < 95 )
					MenuStruct.osc_duty_percent[MenuStruct.menu_line_counter-1] += 5;
				else
					MenuStruct.osc_duty_percent[MenuStruct.menu_line_counter-1] = 5;

				ChangeOscillatorDuty(MenuStruct.menu_line_counter-1 , MenuStruct.osc_duty_percent[MenuStruct.menu_line_counter]);
				DisplayDuty();
			}
		}
		break;
	case	MENU_STATE_OSC_DETUNE:
		current_screen = (ScreenTypeDef *)&Osc_DeTuneMenu_Screen;
		if ((( MenuStruct.buttons_flag & BUTTON_TACT0) == BUTTON_TACT0) || (( MenuStruct.buttons_flag & BUTTON_TACT1) == BUTTON_TACT1))
		{
			old_line_number = MenuStruct.menu_line_counter;
			move_menu(current_screen,old_line_number,MenuStruct.menu_line_counter,MENU_MAX_OSC_DETUNE_LINE);
			MenuStruct.buttons_flag &= ~( BUTTON_TACT0 | BUTTON_TACT1);
		}
		if (( MenuStruct.buttons_flag & BUTTON_TACT2) == BUTTON_TACT2)
		{
			if ( MenuStruct.menu_line_counter == MENU_MAX_OSC_DETUNE_LINE)
			{
				MenuStruct.menu_state = MENU_STATE_OSC_TOP;
				change_menu((ScreenTypeDef *)&Osc_Menu_Screen,current_screen);
				DisplayADSR();
			}
			else
			{
				if ( MenuStruct.osc_detune[MenuStruct.menu_line_counter-1] < 99 )
					MenuStruct.osc_detune[MenuStruct.menu_line_counter-1] += 1;
				else
					MenuStruct.osc_detune[MenuStruct.menu_line_counter-1] = 0;
				ChangeOscillatorDetune(MenuStruct.menu_line_counter-1);
				DisplayDetune();
			}
		}
		break;
	case	MENU_STATE_OSC_VOLUME:
		current_screen = (ScreenTypeDef *)&Osc_VolumeMenu_Screen;
		if ((( MenuStruct.buttons_flag & BUTTON_TACT0) == BUTTON_TACT0) || (( MenuStruct.buttons_flag & BUTTON_TACT1) == BUTTON_TACT1))
		{
			old_line_number = MenuStruct.menu_line_counter;
			move_menu(current_screen,old_line_number,MenuStruct.menu_line_counter,MENU_MAX_OSC_VOLUME_LINE);
			MenuStruct.buttons_flag &= ~( BUTTON_TACT0 | BUTTON_TACT1);
		}
		if (( MenuStruct.buttons_flag & BUTTON_TACT2) == BUTTON_TACT2)
		{
			if ( MenuStruct.menu_line_counter == MENU_MAX_OSC_VOLUME_LINE)
			{
				MenuStruct.menu_state = MENU_STATE_OSC_TOP;
				change_menu((ScreenTypeDef *)&Osc_Menu_Screen,current_screen);
				DisplayADSR();
			}
			else
			{
				if ( MenuStruct.osc_volume[MenuStruct.menu_line_counter-1] < 10 )
					MenuStruct.osc_volume[MenuStruct.menu_line_counter-1] += 1;
				else
					MenuStruct.osc_volume[MenuStruct.menu_line_counter-1] = 0;
				ChangeOscillatorVolume(MenuStruct.menu_line_counter-1);
				DisplayVolume();
			}
		}
		break;
	case	MENU_STATE_ADSR:
		current_screen = (ScreenTypeDef *)&Osc_ADSRMenu_Screen;
		if ((( MenuStruct.buttons_flag & BUTTON_TACT0) == BUTTON_TACT0) || (( MenuStruct.buttons_flag & BUTTON_TACT1) == BUTTON_TACT1))
		{
			old_line_number = MenuStruct.menu_line_counter;
			move_menu(current_screen,old_line_number,MenuStruct.menu_line_counter,MENU_MAX_OSC_ADSR_LINE);
			MenuStruct.buttons_flag &= ~( BUTTON_TACT0 | BUTTON_TACT1);
		}
		if (( MenuStruct.buttons_flag & BUTTON_TACT2) == BUTTON_TACT2)
		{
			if ( MenuStruct.menu_line_counter == MENU_MAX_OSC_ADSR_LINE)
			{
				MenuStruct.menu_state = MENU_STATE_OSC_TOP;
				change_menu((ScreenTypeDef *)&Osc_Menu_Screen,current_screen);
			}
			else
			{
				if ( MenuStruct.menu_line_counter == 1)
				{
					if ( MenuStruct.Atime < MenuStruct.Dtime )
						MenuStruct.Atime++;
					else
						MenuStruct.Atime=1;
					DisplayADSR();
				}
				if ( MenuStruct.menu_line_counter == 2)
				{
					if ( MenuStruct.Dtime < MenuStruct.Rtime )
						MenuStruct.Dtime++;
					else
						MenuStruct.Dtime=MenuStruct.Atime;
					DisplayADSR();
				}
				if ( MenuStruct.menu_line_counter == 3)
				{
					MenuStruct.Sval--;
					if ( MenuStruct.Sval == 0 )
						MenuStruct.Sval= ADSR_H;
					DisplayADSR();
				}
				if ( MenuStruct.menu_line_counter == 4)
				{
					if ( MenuStruct.Rtime < ADSR_W )
						MenuStruct.Rtime++;
					else
						MenuStruct.Rtime=MenuStruct.Dtime;
					DisplayADSR();
				}
			}
		}
		break;

	case	MENU_STATE_AFX:
		current_screen = (ScreenTypeDef *)&AFX_Menu_Screen;
		if ((( MenuStruct.buttons_flag & BUTTON_TACT0) == BUTTON_TACT0) || (( MenuStruct.buttons_flag & BUTTON_TACT1) == BUTTON_TACT1))
		{
			old_line_number = MenuStruct.menu_line_counter;
			move_menu(current_screen,old_line_number,MenuStruct.menu_line_counter,MENU_MAX_EFF_LINE);
		}
		if (( MenuStruct.buttons_flag & BUTTON_TACT2) == BUTTON_TACT2)
		{
			if ( MenuStruct.menu_line_counter == 1) // band
			{
				if (( MenuStruct.afxtype_flags & AFXTYPE_MOOG1) == AFXTYPE_MOOG1)
				{
					MenuStruct.afxtype_flags &= ~AFXTYPE_MOOG1;
					MenuStruct.afxtype_flags |= AFXTYPE_MOOG2;
				}
				else if (( MenuStruct.afxtype_flags & AFXTYPE_MOOG2) == AFXTYPE_MOOG2)
				{
					MenuStruct.afxtype_flags &= ~AFXTYPE_MOOG2;
					MenuStruct.afxtype_flags |= AFXTYPE_PHASER;
				}
				else if (( MenuStruct.afxtype_flags & AFXTYPE_PHASER) == AFXTYPE_PHASER)
				{
					MenuStruct.afxtype_flags &= ~AFXTYPE_PHASER;
					MenuStruct.afxtype_flags |= AFXTYPE_MOOG1;
				}
				Draw_Effects();
				Clear_AFX_data();
			}

			if ( MenuStruct.menu_line_counter == 2) // band
			{
				switch ( MenuStruct.afx_flags & AFX_TYPE_MASK)
				{
				case	AFX_CONTROL_LP :
					MenuStruct.afx_flags &= ~AFX_TYPE_MASK;
					MenuStruct.afx_flags |= AFX_CONTROL_BP;
					break;
				case	AFX_CONTROL_BP :
					MenuStruct.afx_flags &= ~AFX_TYPE_MASK;
					MenuStruct.afx_flags |= AFX_CONTROL_HP;
					break;
				case	AFX_CONTROL_HP :
					MenuStruct.afx_flags &= ~AFX_TYPE_MASK;
					MenuStruct.afx_flags |= AFX_CONTROL_LP;
					break;
				default :
					MenuStruct.afx_flags &= ~AFX_TYPE_MASK;
					MenuStruct.afx_flags |= AFX_CONTROL_LP;
					break;
				}
				Draw_AFX_Params();
			}
			if ( MenuStruct.menu_line_counter == 3) // control
			{
				switch ( MenuStruct.afx_flags & AFX_CONTROL_MASK)
				{
				case	AFX_CONTROL_POT :
					MenuStruct.afx_flags &= ~AFX_CONTROL_MASK;
					MenuStruct.afx_flags |= AFX_CONTROL_MIDI;
					break;
				case	AFX_CONTROL_MIDI :
					MenuStruct.afx_flags &= ~AFX_CONTROL_MASK;
					MenuStruct.afx_flags |= AFX_CONTROL_CV;
					break;
				case	AFX_CONTROL_CV :
					MenuStruct.afx_flags &= ~AFX_CONTROL_MASK;
					MenuStruct.afx_flags |= AFX_CONTROL_POT;
					break;
				default :
					MenuStruct.afx_flags &= ~AFX_CONTROL_MASK;
					MenuStruct.afx_flags |= AFX_CONTROL_MIDI;
					break;
				}
				Draw_AFX_Params();
			}
			if ( MenuStruct.menu_line_counter == 4) // enable
			{
				if (( MenuStruct.afx_flags & AFX_ENABLED) == AFX_ENABLED)
				{
					MenuStruct.afx_flags &= ~AFX_ENABLED;
				}
				else
				{
					MenuStruct.afx_flags |= AFX_ENABLED;
				}
				Draw_AFX_Params();
				Draw_Effects();
				View_Sequence();
			}
			if ( MenuStruct.menu_line_counter == MENU_MAX_EFF_LINE)
			{
				MenuStruct.menu_state = MENU_STATE_TOP;
				change_menu((ScreenTypeDef *)&Main_Menu_Screen,current_screen);
			}
		}
		break;


	case	MENU_STATE_DELAY:
		current_screen = (ScreenTypeDef *)&Delay_Menu_Screen;
		if ((( MenuStruct.buttons_flag & BUTTON_TACT0) == BUTTON_TACT0) || (( MenuStruct.buttons_flag & BUTTON_TACT1) == BUTTON_TACT1))
		{
			old_line_number = MenuStruct.menu_line_counter;
			move_menu(current_screen,old_line_number,MenuStruct.menu_line_counter,MENU_MAX_DLY_LINE);
		}
		if (( MenuStruct.buttons_flag & BUTTON_TACT2) == BUTTON_TACT2)
		{
			if ( MenuStruct.menu_line_counter == 1)
			{
				if (MenuStruct.delay_value_from_prog < DELAY_MAX_VALUE )
					MenuStruct.delay_value_from_prog += DELAY_DELTA_VALUE;
				View_Delay_Val();
			}
			if ( MenuStruct.menu_line_counter == 2)
			{
				if (MenuStruct.delay_value_from_prog != 0 )
					MenuStruct.delay_value_from_prog -= DELAY_DELTA_VALUE;
				View_Delay_Val();
			}
			if ( MenuStruct.menu_line_counter == 3)
			{
				switch(MenuStruct.delay_flags & DLY_TYPE_MASK )
				{
				case	DLY_MIXER_FLANGER_POT :
					MenuStruct.delay_flags &= ~DLY_TYPE_MASK;
					MenuStruct.delay_flags |= DLY_MIXER_REVERB_POT;
					break;
				case	DLY_MIXER_REVERB_POT :
					MenuStruct.delay_flags &= ~DLY_TYPE_MASK;
					MenuStruct.delay_flags |= DLY_MIXER_FLANGER_MIDI;
					break;
				case	DLY_MIXER_FLANGER_MIDI :
					MenuStruct.delay_flags &= ~DLY_TYPE_MASK;
					MenuStruct.delay_flags |= DLY_MIXER_REVERB_MIDI;
					break;
				case	DLY_MIXER_REVERB_MIDI :
					MenuStruct.delay_flags &= ~DLY_TYPE_MASK;
					MenuStruct.delay_flags |= DLY_MIXER_FLANGER_POT;
					break;
				default :
					MenuStruct.delay_flags &= ~DLY_TYPE_MASK;
					MenuStruct.delay_flags |= DLY_MIXER_FLANGER_POT;
					break;
				}
				View_Delay();
				View_Delay_Val();
			}
			if ( MenuStruct.menu_line_counter == 4)
			{
				if (( MenuStruct.delay_flags & DLY_ENABLED) == DLY_ENABLED)
					MenuStruct.delay_flags &= ~DLY_ENABLED;
				else
					MenuStruct.delay_flags |= DLY_ENABLED;
				View_Delay();
				View_Sequence();
			}
			if ( MenuStruct.menu_line_counter == MENU_MAX_DLY_LINE)
			{
				MenuStruct.menu_state = MENU_STATE_TOP;
				change_menu((ScreenTypeDef *)&Main_Menu_Screen,current_screen);
			}
		}
		break;
	case	MENU_STATE_SYSTEM:
		current_screen = (ScreenTypeDef *)&System_Menu_Screen;
		if ((( MenuStruct.buttons_flag & BUTTON_TACT0) == BUTTON_TACT0) || (( MenuStruct.buttons_flag & BUTTON_TACT1) == BUTTON_TACT1))
		{
			old_line_number = MenuStruct.menu_line_counter;
			move_menu(current_screen,old_line_number,MenuStruct.menu_line_counter,MENU_MAX_SYSTEM_LINE);
		}
		if (( MenuStruct.buttons_flag & BUTTON_TACT2) == BUTTON_TACT2)
		{
			if ( MenuStruct.menu_line_counter == 1)
			{
				if (( MenuStruct.oscillator_flags & OSC_SRCFLAG) == OSC_SRCFLAG)
				{
					MenuStruct.oscillator_flags &= ~OSC_SRCFLAG;
					ST7735_WriteString(LINE_X_INPUT_MIDI, LINE_Y_INPUT, "CV  ", Font_7x10, ST7735_DARKGREEN, ST7735_BLACK);
				}
				else
				{
					MenuStruct.oscillator_flags |= OSC_SRCFLAG;
					ST7735_WriteString(LINE_X_INPUT_MIDI, LINE_Y_INPUT, "MIDI", Font_7x10, ST7735_DARKGREEN, ST7735_BLACK);
				}
			}
			if ( MenuStruct.menu_line_counter == 2)
			{
				if (( MenuStruct.control_flags & CONTROL_VCA) == CONTROL_VCA)
					MenuStruct.control_flags &= ~CONTROL_VCA;
				else
					MenuStruct.control_flags |= CONTROL_VCA;
				view_am();
			}
			if ( MenuStruct.menu_line_counter == 3)
			{
				if (( MenuStruct.control_flags & CONTROL_FM) == CONTROL_FM)
					MenuStruct.control_flags &= ~CONTROL_FM;
				else
					MenuStruct.control_flags |= CONTROL_FM;
				view_fm();
			}

			if ( MenuStruct.menu_line_counter == 4)
			{
				if (( MenuStruct.control_flags & CONTROL_OSC_VCF_DLY) == CONTROL_OSC_VCF_DLY)
				{
					MenuStruct.control_flags &= ~CONTROL_OSC_VCF_DLY;
				}
				else
				{
					MenuStruct.control_flags |= CONTROL_OSC_VCF_DLY;
				}
				View_Sequence();
			}
			if ( MenuStruct.menu_line_counter == 5)
			{
				MenuStruct.menu_state = MENU_STATE_PGM;
				MenuStruct.program_number = 0;
				change_menu((ScreenTypeDef *)&System_PGM_Menu_Screen,current_screen);
				char tmp_buf[4];
				sprintf(tmp_buf,"%d",MenuStruct.program_number);
				ST7735_WriteString(LINE2_X+4, LINE2_Y, tmp_buf, Font_7x10, ST7735_DARKGREEN, ST7735_BLACK);
			}
			if ( MenuStruct.menu_line_counter == MENU_MAX_SYSTEM_LINE)
			{
				MenuStruct.menu_state = MENU_STATE_TOP;
				change_menu((ScreenTypeDef *)&Main_Menu_Screen,current_screen);
			}
		}
		break;
	case	MENU_STATE_PGM:
		current_screen = (ScreenTypeDef *)&System_PGM_Menu_Screen;
		if ((( MenuStruct.buttons_flag & BUTTON_TACT0) == BUTTON_TACT0) || (( MenuStruct.buttons_flag & BUTTON_TACT1) == BUTTON_TACT1))
		{
			old_line_number = MenuStruct.menu_line_counter;
			move_menu(current_screen,old_line_number,MenuStruct.menu_line_counter,MENU_MAX_PGM_LINE);
		}
		if (( MenuStruct.buttons_flag & BUTTON_TACT2) == BUTTON_TACT2)
		{
			if ( MenuStruct.menu_line_counter == 1)
			{
				MenuStruct.program_number++;
				MenuStruct.program_number &= (NUM_PROGRAMS_MAX-1);
				char tmp_buf[4];
				sprintf(tmp_buf,"%d",MenuStruct.program_number);
				ST7735_WriteString(LINE2_X+4, LINE2_Y, tmp_buf, Font_7x10, ST7735_DARKGREEN, ST7735_BLACK);
			}
			if ( MenuStruct.menu_line_counter == 2)
			{
				if ( ee24_load_program(MenuStruct.program_number) != 0)
					ST7735_WriteString(LINE2_X, LINE2_Y, "FAIL", Font_7x10, ST7735_RED, ST7735_BLACK);
				else
				{
					MenuStruct.menu_state = MENU_STATE_SYSTEM;
					MenusDrawStatus();
					Draw_Waveform(0 , MenuStruct.osc_waves[0] );
					Draw_Waveform(1 , MenuStruct.osc_waves[1] );
					Draw_Waveform(2 , MenuStruct.osc_waves[2] );
					Draw_Waveform(3 , MenuStruct.osc_waves[3] );
					View_Sequence();
					MenuStruct.menu_state = MENU_STATE_TOP;
					change_menu((ScreenTypeDef *)&Main_Menu_Screen,current_screen);
				}
			}
			if ( MenuStruct.menu_line_counter == 3)
			{
				ee24_store_program(MenuStruct.program_number);
				MenuStruct.menu_state = MENU_STATE_TOP;
				change_menu((ScreenTypeDef *)&Main_Menu_Screen,current_screen);
			}

			if ( MenuStruct.menu_line_counter == MENU_MAX_PGM_LINE)
			{
				MenuStruct.menu_state = MENU_STATE_SYSTEM;
				change_menu((ScreenTypeDef *)&System_Menu_Screen,current_screen);
			}
		}
		break;
		/*
	case	MENU_STATE_STOREPGM:
		current_screen = (ScreenTypeDef *)&System_StorePGM_Menu_Screen;
		if ((( MenuStruct.buttons_flag & BUTTON_TACT0) == BUTTON_TACT0) || (( MenuStruct.buttons_flag & BUTTON_TACT1) == BUTTON_TACT1))
		{
			old_line_number = MenuStruct.menu_line_counter;
			move_menu(current_screen,old_line_number,MenuStruct.menu_line_counter,MENU_MAX_STOREPGM_LINE);
		}
		if (( MenuStruct.buttons_flag & BUTTON_TACT2) == BUTTON_TACT2)
		{
			if ( MenuStruct.menu_line_counter == 1)
			{
				MenuStruct.program_number++;
				MenuStruct.program_number &= (NUM_PROGRAMS_MAX-1);
				char tmp_buf[4];
				sprintf(tmp_buf,"%d",MenuStruct.program_number);
				ST7735_WriteString(LINE2_X+4, LINE2_Y, tmp_buf, Font_7x10, ST7735_DARKGREEN, ST7735_BLACK);
			}
			if ( MenuStruct.menu_line_counter == 2)
			{
				ee24_store_program(MenuStruct.program_number);
				MenuStruct.menu_state = MENU_STATE_SYSTEM;
				change_menu((ScreenTypeDef *)&System_Menu_Screen,current_screen);
			}
			if ( MenuStruct.menu_line_counter == MENU_MAX_STOREPGM_LINE)
			{
				MenuStruct.menu_state = MENU_STATE_SYSTEM;
				change_menu((ScreenTypeDef *)&System_Menu_Screen,current_screen);
			}
		}
		break;
		*/
	}
	MenuStruct.buttons_flag &= ~(BUTTON_TACT0 | BUTTON_TACT1 | BUTTON_TACT2);

}

void bB101_Print_Tuner(void)
{
char 	tmp_buf[5];
int		value;
	value = (int ) ((TUNER_CONTROL  - 2048 )/ 20);
	if ( value > 98 )
		value = 98;
	if ( value < -98 )
		value = -98;
	sprintf(tmp_buf,"%d%% ",value);
	ST7735_WriteString(LINE_X_TUNER, LINE_Y_TUNER, tmp_buf, Font_7x10, ST7735_DARKGREEN, ST7735_BLACK);
}

void MenusDrawEmptyStatus(void)
{
uint8_t	i;

	for(i=0;i<4;i++)
		Draw_Waveform(i,MenuStruct.osc_waves[i]);
	ST7735_WriteString(LINE_X_FILTER,LINE_Y_FILTER,"LP", Font_7x10, ST7735_DARKGREEN, ST7735_BLACK);
	if (( MenuStruct.oscillator_flags & OSC_SRCFLAG) == OSC_SRCFLAG)
	{
		ST7735_WriteString(LINE_X_INPUT_MIDI, LINE_Y_INPUT, "MIDI", Font_7x10, ST7735_DARKGREEN, ST7735_BLACK);
	}

	View_Sequence();
	View_Delay();
	View_Delay_Val();
	Draw_AFX_Params();
	Draw_Effects();
	view_am();
	view_fm();
}

void MenusDrawStatus(void)
{
	bB101_Print_Tuner();
}
#endif // #ifdef NOTYET

void Menus_Hilight_Line(ScreenTypeDef *screen, uint16_t old_line_number, uint16_t new_line_number)
{
	ST7735_WriteString(screen[old_line_number].x,screen[old_line_number].y,screen[old_line_number].line, Font_7x10, screen[old_line_number].fcolor, screen[old_line_number].bcolor);
	ST7735_WriteString(screen[new_line_number].x,screen[new_line_number].y,screen[new_line_number].line, Font_7x10, ST7735_BLACK, ST7735_BLACK);
	ST7735_WriteString(screen[new_line_number].x,screen[new_line_number].y,screen[new_line_number].line, Font_7x10, screen[new_line_number].bcolor, screen[new_line_number].fcolor);
}

void move_menu(ScreenTypeDef *screen, uint16_t old_line_number, uint16_t new_line_number, uint16_t max_line_number)
{
	if ((MenuStruct.inputs & ENCODER_DATA)== ENCODER_DATA)
	{
		if ( MenuStruct.menu_line_counter == 1 )
			MenuStruct.menu_line_counter = max_line_number;
		else
			MenuStruct.menu_line_counter --;
	}
	else
	{
		if ( MenuStruct.menu_line_counter >= max_line_number )
			MenuStruct.menu_line_counter = 1;
		else
			MenuStruct.menu_line_counter ++;
	}
	Menus_Hilight_Line(screen,old_line_number,MenuStruct.menu_line_counter);
}

void DoMenus(uint32_t event)
{
uint16_t	old_line_number;
ScreenTypeDef	*current_screen;

	switch ( MenuStruct.menu_state)
	{
	case	MENU_STATE_TOP:
		current_screen = (ScreenTypeDef *)&Main_Menu_Screen;
		if ( (event & ENCODER_CLK) == ENCODER_CLK )
		{
			MenuStruct.inputs = event;
			old_line_number = MenuStruct.menu_line_counter;
			move_menu(current_screen,old_line_number,MenuStruct.menu_line_counter,MENU_MAX_TOP_LINE);
		}
		break;
	}

	//HAL_Delay(100);
	//enable_exti(0);
}

void Draw_Menu(ScreenTypeDef *screen)
{
uint8_t	i=0;
	while(screen[i].line[0] != 0x20 )
	{
		if (( screen == Main_Menu_Screen ) && (i == 0 ))
		{
			ST7735_WriteString(screen[i].x,   screen[i].y,MenuStruct.Header,  Font_7x10, ST7735_BLUE, ST7735_BLACK);
			ST7735_WriteString(screen[i].x+(strlen(MenuStruct.Header)*7)+6,screen[i].y,MenuStruct.Version, Font_7x10, ST7735_BLUE, ST7735_BLACK);
		}
		if ( i == 1 )
		{
			MenuStruct.menu_line_counter = 1;
			ST7735_WriteString(screen[i].x,screen[i].y,screen[i].line, Font_7x10, ST7735_BLACK, ST7735_BLUE);
		}
		else
			ST7735_WriteString(screen[i].x,screen[i].y,screen[i].line, Font_7x10, ST7735_BLUE, ST7735_BLACK);
		i++;
	}
}

void Main_Menu(void)
{
	ST7735_FillScreen(ST7735_BLACK);
	Draw_Menu((ScreenTypeDef *)&Main_Menu_Screen);
}

void Menus_Init(uint16_t brightness)
{
	LcdSetBrightness(ZERO_BRIGHTNESS);
	LcdClearScreen();
	MenuStruct.current_brightness = brightness;
	MenuStruct.menu_line_counter = 0;
	sprintf(MenuStruct.Header,MACHINE_NAME);
	sprintf(MenuStruct.Version,MACHINE_VERSION);
	Main_Menu();
	LcdSetBrightness(brightness);
}

