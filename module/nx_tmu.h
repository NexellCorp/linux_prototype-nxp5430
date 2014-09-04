//------------------------------------------------------------------------------
//
//	Copyright (C) 2012 Nexell Co., All Rights Reserved
//	Nexell Co. Proprietary & Confidential
//
//	NEXELL INFORMS THAT THIS CODE AND INFORMATION IS PROVIDED "AS IS" BASE
//	AND WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING
//	BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS
//	FOR A PARTICULAR PURPOSE.
//
//	Module		: TIMER Timer
//	File		: nx_tmu.h
//	Description	:
//	Author		: Firmware Team
//	History		: 20140806 first implementation
//------------------------------------------------------------------------------
#ifndef _NX_TMU_H
#define _NX_TMU_H

//------------------------------------------------------------------------------
//  includes
//------------------------------------------------------------------------------
#include "nx_prototype.h"

#ifdef	__cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
//  defines
//------------------------------------------------------------------------------
#define NX_TMU_CHANNEL	5
#define NX_TIMER_INT		4
#define NX_PWM_CHANNEL		4

//------------------------------------------------------------------------------
/// @brief  TMU register set structure
//------------------------------------------------------------------------------
struct NX_TMU_Probe_Temp
{
	volatile U32 Px_PAST_TEMP3_0;		// 0xx0	// Probe#x Past temperature 3-0 for tracing temperature
	volatile U32 Px_PAST_TEMP7_4;		// 0xx4	// Probe#x Past temperature 7-4 for tracing temperature
	volatile U32 Px_PAST_TEMP11_8;		// 0xx8	// Probe#x Past temperature 11-8 for tracing temperature
	volatile U32 Px_PAST_TEMP15_12;		// 0xxC	// Probe#x Past temperature 15-12 for tracing temperature
}
struct NX_TMU_Probe_IntCtrl
{
	volatile U32 Px_INTEN;				// 0xx0 // Px interrupt enable
	volatile U32 Px_INTSTAT;			// 0xx4 // Px interrupt status
	volatile U32 Px_INTCLEAR;			// 0xx8 // Px interrupt clear
	volatile U32 _Reserved0;			// 0xxC
}
struct NX_TMU_RegisterSet
{
	volatile U32 TRIMINFO;				// 0x00	// E-fuse information for trimming sensor data
	volatile U32 _Reserved0[3];			// 0x04~0x0C
	volatile U32 TRIMINFO_CFG;			// 0x10	// TrimInfo configure
	volatile U32 TRIMINFO_CTRL;			// 0x14	// TrimInfo control
	volatile U32 _Reserved1[2];			// 0x18~0x1C
	volatile U32 CONTROL;				// 0x20	// control
	volatile U32 CONTROL1;				// 0x24	// control1
 	volatile U32 STATUS;				// 0x28	// status
	volatile U32 SAMPLING_INTERVAL;		// 0x2C	// sampling interval
	volatile U32 COUNTER_VALUE0;		// 0x30	// set time to control EN_TEMP_SEN_ON/OFF
	volatile U32 COUNTER_VALUE1;		// 0x34	// set time to control CLK_SENSE_ON/OFF
	volatile U32 _Reserved2[2];			// 0x38~0x3C
	volatile U32 CURRENT_TEMP0;			// 0x40	// current temperature information for internal probe
	volatile U32 CURRENT_TEMP1;			// 0x44	// current temperature information for remote probes
	volatile U32 _Reserved3[2];			// 0x48~0x4C
	volatile U32 THRESHOLD_TEMP_RISE;	// 0x50 // Threshold for temperature rising
	volatile U32 THRESHOLD_TEMP_FALL;	// 0x54	// Threshold for temperature falling
	volatile U32 _Reserved4[2];			// 0x58~0x5C

	struct NX_TMU_Probe_Temp PAST_TEMP[NX_TMU_CHANNEL];

	struct NX_TMU_Probe_IntCtrl IntCtrl[NX_TMU_CHANNEL];

	volatile U32 EMUL_CON;				// 0x100 // Emulation control
	volatile U8 _Reserved5[0x1000-0x104];	// 0x104~0x1000
};

//------------------------------------------------------------------------------
/// @name	Module Interface
//@{
CBOOL	NX_TMU_Initialize( void );
U32		NX_TMU_GetNumberOfModule( void );
U32		NX_TMU_GetNumberOfChannel( void );
//@}

//------------------------------------------------------------------------------
///	@name	Basic Interface
//@{
U32		NX_TMU_GetPhysicalAddress( U32 ModuleIndex );
U32		NX_TMU_GetSizeOfRegisterSet( void );
void	NX_TMU_SetBaseAddress( U32 ModuleIndex, U32 BaseAddress );
U32		NX_TMU_GetBaseAddress( U32 ModuleIndex );
CBOOL	NX_TMU_OpenModule( U32 ModuleIndex );
CBOOL	NX_TMU_CloseModule( U32 ModuleIndex );
CBOOL	NX_TMU_CheckBusy( U32 ModuleIndex );
CBOOL	NX_TMU_CanPowerDown( U32 ModuleIndex );
//@}

//------------------------------------------------------------------------------
///	@name	clock Interface
//------------------------------------------------------------------------------
//@{
// no clock generator need
//@}

//------------------------------------------------------------------------------
///	@name	reset Interface
//------------------------------------------------------------------------------
//@{
// no reset control need
//@}

//------------------------------------------------------------------------------
///	@name	Interrupt Interface
//@{
U32		NX_TMU_GetInterruptNumber( U32 ModuleIndex, U32 SubModuleIndex );

void	NX_TMU_SetInterruptEnable( U32 ModuleIndex, U32 IntNum, CBOOL Enable );
CBOOL	NX_TMU_GetInterruptEnable( U32 ModuleIndex, U32 IntNum );
CBOOL	NX_TMU_GetInterruptPending( U32 ModuleIndex, U32 IntNum );
void	NX_TMU_ClearInterruptPending( U32 ModuleIndex, U32 IntNum );

void	NX_TMU_SetInterruptEnableAll( U32 ModuleIndex, CBOOL Enable );
CBOOL	NX_TMU_GetInterruptEnableAll( U32 ModuleIndex );
CBOOL	NX_TMU_GetInterruptPendingAll( U32 ModuleIndex );
void	NX_TMU_ClearInterruptPendingAll( U32 ModuleIndex );

U32		NX_TMU_GetInterruptPendingNumber( U32 ModuleIndex );	// -1 if None
//@}


//------------------------------------------------------------------------------

//--------------------------------------------------------------------------
/// @name	Configuration operations
//--------------------------------------------------------------------------
//@{

//@}

#ifdef	__cplusplus
}
#endif

#endif // _NX_TMU_H
