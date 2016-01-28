
setState_MAIN_MENU:
;========================================
	LDI	currentState, MAIN_MENU
	LDI	currentValue, 0
	RCALL	cursorOFF
	RET
;========================================

setState_VIEW_MENU:
;========================================
	LDI	currentState, VIEW_MENU
	LDI	currentValue, 1
	LDI	temp, 36
	RCALL	moveCursor
	RCALL	cursorON
	RET
;========================================

setState_SUBJECT_SELECT:
;========================================
	LDI	currentState, SUBJECT_SELECT
	STS	classesRAM, currentValue
	LDS	currentValue, subjectRAM

	LDI	temp, HIGH(subjectList)	MOV	R3, temp	//base address in [R3:R2]
	LDI	temp, LOW (subjectList)	MOV	R2, temp
	LDI	temp, 1
	RCALL	moveCursor
	RCALL	cursorON
	RET
;========================================

setState_DAY_SELECT:
;========================================
	LDI	currentState, DAY_SELECT
	STS	subjectRAM, currentValue
	LDS	currentValue, dayRAM

	LDI	temp, HIGH(dayList)	MOV	R3, temp	//base address in [R3:R2]
	LDI	temp, LOW (dayList)	MOV	R2, temp
	LDI	temp, 10
	RCALL	moveCursor
	RET
;========================================

setState_MONTH_SELECT:
;========================================
	LDI	currentState, MONTH_SELECT
	STS	dayRAM, currentValue
	LDS	currentValue, monthRAM

	LDI	temp, HIGH(monthList)	MOV	R3, temp	//base address in [R3:R2]
	LDI	temp, LOW (monthList)	MOV	R2, temp
	LDI	temp, 13
	RCALL	moveCursor
	RET
;========================================

setState_YEAR_SELECT:
;========================================
	LDI	currentState, YEAR_SELECT
	STS	monthRAM, currentValue
	LDS	currentValue, yearRAM

	LDI	temp, HIGH(yearList)	MOV	R3, temp	//base address in [R3:R2]
	LDI	temp, LOW (yearList)	MOV	R2, temp
	LDI	temp, 17
	RCALL	moveCursor
	RET
;========================================

setState_CLASSES_SELECT:
;========================================
	LDI	currentState, CLASSES_SELECT
	STS	yearRAM, currentValue
	LDS	currentValue, classesRAM

	LDI	temp, HIGH(classesList)	MOV	R3, temp	//base address in [R3:R2]
	LDI	temp, LOW (classesList)	MOV	R2, temp
	LDI	temp, 38
	RCALL	moveCursor
	RET
;========================================

setState_ATTENDANCE_PROCESS:
;========================================
	LDI	currentState, ATTENDANCE_PROCESS
	LDI	currentValue, 0	//;~~~ current Rno index is 0
	LDI	bitCounter, 7	//~~~ CLR	bitCounter
	CLR	byteCounter
	LDI	temp, 38
	RCALL	moveCursor
	RET
;========================================

setState_CONFIRM_ATTENDANCE:
;========================================
	LDI	currentState, CONFIRM_ATTENDANCE
	CLR	currentValue	// default choice is NO
	LDI	temp, 38
	RCALL	moveCursor		// place cursor at NO location
	RET
;========================================
