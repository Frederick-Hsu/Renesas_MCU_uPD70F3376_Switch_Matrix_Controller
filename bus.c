/********************************************************************************************************
 * Program name	: bus.c
 * Description	: Construct the bus, such as 24-bit Data bus, 8-bit Address bus and 24-bit Digit IN
 *		: Control bus, etc.
 *		: And the manipulation on these bus.
 *		: This file is the implematation.
 *
 * Author	: XU ZAN
 * Date		: Wed.	July 25, 2012
 * Copyright(C)		2010 --- 2012	Hella (Shanghai) Electronics Co., Ltd.
 * All rights reserved.
 *
 ********************************************************************************************************/

#include <string.h>
#include "bus.h"
#include "serial.h"
#include "port.h"

#pragma ioreg
	/*******************************************************************************/
	// Global variables
	
	/*
	 * DataBus[7..0]
	 * -----+-----+-----+-----+-----+-----+-----+-----|
	 *   7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
	 * -----+-----+-----+-----+-----+-----+-----+-----|
	 *  P77 | P76 | P75 | P74 | P73 | P72 | P71 | P70 |
	 * -----+-----+-----+-----+-----+-----+-----+-----+
	 */
	volatile BYTE g_btDataBus_Bit7_0 = 0x00; // = (BYTE)(P7L & 0xFF);
	
	/*
	 * DataBus[15..8]
	 * ------+------+------+------+------+------+-----+-----+
	 *   15  |  14  |  13  |  12  |  11  |  10  |  9  |  8  |
	 * ------+------+------+------+------+------+-----+-----+
	 *  P715 | P714 | P713 | P712 | P711 | P710 | P79 | P78 |
	 * ------+------+------+------+------+------+-----+-----+
	 */
	volatile BYTE g_btDataBus_Bit15_8 = 0x00; //  = (BYTE)(((P7H & 0xFF00) >> 8) & 0xFF);
	
	
	
	/*
	 * PDL[13..6]
	 * ------+------+-------+-------+-------+-------+------+------+------+------+------+------+------+------+------+------+
	 *   15  |  14  |  13   |  12   |  11   |  10   |  9   |  8   |  7   |  6   |  5   |  4   |  3   |  2   |  1   |  0   |
	 * ------+------+-------+-------+-------+-------+------+------+------+------+------+------+------+------+------+------+
	 *       |      | PDL13 | PDL12 | PDL11 | PDL10 | PDL9 | PDL8 | PDL7 | PDL6 | PDL5 | PDL4 | PDL3 | PDL2 | PDL1 | PDL0 |
	 * ------+------+-------+-------+-------+-------+------+------+------+------+------+------+------+------+------+------+
	 *    0  |  0   |   1   |   1   |   1   |   1   |   1  |  1   |  1   |  1   |  0   |   0  |   0  |   0  |  0   |   0  |
	 * ------+------+-------+-------+-------+-------+------+------+------+------+------+------+------+------+------+------+
	 */
	BYTE btTempDataBus; //  = (BYTE)(((PDL & 0x3FC0) >> 6) & 0xFF);
	/*
	 * DataBus[23..16]
	 * ------+------+------+------+-------+-------+-------+-------+
	 *   23  |  22  |  21  |  20  |  19   |  18   |  17   |  16   |
	 * ------+------+------+------+-------+-------+-------+-------+
	 *  PDL6 | PDL7 | PDL8 | PDL9 | PDL10 | PDL11 | PDL12 | PDL13 |
	 * ------+------+------+------+-------+-------+-------+-------+
	 */
	volatile BYTE g_btDataBus_Bit23_16 = 0x00;
	#if 0
						  = ((btTempDataBus & 0x01) << 7) + 
						    ((btTempDataBus & 0x02) << 5) +
						    ((btTempDataBus & 0x04) << 3) +
						    ((btTempDataBus & 0x08) << 1) +
						    ((btTempDataBus & 0x10) >> 1) +
						    ((btTempDataBus & 0x20) >> 3) +
						    ((btTempDataBus & 0x40) >> 5) +
						    ((btTempDataBus & 0x80) >> 7);
	#endif
	
	
	/*
	 * AddressBus[7..0]
	 * ------+------+------+------+------+------+------+------+
	 *   7   |  6   |  5   |  4   |  3   |  2   |  1   |  0   |
	 * ------+------+------+------+------+------+------+------+
	 *  P910 | P911 | P912 | P913 | PCS0 | PCS1 | PCM0 | PCM1 |
	 * ------+------+------+------+------+------+------+------+
	 *
	 */
	volatile BYTE g_btAddressBus_Bit7_0 = 0x00;
	#if 0
					    = ((P9H.2 & 0x01) << 7) + 
					      ((P9H.3 & 0x01) << 6) +
					      ((P9H.4 & 0x01) << 5) +
					      ((P9H.5 & 0x01) << 4) +
					      ((PCS.0 & 0x01) << 3) +
					      ((PCS.1 & 0x01) << 2) +
					      ((PCM.0 & 0x01) << 1) +
					      ((PCM.1 & 0x01));
	#endif
	
	/*
	 * ADC Data Bus[15..0]
	 * ------+------+------+------+------+------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *   15  |  14  |  13  |  12  |  11  |  10  |  9  |  8  |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
	 * ------+------+------+------+------+------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *  P715 | P714 | P713 | P712 | P711 | P710 | P79 | P78 | P77 | P76 | P75 | P74 | P73 | P72 | P71 | P70 |
	 * ------+------+------+------+------+------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *                          P7H                         |                      P7L                      |
	 * ------+------+------+------+------+------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
	 *
	 */
	volatile WORD g_wADC_Value_DataBus_16bit = 0x0000;
	#if 0
					       = (((WORD)(P7H & 0x00FF)) << 8) +
						 ( (WORD)(P7L &   0xFF));
	#endif
	
	
	/*
	 * ADC Input Channel Selector 
	 * AddressBus[2..0]
	 * -----+-----+-----+-----+-----+------+------+------+
	 *   7  |  6  |  5  |  4  |  3  |  2   |  1   |  0   |
	 * -----+-----+-----+-----+-----+------+------+------+
	 *      |     |     |     |     | ADD2 | ADD1 | ADD0 |
	 * -----+-----+-----+-----+-----+------+------+------+
	 *      |     |     |     |     | PCS1 | PCM0 | PCM1 |
	 * -----+-----+-----+-----+-----+------+------+------+
	 */
	BYTE g_btADC_Chnl_Selector_AddressBus_bit2_0 = 0x00; 
	#if 0
						     = ((PCS.1 & 0x01) << 2) +
						       ((PCM.0 & 0x01) << 1) +
						       ((PCM.1 & 0x01));
	#endif
	
	
	
	
	/*
	 * Digital In Bus[23..0]
	 * ------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+-----+-----+------+------+------+------+------+------+------+------+
	 *   31  |  30  |  29  |  28  |  27  |  26  |  25  |  24  |  23  |  22  |  21  |  20  |  19  |  18  |  17  |  16  |  15  |  14  |  13  |  12  |  11  |  10  |  9  |  8  |  7   |  6   |  5   |  4   |  3   |  2   |  1   |  0   |
	 * ------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+-----+-----+------+------+------+------+------+------+------+------+
	 *       |      |      |      |      |      |      |      | DI23 | DI22 | DI21 | DI20 | DI19 | DI18 | DI17 | DI16 | DI15 | DI14 | DI13 | DI12 | DI11 | DI10 | DI9 | DI8 | DI7  | DI6  | DI5  | DI4  | DI3  | DI2  | DI1  | DI0  |
	 * ------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+-----+-----+------+------+------+------+------+------+------+------+
	 *       |      |      |      |      |      |      |      | P10  | P11  | P00  | P01  | P02  | P03  | P04  | P06  | P35  | P36  | P37  | P50  | P51  | P90  | P91 | P92 | PCT4 | PCT6 | PDL0 | PDL1 | PDL2 | PDL3 | PDL4 | PDL5 |   // Current order
	 * ------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+-----+-----+------+------+------+------+------+------+------+------+
	 * 
	 * Original order :
	 *       |      |      |      |      |      |      |      | PDL5 | PDL4 | PDL3 | PDL2 | PDL1 | PDL0 | PCT6 | PCT4 | P92  | P91  | P90  | P51  | P50  | P37  | P36 | P35 | P06  | P04  | P03  | P02  | P01  | P00  | P11  | P10  |
	 * ------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+-----+-----+------+------+------+------+------+------+------+------+
	 */
	volatile DWORD g_dwDigitalIN_Bus_bit23_0 = 0x00000000;
	#if 0
	/* How to calculate the DIN_bus[0..23] for current order condition */
						 = DIN00 + 
						   DIN01<<1 + 
						   DIN02<<2 + 
						   DIN03<<3 + 
						   DIN04<<4 + 
						   DIN05<<5 +
						   DIN06<<6 +
						   DIN07<<7 +
						   DIN08<<8 +
						   DIN09<<9 +
						   DIN10<<10 +
						   DIN11<<11 +
						   DIN12<<12 +
						   DIN13<<13 +
						   DIN14<<14 +
						   DIN15<<15 +
						   DIN16<<16 +
						   DIN17<<17 +
						   DIN18<<18 +
						   DIN19<<19 +
						   DIN20<<20 +
						   DIN21<<21 +
						   DIN22<<22 +
						   DIN23<<23;
	#endif
	
	
	/*
	 * DAC Input Data Bus[7..0]
	 * -----+-----+-----+-----+-----+-----+-----+-----+
	 *   7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
	 * -----+-----+-----+-----+-----+-----+-----+-----+
	 *  P77 | P76 | P75 | P74 | P73 | P72 | P71 | P70 |
	 * -----+-----+-----+-----+-----+-----+-----+-----+
	 */
	BYTE g_btDAC_In_Databus_bit7_0 = 0x00; // = P7L;
	
	
	
	
