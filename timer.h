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
**  Filename :	timer.h
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
#ifndef _MDTIMER_
#define _MDTIMER_
/*
*******************************************************************************
**	Register bit define
*******************************************************************************
*/
/* 
	TAA control register 0 (TAAnCTL0)
*/

/* Timer AAn operation control (TAAnCE) */
#define	TAA_OPERATION_DISABLE		0x00	/* disable internal operating clock operation (asynchronously reset TAAn) */
#define	TAA_OPERATION_ENABLE		0x80	/* enable internal operating clock operation */

/* Internal count clock selection (TAAnCKS2,TAAnCKS1,TAAnCKS0) */
#define	TAA_INTERNAL_CLOCK0			0x00	/* fxp1 */
#define	TAA_INTERNAL_CLOCK1			0x00	/* fxp2 */
#define	TAA_INTERNAL_CLOCK2			0x01	/* fxp1/2 */
#define	TAA_INTERNAL_CLOCK3			0x01	/* fxp2/2 */
#define	TAA_INTERNAL_CLOCK4			0x02	/* fxp1/4 */
#define	TAA_INTERNAL_CLOCK5			0x02	/* fxp2/4 */
#define	TAA_INTERNAL_CLOCK6			0x03	/* fxp1/8 */
#define	TAA_INTERNAL_CLOCK7			0x04	/* fxp1/16 */
#define	TAA_INTERNAL_CLOCK8			0x05	/* fxp1/32 */
#define	TAA_INTERNAL_CLOCK9			0x06	/* fxp1/64 */
#define	TAA_INTERNAL_CLOCK10			0x07	/* fxp1/128 or fxt */

/* 
	TAA control register 1 (TAAnCTL1)
*/

/* Synchroneous operation mode enable (TAAnSYE) */
#define	TAA_OPERATION_INDEPENDENT	0x00	/* independent operation mode (asynchronous operation mode) */
#define	TAA_OPERATION_SYNCHRONEOUS	0x80	/* synchroneous operation mode (specification of slave operation) */

/* Software trigger control (TAAnEST) */
#define	TAA_SOFTTRIGGER_OFF			0x00	/* no operation */
#define	TAA_SOFTTRIGGER_ON			0x40	/* in one-shot pulse mode: One-shot pulse software trigger */
											/* in external trigger pulse output mode: Pulse output software trigger */
/* Count clock selection (TAAnEEE) */
#define	TAA_INTERNAL_CLOCK			0x00	/* use the internal clock (clock selected with bits TAAnCKS2 to TAAnCKS0) */
#define	TAA_EXTERNAL_CLOCK			0x20	/* use the external clock from the TIABn0 input pin */ 

/* Timer mode selection (TAAnMD2,TAAnMD1,TAAnMD0) */
#define	TAA_MODE_INTERVAL			0x00	/* interval timer mode */
#define	TAA_MODE_EXTERNALCOUNT		0x01	/* external event counter mode */
#define	TAA_MODE_EXTERNALTRG		0x02	/* external trigger pulse output mode */
#define	TAA_MODE_ONESHOT			0x03	/* one-shot pulse mode */
#define	TAA_MODE_PWM				0x04	/* PWM mode */
#define	TAA_MODE_FREERUNNING		0x05	/* free-running mode */
#define	TAA_MODE_PULSEMEASURE		0x06	/* pulse width measurement mode */

/* 
	TAA dedicated I/O control register 0 (TAAnIOC0)
*/

/* Timer output 0 level setting (TAAnOL0) */
#define	TAA_OUTPUT0_NORMAL			0x00	/* normal output */
#define	TAA_OUTPUT0_INVERTED		0x02	/* inverted output */

/* Timer output 0 setting (TAAnOE0) */
#define	TAA_OUTPUT0_DISABLE			0x00	/* disable timer output */
#define	TAA_OUTPUT0_ENABLE			0x01	/* enable timer output (TOAAn0 pin outputs pulses) */

/* Timer output 1 level setting (TAAnOL1) */
#define	TAA_OUTPUT1_NORMAL			0x00	/* normal output */
#define	TAA_OUTPUT1_INVERTED		0x08	/* inverted output */

/* Timer output 1 setting (TAAnOE1) */
#define	TAA_OUTPUT1_DISABLE			0x00	/* disable timer output */
#define	TAA_OUTPUT1_ENABLE			0x04	/* enable timer output (TOAAn1 pin outputs pulses) */

/* 
	TAA dedicated I/O control register 1 (TAAnIOC1)
*/

