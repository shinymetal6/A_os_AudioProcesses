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
 * Project : vb101_VCO_00
*/
/*
 * usb_midi.c
 *
 *  Created on: Mar 14, 2024
 *      Author: fil
 */


#include "main.h"
#include "A_os_includes.h"
#include "A_os_AudioInclude.h"
#include "usb_midi.h"

__attribute__ ((aligned (4)))	uint8_t		midi_rx_buf[MIDI_RXBUF_SIZE];
__attribute__ ((aligned (4)))	uint8_t		midi_tx_buf[MIDI_RXBUF_SIZE];
__attribute__ ((aligned (4)))	uint8_t		sysex_buffer[MIDI_RXBUF_SIZE];
uint8_t	sysex_len;

uint16_t SYSEX_ConvertMidiBufOut(uint8_t *buf_out , uint16_t len)
{
uint32_t	r=0,k=0;

	midi_tx_buf[k] = SYSEX_STARTC;
	k++;
	midi_tx_buf[k] = SYSEX_START;
	k++;
	r = 0;
	while ( r < len )
	{
		midi_tx_buf[k] = buf_out[r];
		r++;
		k++;
		if ( (k & 0x03 ) == 0)
		{
			if (( len - r ) == 2)
				midi_tx_buf[k] = SYSEX_END_3;
			else if (( len - r ) == 1)
				midi_tx_buf[k] = SYSEX_END_2;
			else if (( len - r ) == 0)
				midi_tx_buf[k] = SYSEX_END_1;
			else
				midi_tx_buf[k] = SYSEX_STARTC;
			k++;
		}
	}
	midi_tx_buf[k] = SYSEX_END;
	while ((k & 0x03 ) != 0 )
		k++;
	return k;
}

void DumpProgram(uint8_t program_number)
{
}

void DumpCurrentProgram(void)
{
}

uint8_t UsbMidiParseNoteOFF(uint8_t channel ,uint8_t midi_note , uint8_t velocity)
{
	DisableOscillator(channel,midi_note,velocity);
	return 4;
}

uint8_t UsbMidiParseNoteON(uint8_t	channel , uint8_t midi_note , uint8_t velocity)
{
	if ( velocity == 0 )
		DisableOscillator(channel,midi_note,velocity);
	else
		EnableOscillator(channel,midi_note,velocity);
	return 4;
}

void UsbSysExApplyValues(void)
{
	if ( sysex_buffer[1] == SYS_COMMAND_CMD)
	{
		if ( sysex_buffer[2] == SYSEX_DUMP_PROGRAM_CMD )
			DumpProgram(sysex_buffer[3] & (NUM_PROGRAMS_MAX-1));
		if ( sysex_buffer[2] == SYSEX_DUMP_CURRENT_PROGRAM_CMD )
			DumpCurrentProgram();
	}
}

uint8_t UsbMidiParseSysEx(uint8_t channel , uint8_t sub_command,uint32_t len,uint8_t* buf)
{
uint8_t	i,j=1,k=0;

	if ( len > SYSEX_MAX_LEN )
		return 0;

	sysex_len = 0;
	for(i=0;i<len;i+=4)
	{
		if ( buf[i] == SYSEX_STARTC )
		{
			sysex_buffer[k] = buf[j];
			sysex_buffer[k+1] = buf[j+1];
			sysex_buffer[k+2] = buf[j+2];
			k +=3;
			j +=4;
			sysex_len+=3;
		}
		if ( buf[i] == SYSEX_END_1 )
		{
			sysex_buffer[k] = buf[j];
			sysex_len+=0;
			i = len;
		}
		if ( buf[i] == SYSEX_END_2 )
		{
			sysex_buffer[k] = buf[j];
			sysex_buffer[k+1] = buf[j+1];
			sysex_len+=1;
			i = len;
		}
		if ( buf[i] == SYSEX_END_3 )
		{
			sysex_buffer[k] = buf[j];
			sysex_buffer[k+1] = buf[j+1];
			sysex_buffer[k+2] = buf[j+2];
			sysex_len+=2;
			i = len;
		}
	}
	if ( sysex_buffer[sysex_len] == SYSEX_END )
		UsbSysExApplyValues();
	return len;
}

void change_wave(uint8_t channel, uint8_t value)
{
}

void change_volume(uint8_t channel, uint8_t value)
{
}

void change_duty(uint8_t channel, uint8_t value) // max_val is 100
{
}

void change_detune(uint8_t channel, uint8_t value)
{
}

void change_afx_resonance( uint8_t value )
{
}

void change_afx_cutoff( uint8_t value )
{
}

void change_afx_type( uint8_t value )
{
}

void change_afx_source( uint8_t value )
{
}

void change_afx_enable( uint8_t value )
{
}

void change_DelayLen( uint8_t value )
{
}

void change_DelaySource( uint8_t value )
{

}

void change_DelayEnable( uint8_t value )
{
}

