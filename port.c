/*
*******************************************************************************
**
**  This device driver was created by Applilet2 for V850ES/Fx3
**  32-Bit Single-Chip Microcontrollers
**
**  Copyright(C) 2002, 2012 Renesas Electronics Corporation
**  All rights reserved by Renesas Electronics Corporation.
**
**  This program should be used on your own responsibility.
**  Renesas Electronics Corporation assumes no responsibility for any losses
**  incurred by customers or third parties arising from the use of this file.
**
**  Filename :	port.c
**  Abstract :	This file implements device driver for PORT module.
**  APIlib :	Applilet2 for V850ES/Fx3 V2.43 [30 Mar 2011]
**
**  Device :	uPD70F3376
**
**  Compiler :	CA850
**
**  Creation date:	09/26/2012
**  
*******************************************************************************
*/

/*
*******************************************************************************
**  Include files
*******************************************************************************
*/
#include "macrodriver.h"
#include "port.h"
/* Start user code for include definition. Do not edit comment generated here */
/* End user code for include definition. Do not edit comment generated here */
#include "user_define.h"

/*
*******************************************************************************
**  Global define
*******************************************************************************
*/
/* Start user code for global definition. Do not edit comment generated here */
/* End user code for global definition. Do not edit comment generated here */


/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function initializes the Port I/O.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_Init(void)
{

	PM0 = PMn0_MODE_INPUT | PMn1_MODE_INPUT | PMn2_MODE_INPUT | PMn3_MODE_INPUT | PMn4_MODE_INPUT | PMn5_MODE_DEFAULT | PMn6_MODE_INPUT | PMn7_MODE_DEFAULT;
	PM1 = PMn0_MODE_INPUT | PMn1_MODE_INPUT | PMn2_MODE_DEFAULT | PMn3_MODE_DEFAULT | PMn4_MODE_DEFAULT | PMn5_MODE_DEFAULT | PMn6_MODE_DEFAULT | PMn7_MODE_DEFAULT;
	PM3L = PMn0_MODE_DEFAULT | PMn1_MODE_DEFAULT | PMn2_MODE_OUTPUT | PMn3_MODE_DEFAULT | PMn4_MODE_DEFAULT | PMn5_MODE_INPUT | PMn6_MODE_INPUT | PMn7_MODE_INPUT;
	PM4 = PMn0_MODE_OUTPUT | PMn1_MODE_OUTPUT | PMn2_MODE_OUTPUT | PMn3_MODE_DEFAULT | PMn4_MODE_DEFAULT | PMn5_MODE_DEFAULT | PMn6_MODE_DEFAULT | PMn7_MODE_DEFAULT;
	PM5 = PMn0_MODE_INPUT | PMn1_MODE_INPUT | PMn2_MODE_DEFAULT | PMn3_MODE_DEFAULT | PMn4_MODE_DEFAULT | PMn5_MODE_DEFAULT | PMn6_MODE_DEFAULT | PMn7_MODE_DEFAULT;
	PM7L = PMn0_MODE_OUTPUT | PMn1_MODE_OUTPUT | PMn2_MODE_OUTPUT | PMn3_MODE_OUTPUT | PMn4_MODE_OUTPUT | PMn5_MODE_OUTPUT | PMn6_MODE_OUTPUT | PMn7_MODE_OUTPUT;
	PM7H = PMn0_MODE_OUTPUT | PMn1_MODE_OUTPUT | PMn2_MODE_OUTPUT | PMn3_MODE_OUTPUT | PMn4_MODE_OUTPUT | PMn5_MODE_OUTPUT | PMn6_MODE_OUTPUT | PMn7_MODE_OUTPUT;
	PM9L = PMn0_MODE_INPUT | PMn1_MODE_INPUT | PMn2_MODE_INPUT | PMn3_MODE_OUTPUT | PMn4_MODE_OUTPUT | PMn5_MODE_OUTPUT | PMn6_MODE_OUTPUT | PMn7_MODE_OUTPUT;
	PM9H = PMn0_MODE_OUTPUT | PMn1_MODE_OUTPUT | PMn2_MODE_OUTPUT | PMn3_MODE_OUTPUT | PMn4_MODE_OUTPUT | PMn5_MODE_OUTPUT | PMn6_MODE_DEFAULT | PMn7_MODE_DEFAULT;
	PMCM = PMn0_MODE_OUTPUT | PMn1_MODE_OUTPUT | PMn2_MODE_OUTPUT | PMn3_MODE_OUTPUT | PMn4_MODE_DEFAULT | PMn5_MODE_DEFAULT | PMn6_MODE_DEFAULT | PMn7_MODE_DEFAULT;
	PMCS = PMn0_MODE_OUTPUT | PMn1_MODE_OUTPUT | PMn2_MODE_DEFAULT | PMn3_MODE_DEFAULT | PMn4_MODE_DEFAULT | PMn5_MODE_DEFAULT | PMn6_MODE_DEFAULT | PMn7_MODE_DEFAULT;
	PMCT = PMn0_MODE_OUTPUT | PMn1_MODE_OUTPUT | PMn2_MODE_DEFAULT | PMn3_MODE_DEFAULT | PMn4_MODE_INPUT | PMn5_MODE_DEFAULT | PMn6_MODE_INPUT | PMn7_MODE_DEFAULT;
	PMDLL = PMn0_MODE_INPUT | PMn1_MODE_INPUT | PMn2_MODE_INPUT | PMn3_MODE_INPUT | PMn4_MODE_INPUT | PMn5_MODE_INPUT | PMn6_MODE_OUTPUT | PMn7_MODE_OUTPUT;
	PMDLH = PMn0_MODE_OUTPUT | PMn1_MODE_OUTPUT | PMn2_MODE_OUTPUT | PMn3_MODE_OUTPUT | PMn4_MODE_OUTPUT | PMn5_MODE_OUTPUT | PMn6_MODE_DEFAULT | PMn7_MODE_DEFAULT;
	PMC0 = PMCn0_OPER_PORT | PMCn1_OPER_PORT | PMCn2_OPER_PORT | PMCn3_OPER_PORT | PMCn4_OPER_PORT | PMCn6_OPER_PORT;
	PMC1 = PMCn0_OPER_PORT | PMCn1_OPER_PORT;
	PMC3L = PMCn2_OPER_PORT | PMCn5_OPER_PORT | PMCn6_OPER_PORT | PMCn7_OPER_PORT;
	PMC4 = PMCn0_OPER_PORT | PMCn1_OPER_PORT | PMCn2_OPER_PORT;
	PMC5 = PMCn0_OPER_PORT | PMCn1_OPER_PORT;
	PMC7L = PMCn0_OPER_PORT | PMCn1_OPER_PORT | PMCn2_OPER_PORT | PMCn3_OPER_PORT | PMCn4_OPER_PORT | PMCn5_OPER_PORT | PMCn6_OPER_PORT | PMCn7_OPER_PORT;
	PMC7H = PMCn0_OPER_PORT | PMCn1_OPER_PORT | PMCn2_OPER_PORT | PMCn3_OPER_PORT | PMCn4_OPER_PORT | PMCn5_OPER_PORT | PMCn6_OPER_PORT | PMCn7_OPER_PORT;
	PMC9L = PMCn0_OPER_PORT | PMCn1_OPER_PORT | PMCn2_OPER_PORT | PMCn3_OPER_PORT | PMCn4_OPER_PORT | PMCn5_OPER_PORT | PMCn6_OPER_PORT | PMCn7_OPER_PORT;
	PMC9H = PMCn0_OPER_PORT | PMCn1_OPER_PORT | PMCn2_OPER_PORT | PMCn3_OPER_PORT | PMCn4_OPER_PORT | PMCn5_OPER_PORT;
	PMCCM = PMCn0_OPER_PORT | PMCn1_OPER_PORT | PMCn2_OPER_PORT | PMCn3_OPER_PORT;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P32 to input mode by software.
**
**	Parameters:
**		enablePU :	Pull-up enable or not
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP32Input(BOOL enablePU)
{
	if (enablePU)
	{
		PU3L |= PUn2_PULLUP_ON;
	}
	else
	{
		PU3L &= (UCHAR)~PUn2_PULLUP_ON;
	}
	PM3L |= PMn2_MODE_INPUT;
	PMC3L &= (UCHAR)~PMCn2_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P32 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP32Output(BOOL initialValue)
{
	if (initialValue)
	{
		P3L |= Pn2_OUTPUT_1;
	}
	else
	{
		P3L &= (UCHAR)~Pn2_OUTPUT_1;
	}
	PM3L &= (UCHAR)~PMn2_MODE_INPUT;
	PMC3L &= (UCHAR)~PMCn2_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P40 to input mode by software.
**
**	Parameters:
**		enablePU :	Pull-up enable or not
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP40Input(BOOL enablePU)
{
	if (enablePU)
	{
		PU4 |= PUn0_PULLUP_ON;
	}
	else
	{
		PU4 &= (UCHAR)~PUn0_PULLUP_ON;
	}
	PM4 |= PMn0_MODE_INPUT;
	PMC4 &= (UCHAR)~PMCn0_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P40 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP40Output(BOOL initialValue)
{
	if (initialValue)
	{
		P4 |= Pn0_OUTPUT_1;
	}
	else
	{
		P4 &= (UCHAR)~Pn0_OUTPUT_1;
	}
	PM4 &= (UCHAR)~PMn0_MODE_INPUT;
	PMC4 &= (UCHAR)~PMCn0_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P41 to input mode by software.
**
**	Parameters:
**		enablePU :	Pull-up enable or not
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP41Input(BOOL enablePU)
{
	if (enablePU)
	{
		PU4 |= PUn1_PULLUP_ON;
	}
	else
	{
		PU4 &= (UCHAR)~PUn1_PULLUP_ON;
	}
	PM4 |= PMn1_MODE_INPUT;
	PMC4 &= (UCHAR)~PMCn1_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P41 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP41Output(BOOL initialValue)
{
	if (initialValue)
	{
		P4 |= Pn1_OUTPUT_1;
	}
	else
	{
		P4 &= (UCHAR)~Pn1_OUTPUT_1;
	}
	PM4 &= (UCHAR)~PMn1_MODE_INPUT;
	PMC4 &= (UCHAR)~PMCn1_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P42 to input mode by software.
**
**	Parameters:
**		enablePU :	Pull-up enable or not
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP42Input(BOOL enablePU)
{
	if (enablePU)
	{
		PU4 |= PUn2_PULLUP_ON;
	}
	else
	{
		PU4 &= (UCHAR)~PUn2_PULLUP_ON;
	}
	PM4 |= PMn2_MODE_INPUT;
	PMC4 &= (UCHAR)~PMCn2_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P42 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP42Output(BOOL initialValue)
{
	if (initialValue)
	{
		P4 |= Pn2_OUTPUT_1;
	}
	else
	{
		P4 &= (UCHAR)~Pn2_OUTPUT_1;
	}
	PM4 &= (UCHAR)~PMn2_MODE_INPUT;
	PMC4 &= (UCHAR)~PMCn2_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P70 to input mode by software.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP70Input(void)
{
	PM7L |= PMn0_MODE_INPUT;
	PMC7L &= (UCHAR)~PMCn0_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P70 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP70Output(BOOL initialValue)
{
	if (initialValue)
	{
		P7L |= Pn0_OUTPUT_1;
	}
	else
	{
		P7L &= (UCHAR)~Pn0_OUTPUT_1;
	}
	PM7L &= (UCHAR)~PMn0_MODE_INPUT;
	PMC7L &= (UCHAR)~PMCn0_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P71 to input mode by software.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP71Input(void)
{
	PM7L |= PMn1_MODE_INPUT;
	PMC7L &= (UCHAR)~PMCn1_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P71 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP71Output(BOOL initialValue)
{
	if (initialValue)
	{
		P7L |= Pn1_OUTPUT_1;
	}
	else
	{
		P7L &= (UCHAR)~Pn1_OUTPUT_1;
	}
	PM7L &= (UCHAR)~PMn1_MODE_INPUT;
	PMC7L &= (UCHAR)~PMCn1_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P72 to input mode by software.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP72Input(void)
{
	PM7L |= PMn2_MODE_INPUT;
	PMC7L &= (UCHAR)~PMCn2_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P72 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP72Output(BOOL initialValue)
{
	if (initialValue)
	{
		P7L |= Pn2_OUTPUT_1;
	}
	else
	{
		P7L &= (UCHAR)~Pn2_OUTPUT_1;
	}
	PM7L &= (UCHAR)~PMn2_MODE_INPUT;
	PMC7L &= (UCHAR)~PMCn2_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P73 to input mode by software.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP73Input(void)
{
	PM7L |= PMn3_MODE_INPUT;
	PMC7L &= (UCHAR)~PMCn3_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P73 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP73Output(BOOL initialValue)
{
	if (initialValue)
	{
		P7L |= Pn3_OUTPUT_1;
	}
	else
	{
		P7L &= (UCHAR)~Pn3_OUTPUT_1;
	}
	PM7L &= (UCHAR)~PMn3_MODE_INPUT;
	PMC7L &= (UCHAR)~PMCn3_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P74 to input mode by software.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP74Input(void)
{
	PM7L |= PMn4_MODE_INPUT;
	PMC7L &= (UCHAR)~PMCn4_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P74 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP74Output(BOOL initialValue)
{
	if (initialValue)
	{
		P7L |= Pn4_OUTPUT_1;
	}
	else
	{
		P7L &= (UCHAR)~Pn4_OUTPUT_1;
	}
	PM7L &= (UCHAR)~PMn4_MODE_INPUT;
	PMC7L &= (UCHAR)~PMCn4_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P75 to input mode by software.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP75Input(void)
{
	PM7L |= PMn5_MODE_INPUT;
	PMC7L &= (UCHAR)~PMCn5_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P75 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP75Output(BOOL initialValue)
{
	if (initialValue)
	{
		P7L |= Pn5_OUTPUT_1;
	}
	else
	{
		P7L &= (UCHAR)~Pn5_OUTPUT_1;
	}
	PM7L &= (UCHAR)~PMn5_MODE_INPUT;
	PMC7L &= (UCHAR)~PMCn5_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P76 to input mode by software.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP76Input(void)
{
	PM7L |= PMn6_MODE_INPUT;
	PMC7L &= (UCHAR)~PMCn6_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P76 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP76Output(BOOL initialValue)
{
	if (initialValue)
	{
		P7L |= Pn6_OUTPUT_1;
	}
	else
	{
		P7L &= (UCHAR)~Pn6_OUTPUT_1;
	}
	PM7L &= (UCHAR)~PMn6_MODE_INPUT;
	PMC7L &= (UCHAR)~PMCn6_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P77 to input mode by software.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP77Input(void)
{
	PM7L |= PMn7_MODE_INPUT;
	PMC7L &= (UCHAR)~PMCn7_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P77 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP77Output(BOOL initialValue)
{
	if (initialValue)
	{
		P7L |= Pn7_OUTPUT_1;
	}
	else
	{
		P7L &= (UCHAR)~Pn7_OUTPUT_1;
	}
	PM7L &= (UCHAR)~PMn7_MODE_INPUT;
	PMC7L &= (UCHAR)~PMCn7_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P78 to input mode by software.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP78Input(void)
{
	PM7H |= PMn0_MODE_INPUT;
	PMC7H &= (UCHAR)~PMCn0_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P78 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP78Output(BOOL initialValue)
{
	if (initialValue)
	{
		P7H |= Pn0_OUTPUT_1;
	}
	else
	{
		P7H &= (UCHAR)~Pn0_OUTPUT_1;
	}
	PM7H &= (UCHAR)~PMn0_MODE_INPUT;
	PMC7H &= (UCHAR)~PMCn0_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P79 to input mode by software.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP79Input(void)
{
	PM7H |= PMn1_MODE_INPUT;
	PMC7H &= (UCHAR)~PMCn1_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P79 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP79Output(BOOL initialValue)
{
	if (initialValue)
	{
		P7H |= Pn1_OUTPUT_1;
	}
	else
	{
		P7H &= (UCHAR)~Pn1_OUTPUT_1;
	}
	PM7H &= (UCHAR)~PMn1_MODE_INPUT;
	PMC7H &= (UCHAR)~PMCn1_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P710 to input mode by software.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP710Input(void)
{
	PM7H |= PMn2_MODE_INPUT;
	PMC7H &= (UCHAR)~PMCn2_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P710 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP710Output(BOOL initialValue)
{
	if (initialValue)
	{
		P7H |= Pn2_OUTPUT_1;
	}
	else
	{
		P7H &= (UCHAR)~Pn2_OUTPUT_1;
	}
	PM7H &= (UCHAR)~PMn2_MODE_INPUT;
	PMC7H &= (UCHAR)~PMCn2_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P711 to input mode by software.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP711Input(void)
{
	PM7H |= PMn3_MODE_INPUT;
	PMC7H &= (UCHAR)~PMCn3_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P711 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP711Output(BOOL initialValue)
{
	if (initialValue)
	{
		P7H |= Pn3_OUTPUT_1;
	}
	else
	{
		P7H &= (UCHAR)~Pn3_OUTPUT_1;
	}
	PM7H &= (UCHAR)~PMn3_MODE_INPUT;
	PMC7H &= (UCHAR)~PMCn3_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P712 to input mode by software.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP712Input(void)
{
	PM7H |= PMn4_MODE_INPUT;
	PMC7H &= (UCHAR)~PMCn4_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P712 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP712Output(BOOL initialValue)
{
	if (initialValue)
	{
		P7H |= Pn4_OUTPUT_1;
	}
	else
	{
		P7H &= (UCHAR)~Pn4_OUTPUT_1;
	}
	PM7H &= (UCHAR)~PMn4_MODE_INPUT;
	PMC7H &= (UCHAR)~PMCn4_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P713 to input mode by software.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP713Input(void)
{
	PM7H |= PMn5_MODE_INPUT;
	PMC7H &= (UCHAR)~PMCn5_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P713 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP713Output(BOOL initialValue)
{
	if (initialValue)
	{
		P7H |= Pn5_OUTPUT_1;
	}
	else
	{
		P7H &= (UCHAR)~Pn5_OUTPUT_1;
	}
	PM7H &= (UCHAR)~PMn5_MODE_INPUT;
	PMC7H &= (UCHAR)~PMCn5_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P714 to input mode by software.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP714Input(void)
{
	PM7H |= PMn6_MODE_INPUT;
	PMC7H &= (UCHAR)~PMCn6_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P714 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP714Output(BOOL initialValue)
{
	if (initialValue)
	{
		P7H |= Pn6_OUTPUT_1;
	}
	else
	{
		P7H &= (UCHAR)~Pn6_OUTPUT_1;
	}
	PM7H &= (UCHAR)~PMn6_MODE_INPUT;
	PMC7H &= (UCHAR)~PMCn6_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P715 to input mode by software.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP715Input(void)
{
	PM7H |= PMn7_MODE_INPUT;
	PMC7H &= (UCHAR)~PMCn7_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P715 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP715Output(BOOL initialValue)
{
	if (initialValue)
	{
		P7H |= Pn7_OUTPUT_1;
	}
	else
	{
		P7H &= (UCHAR)~Pn7_OUTPUT_1;
	}
	PM7H &= (UCHAR)~PMn7_MODE_INPUT;
	PMC7H &= (UCHAR)~PMCn7_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P93 to input mode by software.
**
**	Parameters:
**		enablePU :	Pull-up enable or not
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP93Input(BOOL enablePU)
{
	if (enablePU)
	{
		PU9L |= PUn3_PULLUP_ON;
	}
	else
	{
		PU9L &= (UCHAR)~PUn3_PULLUP_ON;
	}
	PM9L |= PMn3_MODE_INPUT;
	PMC9L &= (UCHAR)~PMCn3_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P93 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP93Output(BOOL initialValue)
{
	if (initialValue)
	{
		P9L |= Pn3_OUTPUT_1;
	}
	else
	{
		P9L &= (UCHAR)~Pn3_OUTPUT_1;
	}
	PM9L &= (UCHAR)~PMn3_MODE_INPUT;
	PMC9L &= (UCHAR)~PMCn3_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P94 to input mode by software.
**
**	Parameters:
**		enablePU :	Pull-up enable or not
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP94Input(BOOL enablePU)
{
	if (enablePU)
	{
		PU9L |= PUn4_PULLUP_ON;
	}
	else
	{
		PU9L &= (UCHAR)~PUn4_PULLUP_ON;
	}
	PM9L |= PMn4_MODE_INPUT;
	PMC9L &= (UCHAR)~PMCn4_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P94 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP94Output(BOOL initialValue)
{
	if (initialValue)
	{
		P9L |= Pn4_OUTPUT_1;
	}
	else
	{
		P9L &= (UCHAR)~Pn4_OUTPUT_1;
	}
	PM9L &= (UCHAR)~PMn4_MODE_INPUT;
	PMC9L &= (UCHAR)~PMCn4_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P95 to input mode by software.
**
**	Parameters:
**		enablePU :	Pull-up enable or not
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP95Input(BOOL enablePU)
{
	if (enablePU)
	{
		PU9L |= PUn5_PULLUP_ON;
	}
	else
	{
		PU9L &= (UCHAR)~PUn5_PULLUP_ON;
	}
	PM9L |= PMn5_MODE_INPUT;
	PMC9L &= (UCHAR)~PMCn5_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P95 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP95Output(BOOL initialValue)
{
	if (initialValue)
	{
		P9L |= Pn5_OUTPUT_1;
	}
	else
	{
		P9L &= (UCHAR)~Pn5_OUTPUT_1;
	}
	PM9L &= (UCHAR)~PMn5_MODE_INPUT;
	PMC9L &= (UCHAR)~PMCn5_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P96 to input mode by software.
**
**	Parameters:
**		enablePU :	Pull-up enable or not
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP96Input(BOOL enablePU)
{
	if (enablePU)
	{
		PU9L |= PUn6_PULLUP_ON;
	}
	else
	{
		PU9L &= (UCHAR)~PUn6_PULLUP_ON;
	}
	PM9L |= PMn6_MODE_INPUT;
	PMC9L &= (UCHAR)~PMCn6_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P96 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP96Output(BOOL initialValue)
{
	if (initialValue)
	{
		P9L |= Pn6_OUTPUT_1;
	}
	else
	{
		P9L &= (UCHAR)~Pn6_OUTPUT_1;
	}
	PM9L &= (UCHAR)~PMn6_MODE_INPUT;
	PMC9L &= (UCHAR)~PMCn6_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P97 to input mode by software.
**
**	Parameters:
**		enablePU :	Pull-up enable or not
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP97Input(BOOL enablePU)
{
	if (enablePU)
	{
		PU9L |= PUn7_PULLUP_ON;
	}
	else
	{
		PU9L &= (UCHAR)~PUn7_PULLUP_ON;
	}
	PM9L |= PMn7_MODE_INPUT;
	PMC9L &= (UCHAR)~PMCn7_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P97 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP97Output(BOOL initialValue)
{
	if (initialValue)
	{
		P9L |= Pn7_OUTPUT_1;
	}
	else
	{
		P9L &= (UCHAR)~Pn7_OUTPUT_1;
	}
	PM9L &= (UCHAR)~PMn7_MODE_INPUT;
	PMC9L &= (UCHAR)~PMCn7_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P98 to input mode by software.
**
**	Parameters:
**		enablePU :	Pull-up enable or not
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP98Input(BOOL enablePU)
{
	if (enablePU)
	{
		PU9H |= PUn0_PULLUP_ON;
	}
	else
	{
		PU9H &= (UCHAR)~PUn0_PULLUP_ON;
	}
	PM9H |= PMn0_MODE_INPUT;
	PMC9H &= (UCHAR)~PMCn0_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P98 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP98Output(BOOL initialValue)
{
	if (initialValue)
	{
		P9H |= Pn0_OUTPUT_1;
	}
	else
	{
		P9H &= (UCHAR)~Pn0_OUTPUT_1;
	}
	PM9H &= (UCHAR)~PMn0_MODE_INPUT;
	PMC9H &= (UCHAR)~PMCn0_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P99 to input mode by software.
**
**	Parameters:
**		enablePU :	Pull-up enable or not
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP99Input(BOOL enablePU)
{
	if (enablePU)
	{
		PU9H |= PUn1_PULLUP_ON;
	}
	else
	{
		PU9H &= (UCHAR)~PUn1_PULLUP_ON;
	}
	PM9H |= PMn1_MODE_INPUT;
	PMC9H &= (UCHAR)~PMCn1_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P99 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP99Output(BOOL initialValue)
{
	if (initialValue)
	{
		P9H |= Pn1_OUTPUT_1;
	}
	else
	{
		P9H &= (UCHAR)~Pn1_OUTPUT_1;
	}
	PM9H &= (UCHAR)~PMn1_MODE_INPUT;
	PMC9H &= (UCHAR)~PMCn1_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P910 to input mode by software.
**
**	Parameters:
**		enablePU :	Pull-up enable or not
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP910Input(BOOL enablePU)
{
	if (enablePU)
	{
		PU9H |= PUn2_PULLUP_ON;
	}
	else
	{
		PU9H &= (UCHAR)~PUn2_PULLUP_ON;
	}
	PM9H |= PMn2_MODE_INPUT;
	PMC9H &= (UCHAR)~PMCn2_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P910 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP910Output(BOOL initialValue)
{
	if (initialValue)
	{
		P9H |= Pn2_OUTPUT_1;
	}
	else
	{
		P9H &= (UCHAR)~Pn2_OUTPUT_1;
	}
	PM9H &= (UCHAR)~PMn2_MODE_INPUT;
	PMC9H &= (UCHAR)~PMCn2_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P911 to input mode by software.
**
**	Parameters:
**		enablePU :	Pull-up enable or not
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP911Input(BOOL enablePU)
{
	if (enablePU)
	{
		PU9H |= PUn3_PULLUP_ON;
	}
	else
	{
		PU9H &= (UCHAR)~PUn3_PULLUP_ON;
	}
	PM9H |= PMn3_MODE_INPUT;
	PMC9H &= (UCHAR)~PMCn3_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P911 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP911Output(BOOL initialValue)
{
	if (initialValue)
	{
		P9H |= Pn3_OUTPUT_1;
	}
	else
	{
		P9H &= (UCHAR)~Pn3_OUTPUT_1;
	}
	PM9H &= (UCHAR)~PMn3_MODE_INPUT;
	PMC9H &= (UCHAR)~PMCn3_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P912 to input mode by software.
**
**	Parameters:
**		enablePU :	Pull-up enable or not
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP912Input(BOOL enablePU)
{
	if (enablePU)
	{
		PU9H |= PUn4_PULLUP_ON;
	}
	else
	{
		PU9H &= (UCHAR)~PUn4_PULLUP_ON;
	}
	PM9H |= PMn4_MODE_INPUT;
	PMC9H &= (UCHAR)~PMCn4_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P912 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP912Output(BOOL initialValue)
{
	if (initialValue)
	{
		P9H |= Pn4_OUTPUT_1;
	}
	else
	{
		P9H &= (UCHAR)~Pn4_OUTPUT_1;
	}
	PM9H &= (UCHAR)~PMn4_MODE_INPUT;
	PMC9H &= (UCHAR)~PMCn4_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P913 to input mode by software.
**
**	Parameters:
**		enablePU :	Pull-up enable or not
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP913Input(BOOL enablePU)
{
	if (enablePU)
	{
		PU9H |= PUn5_PULLUP_ON;
	}
	else
	{
		PU9H &= (UCHAR)~PUn5_PULLUP_ON;
	}
	PM9H |= PMn5_MODE_INPUT;
	PMC9H &= (UCHAR)~PMCn5_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes P913 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangeP913Output(BOOL initialValue)
{
	if (initialValue)
	{
		P9H |= Pn5_OUTPUT_1;
	}
	else
	{
		P9H &= (UCHAR)~Pn5_OUTPUT_1;
	}
	PM9H &= (UCHAR)~PMn5_MODE_INPUT;
	PMC9H &= (UCHAR)~PMCn5_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes PCM0 to input mode by software.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangePCM0Input(void)
{
	PMCM |= PMn0_MODE_INPUT;
	PMCCM &= (UCHAR)~PMCn0_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes PCM0 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangePCM0Output(BOOL initialValue)
{
	if (initialValue)
	{
		PCM |= Pn0_OUTPUT_1;
	}
	else
	{
		PCM &= (UCHAR)~Pn0_OUTPUT_1;
	}
	PMCM &= (UCHAR)~PMn0_MODE_INPUT;
	PMCCM &= (UCHAR)~PMCn0_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes PCM1 to input mode by software.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangePCM1Input(void)
{
	PMCM |= PMn1_MODE_INPUT;
	PMCCM &= (UCHAR)~PMCn1_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes PCM1 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangePCM1Output(BOOL initialValue)
{
	if (initialValue)
	{
		PCM |= Pn1_OUTPUT_1;
	}
	else
	{
		PCM &= (UCHAR)~Pn1_OUTPUT_1;
	}
	PMCM &= (UCHAR)~PMn1_MODE_INPUT;
	PMCCM &= (UCHAR)~PMCn1_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes PCM2 to input mode by software.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangePCM2Input(void)
{
	PMCM |= PMn2_MODE_INPUT;
	PMCCM &= (UCHAR)~PMCn2_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes PCM2 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangePCM2Output(BOOL initialValue)
{
	if (initialValue)
	{
		PCM |= Pn2_OUTPUT_1;
	}
	else
	{
		PCM &= (UCHAR)~Pn2_OUTPUT_1;
	}
	PMCM &= (UCHAR)~PMn2_MODE_INPUT;
	PMCCM &= (UCHAR)~PMCn2_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes PCM3 to input mode by software.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangePCM3Input(void)
{
	PMCM |= PMn3_MODE_INPUT;
	PMCCM &= (UCHAR)~PMCn3_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes PCM3 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangePCM3Output(BOOL initialValue)
{
	if (initialValue)
	{
		PCM |= Pn3_OUTPUT_1;
	}
	else
	{
		PCM &= (UCHAR)~Pn3_OUTPUT_1;
	}
	PMCM &= (UCHAR)~PMn3_MODE_INPUT;
	PMCCM &= (UCHAR)~PMCn3_OPER_ALTER;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes PCS0 to input mode by software.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangePCS0Input(void)
{
	PMCS |= PMn0_MODE_INPUT;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes PCS0 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangePCS0Output(BOOL initialValue)
{
	if (initialValue)
	{
		PCS |= Pn0_OUTPUT_1;
	}
	else
	{
		PCS &= (UCHAR)~Pn0_OUTPUT_1;
	}
	PMCS &= (UCHAR)~PMn0_MODE_INPUT;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes PCS1 to input mode by software.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangePCS1Input(void)
{
	PMCS |= PMn1_MODE_INPUT;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes PCS1 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangePCS1Output(BOOL initialValue)
{
	if (initialValue)
	{
		PCS |= Pn1_OUTPUT_1;
	}
	else
	{
		PCS &= (UCHAR)~Pn1_OUTPUT_1;
	}
	PMCS &= (UCHAR)~PMn1_MODE_INPUT;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes PCT0 to input mode by software.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangePCT0Input(void)
{
	PMCT |= PMn0_MODE_INPUT;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes PCT0 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangePCT0Output(BOOL initialValue)
{
	if (initialValue)
	{
		PCT |= Pn0_OUTPUT_1;
	}
	else
	{
		PCT &= (UCHAR)~Pn0_OUTPUT_1;
	}
	PMCT &= (UCHAR)~PMn0_MODE_INPUT;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes PCT1 to input mode by software.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangePCT1Input(void)
{
	PMCT |= PMn1_MODE_INPUT;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes PCT1 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangePCT1Output(BOOL initialValue)
{
	if (initialValue)
	{
		PCT |= Pn1_OUTPUT_1;
	}
	else
	{
		PCT &= (UCHAR)~Pn1_OUTPUT_1;
	}
	PMCT &= (UCHAR)~PMn1_MODE_INPUT;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes PDL6 to input mode by software.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangePDL6Input(void)
{
	PMDLL |= PMn6_MODE_INPUT;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes PDL6 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangePDL6Output(BOOL initialValue)
{
	if (initialValue)
	{
		PDLL |= Pn6_OUTPUT_1;
	}
	else
	{
		PDLL &= (UCHAR)~Pn6_OUTPUT_1;
	}
	PMDLL &= (UCHAR)~PMn6_MODE_INPUT;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes PDL7 to input mode by software.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangePDL7Input(void)
{
	PMDLL |= PMn7_MODE_INPUT;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes PDL7 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangePDL7Output(BOOL initialValue)
{
	if (initialValue)
	{
		PDLL |= Pn7_OUTPUT_1;
	}
	else
	{
		PDLL &= (UCHAR)~Pn7_OUTPUT_1;
	}
	PMDLL &= (UCHAR)~PMn7_MODE_INPUT;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes PDL8 to input mode by software.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangePDL8Input(void)
{
	PMDLH |= PMn0_MODE_INPUT;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes PDL8 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangePDL8Output(BOOL initialValue)
{
	if (initialValue)
	{
		PDLH |= Pn0_OUTPUT_1;
	}
	else
	{
		PDLH &= (UCHAR)~Pn0_OUTPUT_1;
	}
	PMDLH &= (UCHAR)~PMn0_MODE_INPUT;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes PDL9 to input mode by software.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangePDL9Input(void)
{
	PMDLH |= PMn1_MODE_INPUT;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes PDL9 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangePDL9Output(BOOL initialValue)
{
	if (initialValue)
	{
		PDLH |= Pn1_OUTPUT_1;
	}
	else
	{
		PDLH &= (UCHAR)~Pn1_OUTPUT_1;
	}
	PMDLH &= (UCHAR)~PMn1_MODE_INPUT;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes PDL10 to input mode by software.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangePDL10Input(void)
{
	PMDLH |= PMn2_MODE_INPUT;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes PDL10 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangePDL10Output(BOOL initialValue)
{
	if (initialValue)
	{
		PDLH |= Pn2_OUTPUT_1;
	}
	else
	{
		PDLH &= (UCHAR)~Pn2_OUTPUT_1;
	}
	PMDLH &= (UCHAR)~PMn2_MODE_INPUT;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes PDL11 to input mode by software.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangePDL11Input(void)
{
	PMDLH |= PMn3_MODE_INPUT;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes PDL11 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangePDL11Output(BOOL initialValue)
{
	if (initialValue)
	{
		PDLH |= Pn3_OUTPUT_1;
	}
	else
	{
		PDLH &= (UCHAR)~Pn3_OUTPUT_1;
	}
	PMDLH &= (UCHAR)~PMn3_MODE_INPUT;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes PDL12 to input mode by software.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangePDL12Input(void)
{
	PMDLH |= PMn4_MODE_INPUT;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes PDL12 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangePDL12Output(BOOL initialValue)
{
	if (initialValue)
	{
		PDLH |= Pn4_OUTPUT_1;
	}
	else
	{
		PDLH &= (UCHAR)~Pn4_OUTPUT_1;
	}
	PMDLH &= (UCHAR)~PMn4_MODE_INPUT;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes PDL13 to input mode by software.
**
**	Parameters:
**		None
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangePDL13Input(void)
{
	PMDLH |= PMn5_MODE_INPUT;
}

/*
**-----------------------------------------------------------------------------
**
**	Abstract:
**		This function changes PDL13 to output mode by software.
**
**	Parameters:
**		initialValue :	initial output 1 or 0
**
**	Returns:
**		None
**
**-----------------------------------------------------------------------------
*/
void PORT_ChangePDL13Output(BOOL initialValue)
{
	if (initialValue)
	{
		PDLH |= Pn5_OUTPUT_1;
	}
	else
	{
		PDLH &= (UCHAR)~Pn5_OUTPUT_1;
	}
	PMDLH &= (UCHAR)~PMn5_MODE_INPUT;
}

/* Start adding user code. Do not edit comment generated here */
/* End user code adding. Do not edit comment generated here */


