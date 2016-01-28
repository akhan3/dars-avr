enterRoutine:
	LDI	temp, 'E'
	RCALL	TXD
	CPI	currentState, MAIN_MENU 	BREQ	enter_MAIN_MENU
	CPI	currentState, VIEW_MENU 	BREQ	enter_VIEW_MENU1
	CPI	currentState, SUBJECT_SELECT 	BREQ	enter_SUBJECT_SELECT
	CPI	currentState, DAY_SELECT 	BREQ	enter_DAY_SELECT
	CPI	currentState, MONTH_SELECT	BREQ	enter_MONTH_SELECT
	CPI	currentState, YEAR_SELECT	BREQ	enter_YEAR_SELECT
	CPI	currentState, CLASSES_SELECT	BREQ	enter_CLASSES_SELECT
	CPI	currentState, ATTENDANCE_PROCESS	BREQ	enter_ATTENDANCE_PROCESS1
	CPI	currentState, CONFIRM_ATTENDANCE	BREQ	enter_CONFIRM_ATTENDANCE1

	RJMP	releaseDebounce


enter_VIEW_MENU1:			RJMP	enter_VIEW_MENU
enter_ATTENDANCE_PROCESS1:	RJMP	enter_ATTENDANCE_PROCESS
enter_CONFIRM_ATTENDANCE1:	RJMP	enter_CONFIRM_ATTENDANCE

enter_MAIN_MENU:
;========================================
	TST	currentValue
	BRNE	switchToClassSetup
switchToViewSetup:
	LDI	ZH, HIGH(viewSetup<<1)
	LDI	ZL, LOW (viewSetup<<1)
	CLT
	RCALL	writeScreen
	RCALL	setState_VIEW_MENU
	RJMP	releaseDebounce
switchToClassSetup:
	LDI	ZH, HIGH(classSetup<<1)	
	LDI	ZL, LOW (classSetup<<1)
	CLT
	RCALL	writeScreen
	RCALL	cursorON
	CLR	currentValue
	RCALL	setState_SUBJECT_SELECT
	RJMP	releaseDebounce
;========================================

enter_SUBJECT_SELECT:
	STS	subjectRAM, currentValue
	RCALL	switchToAttendance
	RJMP	releaseDebounce

enter_DAY_SELECT:
	STS	dayRAM, currentValue
	RCALL	switchToAttendance
	RJMP	releaseDebounce

enter_MONTH_SELECT:
	STS	monthRAM, currentValue
	RCALL	switchToAttendance
	RJMP	releaseDebounce

enter_YEAR_SELECT:
	STS	yearRAM, currentValue
	RCALL	switchToAttendance
	RJMP	releaseDebounce

enter_CLASSES_SELECT:
	STS	classesRAM, currentValue
	RCALL	switchToAttendance
	RJMP	releaseDebounce


enter_ATTENDANCE_PROCESS:
;==========================================================================
	LDI	ZH, HIGH(confirm<<1)	
	LDI	ZL, LOW (confirm<<1)
	CLT
	RCALL	writeScreen		// display the confirm message
	LDI	temp, 38
	RCALL	moveCursor		// place cursor at NO location

	PUSH	currentValue	// save the current Rno index on stack
	PUSH	bitCounter		// save the bit and byte counters on stack
	PUSH	byteCounter

	RCALL	setState_CONFIRM_ATTENDANCE
	RJMP	releaseDebounce
;==========================================================================


enter_CONFIRM_ATTENDANCE:
;==========================================================================
	TST	currentValue	// if the choice was YES
	BRNE	save_ATTENDANCE	// then save the attendance

returnToAttendance:		// else return to previous screen
	RCALL	switchToAttendance
	POP	byteCounter		// recover the current Rno index from stack
	POP	bitCounter		// recover the bit and byte counters from stack
	POP	currentValue

