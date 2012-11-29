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
**  Filename :	serial.h
**  Abstract :	This file implements device driver for Serial module.
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
#ifndef _MDSERIAL_
#define _MDSERIAL_
/*
*******************************************************************************
**	Register bit define
*******************************************************************************
*/
/*
	UARTDn control register 0(UDnCTL0)
*/

#define	UARTD_UDnCTL0_INITIALVALUE		0x10
/* UARTDn operation control(UDnPWR) */
#define	UARTD_OPERATION_DISABLE			0x00	/* Disable UARTDn operation (UARTDn reset asynchronously) */
#define	UARTD_OPERATION_ENABLE			0x80	/* Enable UARTDn operation */
/* Transmission operation enable(UDnTXE) */
#define	UARTD_TRANSMISSION_DISABLE		0x00	/* Disable transmission operation */
#define	UARTD_TRANSMISSION_ENABLE		0x40	/* Enable transmission operation */
/* Reception operation enable(UDnRXE) */
#define	UARTD_RECEPTION_DISABLE			0x00	/* Disable reception operation */
#define	UARTD_RECEPTION_ENABLE			0x20	/* Enable reception operation */
/* Transfer direction selection(UDnDIR) */
#define	UARTD_TRANSFDIR_MSB				0x00	/* MSB-first transfer */
#define	UARTD_TRANSFDIR_LSB				0x10	/* LSB-first transfer */
/* Parity selection during transmission/reception(UDnPS1,UDnPS0) */
#define	UARTD_PARITY_NONE				0x00	/* No parity output/Reception with no parity */
#define	UARTD_PARITY_ZREO				0x04	/* 0 parity output/Reception with 0 parity */
#define	UARTD_PARITY_ODD				0x08	/* Odd parity output/Odd parity check */
#define	UARTD_PARITY_EVEN				0x0C	/* Even parity output/Even parity check */
/* Specification of data character length of 1 frame of transmit/receive data(UDnCL) */
#define	UARTD_DATALENGTH_7BIT			0x00	/* 7 bits */
#define	UARTD_DATALENGTH_8BIT			0x02	/* 8 bits */
/* Specification of length of stop bit for transmit data(UDnSL) */
#define	UARTD_STOPLENGTH_1BIT			0x00	/* 1 bit */
#define	UARTD_STOPLENGTH_2BIT			0x01	/* 2 bits */

/*
	UARTDn base clock selects register(UDnCTL1)
*/

/* UDnCTL1 register(UDnCKS3, UDnCKS2, UDnCKS1, UDnCKS0) */
#define	UARTD_BASECLK_FXP1_1			0x00	/* fXP1 */
#define	UARTD_BASECLK_FXP2_1			0x00	/* fXP2 */
#define	UARTD_BASECLK_FXP1_2			0x01	/* fXP1/2 */
#define	UARTD_BASECLK_FXP1_4			0x02	/* fXP1/4 */
#define	UARTD_BASECLK_FXP1_8			0x03	/* fXP1/8 */
#define	UARTD_BASECLK_FXP1_16			0x04	/* fXP1/16 */
#define	UARTD_BASECLK_FXP1_32			0x05	/* fXP1/32 */
#define	UARTD_BASECLK_FXP1_64			0x06	/* fXP1/64 */
#define	UARTD_BASECLK_FXP1_128			0x07	/* fXP1/128 */
#define	UARTD_BASECLK_FXP1_256			0x08	/* fXP1/256 */
#define	UARTD_BASECLK_FXP1_512			0x09	/* fXP1/512 */
#define	UARTD_BASECLK_FXP1_1024			0x0A	/* fXP1/1024 */
/*
	CSIBn control register 0 (CBnCTL0)
*/

/* Specification of CSIBn operation disable/enable (CBnPWR)*/
#define CSIB_OPERATION_DISABLE	0x00	/* disable CSIBn operation and reset the CBnSTR register */
#define CSIB_OPERATION_ENABLE	0x80	/* enable CSIBn operation */

/* Specification of transmit operation disable/enable (CBnTXE)*/
#define CSIB_TRANSMIT_DISABLE	0x00	/* disable transmit operation */
#define CSIB_TRANSMIT_ENABLE	0x40	/* enable transmit operation */

/* Specification of receive operation disable/enable (CBnRXE)*/
#define CSIB_RECEIVE_DISABLE	0x00	/* disable receive operation */
#define CSIB_RECEIVE_ENABLE		0x20	/* enable receive operation */

