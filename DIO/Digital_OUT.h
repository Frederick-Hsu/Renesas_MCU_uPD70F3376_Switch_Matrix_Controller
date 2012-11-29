/******************************************************************************************
 * Program name	: Digital_OUT.h
 * Description	: The declaration for Digital_OUT module.
 * Author	: XU ZAN
 * Date		: Fri.	July 27, 2012
 * Copyright(C)		2010 --- 2012	Hella (Shanghai) Electronics Co., Ltd.
 * All rights reserved.
 *
 ******************************************************************************************/

#ifndef _DIGITAL_OUT_H
#define _DIGITAL_OUT_H

	#include "..\Switch_Relay_Control\Switch_Relay_Control.h"
	
	void DOUT_Single_CHn(PST_Access_Ctrl_SwitchRelayMatrix pSingle_DOUT_CHn);
	void DOUT_Multi_CHn(PST_Access_Ctrl_SwitchRelayMatrix pSingle_DOUT_CHi, ...);

#endif	/*    _DIGITAL_OUT_H    */

