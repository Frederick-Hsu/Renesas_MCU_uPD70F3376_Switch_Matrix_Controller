/*************************************************************************************
 * Program name	: utility.c
 * Description	: Implements some utility functions.
 * Author	: XU ZAN
 * Date		: Tue.	Aug. 7, 2012
 * Copyright(C)		2010 --- 2012	Hella (Shanghai) Electronics Co., Ltd.
 * All rights reserved.
 *
 *************************************************************************************/


#include "utility.h"


long power(int iBase, int iPow)
{
	int i = 0;
	
	long lProduct = 1;
	
	for (i = 1; i <= iPow; i++)
	{
		lProduct = lProduct * iBase;
	}
	
	return lProduct;
}

void ToUpperString(char *String)
{
	size_t i = 0;
	char cTempChar = '0';
	size_t iLenOfString = strlen(String);

	for (i=0; i<iLenOfString; i++)
	{
		cTempChar = toupper(String[i]);
		String[i] = cTempChar;
	}
	return;
}

void ToLowerString(char *String)
{
	int i = 0;
	char cTempChar = '0';
	int iLenOfString = strlen(String);

	for (i=0; i<iLenOfString; i++)
	{
		cTempChar = tolower(String[i]);
		String[i] = cTempChar;
	}
	return;
}

int Convert_Str_To_Int(char *sDigitString, long *lDestVal)
/************************************************************************
 * Function name: Convert_Str_To_Int
 *
 * Purpose	: Convert the hex format or decimal format string into
 *				  integer value.
 *
 * IN argument	: sDigitString
 * OUT argument	: lDestVal
 * Returns	: error number
 *
 * Caution	: This function can only support the hex and decimal format
 *		: IN argument, other formats (e.g. bin or octal) are not 
 *		: supported. 
 *		: and what's more important, the hex format argument must
 *		: be signed explicitly. for example : 0x5D, 69H, 0XFE, 80h,
 *		: otherwise, it could be treated as a decimal format or 
 *		: directly an error.
 ************************************************************************/
{
	int iError = 0;
	size_t i = 0;
	int iLeapStep = 0;

	long lTempValue = 0;

	char sPrefix_Sign[2] = ""; 
	char sSuffix_Sign = '0';
	char cTempChar[2] = "";

	if ( (strncmp(sDigitString, "0x", 2) == 0) || 
	     (strncmp(sDigitString, "0X", 2) == 0) ||
	     (strncmp(sDigitString+strlen(sDigitString)-1, "h", 1) == 0) ||
	     (strncmp(sDigitString+strlen(sDigitString)-1, "H", 1) == 0)		// Explicit Hex format condition
	   )
	{
		for (i=strlen(sDigitString); i>0; i--)
		{
			strncpy(cTempChar, sDigitString+i-1, 1);
			if ( !((cTempChar[0] == 'H') || (cTempChar[0] == 'h')) )
			{
				if ( (cTempChar[0] == 'X') || (cTempChar[0] == 'x') )	// For this condition, it tells the Hex sign "0x" or "0X" have been found, it should break out.
				{
					break;
				}
				if ( ((cTempChar[0] >= '0') && (cTempChar[0] <= '9')) ||
				     ((cTempChar[0] >= 'A') && (cTempChar[0] <= 'F')) ||
				     ((cTempChar[0] >= 'a') && (cTempChar[0] <= 'f')) )
				{
					// lTempValue += atoi(cTempChar) * power(16, (i-strlen(sDigitString))*(-1));
					lTempValue += Convert_Hex_Char_To_Int(cTempChar[0])* power(16, ((i-strlen(sDigitString))*(-1)-iLeapStep)); 
				}
				else
				{
					return -1;
				}
			}
			else if ((cTempChar[0] == 'H') || (cTempChar[0] == 'h'))
			{
				iLeapStep++;
			}
		}
	}
	else	// Decimal format condition
	{
		for (i=strlen(sDigitString); i>0; i--)
		{
			strncpy(cTempChar, sDigitString+i-1, 1);
			if ( ((cTempChar[0] >= '0') && (cTempChar[0] <= '9')) )
			{
				lTempValue += Convert_Hex_Char_To_Int(cTempChar[0]) * power(10, (i-strlen(sDigitString))*(-1));
			}
			else
			{
				return -1;
			}
		}
	}

	*lDestVal = lTempValue;
	return iError;
}

int Convert_Hex_Char_To_Int(char cHexChar)
{
	unsigned int iConvertedValue = 0;
	switch (cHexChar)
	{
	case 'A' :
	case 'a' :
		iConvertedValue = 10;
		break;
	case 'B' :
	case 'b' :
		iConvertedValue = 11;
		break;
	case 'C' :
	case 'c' :
		iConvertedValue = 12;
		break;
	case 'D' :
	case 'd' :
		iConvertedValue = 13;
		break;
	case 'E' :
	case 'e' :
		iConvertedValue = 14;
		break;
	case 'F' :
	case 'f' :
		iConvertedValue = 15;
		break;
	case '0' :
	case '1' :
	case '2' :
	case '3' :
	case '4' :
	case '5' :
	case '6' :
	case '7' :
	case '8' :
	case '9' :
		iConvertedValue = atoi(&cHexChar);
		break;
	default :
		iConvertedValue = 0;
		break;
	}
	return iConvertedValue;
}

