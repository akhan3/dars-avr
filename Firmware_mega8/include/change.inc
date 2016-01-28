changeRoutine:
	LDI	temp, 'C'
	RCALL	TXD
	CPI	currentState, VIEW_MENU 	BREQ	change_VIEW_MENU
	CPI	currentState, SUBJECT_SELECT 	BREQ	change_SUBJECT_SELECT
	CPI	currentState, DAY_SELECT 	BREQ	change_DAY_SELECT
	CPI	currentState, MONTH_SELECT	BREQ	change_MONTH_SELECT
	CPI	currentState, YEAR_SELECT	BREQ	change_YEAR_SELECT
	CPI	currentState, CLASSES_SELECT	BREQ	change_CLASSES_SELECT
	CPI	currentState, ATTENDANCE_PROCESS	BREQ	change_ATTENDANCE_PROCESS
	CPI	currentState, CONFIRM_ATTENDANCE	BREQ	change_CONFIRM_ATTENDANCE
	RJMP	typematicContinue

change_VIEW_MENU:
;==================================
	RCALL	showMainMenu
	RJMP	typematicContinue
;==================================

change_SUBJECT_SELECT:
;==================================
	RCALL	setState_DAY_SELECT
	RJMP	typematicContinue
;==================================

change_DAY_SELECT:
;==================================
	RCALL	setState_MONTH_SELECT
	RJMP	typematicContinue
;==================================

change_MONTH_SELECT:
;==================================
	RCALL	setState_YEAR_SELECT
	RJMP	typematicContinue
;==================================

change_YEAR_SELECT:
;==================================
	RCALL	setState_CLASSES_SELECT
	RJMP	typematicContinue
;==================================

change_CLASSES_SELECT:
;==================================
	RCALL	setState_SUBJECT_SELECT
	RJMP	typematicContinue

;==================================



change_ATTENDANCE_PROCESS:
;==========================================================================
	LDI	ZH, HIGH(attendanceRAM)	LDI	ZL, LOW (attendanceRAM)
	ADD	ZL, byteCounter		ADC	ZH, zeros
	LD	temp1, Z
	RCALL	ANDmask
	AND	temp, temp1
	BREQ	foundAbsentToggleToPresent

foundPresentToggleToAbsent:
	COM	temp
	AND	temp1, temp
	ST	Z, temp1
	LDI	temp, 38	RCALL	moveCursor
	LDI	temp, 'A'	RCALL	writeChar
	LDI	temp, 38	RCALL	moveCursor
	RJMP	exit9

foundAbsentToggleToPresent:
	RCALL	ANDmask
	OR	temp1, temp
	ST	Z, temp1
	LDI	temp, 38	RCALL	moveCursor
	LDI	temp, 'P'	RCALL	writeChar
	LDI	temp, 38	RCALL	moveCursor
	RJMP	exit9

exit9:
	RCALL	down_ATTENDANCE_PROCESS
	RJMP	typematicContinue
;==========================================================================


change_CONFIRM_ATTENDANCE:
;==========================================================================
	TST	currentValue
	BREQ	NOtoYES		// if choice is NO then jump to YES

YEStoNO:
	LDI	currentValue, 0	// make the choice NO
	LDI	temp, 38
	RCALL	moveCursor		// move the cursor to NO location
	RJMP	typematicContinue

NOtoYES:
	LDI	currentValue, 1	// make the choice YES
	LDI	temp, 36
	RCALL	moveCursor		// move the cursor to YES location
	RJMP	typematicContinue
;==========================================================================
