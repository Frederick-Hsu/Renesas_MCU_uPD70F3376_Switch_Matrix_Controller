/***********************************************************************************************************
 * Program name	: Just_test_and_debug.h
 * Description	: This file is used to dedicatedly test and debug all function modules. 
 *		: You can write the test functions freely.
 * Author	: XU ZAN
 * Date		: Sat.	Oct. 27, 2012
 * Copyright(C)		2010 --- 2012	Hella (Shanghai) Electronics Co., Ltd.
 * All rights reserved.
 *
 ***********************************************************************************************************/
 
#ifndef _JUST_TEST_AND_DEBUG_H
#define _JUST_TEST_AND_DEBUG_H

	
 
	#define TEST_DEBUG_PURPOSE

	#if defined (TEST_DEBUG_PURPOSE)
	
	 	void SetInitialState_TurnOffAllSwitches(void);
		
		void Enable_All_Switches();
	 
	 	void Test_Switch_Ctrl(void);
		
		void Print_ADC_Values_8Channels(void);
		
		void Test_MCU_Chip_System(void);
	
	#endif	/*    TEST_DEBUG_PURPOSE    */
	
 	
 
#endif	 /*    _JUST_TEST_AND_DEBUG_H    */

