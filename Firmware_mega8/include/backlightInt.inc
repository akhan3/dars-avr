backlightInt:
	PUSH	temp1				//push on stack
	PUSH	temp
	IN	temp, SREG
	PUSH	temp

pressDebounceINT0://====================
	LDI	temp, pressBounceTime
	RCALL	delay1msLong		//wait for bouncing to die out
	SBIC	PIND, INT0pin		//if glitch
	RJMP	backlightIntRet		//then discard
//======================================

;==***********************************
	SBIS	PORTD, BLout
	SBIC	PORTD, BLout
	RJMP	backlightOFF
	RJMP	backlightON
backlightOFF:
	CBI	PORTD, BLout
	RJMP	backlightIntRet
backlightON:
	SBI	PORTD, BLout
	RJMP	backlightIntRet
;==***********************************

backlightIntRet:
releaseDebounceINT0://==================
	SBIS	PIND, INT0pin		//is button released
	RJMP	releaseDebounceINT0	//if not then scan again
	LDI	temp, releaseBounceTime
	RCALL	delay1msLong		//wait for rebouncing to die out
;=======================================
	POP	temp				//pop from stack
	OUT	SREG, temp
	POP	temp
	POP	temp1
	RETI
