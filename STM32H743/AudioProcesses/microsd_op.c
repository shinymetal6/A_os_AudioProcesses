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
 * Project : A_os
*/
/*
 * microsd_op.c
 *
 *  Created on: Jan 22, 2024
 *      Author: fil
 */

#include "main.h"
#include "A_os_includes.h"
#ifdef SDCARD_ENABLED
#include "microsd_op.h"

extern	SDcard_t	SDcard;

uint8_t	microsd_detect(void)
{
	if ( HAL_GPIO_ReadPin(MICROSD_DETECT_IOPORT, MICROSD_DETECT_PIN) == 0 )
		SDcard.card_status |= CARD_DETECTED;
	else
		SDcard.card_status &= ~CARD_DETECTED;
	return SDcard.card_status;
}
#endif