/* Specification of transfer direction mode (MSB/LSB) (CBnDIR) */
#define CSIB_DATA_MSB	0x00	/* MSB first */ 
#define CSIB_DATA_LSB	0x10	/* LSB first */

/* Transfer mode specification (CBnTMS) */
#define CSIB_MODE_SINGLE		0x00	/* single transfer mode */
#define	CSIB_MODE_CONTINUOUS	0x02	/* continuous transfer mode */

/* Specification of start transfer disable/enable (CBnSCE) */
#define CSIB_STARTTRG_INVALID	0x00	/* Communication start trigger invalid */
#define	CSIB_STARTTRG_VALID		0x01	/* Communication start trigger valid */

/*
	CSIBn control register 1 (CBnCTL1)
*/

/* Specification of data transmission/reception timing in relation to SCKBn (CBnCKP, CBnDAP) */	
#define	CSIB_DATA_TIMING1		0x00	/* communication type 1 */
#define	CSIB_DATA_TIMING2		0x08	/* communication type 2 */
#define	CSIB_DATA_TIMING3		0x10	/* communication type 3 */
#define	CSIB_DATA_TIMING4		0x18	/* communication type 4 */

/* Specification of input clock (CBnCKS2,CBnCKS1,CBnCKS0) */
#define	CSIB_CLOCK_1			0x00	/* fxp1/2 */
#define	CSIB_CLOCK_2			0x01	/* fxp1/4 */
#define	CSIB_CLOCK_3			0x02	/* fxp1/8 */	
#define	CSIB_CLOCK_4			0x03	/* fxp1/16 */
#define	CSIB_CLOCK_5			0x04	/* fxp1/32 */
#define	CSIB_CLOCK_6			0x05	/* fxp1/64 */
#define	CSIB_CLOCK_7			0x06	/* n=0 : fBRG; n=1 : TOAA01; n=2,3 : fxp1/128 */
#define	CSIB_CLOCK_EXT			0x07	/* external clock SCKBn */

/*
	CSIBn control register 2 (CBnCTL2)
*/

/* Serial register bit length (CBnCL3,CBnCL2,CBnCL1,CBnCL0) */
#define	CSIB_DATA_LENGTH_8		0x00	/* 8 bits */
#define	CSIB_DATA_LENGTH_9		0x01	/* 9 bits */
#define	CSIB_DATA_LENGTH_10		0x02	/* 10 bits */
#define	CSIB_DATA_LENGTH_11		0x03	/* 11 bits */
#define	CSIB_DATA_LENGTH_12		0x04	/* 12 bits */
#define	CSIB_DATA_LENGTH_13		0x05	/* 13 bits */
#define	CSIB_DATA_LENGTH_14		0x06	/* 14 bits */
#define	CSIB_DATA_LENGTH_15		0x07	/* 15 bits */
#define	CSIB_DATA_LENGTH_16		0x08	/* 16 bits */

/*
	CSIBn status register (CBnSTR)
*/

/* Communication status flag (CBnTSF) */
#define CSIB_COMMUNICATION_STOP	0x00	/* communication stopped */
#define CSIB_COMMUNICATING		0x80	/* communicating */

/* Overrun error flag (CBnOVE) */
#define CSIB_OVERRUN_NONE		0x00	/* no overrun */
#define CSIB_OVERRUN			0x01	/* overrun */
/*
	IIC	control	register (IICCn)
*/
/* IIC operation enable	(IICEn)	*/
#define	IIC_OPERATION				0x80
#define	IIC_OPERATION_DISABLE		0x00	/* stop	operation */
#define	IIC_OPERATION_ENABLE		0x80	/* enable operation	*/
/* Exit	from communications	(LRELn)	*/
#define	IIC_COMMUNICATION			0x40
#define	IIC_COMMUNICATION_NORMAL	0x00	/* normal operation	*/
#define	IIC_COMMUNICATION_EXIT		0x40	/* exit	from current communication */
/* Wait	cancellation (WRELn) */
#define	IIC_WAITCANCEL				0x20
#define	IIC_WAIT_NOTCANCEL			0x00	/* do not cancel wait */
#define	IIC_WAIT_CANCEL				0x20	/* cancel wait */
/* Generation of interrupt when	stop condition (SPIEn) */
#define	IIC_STOPINT					0x10
#define	IIC_STOPINT_DISABLE			0x00	/* disable */
#define	IIC_STOPINT_ENABLE			0x10	/* enable */
/* Wait	and	interrupt generation (WTIMn) */
#define	IIC_WAITINT					0x08
#define	IIC_WAITINT_CLK8FALLING		0x00	/* generate	at the eighth clock's falling edge	*/	 
#define	IIC_WAITINT_CLK9FALLING		0x08	/* generated at	the	ninth clock's falling edge	*/ 
/* Acknowledgement control (ACKEn) */
#define	IIC_ACK						0x04
#define	IIC_ACK_DISABLE				0x00	/* enable acknowledgement */
#define	IIC_ACK_ENABLE				0x04	/* disable acknowledgement */
/* Start condition trigger (STTn) */
#define	IIC_STARTCONDITION			0x02
#define	IIC_START_NOTGENERATE		0x00	/* do not generate start condition */
#define	IIC_START_GENERATE			0x02	/* generate	start condition	*/
/* Stop	condition trigger (SPTn) */
#define	IIC_STOPCONDITION			0x01
#define	IIC_STOP_NOTGENERATE		0x00	/* do not generate stop	condition */
#define	IIC_STOP_GENERATE			0x01	/* generate	stop condition */

