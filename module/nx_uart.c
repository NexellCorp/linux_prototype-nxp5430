//------------------------------------------------------------------------------
//
//	Copyright (C) 2009 Nexell Co., All Rights Reserved
//	Nexell Co. Proprietary & Confidential
//
//	NEXELL INFORMS THAT THIS CODE AND INFORMATION IS PROVIDED "AS IS" BASE
//	AND WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING
//	BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS
//	FOR A PARTICULAR PURPOSE.
//
//	Module		: pl01115 Uart
//	File		: nx_uart.c
//	Description	:
//	Author		:
//	History		:
//------------------------------------------------------------------------------
#include <nx_chip.h>
#include <nx_uart.h>

#ifdef NUMBER_OF_UART_MODULE
#undef NUMBER_OF_UART_MODULE
#define NUMBER_OF_UART_MODULE 6
#endif
static	struct
{
	struct NX_UART_RegisterSet *pRegister;

} __g_ModuleVariables[NUMBER_OF_UART_MODULE] = { {CNULL, }, };

//------------------------------------------------------------------------------
// Module Interface
//------------------------------------------------------------------------------
/**
 *	@brief	Initialize of prototype enviroment & local variables.
 *	@return \b CTRUE	indicates that Initialize is successed.\r\n
 *			\b CFALSE indicates that Initialize is failed.\r\n
 */
