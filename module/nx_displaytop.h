//------------------------------------------------------------------------------
//
//	Copyright (C) Nexell Co. 2012
//
//  This confidential and proprietary software may be used only as authorized by a
//  licensing agreement from Nexell Co.
//  The entire notice above must be reproduced on all authorized copies and copies
//  may only be made to the extent permitted by a licensing agreement from Nexell Co.
//
//	Module		:
//	File		: nx_DisplayTop.h
//	Description	:
//	Author		:
//	History		:
//------------------------------------------------------------------------------

#ifndef __NX_DISPLAYTOP_H__
#define __NX_DISPLAYTOP_H__

#include "../base/nx_prototype.h"

#ifdef	__cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
/// @defgroup	DISPLAYTOP
//------------------------------------------------------------------------------

//-----------------
// define submodule's defines
// BaseAddress
// ( (PHY_BASEADDR_DISPLAYTOP_MODULE/0x100000) % 2) ?

//#define NUMBER_OF_DISPLAYTOP_MODULE		1
//#define PHY_BASEADDR_DISPLAYTOP_MODULE		0xC0100000



#define HDMI_ADDR_OFFSET	( ( (PHY_BASEADDR_DISPLAYTOP_MODULE/0x00100000) % 2) ? 0x100000  : 0x000000 )
#define OTHER_ADDR_OFFSET	( ( (PHY_BASEADDR_DISPLAYTOP_MODULE/0x00100000) % 2) ? 0x000000  : 0x100000 )

#define PHY_BASEADDR_DISPLAYTOP_MODULE_OFFSET	(OTHER_ADDR_OFFSET + 0x001000)
#define PHY_BASEADDR_DUALDISPLAY_MODULE			(PHY_BASEADDR_DISPLAYTOP_MODULE + OTHER_ADDR_OFFSET + 0x002000)
#define PHY_BASEADDR_RESCONV_MODULE				(PHY_BASEADDR_DISPLAYTOP_MODULE + OTHER_ADDR_OFFSET + 0x003000)
#define PHY_BASEADDR_LCDINTERFACE_MODULE		(PHY_BASEADDR_DISPLAYTOP_MODULE + OTHER_ADDR_OFFSET + 0x004000)
#define PHY_BASEADDR_HDMI_MODULE				(PHY_BASEADDR_DISPLAYTOP_MODULE + 0x000000)							// 내부적으로 처리해줌.
#define PHY_BASEADDR_LVDS_MODULE				(PHY_BASEADDR_DISPLAYTOP_MODULE + OTHER_ADDR_OFFSET + 0x00A000)



//------------------------
// DualDisplay
//------------------------
#define 	NUMBER_OF_DUALDISPLAY_MODULE 		1
#define 	INTNUM_OF_DUALDISPLAY_MODULE_PRIMIRQ        INTNUM_OF_DISPLAYTOP_MODULE_DUALDISPLAY_PRIMIRQ
#define 	INTNUM_OF_DUALDISPLAY_MODULE_SECONDIRQ      INTNUM_OF_DISPLAYTOP_MODULE_DUALDISPLAY_SECONDIRQ
#define 	RESETINDEX_OF_DUALDISPLAY_MODULE_i_nRST     RESETINDEX_OF_DISPLAYTOP_MODULE_i_DualDisplay_nRST

