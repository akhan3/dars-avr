// 	"abcdefghijklmnopqrst"	[t] is the 20th letter

welcome1:
.DB	" Digital Attendance "
.DB	" Recorder   (D.A.R) ",0,0

welcome3:
.DB	" idea and effort of "
.DB	"BE Electronics   NED",0,0

welcome2:
.DB	" idea and effort of "
.DB	"The Logicians NEDUET",0,0

mainMenu:
.DB	0x7E,	"View old attendance"
.DB	0x20,	"Take new attendance",0,0

classSetup:
.DB	"<SSD >   <01-Jan-07>"
.DB	"number of classes<1>",0,0

viewSetup:
.DB	"Select index number "
.DB	"of the  class  <01> ",0,0

attendanceTaking:
.DB	"VLSI       01-Jan-07"
.DB	"#Classes:1  R#001<P>",0,0

confirm:
.DB	"Are you sure to save"
.DB	"this attendance<Y/N>",0,0

saving:
.DB	" Saving information "
.DB	" into EEPROM",0,0

loading:
.DB	"Loading information "
.DB	"from EEPROM",0

done:
.DB	"done"

blanks:
.DB	"                    "



subjectList:	//2 words apart
.DB	"SSD "
.DB	"Opto"
.DB	"VLSI"
.DB	"LCS "
.DB	"CS-2"
.DB	"DSP "
.DB	"MPAL"
.DB	"CCN "
.DB	"NM  "

dayList:		//1 word apart
.DB	"01020304050607080910111213141516171819202122232425262728293031"

monthList:		//2 words apart
.DB	"Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec "

yearList:		//1 word apart
.DB	"0708"

classesList:	//1 word apart
.DB	"1 2 3 4 "

rollList:		//2 words apart
.DB	"001 002 003 004 005 006 007 008 009 010 011 012 013 014 016 017 018 019 020 "
.DB	"021 022 023 024 025 026 027 028 029 031 032 033 034 035 036 038 039 040 "
.DB	"041 042 043 044 045 047 048 049 050 051 052 053 054 055 056 058 059 060 "
.DB	"061 063 064 065 066 067 068 069 070 "
.DB	"305 306 307 308 309 310 "
//missing roll nos	015 030 037 046 057 062 

testMsg1:
.DB	"Digital Attendance Recorder [D.A.R]",0
testMsg2:
.DB	"by Aamir, Adnan, Faraz & Naail. NEDUET.",0

;============================================

CommInProgress:
.DB	" Communication with "
.DB	" PC in progress.... ",0,0
