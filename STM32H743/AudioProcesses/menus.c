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

static ScreenTypeDef	Main_Menu_Screen[] = {
		{
				" ",
				ST7735_BLUE,
				ST7735_BLACK,
		},
		{
				"OSCs",
				ST7735_GREEN,
				ST7735_BLACK,
		},
		{
				"Delay",
				ST7735_GREEN,
				ST7735_BLACK,
		},
		{
				"System",
				ST7735_GREEN,
				ST7735_BLACK,
		},
		{
				" ",
		},
};

//#define	USED_FONT			Font_11x18
#define	USED_FONT			Font_7x11
#define	MACHINE_FONT		Font_7x11


void Menus_Hilight_Line(ScreenTypeDef *screen, uint16_t old_line_number, uint16_t new_line_number)
{
	ST7735_WriteString(screen[old_line_number].x,screen[old_line_number].y,screen[old_line_number].line, USED_FONT, screen[old_line_number].fcolor, screen[old_line_number].bcolor);
	ST7735_WriteString(screen[new_line_number].x,screen[new_line_number].y,screen[new_line_number].line, USED_FONT, ST7735_BLACK, ST7735_BLACK);
	ST7735_WriteString(screen[new_line_number].x,screen[new_line_number].y,screen[new_line_number].line, USED_FONT, screen[new_line_number].bcolor, screen[new_line_number].fcolor);
}

void move_menu(ScreenTypeDef *screen, uint8_t direction)
{
	uint16_t old_line_number = MenuStruct.menu_line_counter;
	if (direction)
	{
		if ( MenuStruct.menu_line_counter == 1 )
			MenuStruct.menu_line_counter = MenuStruct.menu_max_numline;
		else
			MenuStruct.menu_line_counter --;
	}
	else
	{
		if ( MenuStruct.menu_line_counter >= MenuStruct.menu_max_numline )
			MenuStruct.menu_line_counter = 1;
		else
			MenuStruct.menu_line_counter ++;
	}
	Menus_Hilight_Line(screen,old_line_number,MenuStruct.menu_line_counter);
}


void DoMenus(uint32_t event)
{
ScreenTypeDef	*current_screen;

	switch ( MenuStruct.menu_state)
	{
	case	MENU_STATE_TOP:
		current_screen = (ScreenTypeDef *)&Main_Menu_Screen;
		if ( (event & ENCODER_CLK) == ENCODER_CLK )
		{
			MenuStruct.inputs = event;
			move_menu(current_screen,(MenuStruct.inputs & ENCODER_DATA));
		}
		break;
	}
}

void Draw_Menu(ScreenTypeDef *screen)
{
uint8_t		i=0;
uint16_t	xcentered=0;

	xcentered = (ST7735_WIDTH - strlen(screen[0].line) * MACHINE_FONT.width) / 2;
	while(screen[i].line[0] != 0x20 )
	{
		if ( i == 0 )
			ST7735_WriteString(xcentered,screen[i].y,screen[i].line, MACHINE_FONT, screen[i].fcolor, screen[i].bcolor);
		else
			ST7735_WriteString(screen[i].x,screen[i].y,screen[i].line, USED_FONT, screen[i].fcolor, screen[i].bcolor);
		i++;
	}
}

void Main_Menu(void)
{
	ST7735_FillScreen(ST7735_BLACK);
	Draw_Menu((ScreenTypeDef *)&Main_Menu_Screen);
	MenuStruct.menu_line_counter = 1;
	Menus_Hilight_Line(Main_Menu_Screen,1,1);
}

void Menus_Init(uint16_t brightness)
{
uint8_t	i;
	LcdSetBrightness(ZERO_BRIGHTNESS);
	LcdClearScreen();
	MenuStruct.current_brightness = brightness;
	MenuStruct.menu_line_counter = 0;
	MenuStruct.menu_max_numline = MENU_MAX_TOP_LINE;
	sprintf(Main_Menu_Screen[0].line,"%s-%s",MACHINE_NAME,MACHINE_VERSION);
	for(i=0;i<8;i++)
	{
		if ( Main_Menu_Screen[i].line[0] != 0x20 )
		{
			Main_Menu_Screen[i].x = 0;
			Main_Menu_Screen[i].y = i*(USED_FONT.height+STD_Y_SPACE);
			Main_Menu_Screen[i].line_counter = i;
		}
	}
	LcdSetBrightness(brightness);
	Main_Menu();
}

