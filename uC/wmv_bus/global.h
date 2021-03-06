/*! \file wmv_bus/global.h 
 *  \brief AVRlib project global include.
 *  \author Pascal Stang and Mikael Larsmark, SM2WMV
 *  \date 2008-04-13
 */
//*****************************************************************************
//
// File Name	: 'global.h'
// Title		: AVRlib project global include 
// Author		: Pascal Stang - Copyright (C) 2001-2002
// Created		: 7/12/2001
// Revised		: 9/30/2002
// Version		: 1.1
// Target MCU	: Atmel AVR series
// Editor Tabs	: 4
//
//	Description : This include file is designed to contain items useful to all
//					code files and projects.
//
// This code is distributed under the GNU Public License
//		which can be found at http://www.gnu.org/licenses/gpl.txt
//
//*****************************************************************************

#ifndef GLOBAL_H
#define GLOBAL_H

// CPU clock speed
//! The CPU speed
#define F_CPU        14745000               		// 14.745MHz processor
//! Cycles per us
#define CYCLES_PER_US ((F_CPU+500000)/1000000) 	// cpu cycles per microsecond

#endif
