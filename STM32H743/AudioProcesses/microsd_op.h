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
 * microsd_op.h
 *
 *  Created on: Jan 22, 2024
 *      Author: fil
 */

#ifndef STM32H743_AUDIOPROCESSES_MICROSD_OP_H_
#define STM32H743_AUDIOPROCESSES_MICROSD_OP_H_

typedef struct
{
	uint8_t		card_status;
	char		file_name[32];


}SDcard_t;
/* card_status */
#define		CARD_MOUNTED		0x40
#define		CARD_DETECTED		0x80


extern	uint8_t	microsd_detect(void);

#endif /* STM32H743_AUDIOPROCESSES_MICROSD_OP_H_ */