// display the current roll no
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	MOV	temp1, currentValue	//load roll no index in temp1
	LDI	temp, HIGH(rollList)	MOV	R3, temp	//base address in [R3:R2]
	LDI	temp, LOW (rollList)	MOV	R2, temp	//**change
	LDI	temp, 2			//width in words	//**change
	MUL	temp, temp1			//[R1:R0] will now have offset
	ADD	R0, R2	ADC	R1, R3
	LSL	R0		ROL	R1
	MOV	ZH, R1	MOV	ZL, R0
	LDI	temp, 34			//**change
	RCALL	moveCursor
	LDI	arrayCounter, 3		//**change
	RCALL	writeString
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	LDI	ZH, HIGH(attendanceRAM)	LDI	ZL, LOW (attendanceRAM)//Z is source in SRAM
	ADD	ZL, byteCounter		ADC	ZH, zeros
	LD	temp1, Z
	RCALL	ANDmask
	AND	temp, temp1
	BREQ	foundAbsentDisplayA00

foundPresentDisplayP00:
	LDI	temp, 38	RCALL	moveCursor
	LDI	temp, 'P'	RCALL	writeChar
	LDI	temp, 38	RCALL	moveCursor
	RJMP	exit3300

foundAbsentDisplayA00:
	LDI	temp, 38	RCALL	moveCursor
	LDI	temp, 'A'	RCALL	writeChar
	LDI	temp, 38	RCALL	moveCursor
	RJMP	exit3300

exit3300:
	RJMP	releaseDebounce
	
;==========================================================================


save_ATTENDANCE:
;==========================================================================
	RCALL	cursorOFF
	LDI	ZH, HIGH(saving<<1)	
	LDI	ZL, LOW (saving<<1)
	CLT
	RCALL	writeScreen
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
	LDI	temp, 50	RCALL	delay10msLong

 ;================== preapre 2 header bytes in SRAM
     LDS	temp, subjectRAM
	LDI	bitCounter, 4
	RCALL	shiftLeft
	MOV	temp1, temp
     LDS	temp, monthRAM
	OR	temp1, temp
    STS	headerRAM+0, temp1

     LDS	temp, dayRAM
	LDI	bitCounter, 3
	RCALL	shiftLeft
	MOV	temp1, temp
     LDS	temp, yearRAM
	LDI	bitCounter, 2
	RCALL	shiftLeft
	OR	temp1, temp
     LDS	temp, classesRAM
	OR	temp1, temp
    STS	headerRAM+1, temp1

;================== write recently taken attendance to EEPROM
	LDI	ZH, HIGH(EEPROMEND)	//Z is source in EEPROM
	LDI	ZL, LOW (EEPROMEND)
	RCALL	readEEPROM
	PUSH	temp		//************************ important push
	LDI	temp1, 11
	MUL	temp1, temp
	MOV	YH, R1			//Y is destination in EEPROM
	MOV	YL, R0
	LDI	ZH, HIGH(headerRAM)	//Z is source in SRAM
	LDI	ZL, LOW (headerRAM)
	LDI	arrayCounter, 11
	RCALL	SRAMtoEEPROM

	POP	temp
	PUSH	temp
	INC	temp
	LDI	YH, HIGH(EEPROMEND)	//Y is destination in EEPROM	
	LDI	YL, LOW (EEPROMEND)
	RCALL	writeEEPROM

;================== copy 11 bytes from EEPROM to SRAM
	POP	temp
	PUSH	temp
	LDI	temp1, 11
	MUL	temp1, temp
	MOV	ZH, R1			//Z is source in EEPROM
	MOV	ZL, R0
	LDI	YH, HIGH(readAttendaceRAM)//Y is destination in SRAM	
	LDI	YL, LOW (readAttendaceRAM)
	LDI	arrayCounter, 11
	RCALL	EEPROMtoSRAM
	
;================== generate hex of 11 bytes from SRAM to SRAM
	LDI	ZH, HIGH(readAttendaceRAM)//Z is source in SRAM	
	LDI	ZL, LOW (readAttendaceRAM)
	LDI	YH, HIGH(hexRAM)		//Y is destination in SRAM	
	LDI	YL, LOW (hexRAM)
	LDI	arrayCounter, 11
nextByte:
	TST	arrayCounter
	BREQ	exit333
	LD	currentValue, Z+
	RCALL	bin1ToHex2
	ADIW	YH:YL, 2
	DEC	arrayCounter
	RJMP	nextByte
exit333:

