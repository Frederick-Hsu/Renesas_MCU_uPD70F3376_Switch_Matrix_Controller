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
**  Filename :	port.h
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
#ifndef _MDPORT_
#define _MDPORT_
/*
*******************************************************************************
**	Register bit define
*******************************************************************************
*/
/* Port mode control register(PMCn.0 to 7) */
#define PMCn0_OPER_PORT		0x00	/* Pn0 as port mode */
#define PMCn1_OPER_PORT		0x00	/* Pn1 as port mode */
#define PMCn2_OPER_PORT		0x00	/* Pn2 as port mode */
#define PMCn3_OPER_PORT		0x00	/* Pn3 as port mode */
#define PMCn4_OPER_PORT		0x00	/* Pn4 as port mode */
#define PMCn5_OPER_PORT		0x00	/* Pn5 as port mode */
#define PMCn6_OPER_PORT		0x00	/* Pn6 as port mode */
#define PMCn7_OPER_PORT		0x00	/* Pn7 as port mode */

#define PMCn0_OPER_ALTER	0x01	/* Pn0 as alternative mode */
#define PMCn1_OPER_ALTER	0x02	/* Pn1 as alternative mode */
#define PMCn2_OPER_ALTER	0x04	/* Pn2 as alternative mode */
#define PMCn3_OPER_ALTER	0x08	/* Pn3 as alternative mode */
#define PMCn4_OPER_ALTER	0x10	/* Pn4 as alternative mode */
#define PMCn5_OPER_ALTER	0x20	/* Pn5 as alternative mode */
#define PMCn6_OPER_ALTER	0x40	/* Pn6 as alternative mode */
#define PMCn7_OPER_ALTER	0x80	/* Pn7 as alternative mode */

#define	PMCn0_OPER_OCD		0x00	/* PMC0 for MINI2 */

/* Port mode register(PMn.0 to 7) */
#define PMn0_MODE_INPUT		0x01	/* Pn0 as input mode */
#define PMn1_MODE_INPUT		0x02	/* Pn1 as input mode */
#define PMn2_MODE_INPUT		0x04	/* Pn2 as input mode */
#define PMn3_MODE_INPUT		0x08	/* Pn3 as input mode */
#define PMn4_MODE_INPUT		0x10	/* Pn4 as input mode */
#define PMn5_MODE_INPUT		0x20	/* Pn5 as input mode */
#define PMn6_MODE_INPUT		0x40	/* Pn6 as input mode */
#define PMn7_MODE_INPUT		0x80	/* Pn7 as input mode */

#define PMn0_MODE_OUTPUT	0x00	/* Pn0 as output mode */
#define PMn1_MODE_OUTPUT	0x00	/* Pn1 as output mode */
#define PMn2_MODE_OUTPUT	0x00	/* Pn2 as output mode */
#define PMn3_MODE_OUTPUT	0x00	/* Pn3 as output mode */
#define PMn4_MODE_OUTPUT	0x00	/* Pn4 as output mode */
#define PMn5_MODE_OUTPUT	0x00	/* Pn5 as output mode */
#define PMn6_MODE_OUTPUT	0x00	/* Pn6 as output mode */
#define PMn7_MODE_OUTPUT	0x00	/* Pn7 as output mode */

#define PMn0_MODE_DEFAULT	0x01	/* not use Pn0 */
#define PMn1_MODE_DEFAULT	0x02	/* not use Pn1 */
#define PMn2_MODE_DEFAULT	0x04	/* not use Pn2 */
#define PMn3_MODE_DEFAULT	0x08	/* not use Pn3 */
#define PMn4_MODE_DEFAULT	0x10	/* not use Pn4 */
#define PMn5_MODE_DEFAULT	0x20	/* not use Pn5 */
#define PMn6_MODE_DEFAULT	0x40	/* not use Pn6 */
#define PMn7_MODE_DEFAULT	0x80	/* not use Pn7 */

#define	PMn0_MODE_OCD		0x00	/* PMC0 for MINI2 */