/*======================================================================================================================================================================================================*/





void Write_Address_Bus(BYTE btAddrBus_bit7_0)
/*
 * AddressBus[7..0]
 * ------+------+------+------+------+------+------+------+
 *   7   |  6   |  5   |  4   |  3   |  2   |  1   |  0   |
 * ------+------+------+------+------+------+------+------+
 *  P910 | P911 | P912 | P913 | PCS0 | PCS1 | PCM0 | PCM1 |
 * ------+------+------+------+------+------+------+------+
 *
 */
{
	/*
	 * First of all, you must change these ports to output mode by software
	 */
	PORT_ChangePCM1Output( btAddrBus_bit7_0 & 0x01      );	// For A0
	PORT_ChangePCM0Output((btAddrBus_bit7_0 & 0x02) >> 1);	//     A1
	PORT_ChangePCS1Output((btAddrBus_bit7_0 & 0x04) >> 2);	//     A2
	PORT_ChangePCS0Output((btAddrBus_bit7_0 & 0x08) >> 3);	//     A3
	PORT_ChangeP913Output((btAddrBus_bit7_0 & 0x10) >> 4);	//     A4
	PORT_ChangeP912Output((btAddrBus_bit7_0 & 0x20) >> 5);	//     A5
	PORT_ChangeP911Output((btAddrBus_bit7_0 & 0x40) >> 6);	//     A6
	PORT_ChangeP910Output((btAddrBus_bit7_0 & 0x80) >> 7);	//     A7
	
	#if 0
		/*
		 * Start to set the value for corresponding port.
		 */	
		A0 = (btAddrBus_bit7_0 & 0x01);			// PCM1 ----- bit 0
		A1 = (btAddrBus_bit7_0 & 0x02) >> 1;		// PCM0 ----- bit 1
		A2 = (btAddrBus_bit7_0 & 0x04) >> 2;		// PCS1 ----- bit 2
		A3 = (btAddrBus_bit7_0 & 0x08) >> 3;		// PCS0 ----- bit 3
		A4 = (btAddrBus_bit7_0 & 0x10) >> 4;		// P913 ----- bit 4
		A5 = (btAddrBus_bit7_0 & 0x20) >> 5;		// P912 ----- bit 5
		A6 = (btAddrBus_bit7_0 & 0x40) >> 6;		// P911 ----- bit 6
		A7 = (btAddrBus_bit7_0 & 0x80) >> 7;		// P910 ----- bit 7
	#endif
	
	return;
}

