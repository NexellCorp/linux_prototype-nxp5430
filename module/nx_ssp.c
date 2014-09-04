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
//	Module		: NK3 SPI module
//	File		: nx_ssp.c
//	Description	:
//	Author		:
//	History		:
// @choyk 2013/08/14 : NK3 SPI prototype
//------------------------------------------------------------------------------


#include <nx_chip.h>
#include <nx_ssp.h>

static	struct
{
	struct NX_SSP_RegisterSet *pRegister;
} __g_ModuleVariables[NUMBER_OF_SSP_MODULE] = { {CNULL,}, };


//------------------------------------------------------------------------------
//	Module Interface
//------------------------------------------------------------------------------

/**
 *	@brief	Initialize of prototype enviroment & local variables.
 *	@return \b CTRUE	indicate that Initialize is successed.\n
 *			\b CFALSE	indicate that Initialize is failed.
 */
CBOOL	NX_SSP_Initialize( void )
{
	static CBOOL bInit = CFALSE;
	U32 i;

	if( CFALSE == bInit )
	{
		for(i=0; i<NUMBER_OF_SSP_MODULE; i++)
		{
			__g_ModuleVariables[i].pRegister = CNULL;
		}
		bInit = CTRUE;
	}
	return CTRUE;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get number of modules in the chip.
 *	@return		Module's number.
 */
U32		NX_SSP_GetNumberOfModule( void )
{
	return NUMBER_OF_SSP_MODULE;
}

//------------------------------------------------------------------------------
// Basic Interface
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/**
 *	@brief		Get module's physical address.
 *	@return		Module's physical address
 */
U32		NX_SSP_GetPhysicalAddress( U32 ModuleIndex )
{
	static const U32 PhysicalAddr[] = { PHY_BASEADDR_LIST( SSP ) }; // PHY_BASEADDR_SSPx_MODULE

	NX_CASSERT( NUMBER_OF_SSP_MODULE == (sizeof(PhysicalAddr)/sizeof(PhysicalAddr[0])) );
	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );

	return (U32)PhysicalAddr[ModuleIndex];
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get a size, in byte, of register set.
 *	@return		Size of module's register set.
 */
U32		NX_SSP_GetSizeOfRegisterSet( void )
{
	return sizeof( struct NX_SSP_RegisterSet );
}

//------------------------------------------------------------------------------
/**
 *	@brief		Set a base address of register set.
 *	@param[in]	BaseAddress Module's base address
 *	@return		None.
 */
void	NX_SSP_SetBaseAddress( U32 ModuleIndex, U32 BaseAddress )
{

	NX_ASSERT( CNULL != BaseAddress );
	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );

	__g_ModuleVariables[ModuleIndex].pRegister = (struct NX_SSP_RegisterSet *)BaseAddress;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get a base address of register set
 *	@return		Module's base address.
 */
U32		NX_SSP_GetBaseAddress( U32 ModuleIndex )
{
	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );

	return (U32)__g_ModuleVariables[ModuleIndex].pRegister;
}


//------------------------------------------------------------------------------
/**
 *	@brief		Initialize selected modules with default value.
 *	@return		\b CTRUE	indicate that Initialize is successed. \n
 *				\b CFALSE	indicate that Initialize is failed.
 */
CBOOL	NX_SSP_OpenModule( U32 ModuleIndex )
{
	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );
	return CTRUE;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Deinitialize selected module to the proper stage.
 *	@return		\b CTRUE	indicate that Deinitialize is successed. \n
 *				\b CFALSE	indicate that Deinitialize is failed.
 */
CBOOL	NX_SSP_CloseModule( U32 ModuleIndex )
{
	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );
	return CTRUE;
}

//------------------------------------------------------------------------------
/**
 *	@name		NX_SSP_CheckBusy
 *	@brief		Indicates whether the selected modules is busy or not.
 *  this function only can use after transaction .
 *	@return		\b CTRUE	indicate that Module is Busy. \n
 *				\b CFALSE	indicate that Module is NOT Busy.
 */
CBOOL	NX_SSP_CheckBusy( U32 ModuleIndex )
{
	U32 regvalue;
	U32 TX_FIFO_LVL, RX_FIFO_LVL, TX_DONE;

	register struct NX_SSP_RegisterSet* pRegister;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	regvalue = ReadIODW(&pRegister->SPI_STATUS);
	RX_FIFO_LVL = (regvalue >> 15) & 0x1FF ;
	TX_FIFO_LVL = (regvalue >>  6) & 0x1FF ;
	TX_DONE = (regvalue >> 25) & 0x1 ;

	if	(	(0 == RX_FIFO_LVL) &&
			(0 == TX_FIFO_LVL) &&
			(1 == TX_DONE)
		)
	{
		return CFALSE;
	}
	return CTRUE;
}


//------------------------------------------------------------------------------
// Interrupt Interface
//------------------------------------------------------------------------------
/**
 *	@brief		Get an interrupt number for the interrupt controller.
 *	@param[in]	ModuleIndex		an index of module.
 *	@return		An interrupt number.
 *	@remark		Return value can be used for the interrupt controller module's
 *				functions.
 */
U32		NX_SSP_GetInterruptNumber( U32 ModuleIndex )
{
	const U32 INTNumber[NUMBER_OF_SSP_MODULE] =
	{
		INTNUM_LIST(SSP)
	};

	NX_CASSERT( NUMBER_OF_SSP_MODULE == (sizeof(INTNumber)/sizeof(INTNumber[0])) );
	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );
	NX_ASSERT( INTNumber[ModuleIndex] >= 0 );

	return INTNumber[ModuleIndex];
}


