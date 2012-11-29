/******************************************************************************************
 * Program name	: Digital_OUT.c
 * Description	: The implementation for Digital_OUT module.
 * Author	: XU ZAN
 * Date		: Fri.	July 27, 2012
 * Copyright(C)		2010 --- 2012	Hella (Shanghai) Electronics Co., Ltd.
 * All rights reserved.
 *
 ******************************************************************************************/

#include <stdarg.h>
#include <stdio.h>
#include "Digital_OUT.h"

void DOUT_Single_CHn(PST_Access_Ctrl_SwitchRelayMatrix pSingle_DOUT_CHn)
{
	Control_Single_Switch(pSingle_DOUT_CHn);
}

void DOUT_Multi_CHn(PST_Access_Ctrl_SwitchRelayMatrix pSingle_DOUT_CHi, ...)
{
	va_list marker;
	PST_Access_Ctrl_SwitchRelayMatrix next = pSingle_DOUT_CHi;
	
	va_start(marker, pSingle_DOUT_CHi);
	while (next != NULL)
	{
		DOUT_Single_CHn(next);
		next = va_arg(marker, PST_Access_Ctrl_SwitchRelayMatrix);
	}
	va_end(marker);
	
	return;
}