#define PADINDEX_OF_DUALDISPLAY_o_nCS                 PADINDEX_OF_DISPLAYTOP_o_DualDisplay_PADPrimVCLK
#define PADINDEX_OF_DUALDISPLAY_o_nRD                 PADINDEX_OF_DISPLAYTOP_o_DualDisplay_PrimPADnHSync
#define PADINDEX_OF_DUALDISPLAY_o_RS                  PADINDEX_OF_DISPLAYTOP_o_DualDisplay_PrimPADnVSync
#define PADINDEX_OF_DUALDISPLAY_o_nWR                 PADINDEX_OF_DISPLAYTOP_o_DualDisplay_PrimPADDE
#define PADINDEX_OF_DUALDISPLAY_PADPrimVCLK           PADINDEX_OF_DISPLAYTOP_o_DualDisplay_PADPrimVCLK
#define PADINDEX_OF_DUALDISPLAY_o_PrimPADnHSync       PADINDEX_OF_DISPLAYTOP_o_DualDisplay_PrimPADnHSync
#define PADINDEX_OF_DUALDISPLAY_o_PrimPADnVSync       PADINDEX_OF_DISPLAYTOP_o_DualDisplay_PrimPADnVSync
#define PADINDEX_OF_DUALDISPLAY_o_PrimPADDE           PADINDEX_OF_DISPLAYTOP_o_DualDisplay_PrimPADDE
#define PADINDEX_OF_DUALDISPLAY_PrimPADRGB24_0_       PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_0_
#define PADINDEX_OF_DUALDISPLAY_PrimPADRGB24_1_       PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_1_
#define PADINDEX_OF_DUALDISPLAY_PrimPADRGB24_2_       PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_2_
#define PADINDEX_OF_DUALDISPLAY_PrimPADRGB24_3_       PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_3_
#define PADINDEX_OF_DUALDISPLAY_PrimPADRGB24_4_       PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_4_
#define PADINDEX_OF_DUALDISPLAY_PrimPADRGB24_5_       PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_5_
#define PADINDEX_OF_DUALDISPLAY_PrimPADRGB24_6_       PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_6_
#define PADINDEX_OF_DUALDISPLAY_PrimPADRGB24_7_       PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_7_
#define PADINDEX_OF_DUALDISPLAY_PrimPADRGB24_8_       PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_8_
#define PADINDEX_OF_DUALDISPLAY_PrimPADRGB24_9_       PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_9_
#define PADINDEX_OF_DUALDISPLAY_PrimPADRGB24_10_      PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_10_
#define PADINDEX_OF_DUALDISPLAY_PrimPADRGB24_11_      PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_11_
#define PADINDEX_OF_DUALDISPLAY_PrimPADRGB24_12_      PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_12_
#define PADINDEX_OF_DUALDISPLAY_PrimPADRGB24_13_      PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_13_
#define PADINDEX_OF_DUALDISPLAY_PrimPADRGB24_14_      PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_14_
#define PADINDEX_OF_DUALDISPLAY_PrimPADRGB24_15_      PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_15_
#define PADINDEX_OF_DUALDISPLAY_PrimPADRGB24_16_      PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_16_
#define PADINDEX_OF_DUALDISPLAY_PrimPADRGB24_17_      PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_17_
#define PADINDEX_OF_DUALDISPLAY_PrimPADRGB24_18_      PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_18_
#define PADINDEX_OF_DUALDISPLAY_PrimPADRGB24_19_      PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_19_
#define PADINDEX_OF_DUALDISPLAY_PrimPADRGB24_20_      PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_20_
#define PADINDEX_OF_DUALDISPLAY_PrimPADRGB24_21_      PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_21_
#define PADINDEX_OF_DUALDISPLAY_PrimPADRGB24_22_      PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_22_
#define PADINDEX_OF_DUALDISPLAY_PrimPADRGB24_23_      PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_23_
#define PADINDEX_OF_DUALDISPLAY_PADSecondVCLK         PADINDEX_OF_DISPLAYTOP_o_DualDisplay_PADPrimVCLK
#define PADINDEX_OF_DUALDISPLAY_o_SecondPADnHSync     PADINDEX_OF_DISPLAYTOP_o_DualDisplay_PrimPADnHSync
#define PADINDEX_OF_DUALDISPLAY_o_SecondPADnVSync     PADINDEX_OF_DISPLAYTOP_o_DualDisplay_PrimPADnVSync
#define PADINDEX_OF_DUALDISPLAY_o_SecondPADDE         PADINDEX_OF_DISPLAYTOP_o_DualDisplay_PrimPADDE
#define PADINDEX_OF_DUALDISPLAY_SecondPADRGB24_0_     PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_0_
#define PADINDEX_OF_DUALDISPLAY_SecondPADRGB24_1_     PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_1_
#define PADINDEX_OF_DUALDISPLAY_SecondPADRGB24_2_     PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_2_
#define PADINDEX_OF_DUALDISPLAY_SecondPADRGB24_3_     PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_3_
#define PADINDEX_OF_DUALDISPLAY_SecondPADRGB24_4_     PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_4_
#define PADINDEX_OF_DUALDISPLAY_SecondPADRGB24_5_     PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_5_
#define PADINDEX_OF_DUALDISPLAY_SecondPADRGB24_6_     PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_6_
#define PADINDEX_OF_DUALDISPLAY_SecondPADRGB24_7_     PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_7_
#define PADINDEX_OF_DUALDISPLAY_SecondPADRGB24_8_     PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_8_
#define PADINDEX_OF_DUALDISPLAY_SecondPADRGB24_9_     PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_9_
#define PADINDEX_OF_DUALDISPLAY_SecondPADRGB24_10_    PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_10_
#define PADINDEX_OF_DUALDISPLAY_SecondPADRGB24_11_    PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_11_
#define PADINDEX_OF_DUALDISPLAY_SecondPADRGB24_12_    PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_12_
#define PADINDEX_OF_DUALDISPLAY_SecondPADRGB24_13_    PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_13_
#define PADINDEX_OF_DUALDISPLAY_SecondPADRGB24_14_    PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_14_
#define PADINDEX_OF_DUALDISPLAY_SecondPADRGB24_15_    PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_15_
#define PADINDEX_OF_DUALDISPLAY_SecondPADRGB24_16_    PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_16_
#define PADINDEX_OF_DUALDISPLAY_SecondPADRGB24_17_    PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_17_
#define PADINDEX_OF_DUALDISPLAY_SecondPADRGB24_18_    PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_18_
#define PADINDEX_OF_DUALDISPLAY_SecondPADRGB24_19_    PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_19_
#define PADINDEX_OF_DUALDISPLAY_SecondPADRGB24_20_    PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_20_
#define PADINDEX_OF_DUALDISPLAY_SecondPADRGB24_21_    PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_21_
#define PADINDEX_OF_DUALDISPLAY_SecondPADRGB24_22_    PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_22_
#define PADINDEX_OF_DUALDISPLAY_SecondPADRGB24_23_    PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_23_