;================== display hex of 11 bytes from SRAM
	RCALL	clearScreen
	LDI	ZH, HIGH(hexRAM)		//Z is source in SRAM
	LDI	ZL, LOW (hexRAM)
	LDI	arrayCounter, 4		
	RCALL	writeStringRAM

	POP	currentValue
	INC	currentValue
	LDI	YH, HIGH(asciiRAM)	//Y is destination in SRAM
	LDI	YL, LOW (asciiRAM)
	RCALL	bin1ToAsc3
	ADIW	YH:YL, 1
	LDI	temp, 18		
	RCALL	moveCursor
	MOV	ZH, YH			//Z is source in SRAM	
	MOV	ZL, YL
	LDI	arrayCounter, 2
	RCALL	writeStringRAM

	LDI	temp, 20			
	RCALL	moveCursor
	LDI	ZH, HIGH(hexRAM+4)	//Z is source in SRAM
	LDI	ZL, LOW (hexRAM+4)
	LDI	arrayCounter, 18
	RCALL	writeStringRAM

	SBIS	keypad, enter	//wait for 'enter' to re-initialize
		RJMP	reset
	RJMP	PC-2
;==========================================================================


enter_VIEW_MENU:
;==========================================================================
	RCALL	cursorOFF
	LDI	ZH, HIGH(loading<<1)
	LDI	ZL, LOW (loading<<1)
	CLT
	RCALL	writeScreen
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
	LDI	temp, 50	RCALL	delay10msLong

;================== copy 11 bytes from EEPROM to SRAM
	PUSH	currentValue		//************************ important push
	DEC	currentValue
	LDI	temp1, 11
	MUL	temp1, currentValue
	MOV	ZH, R1			//Z is source in EEPROM
	MOV	ZL, R0
	LDI	YH, HIGH(readAttendaceRAM)//Y is destination in SRAM	
	LDI	YL, LOW (readAttendaceRAM)
	LDI	arrayCounter, 11
	RCALL	EEPROMtoSRAM

;================== generate hex of 11 bytes from SRAM to SRAM
	LDI	ZH, HIGH(readAttendaceRAM)//Z is source in SRAM	
	LDI	ZL, LOW (readAttendaceRAM)
	LDI	YH, HIGH(hexRAM)		//Y is destination in SRAM	
	LDI	YL, LOW (hexRAM)
	LDI	arrayCounter, 11
nextByte1:
	TST	arrayCounter
	BREQ	exit3334
	LD	currentValue, Z+
	RCALL	bin1ToHex2
	ADIW	YH:YL, 2
	DEC	arrayCounter
	RJMP	nextByte1
exit3334:

;================== display hex of 11 bytes from SRAM
	RCALL	clearScreen
	LDI	ZH, HIGH(hexRAM)		//Z is source in SRAM
	LDI	ZL, LOW (hexRAM)
	LDI	arrayCounter, 4		
	RCALL	writeStringRAM

	POP	currentValue
	LDI	YH, HIGH(asciiRAM)	//Y is destination in SRAM
	LDI	YL, LOW (asciiRAM)
	RCALL	bin1ToAsc3
	ADIW	YH:YL, 1
	LDI	temp, 18		
	RCALL	moveCursor
	MOV	ZH, YH			//Z is source in SRAM	
	MOV	ZL, YL
	LDI	arrayCounter, 2
	RCALL	writeStringRAM

	LDI	temp, 20			
	RCALL	moveCursor
	LDI	ZH, HIGH(hexRAM+4)	//Z is source in SRAM
	LDI	ZL, LOW (hexRAM+4)
	LDI	arrayCounter, 18
	RCALL	writeStringRAM

	SBIS	keypad, enter	//wait for 'enter' to re-initialize
		RJMP	reset
	RJMP	PC-2
;==========================================================================




