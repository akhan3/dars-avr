//delay subroutines use X pouinter, temp and temp1 registers

delay10us:
	LDI 	XH, HIGH(int(0.00001*f/4))//use the value = 10u*f/4
	LDI 	XL, LOW (int(0.00001*f/4))
	again10u:
	SBIW	XH:XL, 1
	BRNE	again10u
	RET

delay100us:					
	LDI 	XH, HIGH(int(0.0001*f/4))//use the value = 100u*f/4
	LDI 	XL, LOW (int(0.0001*f/4))
	again100u:
	SBIW	XH:XL, 1
	BRNE	again100u
	RET

delay1ms:					
	LDI 	XH, HIGH(int(0.001*f/4))//use the value = 1m*f/4
	LDI 	XL, LOW (int(0.001*f/4))
	again1m:
	SBIW	XH:XL, 1
	BRNE	again1m
	RET

delay10ms:
	LDI 	XH, HIGH(int(0.01*f/4))	//use the value = 10m*f/4
	LDI 	XL, LOW (int(0.01*f/4))
	again10m:
	SBIW	XH:XL, 1 
	BRNE	again10m
	RET

delay1s:				//1s delay created by 100 * 10ms
	LDI	temp1, 100
	again1:
	RCALL	delay10ms
	DEC	temp1
	BRNE	again1
	RET

delay10usLong:			//temp * 10us delay
	RCALL	delay10us
	DEC	temp
	BRNE	delay10usLong
	RET

delay100uslong:			//temp * 100us delay
	RCALL	delay100us
	DEC	temp
	BRNE	delay100usLong
	RET

delay1mslong:			//temp * 1ms delay
	RCALL	delay1ms
	DEC	temp
	BRNE	delay1msLong
	RET

delay10mslong:			//temp * 10ms delay
	RCALL	delay10ms
	DEC	temp
	BRNE	delay10msLong
	RET

delay1slong:			//temp * 1s delay
	RCALL	delay1s
	DEC	temp
	BRNE	delay1sLong
	RET
