/*****************************************************************************************
 * Program name	: ADC_and_DAC.h
 * Description	: In this module, it implements the ADC and DAC functions.
 *		  ADC : acquiring and measuring external analog input voltage;
 *		  DAC : outputing the analog voltage to drive external device.
 * Author	: XU ZAN
 * Date		: Thu.	July 26, 2012
 * Copyright(C)		2010 --- 2012		Hella (Shanghai) Electronics Co., Ltd.
 * All rights reserved.
 *
 *****************************************************************************************/
 
#ifndef _ADC_AND_DAC_H
#define _ADC_AND_DAC_H
 
	#include "..\macrodriver.h"

	typedef enum ADC_CHANNEL
	{
		ADC_CH0 = 0,
		ADC_CH1 = 1,
		ADC_CH2 = 2,
		ADC_CH3 = 3,
		ADC_CH4 = 4,
		ADC_CH5 = 5,
		ADC_CH6 = 6,
		ADC_CH7 = 7
	}
	E_ADC_CH;
	
	typedef struct ADC_Values_Multi_CHs
	{
		E_ADC_CH eADC_CHn;
		float *fAnalogInputValue;
	}
	*PST_ADC_Values_Multi_CHs;
	
	
	/*==========================================================================================================*/
	void Select_ADC_CHn_ON(E_ADC_CH enumCHn);
	
	void Enable_ADC_CHNL_Selector_Chip_ADG1208();
	void Disable_ADC_CHNL_Selector_Chip_ADG1208();
	
	void Enable_DAC_Chip_DAC0832();
	void Disable_DAC_Chip_DAC0832();
	
	void Write_DAC_Value_to_Chip_DAC0832(BYTE btDAV_Value_DataBus_bit7_0);
	/*==========================================================================================================*/
	
	void ADC_Acquiring_AnalogInputValue(E_ADC_CH 	eADC_CHn, 
					    int 	*iAIN_Value);
	
	void ADC_Get_8CHs_AINValue(int iAIN_Value[]);
	
	void Calculate_Analog_Input_Value_for_1Ch(E_ADC_CH 	eADC_CHn, 
						  float 	*fAnalogInputValue);
	
	void Calculate_Multi_CHs_ADC_AIN_Values(PST_ADC_Values_Multi_CHs pADC_CHi_Value, ...);
	
	void Calculate_Analog_Input_Value_for_8Chs(float fAnalogInputValues8Chs[]);
	
	
	/*==========================================================================================================*/
	float DAC_Output_Voltage(BYTE byteDigital_Input);
	float DAC_CommonMode_Output(BYTE bDigitalIn);

#endif	/*    _ADC_AND_DAC_H    */