//------------
// Resolution Converter
//--------------
#define 	NUMBER_OF_RESCONV_MODULE 		1

#define		INTNUM_OF_RESCONV_MODULE    INTNUM_OF_DISPLAYTOP_MODULE_RESCONV_IRQ
#define   RESETINDEX_OF_RESCONV_MODULE_i_nRST    RESETINDEX_OF_DISPLAYTOP_MODULE_i_ResConv_nRST
#define   RESETINDEX_OF_RESCONV_MODULE    RESETINDEX_OF_RESCONV_MODULE_i_nRST


//----------
// LCD Interface
//---------  우선 LCDIF 내부는 수정하지 않도록 한다.
// LCD IF 의 PAD는 내부에서 DisplayTop을 가져다가 쓴다..
//-----------------
#define 	NUMBER_OF_LCDINTERFACE_MODULE 		1
//#define INTNUM_OF_LCDIF_MODULE_IRQ // no Interrupt
#define     RESETINDEX_OF_LCDINTERFACE_MODULE_i_nRST  RESETINDEX_OF_DISPLAYTOP_MODULE_i_LCDIF_nRST

#define PADINDEX_OF_LCDINTERFACE_o_VCLK       PADINDEX_OF_DISPLAYTOP_o_DualDisplay_PADPrimVCLK
#define PADINDEX_OF_LCDINTERFACE_o_nHSync     PADINDEX_OF_DISPLAYTOP_o_DualDisplay_PrimPADnHSync
#define PADINDEX_OF_LCDINTERFACE_o_nVSync     PADINDEX_OF_DISPLAYTOP_o_DualDisplay_PrimPADnVSync
#define PADINDEX_OF_LCDINTERFACE_o_DE         PADINDEX_OF_DISPLAYTOP_o_DualDisplay_PrimPADDE
#define PADINDEX_OF_LCDINTERFACE_RGB24_0_     PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_0_
#define PADINDEX_OF_LCDINTERFACE_RGB24_1_     PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_1_
#define PADINDEX_OF_LCDINTERFACE_RGB24_2_     PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_2_
#define PADINDEX_OF_LCDINTERFACE_RGB24_3_     PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_3_
#define PADINDEX_OF_LCDINTERFACE_RGB24_4_     PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_4_
#define PADINDEX_OF_LCDINTERFACE_RGB24_5_     PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_5_
#define PADINDEX_OF_LCDINTERFACE_RGB24_6_     PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_6_
#define PADINDEX_OF_LCDINTERFACE_RGB24_7_     PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_7_
#define PADINDEX_OF_LCDINTERFACE_RGB24_8_     PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_8_
#define PADINDEX_OF_LCDINTERFACE_RGB24_9_     PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_9_
#define PADINDEX_OF_LCDINTERFACE_RGB24_10_    PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_10_
#define PADINDEX_OF_LCDINTERFACE_RGB24_11_    PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_11_
#define PADINDEX_OF_LCDINTERFACE_RGB24_12_    PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_12_
#define PADINDEX_OF_LCDINTERFACE_RGB24_13_    PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_13_
#define PADINDEX_OF_LCDINTERFACE_RGB24_14_    PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_14_
#define PADINDEX_OF_LCDINTERFACE_RGB24_15_    PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_15_
#define PADINDEX_OF_LCDINTERFACE_RGB24_16_    PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_16_
#define PADINDEX_OF_LCDINTERFACE_RGB24_17_    PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_17_
#define PADINDEX_OF_LCDINTERFACE_RGB24_18_    PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_18_
#define PADINDEX_OF_LCDINTERFACE_RGB24_19_    PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_19_
#define PADINDEX_OF_LCDINTERFACE_RGB24_20_    PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_20_
#define PADINDEX_OF_LCDINTERFACE_RGB24_21_    PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_21_
#define PADINDEX_OF_LCDINTERFACE_RGB24_22_    PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_22_
#define PADINDEX_OF_LCDINTERFACE_RGB24_23_    PADINDEX_OF_DISPLAYTOP_DualDisplay_PrimPADRGB24_23_