/* Port function control register(PFCn.0 to 7) */
#define PFCn0_FUNCTL_0	0x00	/* Pn0 function control 0 */
#define PFCn1_FUNCTL_0	0x00	/* Pn1 function control 0 */
#define PFCn2_FUNCTL_0	0x00	/* Pn2 function control 0 */
#define PFCn3_FUNCTL_0	0x00	/* Pn3 function control 0 */
#define PFCn4_FUNCTL_0	0x00	/* Pn4 function control 0 */
#define PFCn5_FUNCTL_0	0x00	/* Pn5 function control 0 */
#define PFCn6_FUNCTL_0	0x00	/* Pn6 function control 0 */
#define PFCn7_FUNCTL_0	0x00	/* Pn7 function control 0 */

#define PFCn0_FUNCTL_1	0x01	/* Pn0 function control 1 */
#define PFCn1_FUNCTL_1	0x02	/* Pn1 function control 1 */
#define PFCn2_FUNCTL_1	0x04	/* Pn2 function control 1 */
#define PFCn3_FUNCTL_1	0x08	/* Pn3 function control 1 */
#define PFCn4_FUNCTL_1	0x10	/* Pn4 function control 1 */
#define PFCn5_FUNCTL_1	0x20	/* Pn5 function control 1 */
#define PFCn6_FUNCTL_1	0x40	/* Pn6 function control 1 */
#define PFCn7_FUNCTL_1	0x80	/* Pn7 function control 1 */

/* Port function control expension register(PFCEn.0 to 7) */
#define PFCEn0_FUNEX_0	0x00	/* Pn0 function control expension 0 */
#define PFCEn1_FUNEX_0	0x00	/* Pn1 function control expension 0 */
#define PFCEn2_FUNEX_0	0x00	/* Pn2 function control expension 0 */
#define PFCEn3_FUNEX_0	0x00	/* Pn3 function control expension 0 */
#define PFCEn4_FUNEX_0	0x00	/* Pn4 function control expension 0 */
#define PFCEn5_FUNEX_0	0x00	/* Pn5 function control expension 0 */
#define PFCEn6_FUNEX_0	0x00	/* Pn6 function control expension 0 */
#define PFCEn7_FUNEX_0	0x00	/* Pn7 function control expension 0 */

#define PFCEn0_FUNEX_1	0x01	/* Pn0 function control expension 1 */
#define PFCEn1_FUNEX_1	0x02	/* Pn1 function control expension 1 */
#define PFCEn2_FUNEX_1	0x04	/* Pn2 function control expension 1 */
#define PFCEn3_FUNEX_1	0x08	/* Pn3 function control expension 1 */
#define PFCEn4_FUNEX_1	0x10	/* Pn4 function control expension 1 */
#define PFCEn5_FUNEX_1	0x20	/* Pn5 function control expension 1 */
#define PFCEn6_FUNEX_1	0x40	/* Pn6 function control expension 1 */
#define PFCEn7_FUNEX_1	0x80	/* Pn7 function control expension 1 */

/* Port register(Pn.0 to 7) */
#define Pn0_OUTPUT_0	0x00	/* Pn0 output 0 */
#define Pn1_OUTPUT_0	0x00	/* Pn1 output 0 */
#define Pn2_OUTPUT_0	0x00	/* Pn2 output 0 */
#define Pn3_OUTPUT_0	0x00	/* Pn3 output 0 */
#define Pn4_OUTPUT_0	0x00	/* Pn4 output 0 */
#define Pn5_OUTPUT_0	0x00	/* Pn5 output 0 */
#define Pn6_OUTPUT_0	0x00	/* Pn6 output 0 */
#define Pn7_OUTPUT_0	0x00	/* Pn7 output 0 */

#define Pn0_OUTPUT_1	0x01	/* Pn0 output 1 */
#define Pn1_OUTPUT_1	0x02	/* Pn1 output 1 */
#define Pn2_OUTPUT_1	0x04	/* Pn2 output 1 */
#define Pn3_OUTPUT_1	0x08	/* Pn3 output 1 */
#define Pn4_OUTPUT_1	0x10	/* Pn4 output 1 */
#define Pn5_OUTPUT_1	0x20	/* Pn5 output 1 */
#define Pn6_OUTPUT_1	0x40	/* Pn6 output 1 */
#define Pn7_OUTPUT_1	0x80	/* Pn7 output 1 */