/* Capture input (TIAAn1) valid edge setting (TAAnIS3,TAAnIS2) */
#define	TAA_INPUT1_EDGE_NONE		0x00	/* detect no edge (capture operation is invalid) */
#define	TAA_INPUT1_EDGE_RISING		0x04	/* detection of rising edge */
#define	TAA_INPUT1_EDGE_FALLING		0x08	/* detection of falling edge */
#define	TAA_INPUT1_EDGE_BOTH		0x0c	/* detection of both edges */

/* Capture input (TIAAn0) valid edge setting (TAAnIS1,TAAnIS0) */
#define	TAA_INPUT0_EDGE_NONE		0x00	/* detect no edge (capture operation is invalid) */
#define	TAA_INPUT0_EDGE_RISING		0x01	/* detection of rising edge */
#define	TAA_INPUT0_EDGE_FALLING		0x02	/* detection of falling edge */
#define	TAA_INPUT0_EDGE_BOTH		0x03	/* detection of both edges */

/* 
	TAA dedicated I/O control register 2 (TAAnIOC2)
*/
/* Setting of valid edge of external trigger input(TIAAn0) (TAAnETS1,TAAnETS0) */
#define	TAA_EXTTRIGGER_EDGE_NONE	0x00	/* detect no edge (external trigger is invalid) */
#define	TAA_EXTTRIGGER_EDGE_RISING	0x01	/* detection of rising edge */
#define	TAA_EXTTRIGGER_EDGE_FALLING	0x02	/* detection of falling edge */
#define	TAA_EXTTRIGGER_EDGE_BOTH	0x03	/* detection of both edges */

/* Setting of valid edge of external event count input(TIAAn0) (TAAnEES1,TAAnEES0) */
#define	TAA_EXTCOUNT_EDGE_NONE		0x00	/* detect no edge (external event count is invalid) */
#define	TAA_EXTCOUNT_EDGE_RISING	0x04	/* detection of rising edge */
#define	TAA_EXTCOUNT_EDGE_FALLING	0x08	/* detection of falling edge */
#define	TAA_EXTCOUNT_EDGE_BOTH		0x0c	/* detection of both edges */

/* 
	TAA I/O control register 4 (TAAnIOC4)
*/

/* Toggle Control of TOABn1 (TAAnOS1,TAAnOR1) */
#define	TAA_OUTPUT1_STANDARD		0x00	/* standard operation */
#define	TAA_OUTPUT1_INACTIVE		0x04	/* force output level to inactive at next toggle event */
#define	TAA_OUTPUT1_ACTIVE			0x08	/* force output level to active at next toggle event */
#define	TAA_OUTPUT1_FREEZE			0x0c	/* freeze current output level. */

/* Toggle Control of TOABn0 (TAAnOS0,TAAnOR0) */
#define	TAA_OUTPUT0_STANDARD		0x00	/* standard operation */
#define	TAA_OUTPUT0_INACTIVE		0x01	/* force output level to inactive at next toggle event */
#define	TAA_OUTPUT0_ACTIVE			0x02	/* force output level to active at next toggle event */
#define	TAA_OUTPUT0_FREEZE			0x03	/* freeze current output level. */

/* 
	TAA option register 0 (TAAnOPT0)
*/

/* Selection of capture or compare operation of TAAnCCR1 register (TAAnCCS1) */
#define	TAA_CCR1_COMPARE			0x00	/* compare register */
#define	TAA_CCR1_CAPTURE			0x20	/* capture register */

/* Selection of capture or compare operation of TAAnCCR0 register (TAAnCCS0) */
#define	TAA_CCR0_COMPARE			0x00	/* compare register */
#define	TAA_CCR0_CAPTURE			0x10	/* capture register */

/* 
	TAA option register 1 (TAAnOPT1)
*/
#define TAA_CSE_NON_CASCADED		0x00	/* 16-bit non cascaded mode */
#define TAA_CSE_CASCADED			0x80	/* 32-bit cascaded mode */

/* Detection of Timer AB overflow (TAAnOVF) */
#define TAA_OVERFLOW_OCCUR			0x01	/* overflow occurred */
#define TAA_OVERFLOW_CLEAR			0x00	/* clear overflow */
/* 
	TAB control register 0 (TABnCTL0)
*/

/* Timer ABn operation control (TABnCE) */
#define	TAB_OPERATION_DISABLE		0x00	/* disable internal operating clock operation (asynchronously reset TABn) */
#define	TAB_OPERATION_ENABLE		0x80	/* enable internal operating clock operation */