// Interlace Converter 삭제 2012-11-07 오후 9:01:42

//-------------
// HDMI Block
//-------------
#define 	NUMBER_OF_HDMI_MODULE 		              1

#define     INTNUM_OF_HDMI_MODULE                    INTNUM_OF_DISPLAYTOP_MODULE_HDMI_IRQ
//#define     CLOCKINDEX_OF_MIPI_MODULE
#define     RESETINDEX_OF_HDMI_MODULE_i_nRST          RESETINDEX_OF_DISPLAYTOP_MODULE_i_HDMI_nRST
#define     RESETINDEX_OF_HDMI_MODULE_i_nRST_VIDEO    RESETINDEX_OF_DISPLAYTOP_MODULE_i_HDMI_VIDEO_nRST
#define     RESETINDEX_OF_HDMI_MODULE_i_nRST_SPDIF    RESETINDEX_OF_DISPLAYTOP_MODULE_i_HDMI_SPDIF_nRST
#define     RESETINDEX_OF_HDMI_MODULE_i_nRST_TMDS     RESETINDEX_OF_DISPLAYTOP_MODULE_i_HDMI_TMDS_nRST
#define     RESETINDEX_OF_HDMI_MODULE_i_nRST_PHY      RESETINDEX_OF_DISPLAYTOP_MODULE_i_HDMI_PHY_nRST
#define		PADINDEX_OF_HDMI_i_PHY_CLKI	 	PADINDEX_OF_DISPLAYTOP_i_HDMI_CLKI
#define		PADINDEX_OF_HDMI_o_PHY_CLKO	 	PADINDEX_OF_DISPLAYTOP_o_HDMI_CLKO
#define		PADINDEX_OF_HDMI_io_PHY_REXT	 	PADINDEX_OF_DISPLAYTOP_io_HDMI_REXT
#define		PADINDEX_OF_HDMI_o_PHY_TX0P	 	PADINDEX_OF_DISPLAYTOP_o_HDMI_TX0P
#define		PADINDEX_OF_HDMI_o_PHY_TX0N	 	PADINDEX_OF_DISPLAYTOP_o_HDMI_TX0N
#define		PADINDEX_OF_HDMI_o_PHY_TX1P	 	PADINDEX_OF_DISPLAYTOP_o_HDMI_TX1P
#define		PADINDEX_OF_HDMI_o_PHY_TX1N	 	PADINDEX_OF_DISPLAYTOP_o_HDMI_TX1N
#define		PADINDEX_OF_HDMI_o_PHY_TX2P	 	PADINDEX_OF_DISPLAYTOP_o_HDMI_TX2P
#define		PADINDEX_OF_HDMI_o_PHY_TX2N	 	PADINDEX_OF_DISPLAYTOP_o_HDMI_TX2N
#define		PADINDEX_OF_HDMI_o_PHY_TXCP	 	PADINDEX_OF_DISPLAYTOP_o_HDMI_TXCP
#define		PADINDEX_OF_HDMI_o_PHY_TXCN	 	PADINDEX_OF_DISPLAYTOP_o_HDMI_TXCN
#define        PADINDEX_OF_HDMI_i_hotplug         PADINDEX_OF_DISPLAYTOP_i_HDMI_hotplug_5V
#define        PADINDEX_OF_HDMI_io_PAD_CEC        PADINDEX_OF_DISPLAYTOP_io_HDMI_CEC