#if 0
	/*
	 * This "Read address bus" will not function any more, because the hardware design
	 * has limited that address bus can only output (i.e.  write direction), 
	 * no input (i.e.  read direction).
	 * 
	 * Disabled by XU ZAN@2012-10-20
	 */
	BYTE Read_Address_Bus()
	{
		/*
		 * Change these ports to input mode by software
		 */
		PORT_ChangePCM1Input();		// For A0
		PORT_ChangePCM0Input();		//     A1
		PORT_ChangePCS1Input();		//     A2
		PORT_ChangePCS0Input();		//     A3
		PORT_ChangeP913Input(0);	//     A4
		PORT_ChangeP912Input(0);	//     A5
		PORT_ChangeP911Input(0);	//     A6
		PORT_ChangeP910Input(0);	//     A7
		
		
		g_btAddressBus_Bit7_0 = ((A7 & 0x01) << 7) + 
					((A6 & 0x01) << 6) +
					((A5 & 0x01) << 5) +
					((A4 & 0x01) << 4) +
					((A3 & 0x01) << 3) +
					((A2 & 0x01) << 2) +
					((A1 & 0x01) << 1) +
					((A0 & 0x01));
		
		return g_btAddressBus_Bit7_0;
	}
#endif

int Read_ADCInput_DataBus_from_DB15_to_DB00()
/*
 * ADC Data Bus[15..0]
 * ------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+
 *   15  |  14  |  13  |  12  |  11  |  10  |  9   |  8   |  7   |  6   |  5   |  4   |  3   |  2   |  1   |  0   |
 * ------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+
 *  P715 | P714 | P713 | P712 | P711 | P710 | P79  | P78  | P77  | P76  | P75  | P74  | P73  | P72  | P71  | P70  |
 * ------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+
 *                          P7H                           |                          P7L                          |
 * ------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+
 *  DB15 | DB14 | DB13 | DB12 | DB11 | DB10 | DB09 | DB08 | DB07 | DB06 | DB05 | DB04 | DB03 | DB02 | DB01 | DB00 |
 * ------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+
 *
 */
{
	int iADCValue = 0x00000000;
	WORD wDataBusValue = 0x0000;
	
	RW = LOW;		// Enable read direction
	
	/*
	 * Change port mode to Input mode for 
	 * data_bus[DB15...DB00]
	 */
	PORT_ChangeP70Input();		// DB00
	PORT_ChangeP71Input();		// DB01
	PORT_ChangeP72Input();		// DB02
	PORT_ChangeP73Input();		// DB03
	PORT_ChangeP74Input();		// DB04
	PORT_ChangeP75Input();		// DB05
	PORT_ChangeP76Input();		// DB06
	PORT_ChangeP77Input();		// DB07
	PORT_ChangeP78Input();		// DB08
	PORT_ChangeP79Input();		// DB09
	PORT_ChangeP710Input();		// DB10
	PORT_ChangeP711Input();		// DB11
	PORT_ChangeP712Input();		// DB12
	PORT_ChangeP713Input();		// DB13
	PORT_ChangeP714Input();		// DB14
	PORT_ChangeP715Input();		// DB15
	
	wDataBusValue = (DB00      ) +
		    	(DB01 <<  1) +
		    	(DB02 <<  2) +
		    	(DB03 <<  3) +
		    	(DB04 <<  4) +
		    	(DB05 <<  5) +
		    	(DB06 <<  6) +
		    	(DB07 <<  7) +
		    	(DB08 <<  8) +
		    	(DB09 <<  9) +
		    	(DB10 << 10) +
		    	(DB11 << 11) +
		    	(DB12 << 12) +
		    	(DB13 << 13) +
		    	(DB14 << 14);
	/*
	 * DB15 is used to detect the sign of positive or negative voltage.
	 */
	if (DB15 == 1)
	{
		iADCValue = wDataBusValue * (-1);
	}
	else
	{
		iADCValue = wDataBusValue;
	}
	
	return iADCValue;
}