/* Pull-up resistor option register(PUn.0 to 7) */
#define PUn0_PULLUP_OFF	0x00	/* Pn0 Pull-up not connected */
#define PUn1_PULLUP_OFF	0x00	/* Pn1 Pull-up not connected */
#define PUn2_PULLUP_OFF	0x00	/* Pn2 Pull-up not connected */
#define PUn3_PULLUP_OFF	0x00	/* Pn3 Pull-up not connected */
#define PUn4_PULLUP_OFF	0x00	/* Pn4 Pull-up not connected */
#define PUn5_PULLUP_OFF	0x00	/* Pn5 Pull-up not connected */
#define PUn6_PULLUP_OFF	0x00	/* Pn6 Pull-up not connected */
#define PUn7_PULLUP_OFF	0x00	/* Pn7 Pull-up not connected */

#define PUn0_PULLUP_ON	0x01	/* Pn0 pull-up connected */
#define PUn1_PULLUP_ON	0x02	/* Pn1 pull-up connected */
#define PUn2_PULLUP_ON	0x04	/* Pn2 pull-up connected */
#define PUn3_PULLUP_ON	0x08	/* Pn3 pull-up connected */
#define PUn4_PULLUP_ON	0x10	/* Pn4 pull-up connected */
#define PUn5_PULLUP_ON	0x20	/* Pn5 pull-up connected */
#define PUn6_PULLUP_ON	0x40	/* Pn6 pull-up connected */
#define PUn7_PULLUP_ON	0x80	/* Pn7 pull-up connected */

/* Function register resistor(PFn.0 to 7) */
#define PFn0_FUN_NORMAL	0x00	/* Pn0 normal output */
#define PFn1_FUN_NORMAL	0x00	/* Pn1 normal output */
#define PFn2_FUN_NORMAL	0x00	/* Pn2 normal output */
#define PFn3_FUN_NORMAL	0x00	/* Pn3 normal output */
#define PFn4_FUN_NORMAL	0x00	/* Pn4 normal output */
#define PFn5_FUN_NORMAL	0x00	/* Pn5 normal output */
#define PFn6_FUN_NORMAL	0x00	/* Pn6 normal output */
#define PFn7_FUN_NORMAL	0x00	/* Pn7 normal output */

#define PFn0_FUN_OPEN	0x01	/* Pn0 open-drain output */
#define PFn1_FUN_OPEN	0x02	/* Pn1 open-drain output */
#define PFn2_FUN_OPEN	0x04	/* Pn2 open-drain output */
#define PFn3_FUN_OPEN	0x08	/* Pn3 open-drain output */
#define PFn4_FUN_OPEN	0x10	/* Pn4 open-drain output */
#define PFn5_FUN_OPEN	0x20	/* Pn5 open-drain output */
#define PFn6_FUN_OPEN	0x40	/* Pn6 open-drain output */
#define PFn7_FUN_OPEN	0x80	/* Pn7 open-drain output */

/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/

