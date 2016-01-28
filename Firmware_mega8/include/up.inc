upRoutine:
	LDI	temp, 'U'
	RCALL	TXD
	CPI	currentState, MAIN_MENU 	BREQ	up_MAIN_MENU1
	CPI	currentState, VIEW_MENU 	BREQ	up_VIEW_MENU1
	CPI	currentState, SUBJECT_SELECT 	BREQ	up_SUBJECT_SELECT1
	CPI	currentState, DAY_SELECT 	BREQ	up_DAY_SELECT1
	CPI	currentState, MONTH_SELECT	BREQ	up_MONTH_SELECT1
	CPI	currentState, YEAR_SELECT	BREQ	up_YEAR_SELECT1
	CPI	currentState, CLASSES_SELECT	BREQ	up_CLASSES_SELECT1
	CPI	currentState, ATTENDANCE_PROCESS	BREQ	up_ATTENDANCE_PROCESS1
	RJMP	typematicContinue

up_MAIN_MENU1:		RJMP	up_MAIN_MENU
up_VIEW_MENU1:		RJMP	up_VIEW_MENU
up_SUBJECT_SELECT1:	RJMP	up_SUBJECT_SELECT
up_DAY_SELECT1:		RJMP	up_DAY_SELECT
up_MONTH_SELECT1:		RJMP	up_MONTH_SELECT
up_YEAR_SELECT1:		RJMP	up_YEAR_SELECT
up_CLASSES_SELECT1:	RJMP	up_CLASSES_SELECT
up_ATTENDANCE_PROCESS1:	RJMP	up_ATTENDANCE_PROCESS

up_MAIN_MENU:
;==========================================================================
	TST	currentValue
	BRNE	newToOld1
OldToNew1:
	LDI	currentValue, 1
	LDI	temp, 0
	RCALL	moveCursor
	LDI	temp, 0x20
	RCALL	writeChar
	LDI	temp, 20
	RCALL	moveCursor
	LDI	temp, 0x7E
	RCALL	writeChar
	RJMP	typematicContinue
newToOld1:
	LDI	currentValue, 0
	LDI	temp, 0
	RCALL	moveCursor
	LDI	temp, 0x7E
	RCALL	writeChar
	LDI	temp, 20
	RCALL	moveCursor
	LDI	temp, 0x20
	RCALL	writeChar
	RJMP	typematicContinue
;==========================================================================

up_VIEW_MENU:
;==========================================================================
	DEC	currentValue
	CPI	currentValue, 0
	BRNE	exit998
	LDI	currentValue, 46
exit998:
	LDI	YH, HIGH(asciiRAM)//Y is destination in SRAM
	LDI	YL, LOW (asciiRAM)
	RCALL	bin1ToAsc3			
	ADIW	YH:YL, 1
	MOV	ZH, YH		//Z is source in SRAM			
	MOV	ZL, YL
	LDI	arrayCounter, 2		
	RCALL	writeStringRAM
	LDI	temp, 36
	RCALL	moveCursor
	RJMP	typematicContinue
;==========================================================================

up_SUBJECT_SELECT:
;==========================================================================
	DEC	currentValue
	CPI	currentValue, -1		//if underflow occured
	BRNE	nextInst1Word	
	LDI	currentValue, 8		//then prevent underflow
	LDI	temp, 2			//width in words
	MUL	temp, currentValue	//[R1:R0] will now have offset
	ADD	R0, R2	ADC	R1, R3
	LSL	R0		ROL	R1
	MOV	ZH, R1	MOV	ZL, R0
	LDI	arrayCounter, 4
	RCALL	writeString
	LDI	temp, 1
	RCALL	moveCursor
	RJMP	typematicContinue
;==========================================================================

up_DAY_SELECT:
;==========================================================================
	DEC	currentValue
	CPI	currentValue, -1		//if underflow occured
	BRNE	nextInst1Word	
	LDI	currentValue, 30		//then prevent underflow
	LDI	temp, 1			//width in words
	MUL	temp, currentValue	//[R1:R0] will now have offset
	ADD	R0, R2	ADC	R1, R3
	LSL	R0		ROL	R1
	MOV	ZH, R1	MOV	ZL, R0
	LDI	arrayCounter, 2
	RCALL	writeString
	LDI	temp, 10
	RCALL	moveCursor
	RJMP	typematicContinue
;==========================================================================

up_MONTH_SELECT:
;==========================================================================
	DEC	currentValue
	CPI	currentValue, -1		//if underflow occured
	BRNE	nextInst1Word	
	LDI	currentValue, 11		//then prevent underflow
	LDI	temp, 2			//width in words
	MUL	temp, currentValue	//[R1:R0] will now have offset
	ADD	R0, R2	ADC	R1, R3
	LSL	R0		ROL	R1
	MOV	ZH, R1	MOV	ZL, R0
	LDI	arrayCounter, 3
	RCALL	writeString
	LDI	temp, 13
	RCALL	moveCursor
	RJMP	typematicContinue
;==========================================================================

up_YEAR_SELECT:
;==========================================================================
	DEC	currentValue
	CPI	currentValue, -1		//if underflow occured
	BRNE	nextInst1Word	
	LDI	currentValue, 1		//then prevent underflow
	LDI	temp, 1			//width in words
	MUL	temp, currentValue	//[R1:R0] will now have offset
	ADD	R0, R2	ADC	R1, R3
	LSL	R0		ROL	R1
	MOV	ZH, R1	MOV	ZL, R0
	LDI	arrayCounter, 2
	RCALL	writeString
	LDI	temp, 17
	RCALL	moveCursor
	RJMP	typematicContinue
;==========================================================================

up_CLASSES_SELECT:
;==========================================================================
	DEC	currentValue
	CPI	currentValue, -1		//if underflow occured
	BRNE	nextInst1Word	
	LDI	currentValue, 3		//then prevent underflow
	LDI	temp, 1			//width in words
	MUL	temp, currentValue	//[R1:R0] will now have offset
	ADD	R0, R2	ADC	R1, R3
	LSL	R0		ROL	R1
	MOV	ZH, R1	MOV	ZL, R0
	LDI	arrayCounter, 1
	RCALL	writeString
	LDI	temp, 38
	RCALL	moveCursor
	RJMP	typematicContinue
;==========================================================================

up_ATTENDANCE_PROCESS:
;==========================================================================

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	DEC	currentValue	//load previous roll no
		CPI	currentValue, -1	//if Rno index is less than 0
		BRNE	exit222
		LDI	currentValue, 69
		LDI	bitCounter, 2
		LDI	byteCounter, 8
		RJMP	exit2
exit222:
	INC	bitCounter
		CPI	bitCounter, 8
		BRNE	exit2
		LDI	bitCounter, 0
		DEC	byteCounter
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

exit2:
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
	BREQ	foundAbsentDisplayA1

foundPresentDisplayP1:
	LDI	temp, 38	RCALL	moveCursor
	LDI	temp, 'P'	RCALL	writeChar
	LDI	temp, 38	RCALL	moveCursor
	RJMP	exit330

foundAbsentDisplayA1:
	LDI	temp, 38	RCALL	moveCursor
	LDI	temp, 'A'	RCALL	writeChar
	LDI	temp, 38	RCALL	moveCursor
	RJMP	exit330

exit330:
	RJMP	typematicContinue
;==========================================================================
