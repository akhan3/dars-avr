;.ESEG .ORG EEPROMEND .DB 0


;	11 Bytes for attendance of 1 class
;	11*22/week = 242 Bytes/week
;	242*2 = 484 Bytes are required for attendance of 2 weeks
;
;	-----------------------------     ---------------------------------
;	| SUB | M | D | Y | Classes |     | Attendacne of 70 students | | |
;	-----------------------------     ---------------------------------
;	   4    4   5   1      2                         70           2(free)
;	\___________  ______________/     \______________  _______________/
;	            \/                                   \/
;	    2 Bytes for header                  9 Bytes for attendance
;
;	1 last byte of EEPROM is for "number of classes recorded"

/*******************************/
.DSEG
.ORG SRAM_START
	subjectRAM:		.BYTE 1
	dayRAM:		.BYTE 1
	monthRAM:		.BYTE 1
	yearRAM:		.BYTE 1
	classesRAM:		.BYTE 1
	
	headerRAM:		.BYTE 2
	attendanceRAM:	.BYTE 9

	readAttendaceRAM:	.BYTE	11
	hexRAM:		.BYTE 22
	asciiRAM:		.BYTE 3
	uartBuffer:		.BYTE 20


.CSEG
/*******************************/

	STS	subjectRAM, zeros
	STS	dayRAM, zeros
	STS	monthRAM, zeros
	STS	yearRAM, zeros
	STS	classesRAM, zeros

	STS	attendanceRAM+0, ones
	STS	attendanceRAM+1, ones
	STS	attendanceRAM+2, ones
	STS	attendanceRAM+3, ones
	STS	attendanceRAM+4, ones
	STS	attendanceRAM+5, ones
	STS	attendanceRAM+6, ones
	STS	attendanceRAM+7, ones
	STS	attendanceRAM+8, ones
