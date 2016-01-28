; Demonstates the use of the EEPROMs
;
; During the programming a counter location, defined in the EEPROM,
; is set to zero. At every restart of the processor this counter is incremented
; and its content is displayed in hex format on the LEDs.
; Please refer to the hints given on the end of this code to avoid confusion!
;
.NOLIST
.INCLUDE "C:\avrtools\appnotes\8515def.inc"
.LIST
;
; Define constants
;
.equ	cnt=$0000 ; Adress of the counter location in the EEPROM
;
; Define registers
.def	mpr=R16 ; Universal register
.def	neu=R17 ; Counter value interim storage
;
; Reset-/Interrupt-Vector
	rjmp	main ; Jump to main program
;
main:
	ldi	mpr,$FF ; all bits of Port B are Output
	out	DDRB,mpr
; Program reads a byte from the EEPROM location
	ldi	mpr,LOW(cnt) ; Set the EEPROM location to read from
	out	EEARL,mpr ; tell this to EEPROM-Port
	ldi	mpr,HIGH(cnt) ; Low/High-Byte will be read separately
	out	EEARH,mpr ; as there are 512 byte locations available
	sbi	EECR,EERE ; Set the Read-Enable-Bit EERE in the
		 ; EEPROM-Control-Register EECR
	in	neu,EEDR ; Read the byte from the EEPROM-location
; Increment the counter and write back to the same EEPROM location
	inc	neu
wart:
; If EEPROM is not ready, wait first
	sbic	EECR,1 ; Read bit 1 in the EEPROM-Control-Register
	rjmp	wart ; and repeat until EEPROM reports ready
; The EEPROM-adress location isn't changed, so we don't need to set that first
; by transfer of the EEPROM-write adress to EEARL/EEARH
	out	EEDR,neu ; New counter value to the EEPROM-data register
; The two write commands must not be interrupted, because they must be executed
; within four commands to ensure prevention of any unwanted write commands to
; the EEPROM. So we have to disable any interrupts before entering the write
; sequence.
	cli ; disables all interrupts
; Now we can start the two write commands:
	sbi	EECR,EEMWE ; Switches on the EEPROM Master Write Enable
	sbi	EECR,EEWE ; Starts the write command to the EEPROM
; During the following ca. 1,5 milliseconds the byte is written to the EEPROM.
; This affects us only if we want to use the EEPROM for further operations.
; Not here: we write the inverted content of the counter to the Port B, the
; LED-port, and end the program with a indefinite loop.
	com	neu ; invert the counter (XOR FFh)
	out	PORTB,neu ; to Port B
loop:
	rjmp	loop ; wait undefinitely
; Here we start defining the initial value of the counter location in the EEPROM
; during programming.
; First we tell the assembler, that the following informations go to the EEPROM.
.ESEG
; Now we define the EEPROM-content:
.DB	$00 ; One byte with a zero
; That's about it.
; IMPORTANT HINTS
; During programming the content of the EEPROM-file TESTEEP.EEP
; will be loaded separately and programmed after the code is loaded.
; Don't forget this!
; During the programming sequence of the different locations for code
; and EEPROM content the software for the board releases the Reset pin
; of the processor, e.g. between programming and verification. As this
; short pause already causes the processor to restart and execute the
; code. Verification of the EEPROM content will therefore fail, because
; the counter is already incremented and does not match its original
; programmed value. Every read operation of the EEPROM content
; onboard will have the same effect.
; The execution of the restart command using the ISP software also
; causes multiple startups of the processor and increases the counter
; value, so don't expect to see correct counting values.
; Exact up-counts are only seen when switching the supply voltage
; of the board off and on.
; To avoid unwanted upcounting during program, verification and read
; operation would require setting a startup delay time, but this is a
; little bit too complex for a beginner.