#define NUMBER_OF_LVDS_MODULE 		              1




#define RESETINDEX_OF_LVDS_MODULE_I_RESETN   RESETINDEX_OF_DISPLAYTOP_MODULE_i_LVDS_nRST
#define RESETINDEX_OF_LVDS_MODULE   RESETINDEX_OF_LVDS_MODULE_I_RESETN


#define	PADINDEX_OF_LVDS_TAP  		PADINDEX_OF_DISPLAYTOP_LVDS_TXP_A
#define	PADINDEX_OF_LVDS_TAN  		PADINDEX_OF_DISPLAYTOP_LVDS_TXN_A
#define	PADINDEX_OF_LVDS_TBP  		PADINDEX_OF_DISPLAYTOP_LVDS_TXP_B
#define	PADINDEX_OF_LVDS_TBN  		PADINDEX_OF_DISPLAYTOP_LVDS_TXN_B
#define	PADINDEX_OF_LVDS_TCP  		PADINDEX_OF_DISPLAYTOP_LVDS_TXP_C
#define	PADINDEX_OF_LVDS_TCN  		PADINDEX_OF_DISPLAYTOP_LVDS_TXN_C
#define	PADINDEX_OF_LVDS_TDP  		PADINDEX_OF_DISPLAYTOP_LVDS_TXP_D
#define	PADINDEX_OF_LVDS_TDN  		PADINDEX_OF_DISPLAYTOP_LVDS_TXN_D
#define	PADINDEX_OF_LVDS_TCLKP		PADINDEX_OF_DISPLAYTOP_LVDS_TXP_CLK
#define	PADINDEX_OF_LVDS_TCLKN		PADINDEX_OF_DISPLAYTOP_LVDS_TXN_CLK
#define	PADINDEX_OF_LVDS_ROUT		PADINDEX_OF_DISPLAYTOP_LVDS_ROUT
#define PADINDEX_OF_LVDS_TEP  PADINDEX_OF_DISPLAYTOP_LVDS_TXN_E
#define PADINDEX_OF_LVDS_TEN  PADINDEX_OF_DISPLAYTOP_LVDS_TXN_E


//-------------
// Display Top Inner CLKGEN ( DISPTOP_CLKGEN )
// RTL자체는 nx00800_CLKGEN_cfg2를 사용한다.
// Prototype은 해당 모듈의 prototype을 복사해서 사용한다.
// CLKGEN.h 이용하여 레지스터 맵 정의.
// [ CLKGEN은 DisplayTop과 Reset을 공유한다 !!! ]
//-------------
#define		NUMBER_OF_DISPTOP_CLKGEN_MODULE		5

enum     DISPTOP_CLKGEN_ModuleIndex{
	ResConv_CLKGEN 		= 0,
	LCDIF_CLKGEN 		= 1,
	ToMIPI_CLKGEN		= 2,
	ToLVDS_CLKGEN		= 3,
	HDMI_CLKGEN         = 4,
};