// this is a subroutine not a jump. Mind it.
switchToAttendance:
;========================================
	RCALL	clearScreen
	
	LDS	temp1, subjectRAM	//**change
	LDI	temp, HIGH(subjectList)	MOV	R3, temp	//base address in [R3:R2]
	LDI	temp, LOW (subjectList)	MOV	R2, temp	//**change
	LDI	temp, 2			//width in words	//**change
	MUL	temp, temp1			//[R1:R0] will now have offset
	ADD	R0, R2	ADC	R1, R3
	LSL	R0		ROL	R1
	MOV	ZH, R1	MOV	ZL, R0
	LDI	temp, 0			//**change
	RCALL	moveCursor
	LDI	arrayCounter, 4		//**change
	RCALL	writeString

	LDS	temp1, dayRAM	//**change
	LDI	temp, HIGH(dayList)	MOV	R3, temp	//base address in [R3:R2]
	LDI	temp, LOW (dayList)	MOV	R2, temp	//**change
	LDI	temp, 1			//width in words	//**change
	MUL	temp, temp1			//[R1:R0] will now have offset
	ADD	R0, R2	ADC	R1, R3
	LSL	R0		ROL	R1
	MOV	ZH, R1	MOV	ZL, R0
	LDI	temp, 11			//**change
	RCALL	moveCursor
	LDI	arrayCounter, 2		//**change
	RCALL	writeString

	LDI	temp, '-'	RCALL	writeChar

	LDS	temp1, monthRAM	//**change
	LDI	temp, HIGH(monthList)	MOV	R3, temp	//base address in [R3:R2]
	LDI	temp, LOW (monthList)	MOV	R2, temp	//**change
	LDI	temp, 2			//width in words	//**change
	MUL	temp, temp1			//[R1:R0] will now have offset
	ADD	R0, R2	ADC	R1, R3
	LSL	R0		ROL	R1
	MOV	ZH, R1	MOV	ZL, R0
	LDI	temp, 14			//**change
	RCALL	moveCursor
	LDI	arrayCounter, 3		//**change
	RCALL	writeString

	LDI	temp, '-'	RCALL	writeChar

	LDS	temp1, yearRAM	//**change
	LDI	temp, HIGH(yearList)	MOV	R3, temp	//base address in [R3:R2]
	LDI	temp, LOW (yearList)	MOV	R2, temp	//**change
	LDI	temp, 1			//width in words	//**change
	MUL	temp, temp1			//[R1:R0] will now have offset
	ADD	R0, R2	ADC	R1, R3
	LSL	R0		ROL	R1
	MOV	ZH, R1	MOV	ZL, R0
	LDI	temp, 18			//**change
	RCALL	moveCursor
	LDI	arrayCounter, 2		//**change
	RCALL	writeString

	LDI	ZH, HIGH(attendanceTaking+10<<1)	
	LDI	ZL, LOW (attendanceTaking+10<<1)
	LDI	temp, 20
	RCALL	moveCursor
	LDI	arrayCounter, 9		//**change
	RCALL	writeString

	LDS	temp1, classesRAM	//**change
	LDI	temp, HIGH(classesList)	MOV	R3, temp	//base address in [R3:R2]
	LDI	temp, LOW (classesList)	MOV	R2, temp	//**change
	LDI	temp, 1			//width in words	//**change
	MUL	temp, temp1			//[R1:R0] will now have offset
	ADD	R0, R2	ADC	R1, R3
	LSL	R0		ROL	R1
	MOV	ZH, R1	MOV	ZL, R0
	LDI	temp, 29			//**change
	RCALL	moveCursor
	LDI	arrayCounter, 1		//**change
	RCALL	writeString

	LDI	ZH, HIGH(attendanceTaking+15<<1)	
	LDI	ZL, LOW (attendanceTaking+15<<1)
	LDI	temp, 30
	RCALL	moveCursor
	LDI	arrayCounter, 10		//**change
	RCALL	writeString

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	LDI	temp1, 0			//initial roll no
	LDI	temp, HIGH(rollList)	MOV	R3, temp	//base address in [R3:R2]
	LDI	temp, LOW (rollList)	MOV	R2, temp	//**change
	LDI	temp, 2			//width in words	//**change
	MUL	temp, temp1			//[R1:R0] will now have offset
	ADD	R0, R2	ADC	R1, R3
	LSL	R0		ROL	R1
	MOV	ZH, R1	MOV	ZL, R0
	LDI	temp, 34			//**change
	RCALL	moveCursor
	LDI	arrayCounter, 3		//**change
	RCALL	writeString
	LDI	temp, 38
	RCALL	moveCursor
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	RCALL	setState_ATTENDANCE_PROCESS
	RET
;========================================