//------------------------------------------------------------------------------
/**
 *	@brief		Set a specified interrupt to be enable or disable.
 *	@param[in]	ModuleIndex		Module Index Number .
 *	@param[in]	IntNum			Interrupt Index Number .
 *	@param[in]	Enable	\b CTRUE	indicate that Interrupt Enable. \n
 *						\b CFALSE	indicate that Interrupt Disable.
 *	@return		None.
 */

//------------------------------------------------------------------------------
void	NX_SSP_SetInterruptEnable		( U32 ModuleIndex, NX_SSP_INTR_MASK IntNum, CBOOL Enable )
{
	register struct NX_SSP_RegisterSet *pRegister;
	U32			regvalue;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );
	NX_ASSERT( NX_SSP_INTR_MAXNUMBER  > IntNum );
	NX_ASSERT( (1 == Enable) || (0 == Enable) );

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	regvalue = ReadIODW(&pRegister->SPI_INT_EN);

	if( CTRUE == Enable )
	{
		regvalue |= ( 1UL << IntNum );
	}
	else
	{
		regvalue &= ~( 1UL << IntNum );
	}

	WriteIODW(&pRegister->SPI_INT_EN, regvalue);
}

//------------------------------------------------------------------------------
/**
 *	@brief		Indicates whether a specified interrupt is enabled or disabled.
 *	@param[in]	ModuleIndex		an index of module.
 *	@param[in]	IntNum			Interrupt Index Number .
 *	@return		CTRUE	indicates an interrupt specified by @a IntNum is enabled.\n
 *				CFALSE	indicates an interrupt specified by @a IntNum is disabled.
 */
CBOOL	NX_SSP_GetInterruptEnable		( U32 ModuleIndex, NX_SSP_INTR_MASK IntNum )
{
	register struct NX_SSP_RegisterSet *pRegister;
	U32			regvalue;


	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );
	NX_ASSERT( NX_SSP_INTR_MAXNUMBER > IntNum );

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	regvalue = ReadIODW(&pRegister->SPI_INT_EN);

	if( 0 != (( 1UL << IntNum ) & regvalue) )
	{
		return CFALSE;
	}
	return CTRUE;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Indicates whether a specified interrupt is pended or not.
 *	@param[in]	ModuleIndex		an index of module.
 *	@param[in]	ChannelIndex	Interrupt Index Number .
 *	@return		CTRUE	indicates an interrupt specified by @a IntNum is pended.\n
 *				CFALSE	indicates an interrupt specified by @a IntNum is not pended.
 *	@remark		The interrupt pending status are logged regardless of interrupt
 *				enable status. Therefore the return value can be CTRUE even
 *				though the specified interrupt has been disabled.
 */
CBOOL	NX_SSP_GetInterruptPending		( U32 ModuleIndex , NX_SSP_INTR_MASK IntNum )
{
	register struct NX_SSP_RegisterSet *pRegister;
	U32			irq_status;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );
	NX_ASSERT( NX_SSP_INTR_MAXNUMBER > IntNum );

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	irq_status = ReadIODW(&pRegister->SPI_STATUS);

	if( 0 != ( ( 1UL << IntNum ) & irq_status) )
	{
		return CTRUE;
	}
	return CFALSE;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Clear a pending state of specified interrupt.
 *	@param[in]	ModuleIndex		an index of module.
 *	@param[in]	ChannelIndex	Interrupt Index Number .
 *	@return		None.
 */
void	NX_SSP_ClearInterruptPending	( U32 ModuleIndex, NX_SSP_INTR_MASK IntNum )
{
	register struct NX_SSP_RegisterSet *pRegister;
	U32			irq_pending ;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );
	NX_ASSERT( NX_SSP_INTR_MAXNUMBER > IntNum );

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	if( IntNum == TRAILING   ) irq_pending = 1<<0;
	if( IntNum == RX_OVERRUN ) irq_pending = 1<<1;
	if( IntNum == TX_UNDERRUN) irq_pending = 1<<2;
	if( IntNum == TX_OVERRUN ) irq_pending = 1<<3;
	if( IntNum == RX_UNDERRUN) irq_pending = 1<<4;

	WriteIODW(&pRegister->PENDING_CLR_REG, irq_pending);
}

//------------------------------------------------------------------------------
/**
 *	@brief		Set all interrupts to be enabled or disabled.
 *	@param[in]	ModuleIndex		an index of module.
 *	@param[in]	bEnb			Set it as CTRUE to enable all interrupts. \n
 *								Set it as CFALSE to disable all interrupts.
 *	@return		None.
 */
void	NX_SSP_SetInterruptEnableAll	( U32 ModuleIndex, CBOOL Enable )
{
	register struct NX_SSP_RegisterSet *pRegister;
	U32			new_irq_mask;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );
	NX_ASSERT( (1 == Enable) || (0 == Enable) );

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	if( CTRUE == Enable )
	{
		new_irq_mask = (0x7F); // All
	}
	else
	{
		new_irq_mask = (0x00);
	}

	WriteIODW(&pRegister->SPI_INT_EN, new_irq_mask);
}

