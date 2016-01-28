//stack pointer initialization from the bottom of RAM
	LDI	temp, HIGH(RAMEND)
	OUT	SPH, temp
	LDI	temp, LOW (RAMEND)
	OUT	SPL, temp

//registers loading
	LDI	temp, 0xFF
	MOV	ones, temp
	CLR	zeros

//port settings
	OUT	DDRB, ones		//PORTB drives LCD control pins
	OUT	PORTB, ones		//render it as output port

	OUT	DDRC, ones		//PORTC drives LCD data pins
	OUT	PORTC, ones

	OUT	DDRD, zeros		//PORTD takes input from keypad
	OUT	PORTD, ones		//all pullups enable
	OUT	PIND, ones		//dummy inst for simulator
	SBI	DDRD, PD1		//output for TXD
	SBI	DDRD, BLout		//output for Backlight


//interrupt settings
	LDI	temp, 0b10		//backlight button interrupt INT0 is  on negative edge
	OUT	MCUCR, temp
	LDI	temp, 1<<INT0	//INT0 is enabled
	OUT	GICR, temp
	SEI				//Global Interrupt enable


//UART settings
;	baud rate	9600
;	start bit	1
;	data bits	8
;	parity	none
;	stop bits	1
	OUT	UCSRB, zeros	//disable UART to flush the serial buffer

	LDI	temp, f/16/BAUD-1	//set the baud rate
	OUT	UBRRL, temp
	LDI	temp, 1<<TXEN | 1<<RXEN | 1<<RXCIE
	OUT	UCSRB, temp		//RXC interrupt enabled

