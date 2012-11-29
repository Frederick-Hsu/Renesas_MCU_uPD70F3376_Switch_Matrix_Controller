/***********************************************************************************************************
 * Program name	: Just_test_and_debug.c
 * Description	: This file is used to dedicatedly test and debug all function modules. 
 *		: You can write the test functions freely.
 * Author	: XU ZAN
 * Date		: Sat.	Oct. 27, 2012
 * Copyright(C)		2010 --- 2012	Hella (Shanghai) Electronics Co., Ltd.
 * All rights reserved.
 *
 ***********************************************************************************************************/


#include "Just_test_and_debug.h"
 
#include "Switch_Relay_Control\Switch_Relay_Control.h"
#include "bus.h"


/*************************************************************************/
//  External global variables :
#include "heap_memory_area.h"
extern int __sysheap[SIZEOF_HEAP>>2];
extern size_t __sizeof_sysheap;




#if defined (TEST_DEBUG_PURPOSE)

	void SetInitialState_TurnOffAllSwitches(void)
	{
		CS0 = LOW;
		RW = HIGH;
		
		/*
		 * Shielding the influence on ADC and DAC
		 */
		ENDA = HIGH;
		ENAD = LOW;
		
		Write_Address_Bus(0x01);
		Write_All_DataBus(0x00000000);
		
		/*
		 * At last, you should disable the Address selector chip 74ALS520.
		 * In order to keep the current state of switches.
		 */
		CS0 = HIGH;
		
		return;
	}


	 
	void Test_Switch_Ctrl(void)
	{
		#if 1
			int i = 0;
			PST_Access_Ctrl_SwitchRelayMatrix pSwitch  = (PST_Access_Ctrl_SwitchRelayMatrix)malloc(sizeof(ST_Access_Ctrl_SwitchRelayMatrix)),
							  pSwitch1 = (PST_Access_Ctrl_SwitchRelayMatrix)malloc(sizeof(ST_Access_Ctrl_SwitchRelayMatrix)),
							  pSwitch2 = (PST_Access_Ctrl_SwitchRelayMatrix)malloc(sizeof(ST_Access_Ctrl_SwitchRelayMatrix)),
							  pSwitch3 = (PST_Access_Ctrl_SwitchRelayMatrix)malloc(sizeof(ST_Access_Ctrl_SwitchRelayMatrix)),
							  pSwitch4 = (PST_Access_Ctrl_SwitchRelayMatrix)malloc(sizeof(ST_Access_Ctrl_SwitchRelayMatrix)),
							  pSwitch5 = (PST_Access_Ctrl_SwitchRelayMatrix)malloc(sizeof(ST_Access_Ctrl_SwitchRelayMatrix));
			
			pSwitch->byteBoardID = 0x01;
			pSwitch->dwSwitch_Relay_CHn = 5;
			pSwitch->eOpen_Close_State = CLOSE;
			
			/**************************************************************************/
			pSwitch1->byteBoardID = 0x01;
			pSwitch1->dwSwitch_Relay_CHn = 3;
			pSwitch1->eOpen_Close_State = CLOSE;
			
			pSwitch2->byteBoardID = 0x01;
			pSwitch2->dwSwitch_Relay_CHn = 23;
			pSwitch2->eOpen_Close_State = CLOSE;
			
			pSwitch3->byteBoardID = 0x01;
			pSwitch3->dwSwitch_Relay_CHn = 17;
			pSwitch3->eOpen_Close_State = CLOSE;
			
			pSwitch4->byteBoardID = 0x01;
			pSwitch4->dwSwitch_Relay_CHn = 10;
			pSwitch4->eOpen_Close_State = CLOSE;
			
			pSwitch5->byteBoardID = 0x01;
			pSwitch5->dwSwitch_Relay_CHn = 5;
			pSwitch5->eOpen_Close_State = OPEN;
			/**************************************************************************/
			
			
			
			Control_Single_Switch(pSwitch);
			
			
			for (i=0; i<5000000; i++)
			{
				NOP();
			}
			Control_Multi_Switch(pSwitch1, pSwitch2, pSwitch3, pSwitch4, pSwitch5);
			
			free(pSwitch);
			free(pSwitch1);
			free(pSwitch2);
			free(pSwitch3);
			free(pSwitch4);
			free(pSwitch5);
		#endif
		
		
		
		
		
		
	/*******************************************************/
		return;
	}
	
	void Enable_All_Switches()
	{
		CS0 = LOW;
		RW = HIGH;
	
		ENDA = HIGH;
		ENAD = LOW;
		
		Write_Address_Bus(0x01);
		Write_All_DataBus(0x0000FFFF);
		CS0 = HIGH;
		
		return;
	}
	
	void Print_ADC_Values_8Channels(void)
	{
		int iADCValue[8] = {0};
		char sADC_8CHs_Value[512] = {0};
		
		ADC_Get_8CHs_AINValue(iADCValue);
		
		sprintf(sADC_8CHs_Value,
			"ADC Value : %d,\t%d,\t%d,\t%d,\t%d,\t%d,\t%d,\t%d\n\n", 
			iADCValue[0], 
			iADCValue[1], 
			iADCValue[2],
			iADCValue[3],
			iADCValue[4],
			iADCValue[5],
			iADCValue[6],
			iADCValue[7]);
			
		UARTD2_SendData(sADC_8CHs_Value, strlen(sADC_8CHs_Value)*sizeof(char));
		
		return;
	}
	
	void Test_MCU_Chip_System(void)
	{
		int iBit = 12315;
		char sTemp[128] = {0};
		
		sprintf(sTemp, "This MCU chip is a %d-byte system.\n\n", sizeof(iBit));
		UARTD2_SendData(sTemp, strlen(sTemp)*sizeof(char));
		
		return;
	}

#endif	/*    TEST_DEBUG_PURPOSE    */