//------------------------------------------------------------------------------
/**
 *	@brief		Indicates whether some of interrupts are enabled or not.
 *	@param[in]	ModuleIndex		an index of module.
 *	@return		CTURE	indicates there's interrupts which are enabled.\n
 *				CFALSE	indicates there's no interrupt which are enabled.
 */
CBOOL	NX_SSP_GetInterruptEnableAll	( U32 ModuleIndex )
{
	register struct NX_SSP_RegisterSet *pRegister;
	U32			irq_mask;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	irq_mask = ReadIODW(&pRegister->SPI_INT_EN);

	if( 0 != ((0x7f) & irq_mask) )
	{
		return CTRUE;
	}
	return CFALSE;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Indicates whether some of interrupts are pended or not.
 *	@param[in]	ModuleIndex		an index of module.
 *	@return		CTURE	indicates there's interrupts which are pended.\n
 *				CFALSE	indicates there's no interrupt which are pended.
 */
CBOOL	NX_SSP_GetInterruptPendingAll	( U32 ModuleIndex )
{
	register struct NX_SSP_RegisterSet *pRegister;
	U32			masked_irq_status;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	masked_irq_status = ReadIODW(&pRegister->SPI_STATUS);

	if( 0 != ( 0x3F & masked_irq_status) )
	{
		return CTRUE;
	}
	return CFALSE;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Clear pending state of all interrupts.
 *	@param[in]	ModuleIndex		an index of module.
 *	@return		None.
 */
void	NX_SSP_ClearInterruptPendingAll	( U32 ModuleIndex )
{
	register struct NX_SSP_RegisterSet *pRegister;
	U32			irq_pending = 0x1F;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	WriteIODW(&pRegister->PENDING_CLR_REG, irq_pending);
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get an interrupt number which has the most prority of pended interrupts.
 *	@param[in]	ModuleIndex		an index of module.
 *	@return		an interrupt number which has the most priority of pended interrupts. \n
 *				This value is one of @ref NX_SSP_INT enum.
 *				If there's no interrupt which is pended and unmasked, it returns -1.
 */
NX_SSP_INTR_MASK	NX_SSP_GetInterruptPendingNumber( U32 ModuleIndex )	// -1 if None
{
	register struct NX_SSP_RegisterSet *pRegister;
	U32			irq_status;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	irq_status = ReadIODW(&pRegister->SPI_STATUS);
	if( (irq_status >> 0) & 0x01 ) return TXFIFO_RDY;
	if( (irq_status >> 1) & 0x01 ) return RXFIFO_RDY;
	if( (irq_status >> 2) & 0x01 ) return TX_UNDERRUN;
	if( (irq_status >> 3) & 0x01 ) return TX_OVERRUN;
	if( (irq_status >> 4) & 0x01 ) return RX_UNDERRUN;
	if( (irq_status >> 5) & 0x01 ) return RX_OVERRUN;
	if( (irq_status >> 6) & 0x01 ) return TRAILING;
	return -1; // no interrupt pending now
}
#if 0
//------------------------------------------------------------------------------
/**	@name		NX_SSP_EnablePAD
 *	@brief		SSP Pad Enable Function.
 *				for GPIO Alt & SwitchDevice Enable pin Config
 *	@param[in]	ModuleIndex		an index of module.
 *	@return		an interrupt number which has the most priority of pended interrupts. \n
 *				This value is one of @ref NX_SSP_INT enum.
 *				If there's no interrupt which is pended and unmasked, it returns -1.
 */
void NX_SSP_EnablePAD( U32 ModuleIndex )
{
	U32 i;
	const U32 PADNumber[4][NUMBER_OF_SSP_MODULE] =	{
		 { PADINDEX_WITH_CHANNEL_LIST( SSP, SSPCLK_IO ) },
	     { PADINDEX_WITH_CHANNEL_LIST( SSP, SSPFSS ) },
	     { PADINDEX_WITH_CHANNEL_LIST( SSP, SSPRXD ) },
	     { PADINDEX_WITH_CHANNEL_LIST( SSP, SSPTXD ) }
	};
	NX_CASSERT( NUMBER_OF_SSP_MODULE == (sizeof(PADNumber[0])/sizeof(PADNumber[0][0])) );
	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );

	for(i=0; i<sizeof( PADNumber)/sizeof(PADNumber[0]); i++)
	{
		NX_SWITCHDEVICE_Set_Switch_Enable ( PADNumber[i][ModuleIndex] );
		//@todo : GPIO Alt Select 부분 추가.
		#ifdef NUMBER_OF_GPIO_MODULE
		NX_GPIO_SetPadFunctionEnable ( PADNumber[i][ModuleIndex] );
		// SSP의 PAD를 빠르게..
		#endif
	}
}
#endif



//------------------------------------------------------------------------------
// DMA Interface
//------------------------------------------------------------------------------
/**
 *	@brief		Get DMA peripheral index for SSP/SPI Tx.
 *	@param[in]	ModuleIndex		an index of module.
 *	@return		DMA peripheral index for SSP/SPI Tx.
 */
U32		NX_SSP_GetDMAIndex_Tx( U32 ModuleIndex )
{
	const U32	SspDmaIndexTx[NUMBER_OF_SSP_MODULE] =
		{ DMAINDEX_WITH_CHANNEL_LIST(SSP,SSPTXDMA)  };

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );

	return SspDmaIndexTx[ModuleIndex];
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get DMA peripheral index for SSP/SPI Rx.
 *	@param[in]	ModuleIndex		an index of module.
 *	@return		DMA peripheral index for SSP/SPI Rx.
 */
U32		NX_SSP_GetDMAIndex_Rx( U32 ModuleIndex )
{
	const U32	SspDmaIndexRx[NUMBER_OF_SSP_MODULE] =
		{ DMAINDEX_WITH_CHANNEL_LIST(SSP,SSPRXDMA)  };

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );

	return SspDmaIndexRx[ModuleIndex];
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get DMA bus width of SSP/SPI.
 *	@param[in]	ModuleIndex		an index of module.
 *	@return		DMA bus width of SSP/SPI.\n.
 *				It returns 8 in case of the data bit width is between 1 and 8,\n
 *				16 in case of the data bit width is between 9 and 16.\n.
 *	@remark		You have to call NX_SSP_SetBitWidth() to set the data bit
 *				width properly before using	this function.
 */
U32		NX_SSP_GetDMABusWidth( U32 ModuleIndex )
{
	U32	DSS;
	register struct NX_SSP_RegisterSet *pRegister;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );
	DSS = (U32)((ReadIODW(&pRegister->MODE_CFG)>>17) & 0x03);

	if( DSS == 0 )   	{ return  8; 	}
	if( DSS == 1 )   	{ return 16; 	}
	if( DSS == 2 )   	{ return 32; 	}

	NX_ASSERT(DSS != 3);
}

//------------------------------------------------------------------------------
///	@name	Clock Control Interface
// NK3 SPI has only 2x clock divider.
// SCLK_SPI must be divided in System Controller for operation .
//------------------------------------------------------------------------------

//--------------------------------------------------------------------------
/// @name Configuration Function
//------------------------------------------------------------------------------
/**	@name		NX_SSP_SetAllDMAMode
 *	@brief		Set Transmit DMA Mode
 *	@param[in]	ModuleIndex		an index of module.
 *	@param[in]	Enable	\b CTRUE indicate that Transmit/Receive DMA Enable. \n
 *						\b CFALSE indicate that Transmit/Receive DMA Disable. \n.
 *	@return		None.
**/
void	NX_SSP_SetDMATransferMode( U32 ModuleIndex, CBOOL Enable )
{
	U32 regvalue;
	register struct NX_SSP_RegisterSet *pRegister;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );
	NX_ASSERT( 1 == Enable || 0 == Enable);

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	regvalue = ReadIODW(&pRegister->MODE_CFG);
	if( CTRUE == Enable )
	{
		regvalue |= (3UL<<1);
	}
	else
	{
		regvalue &= (~(3UL<<1));
	}
	WriteIODW(&pRegister->MODE_CFG, regvalue);
}

