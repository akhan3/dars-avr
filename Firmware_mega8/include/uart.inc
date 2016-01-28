//=========================================
passwordROM:
.DB	"ned0304",0
//=========================================


checkPassword:
;========================================================================
	CBI	UCSRB, RXCIE		//disable the RXC interrupt
	SEI					//enable the nested interrupt for backlight

	LDI	ZH, HIGH(passwordROM<<1)//Z is source for password in flash
	LDI	ZL, LOW (passwordROM<<1)
matchNextChar:
	LDI	temp, 256-18	//load the timer counter register
	OUT	TCNT0, temp
	LDI	temp, 0b101		//start the timer with 1024 prescalar
	OUT	TCCR0, temp
RXD1:
	IN	temp, TCNT0
	TST	temp			//if timer overflows....
	BREQ	timeOut		//then time out else....
	SBIS	UCSRA, RXC		//wait for receive flag to go high
	RJMP	RXD1
		IN	temp, UDR	//read the incoming character in temp
		RJMP	stopTimer
timeOut:	LDI	temp, 1	//return temp with 0x01 (arbitrary)
stopTimer:	OUT	TCCR0, zeros//stop the timer

	LPM	temp1, Z+		//read the password char by char stored in flash
	CP	temp, temp1		//match it with password stored in flash
	BRNE	passwordIsWrong
	TST	temp1			//if null char not received ....
	BREQ	passwordIsCorrect
	RJMP	matchNextChar	//....then match next char
;========================================================================

passwordIsCorrect:
;========================================================================
	LDI	temp, 'A'		//transmit the acknowledge signal
	RCALL	TXD

		//display message
		LDI	ZH, HIGH(CommInProgress<<1)
		LDI	ZL, LOW (CommInProgress<<1)
		CLT
		RCALL	writeScreen	

	RJMP	waitForCommand
;========================================================================

passwordIsWrong:
;========================================================================
	LDI	temp, 'R'		//transmit the reject signal
	RCALL	TXD

		//display message
		LDI	ZH, HIGH(CommInProgress<<1)
		LDI	ZL, LOW (CommInProgress<<1)
		CLT
		RCALL	writeScreen	

	RCALL	delay1s
	RJMP	reset
;========================================================================

waitForCommand:
;========================================================================
	RCALL	RXD	//reads the incoming character in temp
	CPI	temp,'S'	BREQ	sendData
	CPI	temp,'E'	BREQ	eraseEEPROM
	RJMP	invalidCommand
;========================================================================

sendData:
;========================================================================
	RCALL	delay1s
	LDI	temp, 'A'			//transmit the acknowledge signal
	RCALL	TXD

	LDI	ZH, HIGH(EEPROMEND)	//Z is source in EEPROM
	LDI	ZL, LOW (EEPROMEND)
	RCALL	readEEPROM
	RCALL	TXD				//send number of classes

;==== transfer all classes from EEPROM to UART
	LDI	temp1, 11
	MUL	temp1, temp
	LDI	ZH, HIGH(0)			//Z is source in EEPROM
	LDI	ZL, LOW (0)
transferNextByte:
	RCALL	readEEPROM
	RCALL	TXD				//send class data
	ADIW	ZH:ZL, 1
	CP	ZH, R1
	BRNE	transferNextByte
	CP	ZL, R0
	BRNE	transferNextByte

	RCALL	delay1s
	RJMP	reset
;========================================================================

eraseEEPROM:
;========================================================================
	RCALL	delay1s
	LDI	temp, 'A'			//transmit the acknowledge signal
	RCALL	TXD

	LDI	ZH, HIGH(EEPROMEND)	//Z is source in EEPROM
	LDI	ZL, LOW (EEPROMEND)
	RCALL	readEEPROM
	RCALL	TXD				//send number of classes

	LDI	YH, HIGH(EEPROMEND)	//Z is source in EEPROM
	LDI	YL, LOW (EEPROMEND)
	LDI	temp, 0			//resets the number of stored classes to 0
	RCALL	writeEEPROM

	RCALL	delay1s
	RJMP	reset
;========================================================================

invalidCommand:
;========================================================================
	LDI	temp, 'R'			//transmit the reject signal
	RCALL	TXD

	RCALL	delay1s
	RJMP	reset
;========================================================================



TXD:	//transmit the byte in temp register
	SBIS	UCSRA,UDRE	//Wait for empty transmitter buffer
	RJMP	TXD
	OUT	UDR, temp	//Put the byte into transmitter buffer and send it
	RET


RXD:	//receive the byte in temp register
	SBIS	UCSRA, RXC	//Wait for receive flag to go high
	RJMP	RXD
	IN	temp, UDR	//read the incoming byte
	RET
