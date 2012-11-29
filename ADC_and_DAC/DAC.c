/********************************************************************************************
 * Program name	: DAC.c
 * Description	: The implementation on DAC function module.
 * Author	: XU ZAN
 * Date		: Thu.	July 26, 2012
 * Copyright(C)		2010 --- 2012		Hella (Shanghai) Electronics Co., Ltd.
 * All rights reserved.
 *
 ********************************************************************************************/
 
/*===================================================================================*/
// Includes :
#include "ADC_and_DAC.h"
#include "..\bus.h"


/*===================================================================================*/
// Macros :





/*===================================================================================*/
// Global variables :
static const float g_fDACScalingFactor = 7.0000f;	// This value need to be rectified during in-circuit debugging.

void Write_DAC_Value_to_Chip_DAC0832(BYTE btDAV_Value_DataBus_bit7_0)
{
	RW = HIGH;	// Enable the sending direction.
	/*
	 * DAC 8-bit Data Bus :
	 * ------+------+------+------+------+------+------+------+
	 *   7   |  6   |  5   |  4   |  3   |  2   |  1   |  0   |
	 * ------+------+------+------+------+------+------+------+
	 *  DB07 | DB06 | DB05 | DB04 | DB03 | DB02 | DB01 | DB00 |
	 * ------+------+------+------+------+------+------+------+
	 *  P77  | P76  | P75  | P74  | P73  | P72  | P71  | P70  |
	 * ------+------+------+------+------+------+------+------+
	 *
	 */
	PORT_ChangeP77Output((btDAV_Value_DataBus_bit7_0 & 0x80) >> 7);
	PORT_ChangeP76Output((btDAV_Value_DataBus_bit7_0 & 0x40) >> 6);
	PORT_ChangeP75Output((btDAV_Value_DataBus_bit7_0 & 0x20) >> 5);
	PORT_ChangeP74Output((btDAV_Value_DataBus_bit7_0 & 0x10) >> 4);
	PORT_ChangeP73Output((btDAV_Value_DataBus_bit7_0 & 0x08) >> 3);
	PORT_ChangeP72Output((btDAV_Value_DataBus_bit7_0 & 0x04) >> 2);
	PORT_ChangeP71Output((btDAV_Value_DataBus_bit7_0 & 0x02) >> 1);
	PORT_ChangeP70Output((btDAV_Value_DataBus_bit7_0 & 0x01)     );
}

void Enable_DAC_Chip_DAC0832()
{
	ENDA = LOW;	// PCT1 = ENDA, while LOW is active
}

void Disable_DAC_Chip_DAC0832()
{
	ENDA = HIGH;
}

float DAC_Output_Voltage(BYTE byteDigital_Input)
{
	float fDAC_Voltage = 0.0000f;	// unit : V
	
	Enable_DAC_Chip_DAC0832();
	/*
	 * Shielding the influence on ADC and switch output
	 */
	ENAD = LOW;
	CS0  = HIGH;
	
	Write_DAC_Value_to_Chip_DAC0832(byteDigital_Input);
	
	return fDAC_Voltage;
}

float DAC_CommonMode_Output(BYTE bDigitalIn)
{
	float fDACOutput = 0.0000f;
	
	/*
	 * I don't know how to calculate the relationship between AOUT and DB[0..7]
	 * Awaiting for the formula ti implement this function.
	 */
	
	return fDACOutput;
}