void Set_DataBus_from_DB07_to_DB00(BYTE btLowByte_Value)
/*
 * DataBus[7..0]
 * -----+-----+-----+-----+-----+-----+-----+-----|
 *   7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
 * -----+-----+-----+-----+-----+-----+-----+-----|
 *  P77 | P76 | P75 | P74 | P73 | P72 | P71 | P70 |
 * -----+-----+-----+-----+-----+-----+-----+-----+
 */
{
	unsigned char sUART2_Send_Mesg[] = "Data bus value entered error.\n";
	RW = HIGH;	// Enable sending direction for chip 74HC245
	if (btLowByte_Value > 0xFF)
	{
		UARTD2_SendData(sUART2_Send_Mesg, sizeof(sUART2_Send_Mesg));
		return;
	}
	else
	{
		/********************************************************************************
		 * Notice : 
		 * When DBxx output 0, it means that corresponding Relay_Switch  OFF (Disconnect)
		 *                  1,                                           ON  (Connect)
		 *
		 * Please pay key attention on the corresponding relationship.
		 * Remarked by XU ZAN@2012-10-20
		 *
		 ********************************************************************************/
		PORT_ChangeP70Output( btLowByte_Value & 0x01      );	// For	DB00
		PORT_ChangeP71Output((btLowByte_Value & 0x02) >> 1);	//	DB01
		PORT_ChangeP72Output((btLowByte_Value & 0x04) >> 2);	//	DB02
		PORT_ChangeP73Output((btLowByte_Value & 0x08) >> 3);	//	DB03
		PORT_ChangeP74Output((btLowByte_Value & 0x10) >> 4);	//	DB04
		PORT_ChangeP75Output((btLowByte_Value & 0x20) >> 5);	//	DB05
		PORT_ChangeP76Output((btLowByte_Value & 0x40) >> 6);	//	DB06
		PORT_ChangeP77Output((btLowByte_Value & 0x80) >> 7);	//	DB07
		
		#if 0
			// LSB : bit0 : P70
			DB00 = (btLowByte_Value & 0x01);
			
			DB01 = (btLowByte_Value & 0x02) >> 1;
			DB02 = (btLowByte_Value & 0x04) >> 2;
			DB03 = (btLowByte_Value & 0x08) >> 3;
			DB04 = (btLowByte_Value & 0x10) >> 4;
			DB05 = (btLowByte_Value & 0x20) >> 5;
			DB06 = (btLowByte_Value & 0x40) >> 6;
			
			// MSB : bit7 : P77
			DB07 = (btLowByte_Value & 0x80) >> 7;
		#endif
	}
	return;
}