enum DISPTOP_ResConv_ICLK_CCLK
{
	ResConv_ICLK = 0, // Input Clock
	ResConv_CCLK = 1, // Core Clock
};

enum DISPTOP_ResConv_OCLK
{
	ResConv_OCLK = 1,// Output Clock === LCD Interface의 PixelCLK
};
	// LCD Interface CLKGEN Setting
enum DISPTOP_LCDIF_CLK
{
	LCDIF_PixelCLKxN = 0,
	LCDIF_PixelCLK = 1, // === ResConv_OCLK
};



#define HDMI_SPDIF_CLKGEN     2
//-------------------
// 각 CLKGEN의 CLKOUT이 사용되는 번호.
//-------------------
#define HDMI_SPDIF_CLKOUT 0 // HDMI_SPDIF_CLKGEN
#define HDMI_i_VCLK_CLKOUT 0 // HDMI_CLKGEN
#define		PHY_BASEADDR_DISPTOP_CLKGEN0_MODULE		(PHY_BASEADDR_DISPLAYTOP_MODULE + OTHER_ADDR_OFFSET + 0x006000)
#define		PHY_BASEADDR_DISPTOP_CLKGEN1_MODULE		(PHY_BASEADDR_DISPLAYTOP_MODULE + OTHER_ADDR_OFFSET + 0x007000)
#define		PHY_BASEADDR_DISPTOP_CLKGEN2_MODULE		(PHY_BASEADDR_DISPLAYTOP_MODULE + OTHER_ADDR_OFFSET + 0x005000)
#define		PHY_BASEADDR_DISPTOP_CLKGEN3_MODULE		(PHY_BASEADDR_DISPLAYTOP_MODULE + OTHER_ADDR_OFFSET + 0x008000)
#define		PHY_BASEADDR_DISPTOP_CLKGEN4_MODULE		(PHY_BASEADDR_DISPLAYTOP_MODULE + OTHER_ADDR_OFFSET + 0x009000)




//--------------------------------------------------------------------------
/// @brief	INTC register set structure.
struct NX_DISPLAYTOP_RegisterSet
{
	volatile U32 RESCONV_MUX_CTRL;		// 0x00
	volatile U32 INTERCONV_MUX_CTRL;	// 0x04
	volatile U32 MIPI_MUX_CTRL;			// 0x08
	volatile U32 LVDS_MUX_CTRL;			// 0x0C

	volatile U32 HDMIFIXCTRL0;			// 0x10
	volatile U32 HDMISYNCCTRL0;			// 0x14
	volatile U32 HDMISYNCCTRL1;			// 0x18
	volatile U32 HDMISYNCCTRL2;			// 0x1C
	volatile U32 HDMISYNCCTRL3;			// 0x20

	volatile U32 TFTMPU_MUX;            // 0x24
	volatile U32 HDMIFIELDCTRL;         // 0x28

	volatile U32 GREG0;         // 0x2C
	volatile U32 GREG1;         // 0x30
	volatile U32 GREG2;         // 0x34
	volatile U32 GREG3;         // 0x38
	volatile U32 GREG4;         // 0x3C
	volatile U32 GREG5;         // 0x40
};











//------------------------------------------------------------------------------
/// @name	Module Interface
//@{

CBOOL	NX_DISPLAYTOP_Initialize( void );
U32		NX_DISPLAYTOP_GetNumberOfModule( void );
//@}

//------------------------------------------------------------------------------
///	@name	Basic Interface
//@{

U32		NX_DISPLAYTOP_GetPhysicalAddress   ( void );
U32		NX_DISPLAYTOP_GetSizeOfRegisterSet ( void );
void	NX_DISPLAYTOP_SetBaseAddress       ( U32* BaseAddress );
U32*	NX_DISPLAYTOP_GetBaseAddress       ( void );
CBOOL	NX_DISPLAYTOP_OpenModule           ( void );
CBOOL	NX_DISPLAYTOP_CloseModule          ( void );
CBOOL	NX_DISPLAYTOP_CheckBusy            ( void );