/*
	IIC	Status Register	(IICSn)
*/
/* Master device status	(MSTSn)	*/
#define	IIC_MASTERSTATUS			0x80
#define	IIC_STATUS_NOTMASTER		0x00	/* slave device	status or communication	standby	status */
#define	IIC_STATUS_MASTER			0x80	/* master device communication status */
/* Detection of	arbitration	loss (ALDn)	*/
#define	IIC_ARBITRATION				0x40
#define	IIC_ARBITRATION_NO			0x00	/* arbitration win or no arbitration */
#define	IIC_ARBITRATION_LOSS		0x40	/* arbitration loss	*/
/* Detection of	extension code reception (EXCn)	*/
#define	IIC_EXTENSIONCODE			0x20
#define	IIC_EXTCODE_NOT				0x00	/* extension code not received */
#define	IIC_EXTCODE_RECEIVED		0x20	/* extension code received */
/* Detection of	matching addresses (COIn) */
#define	IIC_ADDRESSMATCH			0x10
#define	IIC_ADDRESS_NOTMATCH		0x00	/* addresses do	not	match */
#define	IIC_ADDRESS_MATCH			0x10	/* addresses match */
/* Detection of	transmit/receive status	(TRCn) */
#define	IIC_STATUS					0x08
#define	IIC_STATUS_RECEIVE			0x00	/* receive status */ 
#define	IIC_STATUS_TRANSMIT			0x08	/* transmit	status */
/* Detection of	acknowledge	signal (ACKDn) */
#define	IIC_ACKDETECTION			0x04
#define	IIC_ACK_NOTDETECTED			0x00	/* ACK signal was not detected */
#define	IIC_ACK_DETECTED			0x04	/* ACK signal was detected */
/* Detection of	start condition	(STDn) */
#define	IIC_STARTDETECTION			0x02
#define	IIC_START_NOTDETECTED		0x00	/* start condition not detected	*/
#define	IIC_START_DETECTED			0x02	/* start condition detected	*/
/* Detection of	stop condition (SPDn) */
#define	IIC_STOPDETECTION			0x01
#define	IIC_STOP_NOTDETECTED		0x00	/* stop	condition not detected */
#define	IIC_STOP_DETECTED			0x01	/* stop	condition detected */

/*
	IIC	Flag Register (IICFn)
*/
/* STTn	clear flag (STCFn) */
#define	IIC_STARTFLAG				0x80
#define	IIC_STARTFLAG_GENERATE		0x00	/* generate	start condition	*/
#define	IIC_STARTFLAG_UNSUCCESSFUL	0x80	/* start condition generation unsuccessful */
/* IIC bus status flag (IICBSYn)	*/
#define	IIC_BUSSTATUS				0x40
#define	IIC_BUS_RELEASE				0x00	/* bus release status */
#define	IIC_BUS_COMMUNICATION		0x40	/* bus communication status	*/
/* Initial start enable	trigger	(STCENn)	*/
#define	IIC_STARTWITHSTOP			0x02
#define	IIC_START_WITHSTOP			0x00	/* generation of a start condition without detecting a stop	condition */
#define	IIC_START_WITHOUTSTOP		0x02	/* generation of a start condition upon	detection of a stop	condition */
/* Communication reservation function disable bit (IICRSVn) */
#define	IIC_RESERVATION				0x01
#define	IIC_RESERVATION_ENABLE		0x00	/* enable communication	reservation	*/	
#define	IIC_RESERVATION_DISABLE		0x01	/* disable communication reservation */		

/*
	IIC	clock selection	register (IICCLn)
*/

