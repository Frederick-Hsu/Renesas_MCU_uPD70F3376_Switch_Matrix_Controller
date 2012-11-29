/*************************************************************************************
 * Program name	: utility.h
 * Description	: Defines some utility functions.
 * Author	: XU ZAN
 * Date		: Tue.	Aug. 7, 2012
 * Copyright(C)		2010 --- 2012	Hella (Shanghai) Electronics Co., Ltd.
 * All rights reserved.
 *
 *************************************************************************************/
 
#ifndef _UTILITY_H
#define _UTILITY_H

	/*===============================================================*/
	// Includes : 
	#include <string.h>
	#include <ctype.h>
	#include <stdlib.h>
	
	
	/*===============================================================*/
	// Macros : 
	
	
	
	/*===============================================================*/
	// Global variables :
	
	
	
	/*===============================================================*/
	// Function prototypes :
	long power(int iBase, int iPow);
	

	void ToUpperString(char *String);

	void ToLowerString(char *String);

	int Convert_Str_To_Int(char *sDigitString, long *lDestVal);

	int Convert_Hex_Char_To_Int(char cHexChar);



#endif	/*    _UTILITY_H    */

