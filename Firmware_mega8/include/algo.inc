ANDmask:
;==============
; in: bitCounter (unchanged)
; out:temp
	PUSH	bitCounter
	LDI	temp, 1
again99:	
	TST	bitCounter
	BREQ	exit99
	LSL	temp
	DEC	bitCounter
	RJMP	again99
exit99:
	POP	bitCounter
	RET
;==============

shiftLeft:
;==============
; in: temp, bitCounter
; out:temp
again990:	
	TST	bitCounter
	BREQ	exit990
	LSL	temp
	DEC	bitCounter
	RJMP	again990
exit990:
	RET
;==============


flashToRAM:
	LPM	temp, Z+
	ST	Y+, temp
	CPSE	temp, zeros
	RJMP	flashToRAM
	RET

readEEPROM:
;========================
; temp <- [Z]
	SBIC	EECR, EEWE
	RJMP	readEEPROM
	OUT	EEARH, ZH	
	OUT	EEARL, ZL
	SBI	EECR, EERE
	IN	temp, EEDR
	RET
;========================

writeEEPROM:
;========================
; [Y] <- temp
	SBIC	EECR, EEWE
	RJMP	writeEEPROM
	OUT	EEARH, YH	
	OUT	EEARL, YL
	OUT	EEDR, temp
	CLI
	SBI	EECR, EEMWE
	SBI	EECR, EEWE
	SEI
	RET
;========================

SRAMtoEEPROM:
;========================
; [Y]EEPROM <- [Z]SRAM (arrayCounter as index)
	TST	arrayCounter
	BREQ	exit555
	LD	temp, Z+
	RCALL	writeEEPROM
	ADIW	YH:YL, 1
	DEC	arrayCounter
	RJMP	SRAMtoEEPROM
exit555:
	RET
;========================

EEPROMtoSRAM:
;========================
; [Y]SRAM <- [Z]EEPROM (arrayCounter as index)
	TST	arrayCounter
	BREQ	exit666
	RCALL	readEEPROM
	ST	Y+, temp
	ADIW	ZH:ZL, 1
	DEC	arrayCounter
	RJMP	EEPROMtoSRAM
exit666:
	RET
;========================





; bin1ToAsc3
; ==========
; converts a 8-bit-binary to a 3 digit ASCII-coded decimal
; In:	8-bit-binary in currentValue, Y points to the highest
; 	of 3 ASCII digits, where the result goes to
; Out:Y points to the beginning of the ASCII string, leading 
;	zeros are filled with blanks
; Used registers: currentValue(content is not changed), 
;			temp1 (content is changed), temp
; Called subroutines: bin1ToBcd3

bin1ToAsc3:
	RCALL	bin1ToBcd3 	; convert binary to BCD

	LDI	temp1, 2	; Counter is 2 leading digits
bin1ToAsc3a:
	LD	temp, Y	; read a BCD digit
	TST	temp		; check if leading zero
	BRNE	bin1ToAsc3b ; No, found digit >0
	LDI	temp, '0'	; overwrite with blank
	ST	Y+, temp	; store and set to next position
	DEC	temp1		; decrement counter
	BRNE	bin1ToAsc3a	; further leading blanks
	LD	temp, Y	; Read the laST	BCD
bin1ToAsc3b:
	INC	temp1		; one more char
bin1ToAsc3c:
	SUBI	temp, -'0'	; Add ASCII-0
	ST	Y+, temp	; store and inc pointer
	LD	temp, Y	; read next char
	DEC	temp1		; more chars?
	BRNE	bin1ToAsc3c	; yes, go on
	SBIW	YH:YL, 3	; Put pointer to firST	BCD
	RET			; done


; bin1ToBcd3
; ==========
; converts a 8-bit-binary to a 3-digit-BCD
; In:	8-bit-binary in currentValue, Y points to firST	digit
; 	where the result goes to
; Out:3-digit-BCD, Y points to firST	BCD-digit
; Used registers: currentValue (unchanged), temp1 (changed), temp
; Called subroutines: bin1ToDigit

bin1ToBcd3:
	PUSH	currentValue 	; Save number

	LDI	temp1, 100 		; Start with hundreds
	RCALL	bin1ToDigit 	; Calculate digit
	LDI	temp1, 10 		; Next with tens
	RCALL	bin1ToDigit 	; Calculate digit
	ST	Y, currentValue 	; Remainder are ones
	SBIW	YH:YL, 2 		; Put pointer to firST	BCD

	POP	currentValue 	; Restore original binary
	RET				; and return
;
; bin1ToDigit
; ===========
; converts one decimal digit by continued subraction of a binary coded decimal
; Used by: bin1ToBcd3, bin1ToAsc3, bin1ToAsc
; In: 8-bit-binary in currentValue, binary coded decimal in 
;	temp1, Y points to current BCD digit
; Out: Result in Y, Y incremented
; Used registers: currentValue (holds remainder of the binary), temp1 (unchanged), temp
; Called subroutines: -

bin1ToDigit:
	CLR	temp 			; digit count is zero
bin1ToDigit1:
	CP	currentValue, temp1; Number bigger than decimal?
	BRCS	bin1ToDigit2 	; if smaller than decimal
	SUB	currentValue, temp1; Subtract
	INC	temp 			; Increment digit count
	RJMP	bin1ToDigit1 	; Next loop
bin1ToDigit2:
	ST	Y+, temp 		; Save digit and increment pointer
	RET				; done
;
; **************************************************


; bin1ToHex2
; ==========
; converts a 8-bit-binary to uppercase Hex-ASCII
; In:	8-bit-binary in currentValue, Y points to the first
;	position of the 2-character Hex-ASCII
; Out:Y points to the first digit of the 2-character
;	Hex-ASCII, ASCII digits A..F in capital letters
; Used registers: currentValue(unchanged), temp
; Called subroutines: bin1ToHex2a, bin1ToHex1

bin1ToHex2:
	MOV	temp,currentValue ; load byte
	RCALL	bin1ToHex2a ; convert byte
	SBIW	YH:YL,2 ; Set Y to start
	RET
bin1ToHex2a:
	PUSH	temp ; Save byte
	SWAP	temp ; upper to lower nibble
	RCALL	bin1ToHex1
	POP	temp ; Restore byte
bin1ToHex1:
	ANDI	temp,0x0F ; mask upper nibble
	SUBI	temp,-'0' ; add 0 to convert to ASCII
	CPI	temp,'9'+1 ; A..F?
	BRCS	bin1ToHex1a
	SUBI	temp,-7 ; add 7 for A..F
bin1ToHex1a:
	ST	Y+,temp ; store in target
	RET ; and return
;
; *******************************************
