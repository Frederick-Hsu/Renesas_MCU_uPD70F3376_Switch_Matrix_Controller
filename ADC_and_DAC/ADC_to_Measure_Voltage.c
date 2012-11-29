/******************************************************************************
 * Program name	: ADC_to_Measure_Voltage.c
 * Description	: Implement the measurement function of voltage-acquiring.
 * Author	: XU ZAN
 * Date		: Thu.	July 26, 2012
 * Copyright(C)		2010 --- 2012	Hella (Shanghai) Electronics Co., Ltd.
 * All rights reserved.
 *
 ******************************************************************************/

/*========================================================================================================*/
// Includes : 
#include <stdio.h>
#include <stdarg.h>
#include "ADC_to_Measure_Voltage_Current.h"


/*========================================================================================================*/
// Macros :
#define SCALING_COEFFICIENT_FIXED_BY_REXT		1
#define SCALING_COEFFICIENT_DETERMINED_BY_USER		2

#define SCALING_COEFFICIENT	SCALING_COEFFICIENT_FIXED_BY_REXT


/*========================================================================================================*/
// Global variables :

/*
 * How to calculate the scaling coefficient of the operation amplifier? 
 * Scaling coefficient is the system total gain.
 * 
 * Formula :  
 * 	Gtotal = 0.1 * (1 + Rext1/Rext2) = 0.1
 * 
 * But the operation-amplifier (chip AD628AR) acts as a shrink device, so the scaling coefficient is 1/Gtotal.
 *
 */
 static const float g_fScalingCoefficient_FixedByRext = 10.00f;



/*========================================================================================================*/
// Function implementations :
float Measure_Single_CHn_Voltage_Value(E_ADC_CH 	eCHn,
			               float		fScalingCoefficient)
{
	float fVoltage = 0.0000f;
	
	Calculate_Analog_Input_Value_for_1Ch(eCHn, &fVoltage);
	
	#if (SCALING_COEFFICIENT == SCALING_COEFFICIENT_FIXED_BY_REXT)
	
		fVoltage = fVoltage * g_fScalingCoefficient_FixedByRext;
		
	#elif (SCALING_COEFFICIENT == SCALING_COEFFICIENT_DETERMINED_BY_USER)
	
		fVoltage = fVoltage * fScalingCoefficient;
	
	#endif
	
	return fVoltage;
}


void Measure_8CHs_Voltage_Values(float 	fUniformScalingCoefficient, 
				 float 	f8CHsVoltageValues[])
{
	int i = 0;
	float fTemp8CHsVoltage[8] = {0.0000f};
	
	Calculate_Analog_Input_Value_for_8Chs(fTemp8CHsVoltage);
	
	for (i=0; i<8; i++)
	{
		#if (SCALING_COEFFICIENT == SCALING_COEFFICIENT_FIXED_BY_REXT)
	
			f8CHsVoltageValues[i] = fTemp8CHsVoltage[i] * g_fScalingCoefficient_FixedByRext;
		
		#elif (SCALING_COEFFICIENT == SCALING_COEFFICIENT_DETERMINED_BY_USER)
	
			f8CHsVoltageValues[i] = fTemp8CHsVoltage[i] * fUniformScalingCoefficient;
	
		#endif
	}
	return;
}


void Measure_Multi_CHs_Voltage_Values(PST_ADC_CHn_Voltage pCHn_Voltage, ...)
{
	float fTempVoltage = 0.0000f;
	
	va_list marker;
	
	PST_ADC_CHn_Voltage next = pCHn_Voltage;
	va_start(marker, pCHn_Voltage);
	while (next != NULL)
	{
		Calculate_Analog_Input_Value_for_1Ch(next->eCHn, &fTempVoltage);
		#if (SCALING_COEFFICIENT == SCALING_COEFFICIENT_FIXED_BY_REXT)
			fTempVoltage *= g_fScalingCoefficient_FixedByRext;
		#elif (SCALING_COEFFICIENT == SCALING_COEFFICIENT_DETERMINED_BY_USER)
			fTempVoltage *= next->fScalingCoefficient;
		#endif
		
		next->fVoltage = &fTempVoltage;
		
		next = va_arg(marker, PST_ADC_CHn_Voltage);
	}
	va_end(marker);
	
	return;
}

