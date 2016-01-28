//#define	f			36864//00
#define	f			3686400 	//XTAL =  3.6864MHz (3686400)
#define	BAUD			9600
#define	nextInst1Word	PC+1+1
#define 	nextInst2Word	PC+1+2
#define	pressBounceTime	30	//msec after press not bouncing
#define	releaseBounceTime	10	//msec after release not bouncing
#define	typematicDelay	200	//msec before key's operation repeats
#define	LCDcharDelay	2	//msec between char printing on LCD

//register definitions
.def	ones 		= R14		//all ones
.def	zeros 	= R15		//all zeros
.def	temp 		= R16		//temporary register
.def	temp1		= R17		//another temporary register
.def	cursor 	= R18		//LCD cursor index
.def	arrayCounter= R19
.def	currentValue= R20
.def	currentState= R21
.def	bitCounter	= R22
.def	byteCounter	= R23


//variable definitions
.equ	keypad	= PIND	//Keypad buttons
.equ	data		= PORTC	//LCD data pins
.equ	control	= PORTB	//LCD control pins
.equ	INT0pin	= PD2		//Backlight switch at interrupt0 pin
.equ	RS		= PB0		//LCD register select pin
.equ	EN		= PB1		//LCD enable pin
.equ	BLout		= PD3		//backlight output

.equ	BLin		= PD2		//backlight button
.equ	up		= PD7		//up button
.equ	down		= PD6		//down button
.equ	enter		= PD5		//enter button
.equ	change	= PD4		//change button

//state assignment
#define MAIN_MENU 0
#define VIEW_MENU 1
#define SUBJECT_SELECT 2
#define DAY_SELECT 3
#define MONTH_SELECT 4
#define YEAR_SELECT 5
#define CLASSES_SELECT 6
#define ATTENDANCE_PROCESS 7
#define CONFIRM_ATTENDANCE 8
