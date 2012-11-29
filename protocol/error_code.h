/**************************************************************************************************
 * Program name	: error_code.h
 * Description	: List all error-code numbers in this file, these error-code numbers could be
 *		  referred and called in the entire project.
 * Author	: XU ZAN
 * Date		: Thur.		Sept. 13, 2012
 * Copyright(C)		2010 --- 2012		Hella (Shanghai) Electronics Co., Ltd.
 * All rights reserved.
 *
 **************************************************************************************************/

 
#ifndef _ERROR_CODE_H
#define _ERROR_CODE_H

	char sErrorCode[][256] = 
	{
		"Error code # 000: No error!\n",
		"Error code # 001: Command Syntax error\n",
		"Error code # 002: Not exists this action catalog\n",
		"Error code # 003: Switch Board ID error\n",
		"Error code # 004: Switch action command error\n",
		"Error code # 005: Switch channel error\n",
		"Erroe code # 006: Switch state error\n",
		"Error code # 007: Action keyword 'SWITCH' error\n",
		""
	};


#endif	/*    _ERROR_CODE_H    */