void Set_DataBus_from_DB15_to_DB08(BYTE btMiddleByte_Value)
/*
 * DataBus[15..8]
 * ------+------+------+------+------+------+-----+-----+
 *   15  |  14  |  13  |  12  |  11  |  10  |  9  |  8  |
 * ------+------+------+------+------+------+-----+-----+
 *  P715 | P714 | P713 | P712 | P711 | P710 | P79 | P78 |
 * ------+------+------+------+------+------+-----+-----+
 */
{
	unsigned char sUART2_Send_Mesg[] = "Data bus value entered error.\n";
	RW = HIGH;
	if (btMiddleByte_Value > 0xFF)
	{
		UARTD2_SendData(sUART2_Send_Mesg, sizeof(sUART2_Send_Mesg));
		return;
	}
	else
	{
		PORT_ChangeP78Output(  btMiddleByte_Value & 0x01      );
		PORT_ChangeP79Output( (btMiddleByte_Value & 0x02) >> 1);
		PORT_ChangeP710Output((btMiddleByte_Value & 0x04) >> 2);
		PORT_ChangeP711Output((btMiddleByte_Value & 0x08) >> 3);
		PORT_ChangeP712Output((btMiddleByte_Value & 0x10) >> 4);
		PORT_ChangeP713Output((btMiddleByte_Value & 0x20) >> 5);
		PORT_ChangeP714Output((btMiddleByte_Value & 0x40) >> 6);
		PORT_ChangeP715Output((btMiddleByte_Value & 0x80) >> 7);
		
		#if 0
			// LSB : bit8 : P78
			DB08 = (btMiddleByte_Value & 0x01);
			
			DB09 = (btMiddleByte_Value & 0x02) >> 1;
			DB10 = (btMiddleByte_Value & 0x04) >> 2;
			DB11 = (btMiddleByte_Value & 0x08) >> 3;
			DB12 = (btMiddleByte_Value & 0x10) >> 4;
			DB13 = (btMiddleByte_Value & 0x20) >> 5;
			DB14 = (btMiddleByte_Value & 0x40) >> 6;
			
			// MSB : bit15 : P715
			DB15 = (btMiddleByte_Value & 0x80) >> 7;
		#endif
	}
	return;
}

