/********************************************************************************************
 * Program name	: ADC_to_Measure_Voltage_Current.h
 * Description	: Functions prototype of measuring voltage & current with ADC.
 * Author	: XU ZAN
 * Date		: Tue.	Aug. 7, 2012
 * Copyright(C)		2010 --- 2012		Hella (Shanghai) Electronics Co., Ltd.
 * All rights reserved.
 *
 ********************************************************************************************/

 
#ifndef _ADC_TO_MEASURE_VOLTAGE_CURRENT_H
#define _ADC_TO_MEASURE_VOLTAGE_CURRENT_H

	/*==================================================================================*/
	// Includes :
	#include "ADC_and_DAC.h"
	
	
	/*==================================================================================*/
	// type definitions : 
	typedef struct ADC_CHn_Voltage
	{
		E_ADC_CH 	eCHn;
		float		fScalingCoefficient;
		float 		*fVoltage;		// unit : V
	}
	ST_ADC_CHn_Voltage, *PST_ADC_CHn_Voltage;
	
	typedef struct ADC_CHn_Current
	{
		E_ADC_CH	eCHn;
		float		fScalingCoefficient;
		float		fMediaResistor_unit_ohm;
		float		*fCurrent;		// unit : A
	}
	ST_ADC_CHn_Current, *PST_ADC_CHn_Current;
	
	
	

	/*==================================================================================*/
	// Function prototypes :
	float Measure_Single_CHn_Voltage_Value(E_ADC_CH	eCHn,
			       		       float	fScalingCoefficient);
	
	void Measure_8CHs_Voltage_Values(float 	fUniformScalingCoefficient, 
					 float 	f8CHsVoltageValues[]);
	
	void Measure_Multi_CHs_Voltage_Values(PST_ADC_CHn_Voltage pCHn_Voltage, ...);
	
	/*-----------------------------------------------------------------------------------*/
	
	float Measure_Single_CHn_Current(E_ADC_CH 	eCHn,
					 float 		fScalingCoefficient,
					 float 		fMediaResistor_unit_ohm);

	void Measure_Multi_CHs_Current_Values(PST_ADC_CHn_Current pCHn_Current, ...);
	
	

#endif	/*    _ADC_TO_MEASURE_VOLTAGE_CURRENT_H    */

