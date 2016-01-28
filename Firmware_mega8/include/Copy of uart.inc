RXCInt:
;========================================================================
	PUSH	temp1				//push on stack
	PUSH	temp
	IN	temp, SREG
	PUSH	temp

	IN	temp, UDR			//reads the incoming character
	CPI	temp, 'C'			//if 'C' received....
	BREQ	checkPassword		//then continue to check password

	POP	temp				//pop from stack
	OUT	SREG, temp
	POP	temp
	POP	temp1
	RETI
;========================================================================


checkPassword:	;	"ned123"
;========================================================================
	CBI	UCSRB, RXCIE		//disable the RXC interrupt

	SBIS	UCSRA, RXC
	RJMP	PC-1
	IN	temp, UDR	//reads the incoming character
	CPI	temp, 'n'
	BRNE	passwordIsWrong

	SBIS	UCSRA, RXC
	RJMP	PC-1
	IN	temp, UDR	//reads the incoming character
	CPI	temp, 'e'
	BRNE	passwordIsWrong

	SBIS	UCSRA, RXC
	RJMP	PC-1
	IN	temp, UDR	//reads the incoming character
	CPI	temp, 'd'
	BRNE	passwordIsWrong

	SBIS	UCSRA, RXC
	RJMP	PC-1
	IN	temp, UDR	//reads the incoming character
	CPI	temp, '1'
	BRNE	passwordIsWrong

	SBIS	UCSRA, RXC
	RJMP	PC-1
	IN	temp, UDR	//reads the incoming character
	CPI	temp, '2'
	BRNE	passwordIsWrong

	SBIS	UCSRA, RXC
	RJMP	PC-1
	IN	temp, UDR	//reads the incoming character
	CPI	temp, '3'
	BRNE	passwordIsWrong

passwordIsCorrect:
;========================================================================
	LDI	temp, 'A'	//acknowledge
	RCALL	TXD
	LDI	ZH, HIGH(pwCorrect<<1)
	LDI	ZL, LOW (pwCorrect<<1)
	CLT
	RCALL	writeScreen	
	RCALL	delay1s
	RJMP	waitForCommand

passwordIsWrong:
;========================================================================
	LDI	temp, 'R'	//reject
	RCALL	TXD
	LDI	ZH, HIGH(pwWrong<<1)	
	LDI	ZL, LOW (pwWrong<<1)
	CLT
	RCALL	writeScreen
	RCALL	delay1s
	RJMP	PC

waitForCommand:
;========================================================================
	SBIS	UCSRA, RXC
	RJMP	waitForCommand
	IN	temp, UDR
	CPI	temp,'S'	BREQ	sendData
	CPI	temp,'E'	BREQ	eraseEEPROM
;	LDI	temp, 'R'	//reject the unknown command
;	RCALL	TXD
	RJMP	waitForCommand

sendData:
;============================
	LDI	temp, 'A'	//acknowledge
	RCALL	TXD
		RCALL	pulseTest
		LDI	ZH, HIGH(sendCommandReceived<<1)	
		LDI	ZL, LOW (sendCommandReceived<<1)
		CLT
		RCALL	writeScreen
		LDI	temp, 28
		RCALL	moveCursor
		LDI	ZH, HIGH(EEPROMEND)	//Z is source in EEPROM
		LDI	ZL, LOW (EEPROMEND)
		RCALL	readEEPROM
		MOV	currentValue, temp
		LDI	YH, HIGH(asciiRAM)	//Y is destination in SRAM
		LDI	YL, LOW (asciiRAM)
		RCALL	bin1ToAsc3
		ADIW	YH:YL, 1
		MOV	ZH, YH			//Z is source in SRAM	
		MOV	ZL, YL
		LDI	arrayCounter, 2
		RCALL	writeStringRAM
	LDI	ZH, HIGH(EEPROMEND)	//Z is source in EEPROM
	LDI	ZL, LOW (EEPROMEND)
	RCALL	readEEPROM
	RCALL	TXD	//send number of classes

;==== transfer all classes from EEPROM to UART
	LDI	temp1, 11
	MUL	temp1, temp
	LDI	ZH, HIGH(0)			//Z is source in EEPROM
	LDI	ZL, LOW (0)
transferNextByte:
	RCALL	readEEPROM
	RCALL	TXD	//send class data
	ADIW	ZH:ZL, 1
	CP	ZH, R1
	BRNE	transferNextByte
	CP	ZL, R0
	BRNE	transferNextByte

		LDI	temp, 31
		RCALL	moveCursor
		LDI	temp, 20	RCALL	delay10msLong
		LDI	temp, '.'	RCALL	writeChar
		LDI	temp, 20	RCALL	delay10msLong
		LDI	temp, '.'	RCALL	writeChar
		LDI	temp, 20	RCALL	delay10msLong
		LDI	temp, '.'	RCALL	writeChar
		LDI	temp, 50	RCALL	delay10msLong
		LDI	ZH, HIGH(done<<1)	
		LDI	ZL, LOW (done<<1)
		LDI	arrayCounter, 4		
		RCALL	writeString
	RJMP	PC
;============================

eraseEEPROM:
;============================
	LDI	temp, 'A'	//acknowledge
	RCALL	TXD
		RCALL	pulseTest
		LDI	ZH, HIGH(eraseCommandReceived<<1)	
		LDI	ZL, LOW (eraseCommandReceived<<1)
		CLT
		RCALL	writeScreen
		LDI	temp, 28
		RCALL	moveCursor
		LDI	ZH, HIGH(EEPROMEND)	//Z is source in EEPROM
		LDI	ZL, LOW (EEPROMEND)
		RCALL	readEEPROM
		MOV	currentValue, temp
		LDI	YH, HIGH(asciiRAM)	//Y is destination in SRAM
		LDI	YL, LOW (asciiRAM)
		RCALL	bin1ToAsc3
		ADIW	YH:YL, 1
		MOV	ZH, YH			//Z is source in SRAM	
		MOV	ZL, YL
		LDI	arrayCounter, 2
		RCALL	writeStringRAM
	LDI	ZH, HIGH(EEPROMEND)	//Z is source in EEPROM
	LDI	ZL, LOW (EEPROMEND)
	RCALL	readEEPROM
	RCALL	TXD	//send number of classes

	LDI	YH, HIGH(EEPROMEND)	//Z is source in EEPROM
	LDI	YL, LOW (EEPROMEND)
	LDI	temp, 0			//resets the number of stored classes to 0
	RCALL	writeEEPROM
		LDI	temp, 31
		RCALL	moveCursor
		LDI	temp, 20	RCALL	delay10msLong
		LDI	temp, '.'	RCALL	writeChar
		LDI	temp, 20	RCALL	delay10msLong
		LDI	temp, '.'	RCALL	writeChar
		LDI	temp, 20	RCALL	delay10msLong
		LDI	temp, '.'	RCALL	writeChar
		LDI	temp, 50	RCALL	delay10msLong
		LDI	ZH, HIGH(done<<1)	
		LDI	ZL, LOW (done<<1)
		LDI	arrayCounter, 4		
		RCALL	writeString
	RJMP	PC
;============================


;========================================================================



TXD:
	SBIS	UCSRA,UDRE		//Wait for empty transmit buffer
	RJMP	TXD
	OUT	UDR, temp		//Put data into buffer, sends the data
	RET


RXD:
	SBIS	UCSRA,UDRE		//Wait for empty transmit buffer
	RJMP	TXD
	OUT	UDR, temp		//Put data into buffer, sends the data
	RET
