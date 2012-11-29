/******************************************************************************
 * Program name	: ADC_to_Measure_Current.c
 * Description	: By using the combination of both AD976BR chip and AD628AR 
 *		  operation amplifier, implement how to measure the current.
 * Author	: XU ZAN
 * Date		: Thu.	July 26, 2012
 * Copyright(C)		2010 --- 2012	Hella (Shanghai) Electronics Co., Ltd.
 * All rights reserved.
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdarg.h>
#include "ADC_to_Measure_Voltage_Current.h"


float Measure_Single_CHn_Current(E_ADC_CH 	eCHn,
				float 		fScalingCoefficient,
				float 		fMediaResistor_unit_ohm)
{
	float fTempCurrent = 0.0000f;	// current unit : A
	float fTempVoltage = 0.0000f;	// voltage unit : V
	
	fTempVoltage = Measure_Single_CHn_Voltage_Value(eCHn, fScalingCoefficient);
	
	fTempCurrent = fTempVoltage / fMediaResistor_unit_ohm;
	
	return (fTempCurrent);
}

void Measure_Multi_CHs_Current_Values(PST_ADC_CHn_Current pCHn_Current, ...)
{
	float fTempCurrent = 0.0000f;
	
	va_list marker;
	PST_ADC_CHn_Current next = pCHn_Current;
	
	va_start(marker, pCHn_Current);
	while (next != NULL)
	{
		fTempCurrent = Measure_Single_CHn_Current(next->eCHn,
							  next->fScalingCoefficient,
							  next->fMediaResistor_unit_ohm);
		next->fCurrent = &fTempCurrent;
		
		next = va_arg(marker, PST_ADC_CHn_Current);
	}
	va_end(marker);
	
	return;
}