/* Internal count clock selection (TABnCKS2,TABnCKS1,TABnCKS0) */
#define	TAB_INTERNAL_CLOCK0			0x00	/* fxp1 */
#define	TAB_INTERNAL_CLOCK1			0x01	/* fxp1/2 */
#define	TAB_INTERNAL_CLOCK2			0x02	/* fxp1/4 */
#define	TAB_INTERNAL_CLOCK3			0x03	/* fxp1/8 */
#define	TAB_INTERNAL_CLOCK4			0x04	/* fxp1/16 */
#define	TAB_INTERNAL_CLOCK5			0x05	/* fxp1/32 */
#define	TAB_INTERNAL_CLOCK6			0x06	/* fxp1/64 */
#define	TAB_INTERNAL_CLOCK7			0x07	/* fxp1/128 */

/* 
	TAB control register 1 (TABnCTL1)
*/

/* Synchroneous operation mode enable (TABnSYE) */
#define	TAB_OPERATION_INDEPENDENT	0x00	/* independent operation mode (asynchronous operation mode) */
#define	TAB_OPERATION_SYNCHRONEOUS	0x80	/* synchroneous operation mode (specification of slave operation) */

/* Software trigger control (TABnEST) */
#define	TAB_SOFTTRIGGER_OFF			0x00	/* no operation */
#define	TAB_SOFTTRIGGER_ON			0x40	/* in one-shot pulse mode: One-shot pulse software trigger */
											/* in external trigger pulse output mode: Pulse output software trigger */

/* Count clock selection (TABnEEE) */
#define	TAB_INTERNAL_CLOCK			0x00	/* use the internal clock (clock selected with bits TABnCKS2 to TABnCKS0) */
#define	TAB_EXTERNAL_CLOCK			0x20	/* use the external clock from the TIABn0 input pin */ 

/* Timer mode selection (TABnMD2,TABnMD1,TABnMD0) */
#define	TAB_MODE_INTERVAL			0x00	/* interval timer mode */
#define	TAB_MODE_EXTERNALCOUNT		0x01	/* external event counter mode */
#define	TAB_MODE_EXTERNALTRG		0x02	/* external trigger pulse output mode */
#define	TAB_MODE_ONESHOT			0x03	/* one-shot pulse mode */
#define	TAB_MODE_PWM				0x04	/* PWM mode */
#define	TAB_MODE_FREERUNNING		0x05	/* free-running mode */
#define	TAB_MODE_PULSEMEASURE		0x06	/* pulse width measurement mode */
#define	TAB_MODE_TRIANGULARPWM		0x07	/* triangular wave PWM mode */

/* 
	TAB dedicated I/O control register 0 (TABnIOC0)
*/

/* Timer output 0 level setting (TABnOL0) */
#define	TAB_OUTPUT0_NORMAL			0x00	/* normal output */
#define	TAB_OUTPUT0_INVERTED		0x02	/* inverted output */

/* Timer output 0 setting (TABnOE0) */
#define	TAB_OUTPUT0_DISABLE			0x00	/* disable timer output */
#define	TAB_OUTPUT0_ENABLE			0x01	/* enable timer output (TOABn0 pin outputs pulses) */

/* Timer output 1 level setting (TABnOL1) */
#define	TAB_OUTPUT1_NORMAL			0x00	/* normal output */
#define	TAB_OUTPUT1_INVERTED		0x08	/* inverted output */

/* Timer output 1 setting (TABnOE1) */
#define	TAB_OUTPUT1_DISABLE			0x00	/* disable timer output */
#define	TAB_OUTPUT1_ENABLE			0x04	/* enable timer output (TOABn1 pin outputs pulses) */

/* Timer output 2 level setting (TABnOL2) */
#define	TAB_OUTPUT2_NORMAL			0x00	/* normal output */
#define	TAB_OUTPUT2_INVERTED		0x20	/* inverted output */

/* Timer output 2 setting (TABnOE2) */
#define	TAB_OUTPUT2_DISABLE			0x00	/* disable timer output */
#define	TAB_OUTPUT2_ENABLE			0x10	/* enable timer output (TOABn2 pin outputs pulses) */

/* Timer output 3 level setting (TABnOL3) */
#define	TAB_OUTPUT3_NORMAL			0x00	/* normal output */
#define	TAB_OUTPUT3_INVERTED		0x80	/* inverted output */

/* Timer output 3 setting (TABnOE3) */
#define	TAB_OUTPUT3_DISABLE			0x00	/* disable timer output */
#define	TAB_OUTPUT3_ENABLE			0x40	/* enable timer output (TOABn3 pin outputs pulses) */

