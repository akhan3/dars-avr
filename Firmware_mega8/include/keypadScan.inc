//*********************************************************************************
//		KEYPAD polling and scanning code
//*********************************************************************************

scanKeypad:	
	IN 	temp, keypad	//Read keypad values in temp
	COM	temp			//Turn them active high
	ANDI	temp, 0b11110000	//mask the 4 keys in upper nibble
	BREQ	scanKeypad		//if none is pressed, scan again

pressDebounce://========================
	LDI	temp, pressBounceTime
	RCALL	delay1msLong	//wait for bouncing to die out
	IN 	temp, keypad	//Read keypad values in temp
	COM	temp			//Turn them active high
	ANDI	temp, 0b11110000	//mask the 4 keys in upper nibble
	BREQ	scanKeypad		//if none is pressed, scan again
//======================================

//*******************************************************
	SBIS	keypad, down	RJMP	downRoutine
	SBIS	keypad, up		RJMP	upRoutine
	SBIS	keypad, change	RJMP	changeRoutine
	SBIS	keypad, enter	RJMP	enterRoutine
//*******************************************************

typematicContinue://========================
	LDI	temp, typematicDelay
	RCALL	delay1msLong		
	RJMP	scanKeypad			//continue after typematic delay
//======================================

releaseDebounce://========================
	IN 	temp, keypad	//Read keypad values in temp
	COM	temp			//Turn them active high
	ANDI	temp, 0b11110000	//mask the 4 keys in upper nibble
	BRNE	releaseDebounce	//if still kept pressed, scan again
	LDI	temp, releaseBounceTime
	RCALL	delay1msLong	//wait for rebouncing to die out
	RJMP	scanKeypad
//======================================