//------------------------------------------------------------------------------
/**	@name		NX_SSP_GetDMATransferMode
 *	@brief		Get All DMA Mode
 *	@param[in]	ModuleIndex		an index of module.
 *	@return		CTURE  indicate that All DMA Enabled
 				CFALSE indicate that All DMA Disabled
**/
CBOOL	NX_SSP_GetDMATransferMode( U32 ModuleIndex )
{
	U32 regvalue;
	register struct NX_SSP_RegisterSet *pRegister;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	regvalue = ReadIODW(&pRegister->MODE_CFG);
	if( 0 != ( (3UL<<1) & regvalue ) )
	{
		return CTRUE;
	}
	return CFALSE;
}


/**	@name		NX_SSP_SetTransmitDMAMode
 *	@brief		Set Transmit DMA Mode
 *	@param[in]	ModuleIndex		an index of module.
 *	@param[in]	Enable	\b CTRUE indicate that Transmit DMA Enable. \n
 *						\b CFALSE indicate that Transmit DMA Disable. \n.
 *	@return		None.
**/
void	NX_SSP_SetDMATransmitMode( U32 ModuleIndex, CBOOL Enable )
{
	U32 regvalue;
	register struct NX_SSP_RegisterSet *pRegister;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );
	NX_ASSERT( 1 == Enable || 0 == Enable);

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	regvalue = ReadIODW(&pRegister->MODE_CFG);
	if( CTRUE == Enable )
	{
		regvalue |= (1UL<<1);
	}
	else
	{
		regvalue &= (~(1UL<<1));
	}
	WriteIODW(&pRegister->MODE_CFG, regvalue);
}

//------------------------------------------------------------------------------
/**	@name		NX_SSP_GetTransmitDMAMode
 *	@brief		Get Transmit DMA Mode
 *	@param[in]	ModuleIndex		an index of module.
 *	@return		CTURE  indicate that Transmit DMA Enabled
 				CFALSE indicate that Transmit DMA Disabled
**/
CBOOL	NX_SSP_GetDMATransmitMode( U32 ModuleIndex )
{
	U32 regvalue;
	register struct NX_SSP_RegisterSet *pRegister;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	regvalue = ReadIODW(&pRegister->MODE_CFG);
	if( 0 != ( (1UL<<1) & regvalue ) )
	{
		return CTRUE;
	}
	return CFALSE;
}

