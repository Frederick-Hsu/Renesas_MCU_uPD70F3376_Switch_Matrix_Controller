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
**  Filename :	system.h
**  Abstract :	This file implements device driver for System module.
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
#ifndef _MDSYSTEM_
#define _MDSYSTEM_
/*
*******************************************************************************
**	Register bit define
*******************************************************************************
*/
/*
	Main system clock mode register (MCM)
*/
/* Clock selection of main system clock fXX (MCM0) */
#define	CG_MAINSYS_HISPEED		0x00	/* operating on 8 MHz clock fRH */
#define	CG_MAINSYS_MAINOSC		0x01	/* operating on MainOSC clock fX */

/*
	Oscillation stabilization time counter status register (OSTC)
*/
/* Oscillation stabilization status of MainOSC ( MSTS) */
#define	CG_OSCSTAB_STOP			0x00	/* MainOSC stopped or waiting for oscillation stabilization */
#define	CG_OSCSTAB_END			0x01	/* MainOSC oscillation stabilization ended */

/*
	Oscillation stabilization time select register (OSTS)
*/
/* Selection of oscillation stabilization / setup time (OSTS4~0) */
#define	CG_OSCSTAB_SEL10		0x00	/* 2^10/fx */
#define	CG_OSCSTAB_SEL11		0x01	/* 2^11/fx */
#define	CG_OSCSTAB_SEL12		0x02	/* 2^12/fx */
#define	CG_OSCSTAB_SEL13		0x03	/* 2^13/fx */
#define	CG_OSCSTAB_SEL14		0x04	/* 2^14/fx */
#define	CG_OSCSTAB_SEL15		0x05	/* 2^15/fx */
#define	CG_OSCSTAB_SEL16		0x06	/* 2^16/fx */
#define	CG_OSCSTAB_SEL17		0x07	/* 2^17/fx */
#define	CG_OSCSTAB_SEL18		0x08	/* 2^18/fx */
#define	CG_OSCSTAB_SEL19		0x09	/* 2^19/fx */
#define	CG_OSCSTAB_SEL20		0x0a	/* 2^20/fx */
#define	CG_OSCSTAB_SEL21		0x0b	/* 2^21/fx */

#define	CG_OSCSTAB2_SEL4		0x12	/* 2^4/fx */
#define	CG_OSCSTAB2_SEL5		0x13	/* 2^5/fx */
#define	CG_OSCSTAB2_SEL6		0x14	/* 2^6/fx */
#define	CG_OSCSTAB2_SEL7		0x15	/* 2^7/fx */
#define	CG_OSCSTAB2_SEL8		0x16	/* 2^8/fx */
#define	CG_OSCSTAB2_SEL9		0x17	/* 2^9/fx */
#define	CG_OSCSTAB2_SEL10		0x18	/* 2^10/fx */
#define	CG_OSCSTAB2_SEL11		0x19	/* 2^11/fx */
#define	CG_OSCSTAB2_SEL12		0x1a	/* 2^12/fx */
#define	CG_OSCSTAB2_SEL13		0x1b	/* 2^13/fx */

/*
	Processor clock control register (PCC)
*/
#define	CG_PCC_INITIALVALUE		0x40
/* Use of built-in Sub oscillator feedback resistor (FRC) */
#define	CG_CPUCLK_SUBFEED		0x00	/* SubOSC feedback resistor connected */
#define	CG_CPUCLK_SUBNOTFEED	0x80	/* SubOSC feedback resistor not connected */
/* Operation of MainOSC (MCK) */
#define	CG_CPUCLK_MAINENABLE	0x00	/* MainOSC oscillation enabled */
#define	CG_CPUCLK_MAINSTOP		0x40	/* MainOSC oscillation stopped */
/* Use of main oscillator on-chip feedback resistor (MFRC) */
#define	CG_CPUCLK_MAINFEEDBACK	0x00	/* MainOSC feedback resistor connected */
#define	CG_CPUCLK_MAINNOTFEED	0x20	/* MainOSC feedback resistor not connected */
/* Status of CPU system clock fVBCLK (CLS) */
#define	CG_CPUCLK_MAINSYSOPER	0x00	/* Main system clock fXX operation */
#define	CG_CPUCLK_SUBOPER		0x10	/* Subclock fSC operation */
/* CPU system clock selection (CK3~0) */
#define	CG_CPUCLK				0x07
#define	CG_CPUCLK_MAIN0			0x00	/* fCPU = fXX */
#define	CG_CPUCLK_MAIN1			0x01	/* fCPU = fXX/2 */
#define	CG_CPUCLK_MAIN2			0x02	/* fCPU = fXX/2^2 */
#define	CG_CPUCLK_MAIN3			0x03	/* fCPU = fXX/2^3 */
#define	CG_CPUCLK_MAIN4			0x04	/* fCPU = fXX/2^4 */
#define	CG_CPUCLK_MAIN5			0x05	/* fCPU = fXX/2^5 */
#define	CG_CPUCLK_SUB			0x08	/* fSC (fXT or fRL) */

