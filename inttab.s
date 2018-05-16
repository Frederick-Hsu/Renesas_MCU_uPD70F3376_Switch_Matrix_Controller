--/*
--*****************************************************************************
--*
--*  This device driver was created by Applilet2 for V850ES/Fx3
--*  32-Bit Single-Chip Microcontrollers
--*
--*  Copyright(C) 2002, 2012 Renesas Electronics Corporation
--*  All rights reserved by Renesas Electronics Corporation.
--*
--*  This program should be used on your own responsibility.
--*  Renesas Electronics Corporation assumes no responsibility for any losses
--*  incurred by customers or third parties arising from the use of this file.
--*
--*  Filename :	 inttab.s
--*  Abstract :	This file implements interrupt vector table.
--*  APIlib :	Applilet2 for V850ES/Fx3 V2.43 [30 Mar 2011]
--*
--*  Device :	uPD70F3376
--*
--*  Compiler :	CA850
--*
--*  Creation date:	09/26/2012
--*  
--*****************************************************************************
--*/

--/*
--*****************************************************************************
--*  interrupt variable
--*****************************************************************************
--*/

	--.section "RESET", text
	--jr      __start
	.section "NMI", text			--nmi pin input
	reti
	.section "INTWDT2", text		--WDT2 OVF nonmaskable
	reti
	.section "TRAP00", text			--TRAP instruction
	.globl	__trap00
__trap00:
	reti
	.section "TRAP10", text			--TRAP instruction
	.globl	__trap01
__trap01:
	reti
	.section "ILGOP", text			--ILGOP/DBG0
	.section "OPTION_BYTES", text
	.byte	 0x00
	.byte	 0x82
	.byte	 0
	.byte	 0
	.byte	 0
	.byte	 0
	.section "INTLVIL", text		--INTLVIL
	reti
	.section "INTLVIH", text		--INTLVIH
	reti
	.section "INTP0", text			--INTP0 pin
	reti
	.section "INTP1", text			--INTP1 pin
	reti
	.section "INTP2", text			--INTP2 pin
	reti
	.section "INTP3", text			--INTP3 pin
	reti
	.section "INTP4", text			--INTP4 pin
	reti
	.section "INTP5", text			--INTP5 pin
	reti
	.section "INTP6", text			--INTP6 pin
	reti
	.section "INTP7", text			--INTP7 pin
	reti
	.section "INTTAB0OV", text		--INTTAB0OV
	reti
	.section "INTTAB0CC0", text		-- INTTAB0CC0
	reti
	.section "INTTAB0CC1", text		-- INTTAB0CC1
	reti
	.section "INTTAB0CC2", text		-- INTTAB0CC2
	reti
	.section "INTTAB0CC3", text		-- INTTAB0CC3
	reti
	.section "INTTAA0OV", text		-- INTTAA0OV
	reti
	.section "INTTAA0CC1", text		--INTTAA0CC1
	reti
	.section "INTTAA1OV", text		--INTTAA1OV
	reti
	.section "INTTAA1CC1", text		--INTTAA1CC1
	reti
	.section "INTTAA2OV", text		--INTTAA2OV
	reti
	.section "INTTAA2CC0", text		--INTTAA2CC0
	reti
	.section "INTTAA2CC1", text		--INTTAA2CC1
	reti
	.section "INTTAA3OV", text		--INTTAA3OV
	reti
	.section "INTTAA3CC0", text		--INTTAA3CC0
	reti
	.section "INTTAA3CC1", text		--INTTAA3CC1
	reti
	.section "INTTAA4OV", text		--INTTAA4OV
	reti
	.section "INTTAA4CC0", text		--INTTAA4CC0
	reti
	.section "INTTAA4CC1", text		--INTTAA4CC1
	reti
	.section "INTCB0R", text		--INTCB0R
	reti
	.section "INTCB0T", text		--INTCB0T
	reti
	.section "INTCB1R", text		--INTCB1R
	reti
	.section "INTCB1T", text		--INTCB1T
	reti
	.section "INTUD1S", text		--INTUD1S
	reti
	.section "INTUD1R", text		--INTUD1R
	reti
	.section "INTUD1T", text		--INTUD1T
	reti
	.section "INTAD", text			--INTAD
	reti
	.section "INTDMA0", text		--INTDMA0
	reti
	.section "INTDMA1", text		--INTDMA1
	reti
	.section "INTDMA2", text		--INTDMA2
	reti
	.section "INTDMA3", text		--INTDMA3
	reti
	.section "INTKR", text			--INTKR
	reti
	.section "INTWTI", text			--INTWTI
	reti
	.section "INTWT", text			--INTWT
	reti
	.section "INTP8", text			--INTP8
	reti
	.section "INTP9", text			--INTP9
	reti
	.section "INTP10", text			--INTP10
	reti
	.section "INTTAB1OV", text		--INTTAB1OV
	reti
	.section "INTTAB1CC0", text		--INTTAB1CC0
	reti
	.section "INTTAB1CC1", text		--INTTAB1CC1
	reti
	.section "INTTAB1CC2", text		--INTTAB1CC2
	reti
	.section "INTTAB1CC3", text		--INTTAB1CC3
	reti
	.section "INTC1ERR", text		--INTC1ERR
	reti
	.section "INTC1WUP", text		--INTC1WUP
	reti
	.section "INTC1REC", text		--INTC1REC
	reti
	.section "INTC1TRX", text		--INTC1TRX
	reti
	.section "INTP14", text			--INTP14
	reti
	.section "INTUD3S", text		--INTUD3S
	reti
	.section "INTUD3R", text		--INTUD3R
	reti
	.section "INTUD3T", text		--INTUD3T
	reti

-- end of file