/* Detection of	SCL0n pin level (CLDn) */
#define	IIC_SCLLEVEL				0x20
#define	IIC_SCL_LOW					0x00	/* clock line at low level */
#define	IIC_SCL_HIGH				0x20	/* clock line at high level */
/* Detection of	SDA0 pin level (DADn) */
#define	IIC_SDALEVEL				0x10
#define	IIC_SDA_LOW					0x00	/* data line at	low level */
#define	IIC_SDA_HIGH				0x10	/* data line at high level */
/* Operation mode switching	(SMCn) */
#define	IIC_OPERATIONMODE			0x08
#define	IIC_MODE_STANDARD			0x00	/* operates in standard mode */
#define	IIC_MODE_HIGHSPEED			0x08	/* operates in high-speed mode */
/* Digital filter operation	control	(DFCn) */
#define	IIC_DIGITALFILTER			0x04
#define	IIC_FILTER_OFF				0x00	/* digital filter off */ 
#define	IIC_FILTER_ON				0x04	/* digital filter on */
/* Operation mode switching	(CLn1, CLn0) */
#define	IIC_CLOCKSELECTION			0x03
#define	IIC_CLOCK0					0x00
#define	IIC_CLOCK1					0x01
#define	IIC_CLOCK2					0x02
#define	IIC_CLOCK3					0x03

/*
	IIC	division clock select register	(OCKSn)
*/
#define	IIC_SELECTED_STOP		0x00
#define	IIC_SELECTED0			0x10
#define	IIC_SELECTED1			0x11
#define	IIC_SELECTED2			0x12
#define	IIC_SELECTED3			0x13
#define	IIC_SELECTED4			0x18

/*
	IIC	function expansion register	0 (IICXn)
*/
/* IIC clock expension (CLXn) */
#define	IIC_CLOCKEXPENSION		0x01
#define	IIC_EXPENSION0			0x00
#define	IIC_EXPENSION1			0x01

#define ADDRESS_COMPLETE		0x80
#define IIC_MASTER_FLAG_CLEAR	0x00

/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/
/* Selection of 8-bit counter output clock (UD0BRS7~UD0BRS0) */
#define	UARTD0_BASECLK_DIVISION		0xd	/* 4 ~ 255 */
/* Selection of 8-bit counter output clock (UD2BRS7~UD2BRS0) */
#define	UARTD2_BASECLK_DIVISION		0xd	/* 4 ~ 255 */
/* Selection of 8-bit counter output clock (UD4BRS7~UD4BRS0) */
#define	UARTD4_BASECLK_DIVISION		0xd	/* 4 ~ 255 */
enum TransferMode { SEND, RECEIVE };

/*
*******************************************************************************
**  Function define
*******************************************************************************
*/
void UARTD0_Init(void);
void UARTD0_Start(void);
void UARTD0_Stop(void);
MD_STATUS UARTD0_SendData(UCHAR* txbuf, USHORT txnum);
MD_STATUS UARTD0_ReceiveData(UCHAR* rxbuf, USHORT rxnum);
void UARTD0_ReceiveEndCallback(void);
void UARTD0_SendEndCallback(void);
void UARTD0_ErrorCallback(UCHAR err_type);
__interrupt void MD_INTUD0R(void);
__interrupt void MD_INTUD0T(void);
__interrupt void MD_INTUD0S(void);
void UARTD2_Init(void);
void UARTD2_Start(void);
void UARTD2_Stop(void);
MD_STATUS UARTD2_SendData(UCHAR* txbuf, USHORT txnum);
MD_STATUS UARTD2_ReceiveData(UCHAR* rxbuf, USHORT rxnum);
void UARTD2_ReceiveEndCallback(void);
void UARTD2_SendEndCallback(void);
void UARTD2_ErrorCallback(UCHAR err_type);
__interrupt void MD_INTUD2R(void);
__interrupt void MD_INTUD2T(void);
__interrupt void MD_INTUD2S(void);
void UARTD4_Init(void);
void UARTD4_Start(void);
void UARTD4_Stop(void);
MD_STATUS UARTD4_SendData(UCHAR* txbuf, USHORT txnum);
MD_STATUS UARTD4_ReceiveData(UCHAR* rxbuf, USHORT rxnum);
void UARTD4_ReceiveEndCallback(void);
void UARTD4_SendEndCallback(void);
void UARTD4_ErrorCallback(UCHAR err_type);
__multi_interrupt void MD_INTUD4R(void);
__interrupt void MD_INTUD4T(void);
__interrupt void MD_INTUD4S(void);
/* Start user code for definition. Do not edit comment generated here */
/* End user code for definition. Do not edit comment generated here */
#endif
