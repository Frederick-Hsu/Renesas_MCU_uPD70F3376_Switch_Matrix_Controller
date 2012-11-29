/********************************************************************************************************
 * Program name	: bus.h
 * Description	: Construct the bus, such as 24-bit Data bus, 8-bit Address bus and 24-bit Digit IN
 *		: Control bus, etc.
 *		: And the manipulation on these bus.
 * Author	: XU ZAN
 * Date		: Wed.	July 25, 2012
 * Copyright(C)		2010 --- 2012	Hella (Shanghai) Electronics Co., Ltd.
 * All rights reserved.
 *
 ********************************************************************************************************/

#ifndef _BUS_H
#define _BUS_H

	/********************************************************************************/
	// Included files
	#pragma ioreg
	
	#include "macrodriver.h"
	
	
	
	/********************************************************************************/
	// Macros
	// Define the control port
	#define CS0	(P9H.1)
	#define CS1	(P9H.0)
	#define CS2	(P9L.7)
	#define CS3	(P9L.6)
	#define CS4	(P9L.5)
	#define CS5	(P9L.4)
	
	#define ENAD	(P9L.3)
	#define ENDA	(PCT.1)
	#define RW	(PCT.0)
	#define BUSY	(PCM.3)
	#define CON	(PCM.2)
	
	#define NSLP	(P3L.2)
	#define ERR	(P4.0)
	#define EN	(P4.1)
	#define STB	(P4.2)
	
	
	
	/*
	 * Specify the Data Bus[23..0], and its corresponding pin.
	 */
	
	// Data bus [0 .. 23]
	#define DB00	(P7L.0)		// P70
	#define DB01	(P7L.1)		// P71
	#define	DB02	(P7L.2)		// P72
	#define	DB03	(P7L.3)		// P73
	#define	DB04	(P7L.4)
	#define DB05	(P7L.5)
	#define DB06	(P7L.6)
	#define DB07	(P7L.7)
	#define DB08	(P7H.0)
	#define DB09	(P7H.1)
	#define DB10	(P7H.2)
	#define DB11	(P7H.3)
	#define DB12	(P7H.4)
	#define DB13	(P7H.5)
	#define DB14	(P7H.6)
	#define DB15	(P7H.7)
	#define DB16	(PDLH.5)
	#define DB17	(PDLH.4)
	#define DB18	(PDLH.3)
	#define DB19	(PDLH.2)
	#define DB20	(PDLH.1)
	#define DB21	(PDLH.0)
	#define DB22	(PDLL.7)
	#define DB23	(PDLH.6)
	
	// Address bus [0 .. 7]
	#define A0	(PCM.1)
	#define A1	(PCM.0)
	#define A2	(PCS.1)
	#define A3	(PCS.0)
	#define A4	(P9H.5)
	#define A5	(P9H.4)
	#define A6	(P9H.3)
	#define A7	(P9H.2)
	
	#define ADD0	A0
	#define ADD1	A1
	#define ADD2	A2
	#define ADD3	A3
	#define ADD4	A4
	#define ADD5	A5
	#define ADD6	A6
	#define ADD7	A7
	
	// Digital IN bus [0 .. 23]
	#define DIN00	(PDLL.5)
	#define DIN01	(PDLL.4)
	#define DIN02	(PDLL.3)
	#define DIN03	(PDLL.2)
	#define DIN04	(PDLL.1)
	#define DIN05	(PDLL.0)
	#define DIN06	(PCT.6)
	#define DIN07	(PCT.4)
	#define DIN08	(P9L.2)
	#define DIN09	(P9L.1)
	#define DIN10	(P9L.0)
	#define DIN11	(P5.1)
	#define DIN12	(P5.0)
	#define DIN13	(P3L.7)
	#define DIN14	(P3L.6)
	#define DIN15	(P3L.5)
	#define DIN16	(P0.6)
	#define DIN17	(P0.4)
	#define DIN18	(P0.3)
	#define DIN19	(P0.2)
	#define DIN20	(P0.1)
	#define DIN21	(P0.0)
	#define DIN22	(P1.1)
	#define DIN23	(P1.0)
	
	// Digital OUT bus [0 .. 23]
	#define DOUT00	DB00
	#define DOUT01	DB01
	#define DOUT02	DB02
	#define DOUT03	DB03
	#define DOUT04	DB04
	#define DOUT05	DB05
	#define DOUT06	DB06
	#define DOUT07	DB07
	#define DOUT08	DB08
	#define DOUT09	DB09
	#define DOUT10	DB10
	#define DOUT11	DB11
	#define DOUT12	DB12
	#define DOUT13	DB13
	#define DOUT14	DB14
	#define DOUT15	DB15
	#define DOUT16	DB16
	#define DOUT17	DB17
	#define DOUT18	DB18
	#define DOUT19	DB19
	#define DOUT20	DB20
	#define DOUT21	DB21
	#define DOUT22	DB22
	#define DOUT23	DB23
	
	
	
	typedef enum CONTROL_PIN_LEVEL
	{
		CONTROL_PIN_LOW = 0,
		CONTROL_PIN_HIGH = 1
	}
	E_CTRL_PIN_LEVEL;
	
	
	
	
/*======================================================================================================================================================================================================*/
	void Write_Address_Bus(BYTE btAddrBus_bit7_0);
	
	#if 0
		/*
		 * This "Read address bus" will not function any more, because the hardware design
		 * has limited that address bus can only output (i.e.  write direction), 
		 * no input (i.e.  read direction).
		 * 
		 * Disabled by XU ZAN@2012-10-20
		 */
		BYTE Read_Address_Bus();
	#endif
	
	int Read_ADCInput_DataBus_from_DB15_to_DB00();
	
	
	void Set_DataBus_from_DB07_to_DB00(BYTE btLowByte_Value);
	void Set_DataBus_from_DB15_to_DB08(BYTE btMiddleByte_Value);
	void Set_DataBus_from_DB23_to_DB16(BYTE btHighByte_Value);
	
	void Write_All_DataBus(unsigned int uiDBValue);
	
	void Write_DataBus_Single_CHn(     DWORD   dwCHn,
				      enum LEVEL   eSpecificLevelValue);
	
	DWORD Read_DataBus_State_from_DB23_to_DB00(void);
	
	
	DWORD Read_Digital_In_Bus_Value();
	
	void Set_DataBus_to_Initial_Default_State_After_Power_ON();
	
	void Set_AddressBus_to_Initial_Default_State_After_Power_ON();
	
	void Set_ControlBus_to_Initial_Default_State_After_Power_ON();
	void Set_Initial_Default_State_After_Power_ON();
	
	
	/*****************************************************************/
	#if defined (UNUSED)
		void Control_Port_Mutx_From_Switch_to_ADC(E_CTRL_PIN_LEVEL eCtrl_Pin_CS0);
		void Control_Port_Mutx_From_ADC_to_Switch(E_CTRL_PIN_LEVEL eCtrl_Pin_ENAD);
		void Control_Port_Mutx_From_ADC_to_DAC(E_CTRL_PIN_LEVEL eCtrl_Pin_ENAD);
		void Control_Port_Mutx_From_DAC_to_ADC(E_CTRL_PIN_LEVEL eCtrl_Pin_ENDA);
	#endif	/* End UNUSED */
	
	


#endif	/*    _BUS_H    */

