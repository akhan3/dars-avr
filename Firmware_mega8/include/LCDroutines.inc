clearScreen:
	LDI	temp, 0b00000001
	RCALL	writeInst
	RET

shiftScreen:
	LDI	temp, 0b00011000
	RCALL	writeInst
	DEC	cursor
	RET

cursorON:
	LDI	temp, 0b00001110
	RCALL	writeInst
	RET

cursorOFF:
	LDI	temp, 0b00001100
	RCALL	writeInst
	RET

moveCursor:
	CPI	temp, 20
	BRMI	do
	SUBI	temp, -44
	do:
	MOV	cursor, temp
	ORI	temp, 128
	RCALL	writeInst
	RET

moveCursorAbs:
	MOV	cursor, temp
	ORI	temp, 128
	RCALL	writeInst
	RET

writeInst:
	CBI	control, RS		//RS=0 for inst
	PUSH	temp
	ORI	temp, 0b00001111  //OR mask for high nibble
	SWAP	temp
	OUT	data, temp		//place higher nibble of inst
	SBI	control, EN		//EN=1
	CBI	control, EN		//EN=0
	POP	temp
	SWAP	temp			//swap nibbles
	ORI	temp, 0b00001111  //OR mask for lower nibble
	SWAP	temp
	OUT	data, temp		//place lower nibble of inst
	SBI	control, EN		//EN=1
	CBI	control, EN		//EN=0
	LDI	temp, 2
	RCALL	delay1msLong	//wait for execution
	RET

writeChar:
	SBI	control, RS		//RS=1 for data
	PUSH	temp
	ORI	temp, 0b00001111  //OR mask for high nibble
	SWAP	temp
	OUT	data, temp		//place higher nibble of data
	SBI	control, EN		//EN=1
	CBI	control, EN		//EN=0
	POP	temp
	SWAP	temp			//swap nibbles
	ORI	temp, 0b00001111  //OR mask for lower nibble
	SWAP	temp
	OUT	data, temp		//place lower nibble of data
	SBI	control, EN		//EN=1
	CBI	control, EN		//EN=0
	INC	cursor
	LDI	temp, LCDcharDelay
	RCALL	delay1msLong	//wait for execution
	RET

lcdReset:
;==============================================================================
	RCALL	delay10ms
	LDI	temp, 0b00110000	//Function Set to byte mode, 1-line and 5x8 font
	RCALL	writeInst
	LDI	temp, 0b00000110	//Entry mode Set
	RCALL	writeInst
	LDI	temp, 0b00001000	//Display OFF, cursor OFF and blinking OFF
	RCALL	writeInst
	LDI	temp, 100
	RCALL	delay1msLong	//wait for 100ms after reset routine
	RET
;==============================================================================

lcdBasic:
;==============================================================================
	LDI	temp, 0b00101000	//Function Set to byte mode, 2-line and 5x8 font
	RCALL	writeInst
	LDI	temp, 0b00000110	//Entry mode Set
	RCALL	writeInst
	LDI	temp, 0b00001100	//Display ON, cursor OFF and blinking OFF
	RCALL	writeInst
	LDI	temp, 0b00000001	//Clear Display
	RCALL	writeInst
	RET
;==============================================================================

writeString:
;==============================================================================
	LPM	temp, Z+
	RCALL	writeChar
	DEC	arrayCounter
	BREQ	terminate
	RJMP	writeString
;==============================================================================

writeStringRAM:
;==============================================================================
	LD	temp, Z+
	RCALL	writeChar
	DEC	arrayCounter
	BREQ	terminate
	RJMP	writeStringRAM
;==============================================================================

writeNullString:
;==============================================================================
	LPM	temp, Z+
	CPI	temp, 0
	BREQ	terminate
	RCALL	writeChar
	RJMP	writeNullString
;==============================================================================

writeScreen:
;==============================================================================
	RCALL	clearScreen
	LDI	cursor,0	//initialize cursor from 0
 load:
	BRTS	fromRAM
  fromFlash:
	LPM	temp, Z+
	RJMP	nextInst1Word
  fromRAM:
	LD	temp, Z+

	MOV	temp1, temp		//save the read char into temp1
	CPI	temp, 0		//check null terminated string
	BREQ	terminate
  line1:
	CPI	cursor, 20	//if line1 ended
	BRNE	line2
	LDI	cursor, 64
	LDI	temp, 128 | 64	//goto line2
	RCALL	writeInst
	RJMP	write
  line2:
	CPI	cursor, 84	//if line2 ended
	BRNE	write
	LDI	cursor, 0
	LDI	temp, 128 | 0	//goto line1
	RCALL	writeInst
 write:
	MOV	temp, temp1		//recover the read char into temp
	RCALL	writeChar		//write single char
	RJMP	load
 terminate:
	RET
;==============================================================================



pulseTest:
	SBI	PORTD, BLout
	LDI	temp, 50
	RCALL	delay1msLong
	CBI	PORTD, BLout
	LDI	temp, 50
	RCALL	delay1msLong
	RET
