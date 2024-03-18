/*
 * processes_table.c
 *
 *  Created on: Sep 13, 2023
 *      Author: fil
 */

#include "main.h"
#include "A_os_includes.h"

extern	void process_1_audio(uint32_t process_id);			//This is process1
extern	void process_2_fat_flash(uint32_t process_id);		//This is process2
extern	void process_2(uint32_t process_id);				//This is process2
extern	void process_3(uint32_t process_id);				//This is process3
extern	void process_4_hmi(uint32_t process_id);			//This is process4

VERSIONING	uint8_t	app_name[32] 		= "BB201 VCO";
VERSIONING	uint8_t	app_version[32] 	= "1.0.0";

USRprcs_t	UserProcesses[USR_PROCESS_NUMBER] =
{
		{
				.user_process = process_1_audio,
				.stack_size = 2048,
		},
		{
				.user_process = process_2,
				.stack_size = 2048,
		},
		{
				.user_process = process_3,
				.stack_size = 2048,
		},
		{
				.user_process = process_4_hmi,
				.stack_size = 2048,
		}
};
