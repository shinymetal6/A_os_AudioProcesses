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
 * audio_component.h
 *
 *  Created on: Jan 3, 2024
 *      Author: fil
 */

#ifndef STM32H743_AUDIOPROCESSES_COMPONENTS_AUDIO_COMPONENT_H_
#define STM32H743_AUDIOPROCESSES_COMPONENTS_AUDIO_COMPONENT_H_

#define	SAMPLE_FREQUENCY				44100
#define	SAMPLE_PERIOD					(1.0F / SAMPLE_FREQUENCY)
#define _2PI                    		6.283185307F
#define _PI                    			3.14159265F
#define	SIGNAL_LEN						256
#define	DAC_BIT							12
#define	BIT_RESOLUTION					DAC_BIT
#define	DAC_RESOLUTION					(1<<DAC_BIT)
#define	HALF_DAC_RESOLUTION				(DAC_RESOLUTION/2)
#define	NUMBER_OF_AUDIO_SAMPLES			SIGNAL_LEN
#define	HALF_NUMBER_OF_AUDIO_SAMPLES	(SIGNAL_LEN/2)
#define	NUMOSCILLATORS_BITSHIFT			5 /* means 32 */
#define	NUMOSCILLATORS					(1<<NUMOSCILLATORS_BITSHIFT)
#define	NORMALIZE_CONTROL				4
#define	NORMALIZE_SHIFT					DAC_BIT


#endif /* STM32H743_AUDIOPROCESSES_COMPONENTS_AUDIO_COMPONENT_H_ */