/*
	Programmable clock mode register (PCLM)
*/
/* PCL enable (PCLE) */
#define	CG_PCL_DISABLE			0x00	/* PCL disabled (PCL pin is fixed to low level) */
#define	CG_PCL_ENABLE			0x10	/* PCL enabled */
/* PCL clock frequency selection (PCK1~0) */
#define	CG_PCL_SEL0				0x00	/* fPCL= fPLLO/4 */
#define	CG_PCL_SEL1				0x01	/* fPCL= fPLLO/8 */
#define	CG_PCL_SEL2				0x02	/* fPCL= fPLLO/16 */
#define	CG_PCL_SEL3				0x03	/* fPCL= fPLLO/32 */

/*
	Ring oscillator mode register (RCM)
*/
#define	CG_RCM_INITIALVALUE		0x80
/* Oscillation stability status of 8 MHz RingOSC (RSTS) */
#define	CG_HICLK_STATUSSTOP		0x00	/* 8 MHz clock stopped or waiting for oscillation stability */
#define	CG_HICLK_STATUSOPER		0x80	/* 8 MHz clock operating */
/* Operation/stop of 8 MHz RingOSC (HRSTOP) */
#define	CG_HICLK_OPER			0x00	/* 8 MHz RingOSC operating */
#define	CG_HICLK_STOP			0x02	/* 8 MHz RingOSC stopped */
/* Operation/stop of 240 KHz clock (RSTOP) */
#define	CG_LOWCLK_OPER			0x00	/* 240 KHz clock operating */
#define	CG_LOWCLK_STOP			0x01	/* 240 KHz clock stopped */

/*
	PLL lock status register (LOCKR)
*/
/* PLL lock status check (LOCK) */
#define	CG_PLLSTATUS_LOCK		0x00	/* locked status */
#define	CG_PLLSTATUS_UNLOCK		0x01	/* unlocked status (during the lockup (frequency stabilization) time) */

/*
	PLL control register (PLLCTL)
*/
/* Main system clock fXX mode selection (SELPLL) */
#define	CG_PLLCTL_CLKTHROHGH	0x00	/* clock-through mode */
#define	CG_PLLCTL_PLL			0x02	/* PLL mode */
/* Control of PLL operation/stop (PLLON) */
#define	CG_PLLCTL_STOPED		0x00	/* PLL stopped */
#define	CG_PLLCTL_STARTED		0x01	/* PLL started */

/*
	PLL lockup time specification register (PLLS)
*/
/* PLL lockup time selection (PLLS2~0) */
#define	CG_PLLLOCKUP_SEL0		0x02	/* 2^12/fX */
#define	CG_PLLLOCKUP_SEL1		0x03	/* 2^13/fX (default value) */
#define	CG_PLLLOCKUP_SEL2		0x04	/* 2^14/fX */

/*
	SSCG control register (SSCGCTL)
*/
/* PLL/SSCG output clock selection (SELSSCG) */
#define	CG_SSCGCTL_SELPLL		0x00	/* PLL output selected (fPLL = fPLLO or fPLLO/2) */
#define	CG_SSCGCTL_SELSSCG		0x02	/* SSCG output selected (fPLL = fSSCGO or fSSCGO/2) */
/* SSCG stop control (SSCGON) */
#define	CG_SSCGCTL_STOP			0x00	/* SSCG stopped */
#define	CG_SSCGCTL_ENABLE		0x01	/* SSCG enabled */