//------------------------------------------------------------------------------
/**	@name		NX_SSP_SetReceiveDMAMode
 *	@brief		Set Receive DMA Mode
 *	@param[in]	ModuleIndex		an index of module.
 *	@param[in]	Enable	\b CTRUE  indicate that Receive DMA Enable. \n
 *						\b CFALSE indicate that Receive DMA Disable. \n.
 *	@return		None.
**/
void	NX_SSP_SetDMAReceiveMode( U32 ModuleIndex, CBOOL Enable )
{
	U32 regvalue;
	register struct NX_SSP_RegisterSet *pRegister;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );
	NX_ASSERT( 1 == Enable || 0 == Enable);

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	regvalue = ReadIODW(&pRegister->MODE_CFG);
	if( CTRUE == Enable )
	{
		regvalue |= (1UL<<2);
	}
	else
	{
		regvalue &= (~(1UL<<2));
	}
	WriteIODW(&pRegister->MODE_CFG, regvalue);
}

//------------------------------------------------------------------------------
/**	@name		NX_SSP_GetReceiveDMAMode
 *	@brief		Get Receive DMA Mode
 *	@param[in]	ModuleIndex		an index of module.
 *	@return		CTURE  indicate that Receive DMA Enabled
 				CFALSE indicate that Receive DMA Disabled
**/
CBOOL	NX_SSP_GetDMAReceiveMode( U32 ModuleIndex )
{
	U32 regvalue;
	register struct NX_SSP_RegisterSet *pRegister;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	regvalue = ReadIODW(&pRegister->MODE_CFG);
	if( 0 != ( (1UL<<2) & regvalue ) )
	{
		return CTRUE;
	}
	return CFALSE;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Set Data bit width
 *	@param[in]	ModuleIndex		an index of module.
 *	@param[in]	bitWidth	Value of Data Bit Width( 8, 16, 32 )
 *	@return		None.
 *	@remarks	NX_SSP_SetBitWidth() must invoke before NX_SSP_GetDMABusWidth()
 *	@code
 *				NX_SSP_SetBitWidth();
 *				NX_SSP_GetDMABusWidth();
 *	@endcode
 */
void	NX_SSP_SetBitWidth( U32 ModuleIndex, U32 bitWidth )
{
	register struct NX_SSP_RegisterSet *pRegister;
	U32		old_sspcr0;
	U32		new_sspcr0;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );
	NX_ASSERT( (bitWidth == 32) || (bitWidth == 16) || (bitWidth == 8) );

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	old_sspcr0 = ReadIODW(&pRegister->MODE_CFG);
	// BUS_WIDTH
	if( bitWidth ==  8 ) new_sspcr0 = ( old_sspcr0 & (~(0x03<<17)) ) | (0<<17) ;
	if( bitWidth == 16 ) new_sspcr0 = ( old_sspcr0 & (~(0x03<<17)) ) | (1<<17) ;
	if( bitWidth == 32 ) new_sspcr0 = ( old_sspcr0 & (~(0x03<<17)) ) | (2<<17) ;

	// CH_WIDTH
	if( bitWidth ==  8 ) new_sspcr0 = ( new_sspcr0 & (~(0x03<<29)) ) | (0<<29) ;
	if( bitWidth == 16 ) new_sspcr0 = ( new_sspcr0 & (~(0x03<<29)) ) | (1<<29) ;
	if( bitWidth == 32 ) new_sspcr0 = ( new_sspcr0 & (~(0x03<<29)) ) | (2<<29) ;

	WriteIODW(&pRegister->MODE_CFG, new_sspcr0);
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get Data Bit Width
 *	@param[in]	ModuleIndex		an index of module.
 *	@return		Data Bit Width( 8, 16, 32 )
 *	@see
 */
U32		NX_SSP_GetBitWidth( U32 ModuleIndex )
{
	register struct NX_SSP_RegisterSet *pRegister;
	U32		old_sspcr0;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	old_sspcr0 = ReadIODW(&pRegister->MODE_CFG);

	if( 0 == ((old_sspcr0 >> 17)&0x03) ) return  8;
	if( 1 == ((old_sspcr0 >> 17)&0x03) ) return 16;
	if( 2 == ((old_sspcr0 >> 17)&0x03) ) return 32;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Set Operation Mode ( Master or Slave )
 *	@param[in]	ModuleIndex		an index of module.
 *	@param[in]	bSlave	\b CTRIE indicate that Slave mode enable. \n
 *						\b CFALSE indicate that Master mode enable.
 *	@return		None.
 */
void	NX_SSP_SetSlaveMode( U32 ModuleIndex, CBOOL bSlave )
{
	register struct NX_SSP_RegisterSet *pRegister;
	U32		regvalue;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );
	NX_ASSERT( 1 == bSlave || 0 == bSlave);

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	regvalue = ReadIODW(&pRegister->CH_CFG);
	if( CTRUE == bSlave )
	{
		regvalue |= (1UL<<4); // SLAVE
	}
	else
	{
		regvalue &= (~(1UL<<4)); // MASTER
	}

	WriteIODW(&pRegister->CH_CFG, regvalue);
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get Operation Mode ( Master or Slave )
 *	@param[in]	ModuleIndex		an index of module.
 *	@return		\b CTRIE indicate that Slave mode enable. \n
 *				\b CFALSE indicate that Master mode enable.
 */
CBOOL	NX_SSP_GetSlaveMode( U32 ModuleIndex )
{
	register struct NX_SSP_RegisterSet *pRegister;
	U32		regvalue;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	regvalue = ReadIODW(&pRegister->CH_CFG);
	if( 0 != ((1UL<<4) & regvalue) )
	{
		return CFALSE;
	}
	return CTRUE;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Set Polarity of SSPCLK
 *	@param[in]	ModuleIndex		an index of module.
 *	@param[in]	bInvert	\b CTRUE indicate that SSPCLK Invert enable. \n
 *						\b CFALSE indicate that SSPCLK Invert disable. \n
 *	@return		None.
 *				This Function can work Motorola SPI frame format only. otherwise,
 *				ASSERT ERROR will be called
 */
void	NX_SSP_SetClockPolarityInvert( U32 ModuleIndex, CBOOL bInvert )
{
	register struct NX_SSP_RegisterSet *pRegister;
	U32		regvalue;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );
	NX_ASSERT( 1 == bInvert || 0 == bInvert);

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	regvalue = ReadIODW(&pRegister->CH_CFG);

	if( CTRUE == bInvert )
	{
		regvalue |= (1UL<<3);
	}
	else
	{
		regvalue &= (~(1UL<<3));
	}

	WriteIODW(&pRegister->CH_CFG, regvalue);
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get status of SSPCLK's polarity is invert or normal.
 *	@param[in]	ModuleIndex		an index of module.
 *	@return		\b CTRUE	indicate that SSPCLK's polarity is invert. \n
 *				\b CFALSE	indicate that SSPCLK's polarity is normal.
 *				This Function can work Motorola SPI frame format only. otherwise,
 *				ASSERT ERROR will be called
 */
CBOOL	NX_SSP_GetClockPolarityInvert( U32 ModuleIndex )
{
	register struct NX_SSP_RegisterSet *pRegister;
	U32		regvalue;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	regvalue = ReadIODW(&pRegister->CH_CFG);

	if( 0 != ((1UL<<3) &  regvalue) )
	{
		return CTRUE;
	}
	return CFALSE;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Set SPI format
 *	@param[in]	ModuleIndex		an index of module.
 *	@param[in]	format		SPI format ( NX_SSP_FORMAT_A[0] or NX_SSP_FORMAT_B[1] )
 *	@return		None.
 */
void	NX_SSP_SetSPIFormat( U32 ModuleIndex, NX_SSP_FORMAT format)
{
	register struct NX_SSP_RegisterSet *pRegister;
	U32		regvalue;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );
	NX_ASSERT( (NX_SSP_FORMAT_A == format) || (NX_SSP_FORMAT_B == format) );

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	regvalue = ReadIODW(&pRegister->CH_CFG);

	switch(format)
	{
	case NX_SSP_FORMAT_B:
		regvalue |= (1UL<<2);
		break;
	case NX_SSP_FORMAT_A:
		regvalue &= (~(1UL<<2));
		break;
	default:
		NX_ASSERT( CFALSE ); //"Never Get Here" );
	}

	WriteIODW(&pRegister->CH_CFG, regvalue);
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get SPI format
 *	@param[in]	ModuleIndex		an index of module.
 *	@return		SPI format ( NX_SSP_FORMAT_A or NX_SSP_FORMAT_B )
 */
NX_SSP_FORMAT	NX_SSP_GetSPIFormat( U32 ModuleIndex )
{
	register struct NX_SSP_RegisterSet *pRegister;
	U32		regvalue;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	regvalue = ReadIODW(&pRegister->CH_CFG);

	return  (NX_SSP_FORMAT)(0x01 &  (regvalue>>2) );
}

//--------------------------------------------------------------------------
/// @name Operation Function
//--------------------------------------------------------------------------
//------------------------------------------------------------------------------
/**
 *	@brief		Set SSP/SPI enable or disable.
 *  RX & TX Channel On
 *	@param[in]	ModuleIndex		an index of module.
 *	@param[in]	bEnable		\b CTRUE indicate that SSP/SPI Enable. \n
 *							\b CFALSE indicate that SSP/SPI Disable.
 *	@return		None.
 */
void	NX_SSP_SetEnable( U32 ModuleIndex, CBOOL bEnable )
{
	register struct NX_SSP_RegisterSet *pRegister;
	U32		regvalue;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );
	NX_ASSERT( 1 == bEnable || 0 == bEnable );

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	regvalue = ReadIODW(&pRegister->CH_CFG);

	if( bEnable )
	{
		regvalue |= (3UL<<0);
	}
	else
	{
		regvalue &= (~(3UL<<0));
	}

	WriteIODW(&pRegister->CH_CFG, regvalue);
}

//------------------------------------------------------------------------------
/**
 *	@brief		Get status of SSP/SPI is enabled or disabled.
 *  RX & TX Channel On
 *	@param[in]	ModuleIndex		an index of module.
 *	@return		\b CTRUE	indicate that SSP/SPI is enabled. \n
 *				\b CFALSE	indicate that SSP/SPI is disabled.
 */
CBOOL	NX_SSP_GetEnable( U32 ModuleIndex )
{
	register struct NX_SSP_RegisterSet *pRegister;
	U32		regvalue;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	regvalue = ReadIODW(&pRegister->CH_CFG);

	if( 3 == ((3UL<<0) & regvalue) )
	{
		return CTRUE;
	}
	return CFALSE;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Read Byte Data.
 *				GetData( U32 ModuleIndex, U32 DataWidth ) 를 사용하도록 권장.
 *	@param[in]	ModuleIndex		an index of module.
 *	@return		Byte Data
 */
U8		NX_SSP_GetByte(U32 ModuleIndex)
{
	register struct NX_SSP_RegisterSet *pRegister;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	return (U8)((ReadIODW(&pRegister->SPI_RX_DATA)) & 0xFF);
}

//------------------------------------------------------------------------------
/**
 *	@brief		Read Half Word Data( 2byte ).
 *	@param[in]	ModuleIndex		an index of module.
 *	@return		Half Word Data( 2byte )
 */
U16		NX_SSP_GetHalfWord(U32 ModuleIndex)
{
	register struct NX_SSP_RegisterSet *pRegister;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	return (U16)((ReadIODW(&pRegister->SPI_RX_DATA)) & 0xffff);
}

//------------------------------------------------------------------------------
/**
 *	@brief		Send Byte.
 *				GetData( U32 ModuleIndex, U32 DataWidth ) 를 사용하도록 권장.
 *	@param[in]	ModuleIndex		an index of module.
 *	@param[in]	ByteData		Value of Data ( 0x0 ~ 0xFF )
 *	@return		None.
 */
void	NX_SSP_PutByte(U32 ModuleIndex, U8 ByteData)
{
	register struct NX_SSP_RegisterSet *pRegister;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );
	NX_ASSERT(8 >= NX_SSP_GetBitWidth(ModuleIndex) );

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );


	WriteIODW(&pRegister->SPI_TX_DATA, (U8)ByteData);	//put the byte data
}

//------------------------------------------------------------------------------
/**
 *	@brief		Send Half Word( 2byte ).
 *	@param[in]	ModuleIndex		an index of module.
 *	@param[in]	HalfWordData	Value of Data ( 0x0 ~ 0xFFFF )
 *	@return		None.
 */
void	NX_SSP_PutHalfWord(U32 ModuleIndex, U16 HalfWordData)
{
	register struct NX_SSP_RegisterSet *pRegister;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );
	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	NX_ASSERT(9 <= NX_SSP_GetBitWidth(ModuleIndex) );

	WriteIODW(&pRegister->SPI_TX_DATA, (U16)HalfWordData);	//put the byte data
}


//--------------------------------------------------------------------------
/// @name FIFO State Check Function
/// @see also	Status Register, SSPSR
//--------------------------------------------------------------------------

//------------------------------------------------------------------------------
/**
 *	@brief		Check Tx FIFO is Empty or Not
 *	@param[in]	ModuleIndex		an index of module.
 *	@return		\b CTRUE Indicate that FIFO Empty.\n
 *				\b CFALSE Indicate that FIFO NOT Empty
 */
CBOOL	NX_SSP_IsTxFIFOEmpty(U32 ModuleIndex)
{
	register struct NX_SSP_RegisterSet *pRegister;
	U32	TX_FIFO_LVL;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	TX_FIFO_LVL = (ReadIODW(&pRegister->SPI_STATUS)>>6) & 0xFF;

	if( 0 == (TX_FIFO_LVL) )
	{
		return CTRUE;
	}
	else
	{
		return CFALSE;
	}
}

U32	NX_SSP_GetTxFIFOLVL(U32 ModuleIndex)
{
	register struct NX_SSP_RegisterSet *pRegister;
	U32	TX_FIFO_LVL;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	return (ReadIODW(&pRegister->SPI_STATUS)>>6) & 0xFF;
}

//------------------------------------------------------------------------------
/**
 *	@brief		Check Tx FIFO is Full or Not
 *	@param[in]	ModuleIndex		an index of module.
 *	@return		\b CTRUE	Indicate that FIFO Full.\n
 *				\b CFALSE	Indicate that FIFO NOT Full.
 */
CBOOL	NX_SSP_IsTxFIFOFull(U32 ModuleIndex)
{
	register struct NX_SSP_RegisterSet *pRegister;
	U32	TX_FIFO_LVL;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	TX_FIFO_LVL = (ReadIODW(&pRegister->SPI_STATUS)>>6) & 0xFF;

	if( NX_SSP_TX_FIFO_FULL_LVL[ModuleIndex] <= TX_FIFO_LVL )
	{
		return CTRUE;
	}
	else
	{
		return CFALSE;
	}
}


//------------------------------------------------------------------------------
/**
 *	@brief		Check Rx FIFO is Empty or Not
 *	@param[in]	ModuleIndex		an index of module.
 *	@return		\b CTRUE	Indicate that FIFO Empty.\n
 *				\b CFALSE	Indicate that FIFO NOT Empty.
 */
CBOOL	NX_SSP_IsRxFIFOEmpty(U32 ModuleIndex)
{
	register struct NX_SSP_RegisterSet *pRegister;
	U32	RX_FIFO_LVL;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	RX_FIFO_LVL = (ReadIODW(&pRegister->SPI_STATUS)>>15) & 0xFF;

	if( 0 == RX_FIFO_LVL )
	{
		return CTRUE;
	}
	else
	{
		return CFALSE;
	}
}

U32	NX_SSP_GetRxFIFOLVL(U32 ModuleIndex)
{
	register struct NX_SSP_RegisterSet *pRegister;
	U32	RX_FIFO_LVL;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	return (ReadIODW(&pRegister->SPI_STATUS)>>15) & 0xFF;
}



//------------------------------------------------------------------------------
/**
 *	@brief		Check Rx FIFO is Full or Not
 *	@param[in]	ModuleIndex		an index of module.
 *	@return		\b CTRUE	Indicate that FIFO Full.\n
 *				\b CFALSE	Indicate that FIFO NOT Full.
 */
CBOOL	NX_SSP_IsRxFIFOFull(U32 ModuleIndex)
{
	register struct NX_SSP_RegisterSet *pRegister;
	U32	RX_FIFO_LVL;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	RX_FIFO_LVL = (ReadIODW(&pRegister->SPI_STATUS)>>15) & 0xFF;

	if( NX_SSP_RX_FIFO_FULL_LVL[ModuleIndex] <= RX_FIFO_LVL )
	{
		return CFALSE;
	}
	else
	{
		return CTRUE;
	}
}

//------------------------------------------------------------------------------
/**
 *	@brief		Check Tx/Rx is End or Not
 *	@param[in]	ModuleIndex		an index of module.
 *	@return		\b CTRUE	Indicate that Tx/Rx is End.\n
 *				\b CFALSE	Indicate that Tx/Rx is NOT End.
 *	@remarks	This function is same to NX_SSP_GetInterruptPending(2)
 */
CBOOL	NX_SSP_IsTxRxEnd( U32 ModuleIndex )
{
	return NX_SSP_CheckBusy(ModuleIndex);
}
//------------------------------------------------------------------------------


void	NX_SSP_SetCSMode( U32 ModuleIndex, NX_SSP_CS_MODE Mode )
{
	register struct NX_SSP_RegisterSet *pRegister;
	U32	regval;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	regval = ( ReadIODW(&pRegister->CS_REG) ) & (~(1<<1));
	regval = regval | ((Mode & 0x01)<<1);
	WriteIODW( &pRegister->CS_REG, regval );
}



//==========================================
// additional function for NK3 SSP
//==========================================

void	NX_SSP_ResetFIFO( U32 ModuleIndex )
{
	register struct NX_SSP_RegisterSet *pRegister;
	U32	regval;
	U32 sw_rst_regval;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );
	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	regval = ( ReadIODW(&pRegister->CH_CFG) ) & (~(1<<5));

	sw_rst_regval = regval | (1<<5);
	WriteIODW( &pRegister->CH_CFG, sw_rst_regval ); // reset FIFO & state
	WriteIODW( &pRegister->CH_CFG, regval ); // reset leave
}


