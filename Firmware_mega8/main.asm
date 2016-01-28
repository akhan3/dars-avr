.include "m8def.inc"
.include "include\defs.inc"			//definitions for registers and ports

.CSEG
.ORG	0x000		RJMP	reset
.ORG 	INT0addr	RJMP	backlightInt	//backlight interrupt
.ORG 	URXCaddr	RJMP	checkPassword	//USART receive interrupt
.ORG	0x0013	reset:

//main program starts below
;========================================================================
;========================================================================
;========================================================================

.include "include\settings.inc"	//basic initial settings like stack and ports
.include "include\memory.inc"

/*	LDI	temp, 19
	LDI	YH, HIGH(EEPROMEND)	//Y is destination in EEPROM	
	LDI	YL, LOW (EEPROMEND)
	RCALL	writeEEPROM
*/

	RCALL	pulseTest
	CBI	PORTD, BLout	//Backlight initially OFF
	RCALL	lcdReset		//reset the LCD
	RCALL	lcdBasic		//initialize LCD to basic settings
//RJMP	directSwitchToClassSetup

welcomeMessages:
	LDI	ZH, HIGH(welcome1<<1)	
	LDI	ZL, LOW (welcome1<<1)
	CLT	//clear T flag for Code memory
	RCALL	writeScreen	
	RCALL	delay1s

	LDI	ZH, HIGH(welcome3<<1)	
	LDI	ZL, LOW (welcome3<<1)
	CLT
	RCALL	writeScreen	
	RCALL	delay1s

showMainMenu:
;==================================
	LDI	ZH, HIGH(mainMenu<<1)	
	LDI	ZL, LOW (mainMenu<<1)
	CLT
	RCALL	writeScreen


	RCALL	setState_MAIN_MENU
	RJMP	scanKeypad
;==================================


directSwitchToClassSetup:
	LDI	ZH, HIGH(classSetup<<1)	
	LDI	ZL, LOW (classSetup<<1)
	CLT
	RCALL	writeScreen
	RCALL	cursorON
	CLR	currentValue
	RCALL	setState_SUBJECT_SELECT
	RJMP	scanKeypad



.include "include\up.inc"
.include "include\down.inc"
.include "include\enter.inc"
.include "include\change.inc"

.include "include\keypadScan.inc"
.include "include\LCDroutines.inc"
.include "include\delays.inc"
.include "include\backlightInt.inc"
.include "include\states.inc"
.include "include\uart.inc"
.include "include\messages.inc"
.include "include\algo.inc"