/*
*******************************************************************************
**  Function define
*******************************************************************************
*/
void PORT_Init(void);
void PORT_ChangeP32Input(BOOL enablePU);
void PORT_ChangeP32Output(BOOL initialValue);
void PORT_ChangeP40Input(BOOL enablePU);
void PORT_ChangeP40Output(BOOL initialValue);
void PORT_ChangeP41Input(BOOL enablePU);
void PORT_ChangeP41Output(BOOL initialValue);
void PORT_ChangeP42Input(BOOL enablePU);
void PORT_ChangeP42Output(BOOL initialValue);
void PORT_ChangeP70Input(void); 
void PORT_ChangeP70Output(BOOL initialValue);
void PORT_ChangeP71Input(void); 
void PORT_ChangeP71Output(BOOL initialValue);
void PORT_ChangeP72Input(void); 
void PORT_ChangeP72Output(BOOL initialValue);
void PORT_ChangeP73Input(void); 
void PORT_ChangeP73Output(BOOL initialValue);
void PORT_ChangeP74Input(void); 
void PORT_ChangeP74Output(BOOL initialValue);
void PORT_ChangeP75Input(void); 
void PORT_ChangeP75Output(BOOL initialValue);
void PORT_ChangeP76Input(void); 
void PORT_ChangeP76Output(BOOL initialValue);
void PORT_ChangeP77Input(void); 
void PORT_ChangeP77Output(BOOL initialValue);
void PORT_ChangeP78Input(void); 
void PORT_ChangeP78Output(BOOL initialValue);
void PORT_ChangeP79Input(void); 
void PORT_ChangeP79Output(BOOL initialValue);
void PORT_ChangeP710Input(void); 
void PORT_ChangeP710Output(BOOL initialValue);
void PORT_ChangeP711Input(void); 
void PORT_ChangeP711Output(BOOL initialValue);
void PORT_ChangeP712Input(void); 
void PORT_ChangeP712Output(BOOL initialValue);
void PORT_ChangeP713Input(void); 
void PORT_ChangeP713Output(BOOL initialValue);
void PORT_ChangeP714Input(void); 
void PORT_ChangeP714Output(BOOL initialValue);
void PORT_ChangeP715Input(void); 
void PORT_ChangeP715Output(BOOL initialValue);
void PORT_ChangeP93Input(BOOL enablePU);
void PORT_ChangeP93Output(BOOL initialValue);
void PORT_ChangeP94Input(BOOL enablePU);
void PORT_ChangeP94Output(BOOL initialValue);
void PORT_ChangeP95Input(BOOL enablePU);
void PORT_ChangeP95Output(BOOL initialValue);
void PORT_ChangeP96Input(BOOL enablePU);
void PORT_ChangeP96Output(BOOL initialValue);
void PORT_ChangeP97Input(BOOL enablePU);
void PORT_ChangeP97Output(BOOL initialValue);
void PORT_ChangeP98Input(BOOL enablePU);
void PORT_ChangeP98Output(BOOL initialValue);
void PORT_ChangeP99Input(BOOL enablePU);
void PORT_ChangeP99Output(BOOL initialValue);
void PORT_ChangeP910Input(BOOL enablePU);
void PORT_ChangeP910Output(BOOL initialValue);
void PORT_ChangeP911Input(BOOL enablePU);
void PORT_ChangeP911Output(BOOL initialValue);
void PORT_ChangeP912Input(BOOL enablePU);
void PORT_ChangeP912Output(BOOL initialValue);
void PORT_ChangeP913Input(BOOL enablePU);
void PORT_ChangeP913Output(BOOL initialValue);
void PORT_ChangePCM0Input(void); 
void PORT_ChangePCM0Output(BOOL initialValue);
void PORT_ChangePCM1Input(void); 
void PORT_ChangePCM1Output(BOOL initialValue);
void PORT_ChangePCM2Input(void); 
void PORT_ChangePCM2Output(BOOL initialValue);
void PORT_ChangePCM3Input(void); 
void PORT_ChangePCM3Output(BOOL initialValue);
void PORT_ChangePCS0Input(void); 
void PORT_ChangePCS0Output(BOOL initialValue);
void PORT_ChangePCS1Input(void); 
void PORT_ChangePCS1Output(BOOL initialValue);
void PORT_ChangePCT0Input(void); 
void PORT_ChangePCT0Output(BOOL initialValue);
void PORT_ChangePCT1Input(void); 
void PORT_ChangePCT1Output(BOOL initialValue);
void PORT_ChangePDL6Input(void); 
void PORT_ChangePDL6Output(BOOL initialValue);
void PORT_ChangePDL7Input(void); 
void PORT_ChangePDL7Output(BOOL initialValue);
void PORT_ChangePDL8Input(void); 
void PORT_ChangePDL8Output(BOOL initialValue);
void PORT_ChangePDL9Input(void); 
void PORT_ChangePDL9Output(BOOL initialValue);
void PORT_ChangePDL10Input(void); 
void PORT_ChangePDL10Output(BOOL initialValue);
void PORT_ChangePDL11Input(void); 
void PORT_ChangePDL11Output(BOOL initialValue);
void PORT_ChangePDL12Input(void); 
void PORT_ChangePDL12Output(BOOL initialValue);
void PORT_ChangePDL13Input(void); 
void PORT_ChangePDL13Output(BOOL initialValue);
/* Start user code for definition. Do not edit comment generated here */
/* End user code for definition. Do not edit comment generated here */
#endif
