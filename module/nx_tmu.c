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
//	Module		: Temperature Management Unit
//	File		: nx_tmu.c
//	Description	:
//	Author		:
//	History		: 20140806 first implementation
//------------------------------------------------------------------------------
#include "nx_tmu.h"

static struct NX_TMU_RegisterSet *__g_pRegister[NUMBER_OF_TMU_MODULE];


//------------------------------------------------------------------------------
// Module Interface
//------------------------------------------------------------------------------
/**
 *	@brief	Initialize of prototype enviroment & local variables.
 *	@return \b CTRUE	indicates that Initialize is successed.\r\n
 *			\b CFALSE indicates that Initialize is failed.\r\n
 */
CBOOL	NX_TMU_Initialize( void )
{
	static CBOOL bInit = CFALSE;

	if( CFALSE == bInit )
	{
		__g_pRegister[0] = (struct NX_TMU_RegisterSet *)CNULL;

		bInit = CTRUE;
	}

	return bInit;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get number of modules in the chip.
 *	@return		Module's number.
 */
U32		NX_TMU_GetNumberOfModule( void )
{
	return NUMBER_OF_TMU_MODULE;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get number of submodules in the temperature manager.
 *	@return		SubModule's number.
 */
U32		NX_TMU_GetNumberOfChannel( void )
{
	return NX_TMU_CHANNEL;
}

//------------------------------------------------------------------------------
// Basic Interface
//------------------------------------------------------------------------------
/**
 *	@brief		Get module's physical address.
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@return		Module's physical address
 */
U32		NX_TMU_GetPhysicalAddress( U32 ModuleIndex )
{
	static const U32 PhysicalAddr[] = { PHY_BASEADDR_LIST( TMU ) };

	NX_ASSERT( NUMBER_OF_TMU_MODULE > ModuleIndex );

	return (U32)PhysicalAddr[ModuleIndex];
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get a size, in byte, of register set.
 *	@return		Size of module's register set.
 */
U32		NX_TMU_GetSizeOfRegisterSet( void )
{
	return sizeof( struct NX_TMU_RegisterSet );
}

//------------------------------------------------------------------------------
/**
 *	@brief		Set a base address of register set.
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@param[in]	BaseAddress Module's base address
 *	@return		None.
 */
void	NX_TMU_SetBaseAddress( U32 ModuleIndex, U32 BaseAddress )
{
	NX_ASSERT( NUMBER_OF_TMU_MODULE > ModuleIndex );
	NX_ASSERT( CNULL != BaseAddress );

	__g_pRegister[ModuleIndex] = (struct NX_TMU_RegisterSet *)BaseAddress;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get a base address of register set
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@return		Module's base address.
 */
U32		NX_TMU_GetBaseAddress( U32 ModuleIndex )
{
	NX_ASSERT( NUMBER_OF_TMU_MODULE > ModuleIndex );

	return (U32)__g_pRegister[ModuleIndex];
}

//------------------------------------------------------------------------------
/**
 *	@brief		Initialize selected modules with default value.
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@return		\b CTRUE	indicates that Initialize is successed. \r\n
 *				\b CFALSE	indicates that Initialize is failed.
 */
CBOOL	NX_TMU_OpenModule( U32 ModuleIndex )
{
	NX_ASSERT( NUMBER_OF_TMU_MODULE > ModuleIndex );

	return CTRUE;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Deinitialize selected module to the proper stage.
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@return		\b CTRUE	indicates that Deinitialize is successed. \r\n
 *				\b CFALSE	indicates that Deinitialize is failed.
 */
CBOOL	NX_TMU_CloseModule( U32 ModuleIndex )
{
	NX_ASSERT( NUMBER_OF_TMU_MODULE > ModuleIndex );

	return CTRUE;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Indicates whether the selected modules is busy or not.
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@return		\b CTRUE	indicates that Module is Busy. \r\n
 *				\b CFALSE	indicates that Module is NOT Busy.
 */
CBOOL	NX_TMU_CheckBusy( U32 ModuleIndex )
{
	NX_ASSERT( NUMBER_OF_TMU_MODULE > ModuleIndex );

	return CFALSE;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Indicaes whether the selected modules is ready to enter power-down stage
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@return		\b CTRUE	indicates that Ready to enter power-down stage. \r\n
 *				\b CFALSE	indicates that This module can't enter to power-down stage.
 */
CBOOL	NX_TMU_CanPowerDown( U32 ModuleIndex )
{
	NX_ASSERT( NUMBER_OF_TMU_MODULE > ModuleIndex );

	return CTRUE;
}

//------------------------------------------------------------------------------
//	clock Interface
//------------------------------------------------------------------------------

// no clock generator need.


//------------------------------------------------------------------------------
//	reset Interface
//------------------------------------------------------------------------------

// no reset control need

//------------------------------------------------------------------------------
// Interrupt Interface
//------------------------------------------------------------------------------
/**
 *	@brief		Get a interrupt number for interrupt controller.
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@return		Interrupt number
 */
U32		NX_TMU_GetInterruptNumber( U32 ModuleIndex, U32 Channel )
{
	const U32	TMUInterruptNumber[] =
				{
					{ INTNUM_LIST(TMU) },
				};

	NX_ASSERT( NUMBER_OF_TMU_MODULE > ModuleIndex );

	return	TMUInterruptNumber[ModuleIndex];
}

//------------------------------------------------------------------------------
/**
 *	@brief		Set a specified interrupt to be enable or disable.
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@param[in]	IntNum	Interrupt Number.
 *	@param[in]	Enable	\b CTRUE	indicates that Interrupt Enable. \r\n
 *						\b CFALSE	indicates that Interrupt Disable.
 *	@return		None.
 */
void	NX_TMU_SetInterruptEnable( U32 ModuleIndex, U32 IntNum, CBOOL Enable )
{
	register struct NX_TMU_RegisterSet*	pRegister;
	register U32	ReadValue;

	NX_ASSERT( NUMBER_OF_TMU_MODULE > ModuleIndex );
	NX_ASSERT( NX_TMU_CHANNEL > IntNum );
	NX_ASSERT( (0==Enable) || (1==Enable) );

	pRegister	=	__g_pRegister[ModuleIndex];

	NX_ASSERT( CNULL != pRegister );

//	ReadValue	=	ReadIODW(&pRegister->TINT_CSTAT) & 0x1F;

//	ReadValue	&=	(U32)(~(1UL << IntNum));
//	ReadValue	|=	(U32)Enable << IntNum ;

//	WriteIODW(&pRegister->TINT_CSTAT, ReadValue);
}

//------------------------------------------------------------------------------
/**
 *	@brief		Indicates whether a specified interrupt is enabled or disabled.
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@param[in]	IntNum	Interrupt Number.
 *	@return		\b CTRUE	indicates that Interrupt is enabled. \r\n
 *				\b CFALSE	indicates that Interrupt is disabled.
 */
CBOOL	NX_TMU_GetInterruptEnable( U32 ModuleIndex, U32 IntNum )
{
	register struct NX_TIMER_RegisterSet*	pRegister;

	NX_ASSERT( NUMBER_OF_TMU_MODULE > ModuleIndex );
	NX_ASSERT( NX_TMU_CHANNEL > IntNum );

	pRegister	=	__g_pRegister[ModuleIndex];

	NX_ASSERT( CNULL != pRegister );

	return	(CBOOL)0//( (ReadIODW(&pRegister->TINT_CSTAT) >> IntNum) & 0x01 );
}

//------------------------------------------------------------------------------
/**
 *	@brief		Indicates whether a specified interrupt is pended or not
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@param[in]	IntNum	Interrupt Number.
 *	@return		\b CTRUE	indicates that Pending is seted. \r\n
 *				\b CFALSE	indicates that Pending is Not Seted.
 */
CBOOL	NX_TMU_GetInterruptPending( U32 ModuleIndex, U32 IntNum )
{
	register struct NX_TMU_RegisterSet*	pRegister;
	const U32	PEND_POS	=	5;

	NX_ASSERT( NUMBER_OF_TMU_MODULE > ModuleIndex );
	NX_ASSERT( NX_TMU_CHANNEL > IntNum );

	pRegister	=	__g_pRegister[ModuleIndex];

	NX_ASSERT( CNULL != pRegister );

	return	(CBOOL)0//( (ReadIODW(&pRegister->TINT_CSTAT) >> (IntNum+PEND_POS)) & 0x01 );
}

//------------------------------------------------------------------------------
/**
 *	@brief		Clear a pending state of specified interrupt.
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ 5 ).
 *	@param[in]	IntNum	Interrupt number.
 *	@return		None.
 */
void	NX_TMU_ClearInterruptPending( U32 ModuleIndex, U32 IntNum )
{
	register struct NX_TMU_RegisterSet*	pRegister;
	const U32	PEND_POS	=	5;
	const U32	PEND_MASK	=	0x1f;
	register U32 PendEnb;


	NX_ASSERT( NUMBER_OF_TMU_MODULE > ModuleIndex );
	NX_ASSERT( NX_TMU_CHANNEL > IntNum );

	pRegister	=	__g_pRegister[ModuleIndex];

	NX_ASSERT( CNULL != pRegister );

//	PendEnb	=	ReadIODW(&pRegister->TINT_CSTAT) & PEND_MASK;
//	PendEnb |=	1UL<<(IntNum+PEND_POS);

//	WriteIODW(&pRegister->TINT_CSTAT, PendEnb );
}

//------------------------------------------------------------------------------
/**
 *	@brief		Set all interrupts to be enables or disables.
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@param[in]	Enable	\b CTRUE	indicates that Set to all interrupt enable. \r\n
 *						\b CFALSE	indicates that Set to all interrupt disable.
 *	@return		None.
 */
void	NX_TMU_SetInterruptEnableAll( U32 ModuleIndex, CBOOL Enable )
{
	register struct NX_TMU_RegisterSet*	pRegister;
	register U32	SetValue;

	NX_ASSERT( NUMBER_OF_TMU_MODULE > ModuleIndex );
	NX_ASSERT( (0==Enable) || (1==Enable) );

	pRegister	=	__g_pRegister[ModuleIndex];

	NX_ASSERT( CNULL != pRegister );


	if( Enable )
		SetValue	=	0x1F;
	else
		SetValue	=	0;

//	WriteIODW(&pRegister->TINT_CSTAT, SetValue);
}

//------------------------------------------------------------------------------
/**
 *	@brief		Indicates whether some of interrupts are enable or not.
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@return		\b CTRUE	indicates that At least one( or more ) interrupt is enabled. \r\n
 *				\b CFALSE	indicates that All interrupt is disabled.
 */
CBOOL	NX_TMU_GetInterruptEnableAll( U32 ModuleIndex )
{
	register struct NX_TMU_RegisterSet*	pRegister;
	const U32	ENABLE_POS	=	0;
	const U32	INT_MASK	=	0x1f;

	NX_ASSERT( NUMBER_OF_TMU_MODULE > ModuleIndex );

	pRegister	=	__g_pRegister[ModuleIndex];

	NX_ASSERT( CNULL != pRegister );

//	if( ReadIODW(&pRegister->TINT_CSTAT) & (INT_MASK << ENABLE_POS) )
	{
//		return CTRUE;
	}

	return CFALSE;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Indicates whether some of interrupts are pended or not.
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@return		\b CTRUE	indicates that At least one( or more ) pending is seted. \r\n
 *				\b CFALSE	indicates that All pending is NOT seted.
 */
CBOOL	NX_TMU_GetInterruptPendingAll( U32 ModuleIndex )
{
	register struct NX_TMU_RegisterSet*	pRegister;
	const U32	PEND_POS	=	5;
	const U32	PEND_MASK	=	0x1f;

	NX_ASSERT( NUMBER_OF_TMU_MODULE > ModuleIndex );

	pRegister	=	__g_pRegister[ModuleIndex];

	NX_ASSERT( CNULL != pRegister );

//	if( ReadIODW(&pRegister->TINT_CSTAT) & (PEND_MASK << PEND_POS) )
	{
//		return CTRUE;
	}

	return CFALSE;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Clear pending state of all interrupts.
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@return		None.
 */
void	NX_TMU_ClearInterruptPendingAll( U32 ModuleIndex )
{
	register struct NX_TMU_RegisterSet*	pRegister;
	const U32	PEND_POS	=	5;
	const U32	PEND_MASK	=	0x1f;

	register U32 PendEnb;

	NX_ASSERT( NUMBER_OF_TMU_MODULE > ModuleIndex );

	pRegister	=	__g_pRegister[ModuleIndex];

	NX_ASSERT( CNULL != pRegister );

//	PendEnb	=	ReadIODW(&pRegister->TINT_CSTAT) & 0x1F;
//	PendEnb |=	PEND_MASK<<PEND_POS;

//	WriteIODW(&pRegister->TINT_CSTAT, PendEnb );
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get a interrupt number which has the most prority of pended interrupts
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@return		Pending Number( If all pending is not set then return -1 ).
 */
U32		NX_TMU_GetInterruptPendingNumber( U32 ModuleIndex )	// -1 if None
{
	register struct NX_TMU_RegisterSet	*pRegister;
	const U32	PEND_POS	=	5;
	const U32	PEND_MASK	=	0x1f << PEND_POS;
	register U32 PendingIndex, Pend;

	NX_ASSERT( NUMBER_OF_TMU_MODULE > ModuleIndex );

	pRegister	=	__g_pRegister[ModuleIndex];

	NX_ASSERT( CNULL != pRegister );

//	Pend	=	(ReadIODW(&pRegister->TINT_CSTAT) & PEND_MASK)>>PEND_POS;

//	for( PendingIndex = 0; PendingIndex<NX_TIMER_INT; PendingIndex++)
//		if(Pend & (1UL<<PendingIndex))
//			break;

//	if(PendingIndex > NX_TIMER_INT)
		return -1;
//	else
//		return PendingIndex;
}

//--------------------------------------------------------------------------
// @name	Configuration operations
//--------------------------------------------------------------------------
//@{

//@}