/* 
	TAB dedicated I/O control register 1 (TABnIOC1)
*/

/* Capture input (TIABn3) valid edge setting (TABnIS7,TABnIS6) */
#define	TAB_INPUT3_EDGE_NONE		0x00	/* detect no edge (capture operation is invalid) */
#define	TAB_INPUT3_EDGE_RISING		0x40	/* detection of rising edge */
#define	TAB_INPUT3_EDGE_FALLING		0x80	/* detection of falling edge */
#define	TAB_INPUT3_EDGE_BOTH		0xc0	/* detection of both edges */

/* Capture input (TIABn2) valid edge setting (TABnIS5,TABnIS4) */
#define	TAB_INPUT2_EDGE_NONE		0x00	/* detect no edge (capture operation is invalid) */
#define	TAB_INPUT2_EDGE_RISING		0x10	/* detection of rising edge */
#define	TAB_INPUT2_EDGE_FALLING		0x20	/* detection of falling edge */
#define	TAB_INPUT2_EDGE_BOTH		0x30	/* detection of both edges */

/* Capture input (TIABn1) valid edge setting (TABnIS3,TABnIS2) */
#define	TAB_INPUT1_EDGE_NONE		0x00	/* detect no edge (capture operation is invalid) */
#define	TAB_INPUT1_EDGE_RISING		0x04	/* detection of rising edge */
#define	TAB_INPUT1_EDGE_FALLING		0x08	/* detection of falling edge */
#define	TAB_INPUT1_EDGE_BOTH		0x0c	/* detection of both edges */

/* Capture input (TIABn0) valid edge setting (TABnIS1,TABnIS0) */
#define	TAB_INPUT0_EDGE_NONE		0x00	/* detect no edge (capture operation is invalid) */
#define	TAB_INPUT0_EDGE_RISING		0x01	/* detection of rising edge */
#define	TAB_INPUT0_EDGE_FALLING		0x02	/* detection of falling edge */
#define	TAB_INPUT0_EDGE_BOTH		0x03	/* detection of both edges */

/* 
	TAB dedicated I/O control register 2 (TABnIOC2)
*/

/* Setting of valid edge of external event count input(TIABn0) (TABnEES1,TABnEES0) */
#define	TAB_EXTCOUNT_EDGE_NONE		0x00	/* detect no edge (external event count is invalid) */
#define	TAB_EXTCOUNT_EDGE_RISING	0x04	/* detection of rising edge */
#define	TAB_EXTCOUNT_EDGE_FALLING	0x08	/* detection of falling edge */
#define	TAB_EXTCOUNT_EDGE_BOTH		0x0c	/* detection of both edges */

/* Setting of valid edge of external trigger input(TIABn0) (TABnETS1,TABnETS0) */
#define	TAB_EXTTRIGGER_EDGE_NONE	0x00	/* detect no edge (external trigger is invalid) */
#define	TAB_EXTTRIGGER_EDGE_RISING	0x01	/* detection of rising edge */
#define	TAB_EXTTRIGGER_EDGE_FALLING	0x02	/* detection of falling edge */
#define	TAB_EXTTRIGGER_EDGE_BOTH	0x03	/* detection of both edges */

/* 
	TAB I/O control register 4 (TABnIOC4)
*/

/* Toggle Control of TOABn3 (TABnOS3,TABnOR3) */
#define	TAB_OUTPUT3_STANDARD		0x00	/* standard operation */
#define	TAB_OUTPUT3_INACTIVE		0x40	/* force output level to inactive at next toggle event */
#define	TAB_OUTPUT3_ACTIVE			0x80	/* force output level to active at next toggle event */
#define	TAB_OUTPUT3_FREEZE			0xc0	/* freeze current output level. */

/* Toggle Control of TOABn2 (TABnOS2,TABnOR2) */
#define	TAB_OUTPUT2_STANDARD		0x00	/* standard operation */
#define	TAB_OUTPUT2_INACTIVE		0x10	/* force output level to inactive at next toggle event */
#define	TAB_OUTPUT2_ACTIVE			0x20	/* force output level to active at next toggle event */
#define	TAB_OUTPUT2_FREEZE			0x30	/* freeze current output level. */

/* Toggle Control of TOABn1 (TABnOS1,TABnOR1) */
#define	TAB_OUTPUT1_STANDARD		0x00	/* standard operation */
#define	TAB_OUTPUT1_INACTIVE		0x04	/* force output level to inactive at next toggle event */
#define	TAB_OUTPUT1_ACTIVE			0x08	/* force output level to active at next toggle event */
#define	TAB_OUTPUT1_FREEZE			0x0c	/* freeze current output level. */

