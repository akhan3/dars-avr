downRoutine:
	LDI	temp, 'D'
	RCALL	TXD
	CPI	currentState, MAIN_MENU 	BREQ	down_MAIN_MENU1
	CPI	currentState, VIEW_MENU 	BREQ	down_VIEW_MENU1
	CPI	currentState, SUBJECT_SELECT 	BREQ	down_SUBJECT_SELECT1
	CPI	currentState, DAY_SELECT 	BREQ	down_DAY_SELECT1
	CPI	currentState, MONTH_SELECT	BREQ	down_MONTH_SELECT1
	CPI	currentState, YEAR_SELECT	BREQ	down_YEAR_SELECT1
	CPI	currentState, CLASSES_SELECT	BREQ	down_CLASSES_SELECT1
	CPI	currentState, ATTENDANCE_PROCESS	BREQ	down_ATTENDANCE_PROCESS1
	RJMP	typematicContinue

down_MAIN_MENU1:			RJMP	down_MAIN_MENU
down_VIEW_MENU1:			RJMP	down_VIEW_MENU
down_SUBJECT_SELECT1:		RJMP	down_SUBJECT_SELECT
down_DAY_SELECT1:			RJMP	down_DAY_SELECT
down_MONTH_SELECT1:		RJMP	down_MONTH_SELECT
down_YEAR_SELECT1:		RJMP	down_YEAR_SELECT
down_CLASSES_SELECT1:		RJMP	down_CLASSES_SELECT
down_ATTENDANCE_PROCESS1:	RJMP	down_ATTENDANCE_PROCESS

down_MAIN_MENU:
;==========================================================================
	TST	currentValue
	BRNE	newToOld
OldToNew:
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
newToOld:
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

down_VIEW_MENU:
;==========================================================================
	INC	currentValue
	CPI	currentValue, 47
	BRNE	exit88
	LDI	currentValue, 1
exit88:
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

down_SUBJECT_SELECT:
;==========================================================================
	INC	currentValue
	CPI	currentValue, 9		//if overflow occured
	BRNE	nextInst1Word	
	LDI	currentValue, 0		//then prevent overflow
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

down_DAY_SELECT:
;==========================================================================
	INC	currentValue
	CPI	currentValue, 31		//if underflow occured
	BRNE	nextInst1Word	
	LDI	currentValue, 0		//then prevent underflow
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

down_MONTH_SELECT:
;==========================================================================
	INC	currentValue
	CPI	currentValue, 12		//if underflow occured
	BRNE	nextInst1Word	
	LDI	currentValue, 0		//then prevent underflow
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

down_YEAR_SELECT:
;==========================================================================
	INC	currentValue
	CPI	currentValue, 2		//if underflow occured
	BRNE	nextInst1Word	
	LDI	currentValue, 0		//then prevent underflow
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

down_CLASSES_SELECT:
;==========================================================================
	INC	currentValue
	CPI	currentValue, 4		//if underflow occured
	BRNE	nextInst1Word	
	LDI	currentValue, 0		//then prevent underflow
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

down_ATTENDANCE_PROCESS:
;==========================================================================

;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	INC	currentValue	//load next roll no
		CPI	currentValue, 70	//if Rno index exceeds 69
		BRNE	exit111
		LDI	currentValue, 0
		LDI	bitCounter, 7
		LDI	byteCounter, 0
		RJMP	exit1
exit111:
	DEC	bitCounter
		CPI	bitCounter, -1
		BRNE	exit1
		LDI	bitCounter, 7
		INC	byteCounter
;~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

exit1:
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
	BREQ	foundAbsentDisplayA

foundPresentDisplayP:
	LDI	temp, 38	RCALL	moveCursor
	LDI	temp, 'P'	RCALL	writeChar
	LDI	temp, 38	RCALL	moveCursor
	RJMP	exit33

foundAbsentDisplayA:
	LDI	temp, 38	RCALL	moveCursor
	LDI	temp, 'A'	RCALL	writeChar
	LDI	temp, 38	RCALL	moveCursor
	RJMP	exit33

exit33:
	RJMP	typematicContinue
;==========================================================================
