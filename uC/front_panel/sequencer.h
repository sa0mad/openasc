/*! \file sequencer.h \brief Front panel board defines 
 * \author Mikael Larsmark, SM2WMV
 * \date 2008-04-16
 */
//    Copyright (C) 2008  Mikael Larsmark, SM2WMV
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef _SEQUENCER_H_
#define _SEQUENCER_H_

/*! Sequencer message types, this is used to we can keep track of different
    messages in the event queue. So if an event is aborted we can easily just 
    remove the upcoming events from the queue, that doesn't need to be executed */

//! Event that the radio should be PTT:ed from footswitch
#define SEQUENCER_EVENT_TYPE_PTT_RADIO_ON			1
//! Event that the amp should be PTT:ed from footswitch
#define SEQUENCER_EVENT_TYPE_PTT_AMP_ON				2
//! Event that the inhibit should be activated from footswitch
#define SEQUENCER_EVENT_TYPE_PTT_INHIBIT_ON		3
//! Event that the radio should be deactivated from footswitch
#define SEQUENCER_EVENT_TYPE_PTT_RADIO_OFF			4
//! Event that the amp should be deactivated from footswitch
#define SEQUENCER_EVENT_TYPE_PTT_AMP_OFF				5
//! Event that the inhibit should be deactiated from footswitch
#define SEQUENCER_EVENT_TYPE_PTT_INHIBIT_OFF		6

#define PTT_INPUT_FOOTSWITCH						0
#define PTT_INPUT_RADIO_SENSE_UP				1
#define PTT_INPUT_RADIO_SENSE_LO				2
#define PTT_INPUT_COMPUTER_RTS					3
#define PTT_INPUT_INVERTED_RADIO_SENSE	4
#define PTT_INPUT_INVERTED_COMPUTER_RTS	5
#define PTT_INPUT_INHIBIT_POLARITY			6

//! Sequencer enabled for RADIO
#define SEQUENCER_PTT_RADIO_ENABLED		0
//! Sequencer enabled for AMP
#define SEQUENCER_PTT_AMP_ENABLED			1
//! Sequencer enabled for INHIBIT
#define SEQUENCER_PTT_INHIBIT_ENABLED	2

/* 
 *	Input
 *	-----
 *	Footswitch
 *	Radio sense lower floor
 *  Radio sense upper floor
 *  Computer RTS
 *  Inverted radio sense
 *  Inverted Computer RTS
 */

//! All the delays are divided with 10 so 100 is really 1000 ms which makes the maximium delay 2550 ms.
typedef struct {
	//! The delay before the radio is PTTed after the input PTT has been activated
	unsigned char radio_pre_delay;	
	//! The delay after the input PTT has been released and the radio PTT is released
	unsigned char radio_post_delay;	
	//! The delay before the amp is PTTed after the input PTT has been activated
	unsigned char amp_pre_delay;
	//! The delay after the input PTT has been released and the amp PTT is released
	unsigned char amp_post_delay;
	//! The delay before the inhibit is activated after the input PTT has been activated
	unsigned char inhibit_pre_delay;
	//! The delay after the input PTT has been released and the inhibit pin is released
	unsigned char inhibit_post_delay;
	//! The delay after theinput PTT has been released and the antennas are switched
	unsigned char antennas_post_delay;
	//! Flags on which sequencer variables that are enabled
	unsigned char active;		//Bit 0 = PTT Radio
													//Bit 1 = PTT Amp
													//Bit 2 = Inhibit enabled
} struct_ptt_sequencer;

typedef struct {
	unsigned int struct_size;
	//! The PTT SEQUENCER for the computer input
	struct_ptt_sequencer computer;		
	//! The PTT SEQUENCER for the footswitch input
	struct_ptt_sequencer footswitch;	
	//! The PTT SEQUENCER for the radio sense input
	struct_ptt_sequencer radio_sense;	
	/*! Bit 0 = Footswitch
	    Bit 1 = Radio sense lower floor
	    Bit 2 = Radio sense upper floor
	    Bit 3 = Computer RTS
	    Bit 4 = Inverted radio sense
	    Bit 5 = Inverted Computer RTS 
		  Bit 6 = Inhibit polarity (0=active low, 1=active high)
	*/
	unsigned char ptt_input;
} struct_ptt;

void sequencer_init_dummy(void);

void sequencer_footsw_pressed(void);
void sequencer_footsw_released(void);

void sequencer_computer_rts_activated(void);
void sequencer_computer_rts_deactivated(void);

void sequencer_radio_sense_activated(void);
void sequencer_radio_sense_deactivated(void);

unsigned char sequencer_get_rts_polarity(void);
unsigned char sequencer_get_sense_polarity(void);

unsigned char sequencer_ptt_active(void);

unsigned char sequencer_get_radio_sense(void);

#endif