/* Toggle Control of TOABn0 (TABnOS0,TABnOR0) */
#define	TAB_OUTPUT0_STANDARD		0x00	/* standard operation */
#define	TAB_OUTPUT0_INACTIVE		0x01	/* force output level to inactive at next toggle event */
#define	TAB_OUTPUT0_ACTIVE			0x02	/* force output level to active at next toggle event */
#define	TAB_OUTPUT0_FREEZE			0x03	/* freeze current output level. */

/* 
	TAB option register 0 (TABnOPT0)
*/

/* Selection of capture or compare operation of TABnCCR3 register (TABnCCS3) */
#define	TAB_CCR3_COMPARE			0x00	/* compare register */
#define	TAB_CCR3_CAPTURE			0x80	/* capture register */

/* Selection of capture or compare operation of TABnCCR2 register (TABnCCS2) */
#define	TAB_CCR2_COMPARE			0x00	/* compare register */
#define	TAB_CCR2_CAPTURE			0x40	/* capture register */

/* Selection of capture or compare operation of TABnCCR1 register (TABnCCS1) */
#define	TAB_CCR1_COMPARE			0x00	/* compare register */
#define	TAB_CCR1_CAPTURE			0x20	/* capture register */

/* Selection of capture or compare operation of TABnCCR0 register (TABnCCS0) */
#define	TAB_CCR0_COMPARE			0x00	/* compare register */
#define	TAB_CCR0_CAPTURE			0x10	/* capture register */

/* Detection of Timer AB overflow (TABnOVF) */
#define TAB_OVERFLOW_OCCUR			0x01	/* overflow occurred */
#define TAB_OVERFLOW_CLEAR			0x00	/* clear overflow */
/* 
	TMM control register 0 (TMnCTL0)
*/

/* Timer M operation control (TMnCE) */
#define	TMM_OPERATION_DISABLE		0x00	/* disable internal operating clock operation (asynchronously reset TMMn) */
#define	TMM_OPERATION_ENABLE		0x80	/* enable internal operating clock operation */

/* Internal count clock selection (TMnCKS2,TMnCKS1,TMnCKS0) */
#define	TMM_INTERNAL_CLOCK0			0x00	/* fxp1 */
#define	TMM_INTERNAL_CLOCK1			0x01	/* fxp1/2 */
#define	TMM_INTERNAL_CLOCK2			0x02	/* fxp1/4 */
#define	TMM_INTERNAL_CLOCK3			0x03	/* fxp1/64 */
#define	TMM_INTERNAL_CLOCK4			0x04	/* fxp1/512, frh/8 */
#define	TMM_INTERNAL_CLOCK5			0x05	/* INTWT */
#define	TMM_INTERNAL_CLOCK6			0x06	/* frl/8 */
#define	TMM_INTERNAL_CLOCK7			0x07	/* fxt */


/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/
/* TAA0 compare register 0 (TAA0CCR0)*/
#define TAA0_CCR0_VALUE			0x2
/* TAA1 compare register 0 (TAA1CCR0)*/
#define TAA1_CCR0_VALUE			0xc7f
/* TMM0 compare register 0 (TM0CMP0) */
#define TMM0_CMP0_VALUE         0xc7f
enum TMChannel { TMCHANNEL0, TMCHANNEL1, TMCHANNEL2, TMCHANNEL3 };
enum TMOutput { STANDARD, INACTIVE, ACTIVE, FREEZE };

/*
*******************************************************************************
**  Function define
*******************************************************************************
*/
void TAA0_Init(void);
void TAA0_Start(void);
void TAA0_Stop(void);
MD_STATUS TAA0_ChangeTimerCondition(USHORT* array_reg, UCHAR array_num);
__interrupt void MD_INTTAA0CC0(void);
void TAA1_Init(void);
void TAA1_Start(void);
void TAA1_Stop(void);
MD_STATUS TAA1_ChangeTimerCondition(USHORT* array_reg, UCHAR array_num);
__interrupt void MD_INTTAA1CC0(void);

void TMM0_Init(void);
void TMM0_Start(void);
void TMM0_Stop(void);
void TMM0_ChangeTimerCondition(USHORT regvalue);
__interrupt void MD_INTTM0EQ0(void);
/* Start user code for definition. Do not edit comment generated here */
/* End user code for definition. Do not edit comment generated here */
#endif