void Set_DataBus_from_DB23_to_DB16(BYTE btHighByte_Value)
/*
 * DataBus[23..16]
 * ------+------+------+------+-------+-------+-------+-------+
 *   23  |  22  |  21  |  20  |  19   |  18   |  17   |  16   |
 * ------+------+------+------+-------+-------+-------+-------+
 *  PDL6 | PDL7 | PDL8 | PDL9 | PDL10 | PDL11 | PDL12 | PDL13 |
 * ------+------+------+------+-------+-------+-------+-------+
 */
{
	unsigned char sUART2_Send_Mesg[] = "Data bus value entered error.\n";
	RW = HIGH;
	if (btHighByte_Value > 0xFF)
	{
		UARTD2_SendData(sUART2_Send_Mesg, sizeof(sUART2_Send_Mesg));
		return;
	}
	else
	{
		/*
		 * PDL
		 * ------+------+-------+-------+-------+-------+------+------+------+------+------+------+------+------+------+------+
		 *   15  |  14  |  13   |  12   |  11   |  10   |  9   |  8   |  7   |  6   |  5   |  4   |  3   |  2   |  1   |  0   |
		 * ------+------+-------+-------+-------+-------+------+------+------+------+------+------+------+------+------+------+
		 *       |                                                    |                    |      |      |      |      |      |
		 *       |      +-----------------------------------------------------------+      |      |      |      |      |      |
		 *       |      | PDL13 | PDL12 | PDL11 | PDL10 | PDL9 | PDL8 | PDL7 | PDL6 | PDL5 | PDL4 | PDL3 | PDL2 | PDL1 | PDL0 |
		 *       |      +-----------------------------------------------------------+      |      |      |      |      |      |
		 *       |                                                    |                    |      |      |      |      |      |
		 * ------+------+-------+-------+-------+-------+------+------+------+------+------+------+------+------+------+------+
		 *                            PDLH                            |                            PDLL                       |
		 * ------+------+-------+-------+-------+-------+------+------+------+------+------+------+------+------+------+------+
		 */
		 
		PORT_ChangePDL13Output( btHighByte_Value & 0x01      );
		PORT_ChangePDL12Output((btHighByte_Value & 0x02) >> 1);
		PORT_ChangePDL11Output((btHighByte_Value & 0x04) >> 2);
		PORT_ChangePDL10Output((btHighByte_Value & 0x08) >> 3);
		PORT_ChangePDL9Output( (btHighByte_Value & 0x10) >> 4);
		PORT_ChangePDL8Output( (btHighByte_Value & 0x20) >> 5);
		PORT_ChangePDL7Output( (btHighByte_Value & 0x40) >> 6);
		PORT_ChangePDL6Output( (btHighByte_Value & 0x80) >> 7);
		 
		#if 0
			// LSB : bit16 : PDL13
			DB16 = (btHighByte_Value & 0x01);		// PDL13
			
			DB17 = (btHighByte_Value & 0x02) >> 1;	// PDL12
			DB18 = (btHighByte_Value & 0x04) >> 2;	// PDL11
			DB19 = (btHighByte_Value & 0x08) >> 3;	// PDL10
			DB20 = (btHighByte_Value & 0x10) >> 4;	// PDL9
			DB21 = (btHighByte_Value & 0x20) >> 5;	// PDL8
			DB22 = (btHighByte_Value & 0x40) >> 6;	// PDL7
			
			// MSB : bit23 : PDL6
			DB23 = (btHighByte_Value & 0x80) >> 7;	// PDL6
		#endif
	}
	return;
}

void Write_All_DataBus(unsigned int uiDBValue)
{
	BYTE btLowByteValue 	= 0x00,
	     btMiddleByteValue 	= 0x00,
	     btHighByteValue 	= 0x00;

	btLowByteValue 		= (uiDBValue & 0x000000FF);
	btMiddleByteValue 	= (uiDBValue & 0x0000FF00) >> 8;
	btHighByteValue 	= (uiDBValue & 0x00FF0000) >> 16;
	
	Set_DataBus_from_DB07_to_DB00(btLowByteValue);
	Set_DataBus_from_DB15_to_DB08(btMiddleByteValue);
	Set_DataBus_from_DB23_to_DB16(btHighByteValue);
}

DWORD Read_Digital_In_Bus_Value()
{
	DWORD dwDigitalInValue = 0x00000000;
	
	/* Becasue all the ports of Digital IN bus [DIN23...DIN00] are configured as Input mode by default,
	 * no need to change the port mode.
	 * Just directly get its individual value of each port.
	 * Remarked by XU ZAN@2012-10-20
	 */
	dwDigitalInValue = DIN00 + 
			   DIN01<<1 + 
			   DIN02<<2 + 
			   DIN03<<3 + 
			   DIN04<<4 + 
			   DIN05<<5 +
			   DIN06<<6 +
			   DIN07<<7 +
			   DIN08<<8 +
			   DIN09<<9 +
			   DIN10<<10 +
			   DIN11<<11 +
			   DIN12<<12 +
			   DIN13<<13 +
			   DIN14<<14 +
			   DIN15<<15 +
			   DIN16<<16 +
			   DIN17<<17 +
			   DIN18<<18 +
			   DIN19<<19 +
			   DIN20<<20 +
			   DIN21<<21 +
			   DIN22<<22 +
			   DIN23<<23;
	
	return dwDigitalInValue;
}


void Set_DataBus_to_Initial_Default_State_After_Power_ON()
{
	/*
	 * Considering the connection (ON) / disconnection (OFF) state transition, all switches and
	 * relais should be disconnected (OFF), in case of emergency, after Power ON.
	 * So, we should set the data bus[23..0] to default : 0x00, to enforce all switches
	 * and relaise disconnected.
	 *
	 * Remarked by XU ZAN @2012-07-27
	 */
	 Set_DataBus_from_DB07_to_DB00(0x00);
	 Set_DataBus_from_DB15_to_DB08(0x00);
	 Set_DataBus_from_DB23_to_DB16(0x00);
}