CBOOL	NX_UART_Initialize( void )
{
	static CBOOL bInit = CFALSE;
	U32 i;

	if( CFALSE == bInit )
	{
		for( i=0; i < NUMBER_OF_UART_MODULE; i++ )
		{
			__g_ModuleVariables[i].pRegister = CNULL;
		}
		bInit = CTRUE;
	}
	return bInit;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get number of modules in the chip.
 *	@return		Module's number.
 */
U32		NX_UART_GetNumberOfModule( void )
{
	return NUMBER_OF_UART_MODULE;
}

//------------------------------------------------------------------------------
// Basic Interface
//------------------------------------------------------------------------------
/**
 *	@brief		Get module's physical address.
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@return		Module's physical address
 */
U32		NX_UART_GetPhysicalAddress( U32 ModuleIndex )
{
	static const U32 PhysicalAddr[] = {
//		PHY_BASEADDR_LIST( UART )
		PHY_BASEADDR_UART0_MODULE,
		PHY_BASEADDR_pl01115_Uart_modem_MODULE,
		PHY_BASEADDR_UART1_MODULE,
		PHY_BASEADDR_LIST(pl01115_Uart_nodma)
	}; // PHY_BASEADDR_UARTx_MODULE

	NX_ASSERT( NUMBER_OF_UART_MODULE > ModuleIndex );

	return (U32)PhysicalAddr[ModuleIndex];
}


/**
 *	@brief		Get module's Reset number.
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@return		Module's Reset number
 */
U32 NX_UART_GetResetNumber (U32 ModuleIndex)
{
	const U32 ResetPinNumber[2][NUMBER_OF_UART_MODULE] =
	{
		RESETINDEX_OF_UART0_MODULE_nUARTRST,
		RESETINDEX_OF_pl01115_Uart_modem_MODULE_nUARTRST,
		RESETINDEX_OF_UART1_MODULE_nUARTRST,
		RESETINDEX_LIST( pl01115_Uart_nodma, nUARTRST )
	};

	return (U32)ResetPinNumber[ModuleIndex];
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get a size, in byte, of register set.
 *	@return		Size of module's register set.
 */
U32		NX_UART_GetSizeOfRegisterSet( void )
{
	return sizeof( struct NX_UART_RegisterSet );
}

//------------------------------------------------------------------------------
/**
 *	@brief		Set a base address of register set.
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@param[in]	BaseAddress Module's base address
 *	@return		None.
 */
void	NX_UART_SetBaseAddress( U32 ModuleIndex, U32 BaseAddress )
{
	NX_ASSERT( CNULL != BaseAddress );
	NX_ASSERT( NUMBER_OF_UART_MODULE > ModuleIndex );

	__g_ModuleVariables[ModuleIndex].pRegister = (struct NX_UART_RegisterSet *)BaseAddress;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get a base address of register set
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@return		Module's base address.
 */
U32		NX_UART_GetBaseAddress( U32 ModuleIndex )
{
	NX_ASSERT( NUMBER_OF_UART_MODULE > ModuleIndex );

	return (U32)__g_ModuleVariables[ModuleIndex].pRegister;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Initialize selected modules with default value.
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@return		\b CTRUE	indicates that Initialize is successed. \r\n
 *				\b CFALSE	indicates that Initialize is failed.
 */
CBOOL	NX_UART_OpenModule( U32 ModuleIndex )
{
	register struct NX_UART_RegisterSet	*pRegister;

	NX_ASSERT( NUMBER_OF_UART_MODULE > ModuleIndex );
	NX_ASSERT( CNULL != __g_ModuleVariables[ModuleIndex].pRegister );

	pRegister	=	__g_ModuleVariables[ModuleIndex].pRegister;

	return CTRUE;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Deinitialize selected module to the proper stage.
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@return		\b CTRUE	indicates that Deinitialize is successed. \r\n
 *				\b CFALSE	indicates that Deinitialize is failed.
 */
CBOOL	NX_UART_CloseModule( U32 ModuleIndex )
{
	register struct NX_UART_RegisterSet	*pRegister;

	NX_ASSERT( NUMBER_OF_UART_MODULE > ModuleIndex );
	NX_ASSERT( CNULL != __g_ModuleVariables[ModuleIndex].pRegister );

	pRegister	=	__g_ModuleVariables[ModuleIndex].pRegister;
	return CTRUE;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Indicates whether the selected modules is busy or not.
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@return		\b CTRUE	indicates that Module is Busy. \r\n
 *				\b CFALSE	indicates that Module is NOT Busy.
 */
CBOOL	NX_UART_CheckBusy( U32 ModuleIndex )
{
	NX_ASSERT( NUMBER_OF_UART_MODULE > ModuleIndex );

	return CFALSE;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Indicaes whether the selected modules is ready to enter power-down stage
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@return		\b CTRUE	indicates that Ready to enter power-down stage. \r\n
 *				\b CFALSE	indicates that This module can't enter to power-down stage.
 */
CBOOL	NX_UART_CanPowerDown( U32 ModuleIndex )
{
	NX_ASSERT( NUMBER_OF_UART_MODULE > ModuleIndex );

	return CTRUE;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get module's clock index.
 *	@return		Module's clock index.\n
 *				It is equal to CLOCKINDEX_OF_UART_MODULE in <nx_chip.h>.
 */
U32 NX_UART_GetClockNumber ( U32 ModuleIndex )
{
	const U32 ClockNumber[] =
	{
//		CLOCKINDEX_LIST( UART )
		CLOCKINDEX_OF_UART0_MODULE,
		CLOCKINDEX_OF_pl01115_Uart_modem_MODULE,
		CLOCKINDEX_OF_UART1_MODULE,
		CLOCKINDEX_LIST(pl01115_Uart_nodma)
	};
	NX_CASSERT( NUMBER_OF_UART_MODULE == (sizeof(ClockNumber)/sizeof(ClockNumber[0])) );
    NX_ASSERT( NUMBER_OF_UART_MODULE > ModuleIndex );

	return	ClockNumber[ModuleIndex];
}

//------------------------------------------------------------------------------
// Interrupt Interface
//------------------------------------------------------------------------------
/**
 *	@brief		Get a interrupt number for interrupt controller.
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@return		Interrupt number
 */
U32		NX_UART_GetInterruptNumber( U32 ModuleIndex )
{
	const U32	UartInterruptNumber[NUMBER_OF_UART_MODULE] =
				{
//					INTNUM_LIST(UART)
					INTNUM_OF_UART0_MODULE,
					INTNUM_OF_pl01115_Uart_modem_MODULE,
					INTNUM_OF_UART1_MODULE,
					INTNUM_LIST(pl01115_Uart_nodma)
				};

	NX_ASSERT( NUMBER_OF_UART_MODULE > ModuleIndex );

	return	UartInterruptNumber[ModuleIndex];
}

//------------------------------------------------------------------------------
// DMA Interface
//------------------------------------------------------------------------------
/**
 *	@brief		Get DMA peripheral index of UART's Tx
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@return		DMA peripheral index of UART's Tx
 */
U32		NX_UART_GetDMAIndex_Tx( U32 ModuleIndex )
{
	const U32 UartDmaIndexTx[NUMBER_OF_UART_MODULE] =
			{
//				DMAINDEX_WITH_CHANNEL_LIST(UART,UARTTXDMA)
				DMAINDEX_OF_UART0_MODULE_UARTTXDMA,
				DMAINDEX_OF_pl01115_Uart_modem_MODULE_UARTTXDMA,
				DMAINDEX_OF_UART1_MODULE_UARTTXDMA
			};

	NX_ASSERT( NUMBER_OF_UART_MODULE > ModuleIndex );

	return UartDmaIndexTx[ModuleIndex];
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get DMA peripheral index of UART's Rx
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@return		DMA peripheral index of UART's Rx
 */
U32		NX_UART_GetDMAIndex_Rx( U32 ModuleIndex )
{
	const U32 UartDmaIndexRx[NUMBER_OF_UART_MODULE] =
			{
//				DMAINDEX_WITH_CHANNEL_LIST(UART,UARTRXDMA)

				DMAINDEX_OF_UART0_MODULE_UARTRXDMA,
				DMAINDEX_OF_pl01115_Uart_modem_MODULE_UARTRXDMA,
				DMAINDEX_OF_UART1_MODULE_UARTRXDMA
			};

	NX_ASSERT( NUMBER_OF_UART_MODULE > ModuleIndex );

	return UartDmaIndexRx[ModuleIndex];
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get DMA bus width of UART
 *	@param[in]	ModuleIndex		An index of module ( 0 ~ x ).
 *	@return		DMA bus width of UART
 */
U32		NX_UART_GetDMABusWidth( U32 ModuleIndex )
{
	NX_ASSERT( NUMBER_OF_UART_MODULE > ModuleIndex );

	return 8;
}
#if 0
//------------------------------------------------------------------------------
/**	@name		NX_UART_EnablePAD
 *	@brief		UART Pad Enable Function.
 *				[kor] SwitchDevice를 통해 해당 모듈의 PAD를 enable 해줍니다. SOC RTL 테스트환경을
 				기준으로 작성되었습니다.
 *	@param[in]	ModuleIndex		an index of module.
 *	@return		an interrupt number which has the most priority of pended interrupts. \n
 *				This value is one of @ref NX_UART_INT enum.
 *				If there's no interrupt which is pended and unmasked, it returns -1.
 */
void NX_UART_EnablePAD( U32 ModuleIndex, U32 ModeIndex )
{
	U32 i;
	const U32 PADNumber[3][NUMBER_OF_UART_MODULE] =	{
	     { PADINDEX_WITH_CHANNEL_LIST( UART, UARTRXD ) },
	     { PADINDEX_WITH_CHANNEL_LIST( UART, UARTTXD ) },
	     { PADINDEX_WITH_CHANNEL_LIST( UART, SMCAYEN ) }
	};
	NX_CASSERT( NUMBER_OF_UART_MODULE == (sizeof(PADNumber[0])/sizeof(PADNumber[0][0])) );
	NX_ASSERT( NUMBER_OF_UART_MODULE > ModuleIndex );

	for(i=0; i<sizeof( PADNumber)/sizeof(PADNumber[0]); i++)
	{
		NX_SWITCHDEVICE_Set_Switch_Enable ( PADNumber[i][ModuleIndex] );
		NX_PAD_SetPadFunctionEnable       ( PADNumber[i][ModuleIndex], ModeIndex );
	}
}
#endif
//--------------------------------------------------------------------------
// Configuration operations
//--------------------------------------------------------------------------
//@{
void	NX_UART_SetTransmitMode( U32 ModuleIndex, U8 mode )
{
	const U32 TRMODE_BITPOS	= 2;
	const U32 TRMODE_MASK	= (3<<TRMODE_BITPOS);
	register U32 temp;

	NX_ASSERT( NUMBER_OF_UART_MODULE > ModuleIndex );
	NX_ASSERT( CNULL != __g_ModuleVariables[ModuleIndex].pRegister );

	temp = ReadIODW(&__g_ModuleVariables[ModuleIndex].pRegister->UCON);
	temp &= ~TRMODE_MASK;
	temp |= (mode<<TRMODE_BITPOS);

	WriteIODW(&__g_ModuleVariables[ModuleIndex].pRegister->UCON, temp);
}

U8	NX_UART_GetTransmitMode( U32 ModuleIndex )
{
	const U32 TRMODE_BITPOS	= 2;
	const U32 TRMODE_MASK	= (3<<TRMODE_BITPOS);

	NX_ASSERT( NUMBER_OF_UART_MODULE > ModuleIndex );
	NX_ASSERT( CNULL != __g_ModuleVariables[ModuleIndex].pRegister );

	return (U8)(( ReadIODW(&__g_ModuleVariables[ModuleIndex].pRegister->UCON) & TRMODE_MASK ) >> TRMODE_BITPOS );
}

void	NX_UART_SetRecieveMode( U32 ModuleIndex, U8 mode )
{
	const U32 RCMODE_BITPOS	= 0;
	const U32 RCMODE_MASK	= (3<<RCMODE_BITPOS);
	register U32 temp;

	NX_ASSERT( NUMBER_OF_UART_MODULE > ModuleIndex );
	NX_ASSERT( CNULL != __g_ModuleVariables[ModuleIndex].pRegister );

	temp = ReadIODW(&__g_ModuleVariables[ModuleIndex].pRegister->UCON);
	temp &= ~RCMODE_MASK;
	temp |= (mode<<RCMODE_BITPOS);

	WriteIODW(&__g_ModuleVariables[ModuleIndex].pRegister->UCON, temp);
}

U8		NX_UART_GetRecieveMode( U32 ModuleIndex )
{
	const U32 RCMODE_BITPOS	= 0;
	const U32 RCMODE_MASK	= (3<<RCMODE_BITPOS);

	NX_ASSERT( NUMBER_OF_UART_MODULE > ModuleIndex );
	NX_ASSERT( CNULL != __g_ModuleVariables[ModuleIndex].pRegister );

	return (U8)(( ReadIODW(&__g_ModuleVariables[ModuleIndex].pRegister->UCON) & RCMODE_MASK ) >> RCMODE_BITPOS );
}


CBOOL	NX_UART_GetTransmitterEmpty( U32 ModuleIndex )
{
	const U32 TREMPTY_BITPOS	= 1;
	const U32 TREMPTY_MASK	= (1<<TREMPTY_BITPOS);

	NX_ASSERT( NUMBER_OF_UART_MODULE > ModuleIndex );
	NX_ASSERT( CNULL != __g_ModuleVariables[ModuleIndex].pRegister );

	return (CBOOL)(( ReadIODW(&__g_ModuleVariables[ModuleIndex].pRegister->USTATUS) & TREMPTY_MASK ) >> TREMPTY_BITPOS );
}

CBOOL	NX_UART_GetTransmitBufferEmpty( U32 ModuleIndex )
{
	const U32 TRBEMPTY_BITPOS	= 1;
	const U32 TRBEMPTY_MASK	= (2<<TRBEMPTY_BITPOS);

	NX_ASSERT( NUMBER_OF_UART_MODULE > ModuleIndex );
	NX_ASSERT( CNULL != __g_ModuleVariables[ModuleIndex].pRegister );

	return (CBOOL)(( ReadIODW(&__g_ModuleVariables[ModuleIndex].pRegister->USTATUS) & TRBEMPTY_MASK ) >> TRBEMPTY_BITPOS );
}

U8		NX_UART_GetRxFIFOCount( U32 ModuleIndex )
{
	const U32 RXFIFOCNT_BITPOS	= 0;
	const U32 RXFIFOCNT_MASK	= (0xff<<RXFIFOCNT_BITPOS);

	NX_ASSERT( NUMBER_OF_UART_MODULE > ModuleIndex );
	NX_ASSERT( CNULL != __g_ModuleVariables[ModuleIndex].pRegister );

	return (U8)(( ReadIODW(&__g_ModuleVariables[ModuleIndex].pRegister->FSTATUS) & RXFIFOCNT_MASK ) >> RXFIFOCNT_BITPOS );
}

//@}

//--------------------------------------------------------------------------
/// @name	Register handling
//--------------------------------------------------------------------------
//@{


//@}


