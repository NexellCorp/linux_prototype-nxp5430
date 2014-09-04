#ifndef _NX_UART_H
#define _NX_UART_H

//------------------------------------------------------------------------------
//  includes
//------------------------------------------------------------------------------
#include "nx_prototype.h"

#ifdef	__cplusplus
extern "C"
{
#endif


//------------------------------------------------------------------------------
/// @brief  UART register set structure
//------------------------------------------------------------------------------
struct NX_UART_RegisterSet
{

	volatile U32	LCON	;	// 0x00	// Line Control
	volatile U32	UCON	;	// 0x04	// Control
	volatile U32	FCON	;	// 0x08	// FIFO Control
	volatile U32	MCON	;	// 0x0C	// Modem Control
	volatile U32	USTATUS	;	// 0x10	// Tx/Rx Status
	volatile U32	ESTATUS	;	// 0x14	// Rx Error Status
	volatile U32	FSTATUS	;	// 0x18	// FIFO Status
	volatile U32	MSTATUS	;	// 0x1C	// Modem Status
	volatile U32	THR		;	// 0x20	// Transmit Buffer
	volatile U32	RBR		;	// 0x24	// Recieve Buffer
	volatile U32	BRDR	;	// 0x28	// Baud Rate Driver
	volatile U32	FRACVAL	;	// 0x2C	// Driver Fractional Value
	volatile U32	INTP	;	// 0x30	// Instrrupt Pending
	volatile U32	INTSP	;	// 0x34	// Instrrupt Source
	volatile U32	INTM	;	// 0x38	// Instrrupt Mask
};

//---------------- LCON enum ----------------//
typedef enum
{
	NX_UART_SIGNAL_MODE_NORMAL		= 0UL,
	NX_UART_SIGNAL_MODE_INFRARED	= 1UL
}NX_UART_SIGNAL_MODE;

typedef enum
{
	NX_UART_PARITY_ODD			= 0UL,
	NX_UART_PARITY_EVEN			= 1UL,
	NX_UART_PARITY_FORCED_1		= 2UL,
	NX_UART_PARITY_FORCED_0		= 3UL
}NX_UART_PARITY;

typedef enum
{
	NX_UART_DATA_BIT_5	= 0UL,
	NX_UART_DATA_BIT_6	= 1UL,
	NX_UART_DATA_BIT_7	= 2UL,
	NX_UART_DATA_BIT_8	= 3UL
}NX_UART_DATA_BIT;

//---------------- UCON enum ----------------//
typedef enum
{
	NX_UART_DMA_BURST_SIZE_1	= 0UL,
	NX_UART_DMA_BURST_SIZE_4	= 1UL,
	NX_UART_DMA_BURST_SIZE_8	= 2UL,
	NX_UART_DMA_BURST_SIZE_16	= 3UL
}NX_UART_DMA_BURST_SIZE;

typedef enum
{
	NX_UART_INT_TYPE_PULSE		= 0UL,
	NX_UART_INT_TYPE_LEVEL		= 1UL
}NX_UART_INT_TYPE;

typedef enum
{
	NX_UART_OPMODE_DISABLE	= 0UL,
	NX_UART_OPMODE_POLLING	= 1UL,
	NX_UART_OPMODE_DMA		= 2UL
}NX_UART_OPMODE;

//---------------- FCON enum ----------------//



//---------------- MCON enum ----------------//
typedef enum
{
	NX_UART_AFC_INACTIVATE	= 0UL, 	// High Level
	NX_UART_AFC_ACTIVATE	= 1UL	// Low Level
}NX_UART_AFC;

//---------------- TRSTATE enum ----------------//

typedef enum
{
	NX_UART_DMA_FSM_IDLE		= 0UL,
	NX_UART_DMA_FSM_BURST_REQ	= 1UL,
	NX_UART_DMA_FSM_BURST_ACK	= 2UL,
	NX_UART_DMA_FSM_BURST_NEXT	= 3UL,
	NX_UART_DMA_FSM_SINGLE_REQ	= 4UL,
	NX_UART_DMA_FSM_SINGLE_ACK	= 5UL,
	NX_UART_DMA_FSM_SINGLE_NEXT	= 6UL,
	NX_UART_DMA_FSM_LBURST_REQ	= 7UL,
	NX_UART_DMA_FSM_LBURST_ACK	= 8UL,
	NX_UART_DMA_FSM_LBURST_NEXT	= 9UL,
	NX_UART_DMA_FSM_LSINGLE_ACK	= 10UL
}NX_UART_DMA_FSM;

//---------------- TRSTATE enum ----------------//


//---------------- UINTPn enum ----------------//
typedef enum
{
	NX_UART_INT_RXD		= 0UL,
	NX_UART_INT_ERROR	= 1UL,
	NX_UART_INT_TXD		= 2UL,
	NX_UART_INT_MODEM	= 3UL
}NX_UART_INT;


//---------------- FSTATUS enum ----------------//


//------------------------------------------------------------------------------
/// @name	Module Interface
//@{
CBOOL	NX_UART_Initialize( void );
U32		NX_UART_GetNumberOfModule( void );
//@}

//------------------------------------------------------------------------------
///	@name	Basic Interface
//@{
U32		NX_UART_GetPhysicalAddress( U32 ModuleIndex );

//U32		NX_UART_GetResetNumber( U32 ModuleIndex, U32 ChannelIndex );
U32		NX_UART_GetNumberOfReset( void );
U32		NX_UART_GetSizeOfRegisterSet( void );
void	NX_UART_SetBaseAddress( U32 ModuleIndex, U32 BaseAddress );
U32		NX_UART_GetBaseAddress( U32 ModuleIndex );
CBOOL	NX_UART_OpenModule( U32 ModuleIndex );
CBOOL	NX_UART_CloseModule( U32 ModuleIndex );
CBOOL	NX_UART_CheckBusy( U32 ModuleIndex );
CBOOL	NX_UART_CanPowerDown( U32 ModuleIndex );
//@}

//------------------------------------------------------------------------------
///	@name	clock ,reset Interface
//------------------------------------------------------------------------------
//@{
U32 NX_UART_GetClockNumber ( U32 ModuleIndex );
U32 NX_UART_GetResetNumber ( U32 ModuleIndex );
//@}

//------------------------------------------------------------------------------
///	@name	Interrupt Interface
//@{
U32		NX_UART_GetInterruptNumber( U32 ModuleIndex );
//@}

//------------------------------------------------------------------------------
///	@name	DMA Interface
//@{
U32		NX_UART_GetDMAIndex_Tx( U32 ModuleIndex );
U32		NX_UART_GetDMAIndex_Rx( U32 ModuleIndex );
U32		NX_UART_GetDMABusWidth( U32 ModuleIndex );
//@}

//------------------------------------------------------------------------------
///	@name	UART Pad Enable Function
//@{
//void NX_UART_EnablePAD( U32 ModuleIndex, U32 ModeIndex );
//@}

//--------------------------------------------------------------------------
/// @name	Configuration operations
//--------------------------------------------------------------------------
//@{
//void	NX_UART_Set( U32 ModuleIndex, CBOOL  );
//CBOOL	NX_UART_Get( U32 ModuleIndex );

void	NX_UART_SetTransmitMode( U32 ModuleIndex, U8 mode );
U8		NX_UART_GetTransmitMode( U32 ModuleIndex );

void	NX_UART_SetRecieveMode( U32 ModuleIndex, U8 mode );
U8		NX_UART_GetRecieveMode( U32 ModuleIndex );

CBOOL	NX_UART_GetTransmitterEmpty( U32 ModuleIndex );
CBOOL	NX_UART_GetTransmitBufferEmpty( U32 ModuleIndex );

U8		NX_UART_GetRxFIFOCount( U32 ModuleIndex );




//@}



//@}

#ifdef	__cplusplus
}
#endif

#endif // _NX_UART_H