/*
	SSCG frequency control register 0 (SFC0)
*/
/* SSCG input frequency divider selector (SFC07) */
#define	CG_SSCGI_DIVBY1			0x00	/* fSSCGI = fx */
#define	CG_SSCGI_DIVBY2			0x80	/* fSSCGI = fx/2 */
/* SSCG input clock divider selector (SFC06~04) */
#define	CG_SSCGDIV_SEL0			0x00	/* fSSCGI */
#define	CG_SSCGDIV_SEL1			0x10	/* fSSCGI/2 */
#define	CG_SSCGDIV_SEL2			0x20	/* fSSCGI/3 */
#define	CG_SSCGDIV_SEL3			0x30	/* fSSCGI/4 */
#define	CG_SSCGDIV_SEL4			0x40	/* fSSCGI/5 */
#define	CG_SSCGDIV_SEL5			0x50	/* fSSCGI/6 */
#define	CG_SSCGDIV_SEL6			0x60	/* fSSCGI/7 */
#define	CG_SSCGDIV_SEL7			0x70	/* fSSCGI/8 */
/* SSCG output clock divider selector (SFC03~02) */
#define	CG_SSCGO_DIVBY2			0x04	/* Division by 2 */
#define	CG_SSCGO_DIVBY4			0x08	/* Division by 4 */
/* SSCG input frequency range specification selector (SFC01~00) */
#define	CG_SSCGFREQ_RANGE0		0x00	/* 0.87MHz <= fPFD < 1.00MHz */
#define	CG_SSCGFREQ_RANGE1		0x01	/* 1.00MHz <= fPFD < 1.22MHz */
#define	CG_SSCGFREQ_RANGE2		0x02	/* 1.22MHz <= fPFD < 1.45MHz */
#define	CG_SSCGFREQ_RANGE3		0x03	/* 1.45MHz <= fPFD <= 1.74MHz */

/*
	SSCG frequency control register (SFC1)
*/
/* Frequency modulation enable control (SFC17) */
#define	CG_SSCGMOD_DISABLE		0x00	/* Modulation disabled */
#define	CG_SSCGMOD_ENABLE		0x80	/* Modulation enabled */
/* Frequency modulation range control (SFC16~14) */
#define	CG_SSCGMOD_RANGE0		0x00	/* 0.5% (typical value) */
#define	CG_SSCGMOD_RANGE1		0x10	/* 1.0% (typical value) */
#define	CG_SSCGMOD_RANGE2		0x20	/* 2.0% (typical value) */
#define	CG_SSCGMOD_RANGE3		0x30	/* 3.0% (typical value) */
#define	CG_SSCGMOD_RANGE4		0x40	/* 4.0% (typical value) */
#define	CG_SSCGMOD_RANGE5		0x50	/* 5.0% (typical value) */
/* Frequency modulation frequency control (SFC11~10) */
#define	CG_SSCGMOD_FREQ0		0x00	/* 40 KHz (typical value) */
#define	CG_SSCGMOD_FREQ1		0x01	/* 50 KHz (typical value) */
#define	CG_SSCGMOD_FREQ2		0x02	/* 60 KHz (typical value) */

/*
	Power save control register (PSC)
*/
/* Stand-by mode release control by occurrence of INTWDT2 signal (NMI1M) */
#define	CG_STANDBY_INTWDT2EN	0x00	/* enable releasing stand-by mode by INTWDT2 signal */
#define	CG_STANDBY_INTWDT2DIS	0x40	/* disable releasing stand-by mode by INTWDT2 signal */
/* Stand-by mode release control by NMI pin input (NMI0M) */
#define	CG_STANDBY_NMIEN		0x00	/* enable releasing stand-by mode by NMI pin input */
#define	CG_STANDBY_NMIDIS		0x20	/* disable releasing stand-by mode by NMI pin input */
/* Stand-by mode release control by maskable interrupt request signal (NMI0M) */
#define	CG_STANDBY_MSKIEN		0x00	/* enable releasing stand-by mode by maskable interrupt request signal */
#define	CG_STANDBY_MSKIDIS		0x10	/* disable releasing stand-by mode by maskable interrupt request signal */
/* Setting of stand-by mode (STP) */
#define	CG_STANDBY_UNUSE		0x00	/* normal mode */
#define	CG_STANDBY_USE			0x02	/* stand-by mode */

/*
	Power save mode control register (PSMR)
*/
/* Specification of operation in software stand-by mode (PSM1~0) */
#define	CG_POWERSAVE_IDLE1		0x00	/* IDLE1 mode */
#define	CG_POWERSAVE_STOP1		0x01	/* stop mode */
#define	CG_POWERSAVE_IDLE2		0x02	/* IDLE2 mode or sub-IDLE mode */
#define	CG_POWERSAVE_STOP2		0x03	/* stop mode */