void Set_AddressBus_to_Initial_Default_State_After_Power_ON()
{
	/*
	 * Set Address Bus[7..0] to default : 0xFF
	 * meanwhile set control pin CS0 to HIGH. (CS0 HIGH means disable.)
	 */
	Write_Address_Bus(0xFF);
	
	CS0 = HIGH;	// CS0 pin = P99
}

void Set_ControlBus_to_Initial_Default_State_After_Power_ON()
{
	/* This function need to determine the state of each control port.
	 * Need to discuss with Henry Xing, under-discussion, wait for implementation later.
	 */
	#if 0
		P9H.0 = HIGH;	// CS1 pin = P98
		P9L.7 = HIGH;	// CS2 pin = P97
		P9L.6 = HIGH;	// CS3 pin = P96
		P9L.5 = HIGH;	// CS4 pin = P95
		P9L.4 = HIGH;	// CS5 pin = P94
		
		RW = HIGH;
		ENAD = LOW;
		CON = LOW;
		BUSY = LOW;
		ENDA = HIGH;
		
		NSLP = HIGH;
		ERR = HIGH;
		EN = LOW;
		STB = HIGH;
	#endif
}

void Set_Initial_Default_State_After_Power_ON()
{
	Set_DataBus_to_Initial_Default_State_After_Power_ON();
	Set_AddressBus_to_Initial_Default_State_After_Power_ON();
	Set_ControlBus_to_Initial_Default_State_After_Power_ON();
}


#if defined (UNUSED)
	void Control_Port_Mutx_From_Switch_to_ADC(E_CTRL_PIN_LEVEL eCtrl_Pin_CS0)
	{
		if (eCtrl_Pin_CS0 == CONTROL_PIN_LOW)
		/* 
		 * CS0 = LOW is active.
		 */
		{
			ENAD = LOW;	// ENAD = LOW is disable
			ENDA = HIGH;	// ENDA = HIGH is disable
		}
		return;
	}

	void Control_Port_Mutx_From_ADC_to_Switch(E_CTRL_PIN_LEVEL eCtrl_Pin_ENAD)
	{
		if ( (eCtrl_Pin_ENAD == CONTROL_PIN_HIGH) ||
		     (ENDA == CONTROL_PIN_LOW) )
		{
			CS0 = HIGH;	// disable
		}
		return;
	}

	void Control_Port_Mutx_From_ADC_to_DAC(E_CTRL_PIN_LEVEL eCtrl_Pin_ENAD)
	{
		if (eCtrl_Pin_ENAD == CONTROL_PIN_HIGH)
		{
			ENDA = HIGH;	// disable
		}
		return;
	}

	void Control_Port_Mutx_From_DAC_to_ADC(E_CTRL_PIN_LEVEL eCtrl_Pin_ENDA)
	{
		if (eCtrl_Pin_ENDA == CONTROL_PIN_LOW)
		{
			ENAD = LOW;
		}
		return;
	}
#endif	/* End UNUSED */