void change_Atime( uint8_t value )
{
}

void change_Dtime( uint8_t value )
{
}

void change_Sval( uint8_t value )
{
}

void change_Rtime( uint8_t value )
{
}

uint8_t	UsbMidiParseControlChange(uint8_t cc_index,uint8_t cc_value)
{
	switch(cc_index)
	{
	case CC_OSCWAVE0		:
	case CC_OSCWAVE1		:
	case CC_OSCWAVE2		:
	case CC_OSCWAVE3		:
		change_wave(cc_index & 0x03 ,cc_value & 0x7f);
		break;
	case CC_OSCVOLUME0		:
	case CC_OSCVOLUME1		:
	case CC_OSCVOLUME2		:
	case CC_OSCVOLUME3		:
		change_volume(cc_index & 0x03 ,cc_value & 0x7f);
		break;
	case CC_OSCDUTY0		:
	case CC_OSCDUTY1		:
	case CC_OSCDUTY2		:
	case CC_OSCDUTY3		:
		change_duty(cc_index & 0x03,cc_value & 0x7f);
		break;
	case CC_OSCDETUNE0		:
	case CC_OSCDETUNE1		:
	case CC_OSCDETUNE2		:
	case CC_OSCDETUNE3		:
		change_detune(cc_index & 0x03,cc_value & 0x7f);
		break;
	case CC_AFXENABLE		:
		change_afx_enable(cc_value & 0x7f);
		break;
	case CC_AFXTYPE		:
		change_afx_type(cc_value & 0x7f);
		break;
	case CC_AFXFREQUENCY		:
		change_afx_cutoff(cc_value & 0x7f);
		break;
	case CC_AFXRESONANCE		:
		change_afx_resonance(cc_value & 0x7f);
		break;
	case CC_AFXCONTROLSOURCE		:
		change_afx_source(cc_value & 0x7f);
		break;
	case CC_DLYENABLE		:
		change_DelayEnable(cc_value & 0x7f);
		break;
	case CC_DELAYLEN		:
		change_DelayLen(cc_value & 0x7f);
		break;
	case CC_DELAYSOURCE		:
		change_DelaySource(cc_value & 0x7f);
		break;

	case CC_ATIME		:
		change_Atime(cc_value & 0x7f);
		break;
	case CC_DTIME		:
		change_Dtime(cc_value & 0x7f);
		break;
	case CC_SVAL		:
		change_Sval(cc_value & 0x7f);
		break;
	case CC_RTIME		:
		change_Rtime(cc_value & 0x7f);
		break;
	default : break;
	}
	return 4;
}

void UsbMidiParser(uint8_t* buf, uint16_t len)
{
uint8_t		cmd,channel,midi_note,velocity;
uint32_t	l_index=0;


	while ( l_index < len )
	{
		cmd = buf[l_index] & CIN_MASK;
		channel = buf[l_index+1] & CHANNEL_MASK;
		midi_note = buf[l_index+2];
		velocity = buf[l_index+3];
		switch(cmd)
		{
			case NOTE_OFF			:
				l_index += UsbMidiParseNoteOFF(channel,midi_note,velocity);
				break;
			case NOTE_ON			:
				l_index += UsbMidiParseNoteON (channel,midi_note,velocity);
				break;
			case SYSEX_END_1			:
				break;
			case SYSEX_STARTC			:
			case SYSEX_END_2			:
			case SYSEX_END_3			:
				if ( buf[1] == SYSEX_START )
					l_index += UsbMidiParseSysEx (channel,cmd,len,buf);
				break;
			case CONTROL_CHANGE			:
				l_index += UsbMidiParseControlChange (buf[l_index+2],buf[l_index+3]);
				break;
				/*
			case PROGRAM_CHANGE			:
				l_index += UsbMidiParseProgramChange (buf[l_index+2],buf[l_index+3]);
				break;
			case POLY_PRESSURE			:
				l_index += UsbMidiParsePolyPressure (channel,midi_note,velocity);
				break;
			case PITCH_BEND			:
				l_index += UsbMidiParsePitchBend (channel,midi_note,velocity);
				break;
			case SINGLEBYTE			:
				l_index += UsbMidiParseSingleByte (channel,midi_note,velocity);
				break;
			case MISC			:
				l_index += UsbMidiParseMisc (channel,midi_note,velocity);
				break;
			case CABLE			:
				l_index += UsbMidiParseCable (channel,midi_note,velocity);
				break;
			case TWO_BYTES			:
				l_index += UsbMidiParseTwoBytes (channel,midi_note,velocity);
				break;
			case THREE_BYTES			:
				l_index += UsbMidiParseThreeBytes (channel,midi_note,velocity);
				break;
				*/
			default			:	l_index += 4; break;
		}
	}
}

uint8_t MIDI_Receive_Callback(uint8_t* Buf, uint16_t Len)
{
	UsbMidiParser(Buf,Len);
	return 0;
}

