.equ	pressBounceTime	= 30	//msec after press not bouncing
.equ	releaseBounceTime	= 10	//msec after release not bouncing

keypadInt:

	PUSH	temp1				//push on stack
	PUSH	temp
	IN	temp, SREG
	PUSH	temp

pressDebounce:
;=======================================
	LDI	temp, pressBounceTime
	RCALL	delay1msLong		//wait for bouncing to die out
	SBIS	PIND, INT0pin		//if glitch
	RJMP	keypadIntRet		//then discard
;=======================================

rcall	pulseTest
	IN 	temp, keypad		//Move keypad values in temp
	COM	temp
	ANDI	temp, 0b00011111

	CPI	temp ,1<<up	 	BREQ	upRoutine1
	CPI	temp ,1<<down	BREQ	downRoutine1
	CPI	temp ,1<<enter	BREQ	enterRoutine1
	CPI	temp ,1<<menu	BREQ	menuRoutine1
	CPI	temp ,1<<toggle	BREQ	toggleRoutine1
	
	RJMP	keypadIntRet

upRoutine1:
	RJMP	upRoutine

downRoutine1:
	RJMP	downRoutine

enterRoutine1:
	RJMP	enterRoutine

menuRoutine1:
	RJMP	menuRoutine
	
toggleRoutine1:
	RJMP	toggleRoutine




keypadIntRet:

releaseDebounce:
;=======================================
	SBIC	PIND, INT0pin		//wait for button to be released
	RJMP	releaseDebounce
	LDI	temp, releaseBounceTime
	RCALL	delay1msLong		//wait for rebouncing to die out
	SBIC	PIND, int0pin		//if glitch
	RJMP	releaseDebounce		//then wait further
;=======================================

	POP	temp				//pop from stack
	OUT	SREG, temp
	POP	temp
	POP	temp1
	RETI