void	NX_SSP_SetDMABurstSize( U32 ModuleIndex , NX_SSP_DMABurstSize Mode )
{
	register struct NX_SSP_RegisterSet *pRegister;
	U32	regval;
	U32 sw_rst_regval;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );
	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	regval = ( ReadIODW(&pRegister->MODE_CFG) ) & (~(1<<0));

	regval = regval | ( (Mode&1) <<0);
	WriteIODW( &pRegister->MODE_CFG, regval );
}


void	NX_SSP_SetNSSOUT( U32 ModuleIndex, U32 NSSOUT )
{
	register struct NX_SSP_RegisterSet *pRegister;
	U32	regval;
	U32 sw_rst_regval;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );
	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	regval = ( ReadIODW(&pRegister->CS_REG) ) & (~(1<<0));

	regval = regval | ( (NSSOUT&1) <<0);
	WriteIODW( &pRegister->CS_REG, regval );
}

U32 NX_SSP_GetClockNumber (U32 ModuleIndex)
{
    static const U32 CLKGEN_SSPLIST[] = { CLOCKINDEX_LIST( SSP ) };
    NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );

    return (U32)CLKGEN_SSPLIST[ModuleIndex];
}

U32	NX_SSP_GetResetNumber (U32 ModuleIndex, U32 ChannelIndex)
{
    const U32 ResetPinNumber[2][NUMBER_OF_SSP_MODULE] =
    {
        { RESETINDEX_LIST( SSP, PRESETn )},
        { RESETINDEX_LIST( SSP, nSSPRST )},
    };

    return (U32)ResetPinNumber[ChannelIndex][ModuleIndex];
}