//@}


//------------------------------------------------------------------------------
///	@name	Basic MUX SEL Function
//@{
enum MUX_Index{
	PrimaryMLC = 0,
	SecondaryMLC = 1,
	ResolutionConv = 2,
};

enum PrimPAD_MUX_Index{ // Primary TFT MUX
	PADMUX_PrimaryMLC = 0,
	PADMUX_PrimaryMPU = 1,
	PADMUX_SecondaryMLC = 2,
	PADMUX_ResolutionConv = 3,
};


void	NX_DISPLAYTOP_SetRESCONVMUX    ( CBOOL bEnb, U32 SEL );
void	NX_DISPLAYTOP_SetHDMIMUX       ( CBOOL bEnb, U32 SEL );
void	NX_DISPLAYTOP_SetMIPIMUX       ( CBOOL bEnb, U32 SEL );
void	NX_DISPLAYTOP_SetLVDSMUX       ( CBOOL bEnb, U32 SEL );
void	NX_DISPLAYTOP_SetPrimaryMUX    ( U32 SEL );
/// @name	HDMI FIX Signal Set Function - 차후에 구현.
//void	NX_DISPLAYTOP_SetHDMIValue(

//@modified choiyk 2012-12-24 오전 11:03:36
//HDMI Sync Set.
void	NX_DISPLAYTOP_HDMI_SetVSyncStart       ( U32 SEL ); // from posedge VSync
void	NX_DISPLAYTOP_HDMI_SetVSyncHSStartEnd  ( U32 Start, U32 End ); // from posedge HSync
void	NX_DISPLAYTOP_HDMI_SetHActiveStart     ( U32 SEL ); // from posedge HSync
void	NX_DISPLAYTOP_HDMI_SetHActiveEnd       ( U32 SEL ); // from posedge HSync

//--------------------------------
///	@name	Display Top의 RESET NUMBER를 구함.
U32 NX_DISPLAYTOP_GetResetNumber ( void );



void	NX_DISPLAYTOP_SetHDMIField(U32 Enable,			// Enable
									U32 InitVal,		// Init Value
									U32 VSyncToggle,	// VSync Toggle
									U32 HSyncToggle,		// HSync Toggle
									U32 VSyncClr,
									U32 HSyncClr,
									U32 FieldUse,
									U32 MUXSEL 	); // MUXSEL, 0 : Prim 1 : Second

//enum PrimPAD_MUX_Index{ // Primary TFT MUX
//	PADMUX_PrimaryMLC = 0,
//	PADMUX_PrimaryMPU = 1,
//	PADMUX_SecondaryMLC = 2,
//	PADMUX_ResolutionConv = 3,
//};

enum PADCLK_Config {
	PADCLK_CLK = 0,
	PADCLK_InvCLK = 1,
	PADCLK_ReservedCLK = 2,
	PADCLK_ReservedInvCLK = 3,
	PADCLK_CLK_div2_0   = 4,
	PADCLK_CLK_div2_90  = 5,
	PADCLK_CLK_div2_180 = 6,
	PADCLK_CLK_div2_270 = 7,
};


void	NX_DISPLAYTOP_SetPADClock(	U32 MUX_Index,
									U32 PADCLK_Cfg );
void	NX_DISPLAYTOP_SetLCDIF_i80Enb( CBOOL Enb );

void	NX_DISPLAYTOP_SetHDMIField(U32 Enable,			// Enable
									U32 InitVal,		// Init Value
									U32 VSyncToggle,	// VSync Toggle
									U32 HSyncToggle,	// HSync Toggle
									U32 VSyncClr,
									U32 HSyncClr,
									U32 FieldUse,
									U32 MUXSEL );		// MUXSEL, 0 : Prim 1 : Second 

//enum PrimPAD_MUX_Index{ // Primary TFT MUX
//	PADMUX_PrimaryMLC = 0,
//	PADMUX_PrimaryMPU = 1,
//	PADMUX_SecondaryMLC = 2,
//	PADMUX_ResolutionConv = 3,
//};

//@}

#ifdef	__cplusplus
}
#endif


#endif // __NX_DISPLAYTOP_H__

