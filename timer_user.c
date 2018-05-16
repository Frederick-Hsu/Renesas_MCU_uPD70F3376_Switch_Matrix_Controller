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
**  Filename :	timer_user.c
**  Abstract :	This file implements device driver for Timer module.
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
#include "timer.h"
/* Start user code for include definition. Do not edit comment generated here */
/* End user code for include definition. Do not edit comment generated here */
#include "user_define.h"

#include "PWM/PWM_Out.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
*******************************************************************************
**  Global define
*******************************************************************************
*/
/* Start user code for global definition. Do not edit comment generated here */
/* End user code for global definition. Do not edit comment generated here */

    #pragma interrupt INTTM0EQ0  MD_INTTM0EQ0
    
#if (PWM_OUT_GENERATE_OPTION == PWM_OUT_GENRATE_OPTION2)
	
    #pragma interrupt INTTAA0CC0 MD_INTTAA0CC0
	#pragma interrupt INTTAA1CC0 MD_INTTAA1CC0

	extern struct PwmOutChnSelector g_stPwmOutChn;
	extern unsigned int iTAA0_FlagCycleCnt; 
	extern unsigned int iTAA1_FlagCycleCnt;
	extern USHORT ushrtPWMOnCnt_TAA0CCR0;
	extern USHORT ushrtPWMOffCnt_TAA1CCR0;

	static unsigned int iTAA0_CycleAccumulator = 0;
	static unsigned int iTAA1_CycleAccumulator = 0;

	/*
	**-----------------------------------------------------------------------------
	**
	**	Abstract:
	**		This function is INTTAA0CC0 interrupt service routine.
	**
	**	Parameters:
	**		None
	**
	**	Returns:
	**		None
	**
	**-----------------------------------------------------------------------------
	*/
	__interrupt void MD_INTTAA0CC0(void)
	{
		USHORT ushrtTempPwmOnCnt_For_TAA0CCR0 = 0;
		/* Start user code. Do not edit comment generated here */	
		/* End user code. Do not edit comment generated here */
		
		if (iTAA0_FlagCycleCnt == 0)	// not use accumulator
		{
			TAA0_Stop();	
			if (g_stPwmOutChn.ePrimaryOrSecondary == PWM_ATTR_PRIMARY)
			{
				Set_PwmOutPrimaryChn_Level(g_stPwmOutChn.iPwmOutChn, LOW);
			}
			else if (g_stPwmOutChn.ePrimaryOrSecondary == PWM_ATTR_SECONDARY)
			{
				Set_PwmOutSecondaryChn_Level(g_stPwmOutChn.bytPwmOutBoardID, g_stPwmOutChn.iPwmOutChn, LOW);
			}
			TAA1_Start();
		}
		else	// use accumulator : iTAA0_CycleAccumulator
		{
			if (iTAA0_CycleAccumulator < iTAA0_FlagCycleCnt)
			{
				iTAA0_CycleAccumulator++;
				TAA0CCIF0 = 0;	/* clear INTTAA0CC0 interrupt flag */
				return;
			}
			else if (iTAA0_CycleAccumulator == iTAA0_FlagCycleCnt)
			{
				TAA0_Stop();
				TAA0_ChangeTimerCondition(&ushrtPWMOnCnt_TAA0CCR0, 1);
				TAA0_Start();
				iTAA0_CycleAccumulator++;
				return;
			}
			else
			{
				//TAA0 timer ---> timeout
				TAA0_Stop();
				
				if (g_stPwmOutChn.ePrimaryOrSecondary == PWM_ATTR_PRIMARY)
				{
					Set_PwmOutPrimaryChn_Level(g_stPwmOutChn.iPwmOutChn, LOW);
				}
				else if (g_stPwmOutChn.ePrimaryOrSecondary == PWM_ATTR_SECONDARY)
				{
					Set_PwmOutSecondaryChn_Level(g_stPwmOutChn.bytPwmOutBoardID, g_stPwmOutChn.iPwmOutChn, LOW);
				}
				
				{
					ushrtTempPwmOnCnt_For_TAA0CCR0 = 0xFFFF;
					TAA0_ChangeTimerCondition(&ushrtTempPwmOnCnt_For_TAA0CCR0, 1);
					iTAA0_CycleAccumulator = 0;	// Reset the accumulator
				}
				TAA1_Start();
			}
		}
	}

	/*
	**-----------------------------------------------------------------------------
	**
	**	Abstract:
	**		This function is INTTAA1CC0 interrupt service routine.
	**
	**	Parameters:
	**		None
	**
	**	Returns:
	**		None
	**
	**-----------------------------------------------------------------------------
	*/
	__interrupt void MD_INTTAA1CC0(void)
	{
		USHORT ushrtTempPwmOffCnt_For_TAA1CCR0 = 0;
		/* Start user code. Do not edit comment generated here */	
		/* End user code. Do not edit comment generated here */
		if (iTAA1_FlagCycleCnt == 0)	// not use accumulator
		{
			// TAA1 timer ---> timeout
			TAA1_Stop();
			if (g_stPwmOutChn.ePrimaryOrSecondary == PWM_ATTR_PRIMARY)
			{
				Set_PwmOutPrimaryChn_Level(g_stPwmOutChn.iPwmOutChn, HIGH);
			}
			else if (g_stPwmOutChn.ePrimaryOrSecondary == PWM_ATTR_SECONDARY)
			{
				Set_PwmOutSecondaryChn_Level(g_stPwmOutChn.bytPwmOutBoardID, g_stPwmOutChn.iPwmOutChn, HIGH);
			}
			TAA0_Start();	// Restart TAA0 timer
		}
		else	// use accumulator : iTAA1_CycleAccumulator
		{
			if (iTAA1_CycleAccumulator < iTAA1_FlagCycleCnt)
			{
				iTAA1_CycleAccumulator++;
				TAA1CCIF0 = 0;	/* clear INTTAA1CC0 interrupt flag */
				return;
			}
			else if (iTAA1_CycleAccumulator == iTAA1_FlagCycleCnt)
			{
				TAA1_Stop();
				TAA1_ChangeTimerCondition(&ushrtPWMOffCnt_TAA1CCR0, 1);
				TAA1_Start();
				iTAA1_CycleAccumulator++;
				return;
			}
			else
			{
				TAA1_Stop();
				if (g_stPwmOutChn.ePrimaryOrSecondary == PWM_ATTR_PRIMARY)
				{
					Set_PwmOutPrimaryChn_Level(g_stPwmOutChn.iPwmOutChn, HIGH);
				}
				else if (g_stPwmOutChn.ePrimaryOrSecondary == PWM_ATTR_SECONDARY)
				{
					Set_PwmOutSecondaryChn_Level(g_stPwmOutChn.bytPwmOutBoardID, g_stPwmOutChn.iPwmOutChn, HIGH);
				}
				
				{
					ushrtTempPwmOffCnt_For_TAA1CCR0 = 0xFFFF;
					TAA1_ChangeTimerCondition(&ushrtTempPwmOffCnt_For_TAA1CCR0, 1);
					iTAA1_CycleAccumulator= 0;	// Reset the accumulator
				}
				TAA0_Start();	// Restart TAA0 timer
			}
		}
	}

#endif

    /*
    **-----------------------------------------------------------------------------
    **
    **	Abstract:
    **		This function is INTTM0EQ0 interrupt service routine.
    **
    **	Parameters:
    **		None
    **
    **	Returns:
    **		None
    **
    **-----------------------------------------------------------------------------
    */
    extern int multiplier;
    extern int keepMultiplier;
    
    extern unsigned long canId;
    extern UCHAR canDataByte[8];
    
    __interrupt void MD_INTTM0EQ0(void)
    {
    	/* Start user code. Do not edit comment generated here */
        if (multiplier == 0)
        {
            /* Send out the CAN telegram */
            if (strlen(canDataByte) != 0)
            {
                CAN0_MsgSetIdDataDlc(1, canId, canDataByte, strlen(canDataByte));
                CAN0_MsgTxReq(1);
            }
            /* Restore the multiplier to repeat the CAN telegram periodically */
            multiplier = keepMultiplier;
        }
        multiplier--;
    	/* End user code. Do not edit comment generated here */
    }

/* Start adding user code. Do not edit comment generated here */
/* End user code adding. Do not edit comment generated here */