void Write_DataBus_Single_CHn(     DWORD  dwCHn,  /* 0 <= CHn <= 23   must */
			      enum LEVEL  eSpecificLevelValue)
{
	RW = HIGH;	// firstly must enable sending direction.
	switch (dwCHn)
	{
	case 0:
		PORT_ChangeP70Output(eSpecificLevelValue);	// For	DB00
		// DB00 = eSpecificLevelValue;
		break;
	case 1:
		PORT_ChangeP71Output(eSpecificLevelValue);	//	DB01
		// DB01 = eSpecificLevelValue;
		break;
	case 2:
		PORT_ChangeP72Output(eSpecificLevelValue);	//	DB02
		// DB02 = eSpecificLevelValue;
		break;
	case 3:
		PORT_ChangeP73Output(eSpecificLevelValue);	//	DB03
		// DB03 = eSpecificLevelValue;
		break;
	case 4:
		PORT_ChangeP74Output(eSpecificLevelValue);	//	DB04
		// DB04 = eSpecificLevelValue;
		break;
	case 5:
		PORT_ChangeP75Output(eSpecificLevelValue);	//	DB05
		// DB05 = eSpecificLevelValue;
		break;
	case 6:
		PORT_ChangeP76Output(eSpecificLevelValue);	//	DB06
		// DB06 = eSpecificLevelValue;
		break;
	case 7:
		PORT_ChangeP77Output(eSpecificLevelValue);	//	DB07
		// DB07 = eSpecificLevelValue;
		break;
	case 8:
		PORT_ChangeP78Output(eSpecificLevelValue);	//	DB08
		// DB08 = eSpecificLevelValue;
		break;
	case 9:
		PORT_ChangeP79Output(eSpecificLevelValue);	//	DB09
		// DB09 = eSpecificLevelValue;
		break;
	case 10:
		PORT_ChangeP710Output(eSpecificLevelValue);	//	DB10
		// DB10 = eSpecificLevelValue;
		break;
	case 11:
		PORT_ChangeP711Output(eSpecificLevelValue);	//	DB11
		// DB11 = eSpecificLevelValue;
		break;
	case 12:
		PORT_ChangeP712Output(eSpecificLevelValue);	//	DB12
		// DB12 = eSpecificLevelValue;
		break;
	case 13:
		PORT_ChangeP713Output(eSpecificLevelValue);	//	DB13
		// DB13 = eSpecificLevelValue;
		break;
	case 14:
		PORT_ChangeP714Output(eSpecificLevelValue);	//	DB14
		// DB14 = eSpecificLevelValue;
		break;
	case 15:
		PORT_ChangeP715Output(eSpecificLevelValue);	//	DB15
		// DB15 = eSpecificLevelValue;
		break;
	case 16:
		PORT_ChangePDL13Output(eSpecificLevelValue);	//	DB16
		// DB16 = eSpecificLevelValue;
		break;
	case 17:
		PORT_ChangePDL12Output(eSpecificLevelValue);	//	DB17
		// DB17 = eSpecificLevelValue;
		break;
	case 18:
		PORT_ChangePDL11Output(eSpecificLevelValue);	//	DB18
		// DB18 = eSpecificLevelValue;
		break;
	case 19:
		PORT_ChangePDL10Output(eSpecificLevelValue);	//	DB19
		// DB19 = eSpecificLevelValue;
		break;
	case 20:
		PORT_ChangePDL9Output(eSpecificLevelValue);	//	DB20
		// DB20 = eSpecificLevelValue;
		break;
	case 21:
		PORT_ChangePDL8Output(eSpecificLevelValue);	//	DB21
		// DB21 = eSpecificLevelValue;
		break;
	case 22:
		PORT_ChangePDL7Output(eSpecificLevelValue);	//	DB22
		// DB22 = eSpecificLevelValue;
		break;
	case 23:
		PORT_ChangePDL6Output(eSpecificLevelValue);	//	DB23
		// DB23 = eSpecificLevelValue;
		break;
	default :
		break;
	}
	return;
}



DWORD Read_DataBus_State_from_DB23_to_DB00(void)
{
	DWORD dwDataBusState = 0x00000000;
	
	RW = LOW;		// Enable read direction
	
	PORT_ChangeP70Input();		
	PORT_ChangeP71Input();		
	PORT_ChangeP72Input();		
	PORT_ChangeP73Input();		
	PORT_ChangeP74Input();		
	PORT_ChangeP75Input();		
	PORT_ChangeP76Input();		
	PORT_ChangeP77Input();		
	PORT_ChangeP78Input();		
	PORT_ChangeP79Input();		
	PORT_ChangeP710Input();		
	PORT_ChangeP711Input();		
	PORT_ChangeP712Input();		
	PORT_ChangeP713Input();		
	PORT_ChangeP714Input();		
	PORT_ChangeP715Input();		
	PORT_ChangePDL13Input();
	PORT_ChangePDL12Input();
	PORT_ChangePDL11Input();
	PORT_ChangePDL10Input();
	PORT_ChangePDL9Input();
	PORT_ChangePDL8Input();
	PORT_ChangePDL7Input();
	PORT_ChangePDL6Input();
	
	dwDataBusState = (DB00      ) +
		    	 (DB01 <<  1) +
		    	 (DB02 <<  2) +
		    	 (DB03 <<  3) +
		    	 (DB04 <<  4) +
		    	 (DB05 <<  5) +
		    	 (DB06 <<  6) +
		    	 (DB07 <<  7) +
		    	 (DB08 <<  8) +
		    	 (DB09 <<  9) +
		    	 (DB10 << 10) +
		    	 (DB11 << 11) +
		    	 (DB12 << 12) +
		    	 (DB13 << 13) +
		    	 (DB14 << 14) +
			 (DB15 << 15) +
			 (DB16 << 16) +
			 (DB17 << 17) +
			 (DB18 << 18) +
			 (DB19 << 19) +
			 (DB20 << 20) +
			 (DB21 << 21) +
			 (DB22 << 22) +
			 (DB23 << 23);
	
	return dwDataBusState;
}