/*
	Prescaler3 mode register (PRSM0)
*/
/* Prescaler3 output (BGCE0) */
#define	CG_PRESCALER3_DISABLE	0x00	/* Prescale3 output disabled */
#define	CG_PRESCALER3_ENABLE	0x10	/* Prescale3 output enabled */
/* Selection of counter clock (BGCS01~00) */
#define	CG_PRESCALER3_CLK0		0x00	/* fX */
#define	CG_PRESCALER3_CLK1		0x01	/* fX/2 */
#define	CG_PRESCALER3_CLK2		0x02	/* fX/4 */
#define	CG_PRESCALER3_CLK3		0x03	/* fX/8 */

/*
	Main oscillator Clock Monitor mode register (CLM)
*/
/* Clock Monitor enable (CLME) */
#define	CG_CLKMONITOR_DISABLE	0x00	/* clock Monitor for main oscillator disabled */
#define	CG_CLKMONITOR_ENABLE	0x01	/* clock Monitor for main oscillator enabled */

/*
	Selector control register 4 (SELCNT4)
*/
#define	CG_SELCNT4_FXX			0x00	/* fXP1 = fXX */
#define	CG_SELCNT4_FXMPLL		0x01	/* fXP1 = fXMPLL */

/*
	Watchdog Timer 2 mode register (WDTM2)
*/
/* Selection of operation mode (WDM21, WDM20) */
#define	WDT2_OPERMODE_STOP		0x00	/* stops operation */
#define	WDT2_OPERMODE_NONMASK	0x20	/* non-maskable interrupt request mode (generation of INTWDT2) */
#define	WDT2_OPERMODE_RESET		0x40	/* reset mode (generation of RESWDT2) */
/* Selection of clock mode (WDCS23) */
#define	WDT2_CLKMODE_LOWSPEED	0x00	/* use 240k low speed interval oscillator */
#define	WDT2_CLKMODE_MAINOSC	0x08	/* use Main OSC clock */
/* Watchdog Timer 2 Clock Selection (WDCS22~WDCS20) */
#define	WDT2_CLOCK_SEL0			0x00	/* 2^12/fRL or 2^16/fX */
#define	WDT2_CLOCK_SEL1			0x01	/* 2^13/fRL or 2^17/fX */
#define	WDT2_CLOCK_SEL2			0x02	/* 2^14/fRL or 2^18/fX */
#define	WDT2_CLOCK_SEL3			0x03	/* 2^15/fRL or 2^19/fX */
#define	WDT2_CLOCK_SEL4			0x04	/* 2^16/fRL or 2^20/fX */
#define	WDT2_CLOCK_SEL5			0x05	/* 2^17/fRL or 2^21/fX */
#define	WDT2_CLOCK_SEL6			0x06	/* 2^18/fRL or 2^22/fX */
#define	WDT2_CLOCK_SEL7			0x07	/* 2^19/fRL or 2^23/fX */
/* Watchdog Timer 2 Clock Control (WDCS24) */
#define	WDT2_CLOCK_STOP			0x10	/* WDT2 clock stop */

/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/
#define	CG_MAINOSC_FREQ			16
#define	CG_SSCGWAITTIME			40
#define	CG_LOCKR_WAITTIME		2000
#define	CG_SSCGLOCK_WAITTIME	16000
#define	CG_OSTC_WAITTIME		20000
#define	CG_SSCG_MINRANGE		8
#define	CG_SSCG_MAXRANGE		48
enum ClockMode { HISPEEDCLK, MAINOSCCLK, PLLCLK, SUBCLK };
enum CPUClock { SYSTEMCLOCK, SYSONEHALF, SYSONEFOURTH, SYSONEEIGHTH, 
				SYSONESIXTEENTH, SYSONETHIRTYSECOND };
enum PSLevel { PSSTOP, PSHALT, PSIDLE1, PSIDLE2 };
enum StabTime { STLEVEL0, STLEVEL1, STLEVEL2, STLEVEL3,
				STLEVEL4, STLEVEL5, STLEVEL6, STLEVEL7,
				STLEVEL8, STLEVEL9, STLEVEL10, STLEVEL11,
				STLEVEL18=18, STLEVEL19,STLEVEL20, STLEVEL21,
				STLEVEL22, STLEVEL23,	STLEVEL24, STLEVEL25,
				STLEVEL26, STLEVEL27};

/*
*******************************************************************************
**  Function define
*******************************************************************************
*/
void Clock_Init(void);
void CG_ReadResetSource(void);
/* Start user code for definition. Do not edit comment generated here */
/* End user code for definition. Do not edit comment generated here */
#endif
