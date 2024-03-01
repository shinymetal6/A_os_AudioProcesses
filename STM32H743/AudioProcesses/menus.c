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

#ifdef LCD_096_ENABLED

extern	MenuStruct_t	MenuStruct;
ScreenLeftTypeDef	*current_left_screen;
ScreenRightTypeDef	*current_right_screen;

static ScreenLeftTypeDef	Main_Menu_Screen[] =
{
		{
				"S",
				ST7735_BLUE,
				ST7735_BLACK,
		},
		{
				"OSCs",
				ST7735_GREEN,
				ST7735_BLACK,
		},
		{
				"Detune",
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

static ScreenLeftTypeDef	OSCs_LeftMenu_Screen[] =
{
		{
				"S",
				ST7735_BLUE,
				ST7735_BLACK,
		},
		{
				"OSC1",
				ST7735_GREEN,
				ST7735_BLACK,
		},
		{
				"OSC2",
				ST7735_GREEN,
				ST7735_BLACK,
		},
		{
				"OSC3",
				ST7735_GREEN,
				ST7735_BLACK,
		},
		{
				"OSC4",
				ST7735_GREEN,
				ST7735_BLACK,
		},
		{
				"Return",
				ST7735_GREEN,
				ST7735_BLACK,
		},
		{
				" ",
		},
};
static ScreenRightTypeDef	OSCs_RightMenu_Screen[] =
{
		{
				"S",
				ST7735_BLUE,
				ST7735_BLACK,
		},
		{
				"Sine",
				ST7735_CYAN,
				ST7735_BLACK,
		},
		{
				"Sine",
				ST7735_CYAN,
				ST7735_BLACK,
		},
		{
				"Sine",
				ST7735_CYAN,
				ST7735_BLACK,
		},
		{
				"Sine",
				ST7735_CYAN,
				ST7735_BLACK,
		},
		{
				" ",
		},
};

#define	USED_FONT			Font_7x11
#define	MACHINE_FONT		Font_7x11


void Menus_Hilight_Line(ScreenLeftTypeDef *screen, uint16_t old_line_number, uint16_t new_line_number)
{
	ST7735_WriteString(screen[old_line_number].x,screen[old_line_number].y,screen[old_line_number].line, USED_FONT, screen[old_line_number].fcolor, screen[old_line_number].bcolor);
	ST7735_WriteString(screen[new_line_number].x,screen[new_line_number].y,screen[new_line_number].line, USED_FONT, ST7735_BLACK, ST7735_BLACK);
	ST7735_WriteString(screen[new_line_number].x,screen[new_line_number].y,screen[new_line_number].line, USED_FONT, screen[new_line_number].bcolor, screen[new_line_number].fcolor);
}

void move_menu(ScreenLeftTypeDef *screen, uint8_t direction)
{
	uint16_t old_line_number = MenuStruct.menu_line_counter;
	if (direction)
	{
		if ( MenuStruct.menu_line_counter == 1 )
			MenuStruct.menu_line_counter = screen->numlines;//  MenuStruct.menu_max_numline;
		else
			MenuStruct.menu_line_counter --;
	}
	else
	{
		if ( MenuStruct.menu_line_counter >= screen->numlines )
			MenuStruct.menu_line_counter = 1;
		else
			MenuStruct.menu_line_counter ++;
	}
	Menus_Hilight_Line(screen,old_line_number,MenuStruct.menu_line_counter);
}

void Draw_LeftMenu(ScreenLeftTypeDef *screen)
{
uint8_t		i=0;
uint16_t	xcentered=0;

	LcdClearScreen();

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

void Draw_RightMenu(ScreenRightTypeDef *screen)
{
uint8_t		i=1;

	while(screen[i].line[0] != 0x20 )
	{
		ST7735_WriteString(screen[i].x,screen[i].y,screen[i].line, USED_FONT, screen[i].fcolor, screen[i].bcolor);
		i++;
	}
}

void DoMenus(void)
{
	if ( (MenuStruct.inputs & ENCODER_CLK) == ENCODER_CLK )
	{
		move_menu(current_left_screen,(MenuStruct.inputs & ENCODER_DATA));
	}
	switch ( MenuStruct.menu_state)
	{
	case	MENU_STATE_TOP:
		if ( (MenuStruct.inputs & ENCODER_BUTTON) == ENCODER_BUTTON )
		{
			if ( MenuStruct.menu_line_counter == 1 )
			{
				Draw_LeftMenu(OSCs_LeftMenu_Screen);
				Draw_RightMenu(OSCs_RightMenu_Screen);
				MenuStruct.menu_state = MENU_STATE_OSC_TOP;
				MenuStruct.menu_line_counter = 1;
				Menus_Hilight_Line(OSCs_LeftMenu_Screen,1,1);
				current_left_screen = OSCs_LeftMenu_Screen;
			}
		}
		break;
	case	MENU_STATE_OSC_TOP:
		if ( (MenuStruct.inputs & ENCODER_BUTTON) == ENCODER_BUTTON )
		{
			if ( MenuStruct.menu_line_counter == 5 )
			{
				Draw_LeftMenu(Main_Menu_Screen);
				MenuStruct.menu_state = MENU_STATE_TOP;
				MenuStruct.menu_line_counter = 1;
				Menus_Hilight_Line(Main_Menu_Screen,1,1);
				current_left_screen = Main_Menu_Screen;
			}
		}
		break;
	}
	MenuStruct.inputs = 0;
}


void Main_Menu(void)
{
	ST7735_FillScreen(ST7735_BLACK);
	MenuStruct.menu_state = MENU_STATE_TOP;
	MenuStruct.menu_line_counter = 1;
	Draw_LeftMenu(Main_Menu_Screen);
	current_left_screen = Main_Menu_Screen;
	Menus_Hilight_Line(Main_Menu_Screen,1,1);
}

static void initialize_left_menus(ScreenLeftTypeDef *cmenu, uint16_t size)
{
uint8_t	i=0;
	sprintf(cmenu[0].line,"%s-%s",MACHINE_NAME,MACHINE_VERSION);
	while ( cmenu[i].line[0] != 0x20 )
	{
		cmenu[i].x = 0;
		cmenu[i].y = i*(USED_FONT.height+STD_Y_SPACE);
		cmenu[i].line_counter = i;
		cmenu[i].numlines = (size/30) - 1;
		i++;
	}
}

static void initialize_right_menus(ScreenRightTypeDef *cmenu, uint16_t size)
{
uint8_t	i=1;
	while ( cmenu[i].line[0] != 0x20 )
	{
		cmenu[i].x = USED_FONT.width*(LEFTMENU_NUMCHAR-4);
		cmenu[i].y = i*(USED_FONT.height+STD_Y_SPACE);
		cmenu[i].line_counter = i;
		cmenu[i].numlines = (size/30) - 1;
		i++;
	}
}

uint16_t size;
void Menus_Init(uint16_t brightness)
{
	LcdSetBrightness(ZERO_BRIGHTNESS);
	LcdClearScreen();
	MenuStruct.current_brightness = brightness;
	MenuStruct.menu_line_counter = 0;
	initialize_left_menus(Main_Menu_Screen,sizeof(Main_Menu_Screen));
	initialize_left_menus(OSCs_LeftMenu_Screen,sizeof(OSCs_LeftMenu_Screen));
	initialize_right_menus(OSCs_RightMenu_Screen,sizeof(OSCs_RightMenu_Screen));

	LcdSetBrightness(brightness);
	Main_Menu();
}

#endif // #ifdef LCD_096_ENABLED
