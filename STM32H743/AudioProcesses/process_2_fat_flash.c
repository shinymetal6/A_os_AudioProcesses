/*
 * process_2.c
 *
 *  Created on: Sep 13, 2023
 *      Author: fil
 */

#include "main.h"
#include "A_os_includes.h"

#ifdef FAT_ON_PROCESS_1
uint8_t	theflag = 0;
uint8_t	sd_data[128];
extern	char 	SDPath[4];   /* SD logical drive path */
extern	FATFS 	SDFatFS;    /* File system object for SD logical drive */
extern	FIL 	SDFile;       /* File object for SD */

uint8_t wtext[] = "bB201xx STM32 FatFs running";
uint8_t rtext[256];

uint8_t	sd_detect=0;

uint8_t	get_sd_detect(void)
{
	sd_detect = HAL_GPIO_ReadPin(SD_DETECT_GPIO_Port, SD_DETECT_Pin);
	return (uint8_t )sd_detect;
}

uint8_t	usd_present = 0;

#define	FAT_ENABLED	1
void process_2_fat_flash(uint32_t process_id)
{
uint32_t	wakeup;
#ifdef	FAT_ENABLED
uint32_t	bytesread,byteswritten;
uint8_t		res;

	create_timer(TIMER_ID_0,1000,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);
	while(1)
	{
		wakeup = wait_event(EVENT_TIMER);
		if (( wakeup & WAKEUP_FROM_TIMER) == WAKEUP_FROM_TIMER)
		{
        	usd_present = 0;
			if ( get_sd_detect() == 0)
			{
				res = 1;
				if(f_mount(&SDFatFS, (TCHAR const*)SDPath, 0) == FR_OK)
				{
			        if(f_open(&SDFile, "STM32.TXT", FA_READ) == FR_OK)
			        {
			        	res = f_read(&SDFile, rtext, sizeof(rtext), (void *)&bytesread);
			            f_close(&SDFile);
			        }
			        else
			        {
			        	res = f_open(&SDFile, "STM32.TXT", FA_CREATE_ALWAYS);
			        	if ( res == 0 )
			        	{
				        	res = f_write(&SDFile, wtext, sizeof(wtext), (void *)&byteswritten);
				            f_close(&SDFile);
			        	}
			        }
				}
		        if ( res == 0 )
		        	usd_present = 1;
			}
		}
	}
#else
	create_timer(TIMER_ID_0,1000,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);
	while(1)
	{
		wakeup = wait_event(EVENT_TIMER);
	}
#endif
}
#else

uint8_t		*storage;
uint32_t	flash_size;
void process_2_fat_flash(uint32_t process_id)
{
uint32_t	wakeup,flags;
	create_timer(TIMER_ID_0,5000,TIMERFLAGS_FOREVER | TIMERFLAGS_ENABLED);
	while(1)
	{
		wait_event(EVENT_TIMER);
		get_wakeup_flags(&wakeup,&flags);
		storage = (uint8_t *)get_flash_storage_ptr();
		flash_size = get_flash_size();
		//copy_code(storage);
		//flash_update(storage,flash_size);
	}
}
#endif