//=======================================
// in slave mode, can use HIGHSPEED mode(half TXD delay)
//=======================================
void  NX_SSP_SetHIGHSPEEDMode( U32 ModuleIndex, U32 Enb)
{
	register struct NX_SSP_RegisterSet *pRegister;
	U32	regval;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );

	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	regval = ReadIODW(&pRegister->CH_CFG);
	if( Enb == CFALSE )
	{
		regval = regval & (~(1<<6))	;
	}
	else
	{
		regval = regval | (1<<6) ;
	}
	WriteIODW( &pRegister->CH_CFG, regval );
}

//=======================================
// TX_RDY_LVL, trigger level in INT mode
//=======================================
void  NX_SSP_SetRXRDYLVL( U32 ModuleIndex, U32 RX_RDY_LVL )
{
	register struct NX_SSP_RegisterSet *pRegister;
	U32	regval;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );
	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	regval = ReadIODW(&pRegister->MODE_CFG);
	regval = regval & (~(0x3F << 11));
	regval = regval | (RX_RDY_LVL & 0x3F)<<11;
	WriteIODW( &pRegister->MODE_CFG, regval );
}

void  NX_SSP_SetTXRDYLVL( U32 ModuleIndex, U32 TX_RDY_LVL )
{
	register struct NX_SSP_RegisterSet *pRegister;
	U32	regval;

	NX_ASSERT( NUMBER_OF_SSP_MODULE > ModuleIndex );
	pRegister = __g_ModuleVariables[ModuleIndex].pRegister;
	NX_ASSERT( CNULL != pRegister );

	regval = ReadIODW(&pRegister->MODE_CFG);
	regval = regval & (~(0x3F << 5));
	regval = regval | (TX_RDY_LVL & 0x3F)<<5;
	WriteIODW( &pRegister->MODE_CFG, regval );
}
