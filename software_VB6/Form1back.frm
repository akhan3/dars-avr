VERSION 5.00
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Object = "{3B7C8863-D78F-101B-B9B5-04021C009402}#1.2#0"; "RICHTX32.OCX"
Begin VB.Form Form1 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "D.A.R.S - Data Acqiusition Interface"
   ClientHeight    =   8595
   ClientLeft      =   1635
   ClientTop       =   1620
   ClientWidth     =   7470
   BeginProperty Font 
      Name            =   "Tahoma"
      Size            =   8.25
      Charset         =   0
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   8595
   ScaleWidth      =   7470
   WhatsThisHelp   =   -1  'True
   Begin MSCommLib.MSComm P1 
      Left            =   6480
      Top             =   3600
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      DTREnable       =   -1  'True
      InBufferSize    =   512
      InputLen        =   1
      RThreshold      =   1
   End
   Begin RichTextLib.RichTextBox RichTextBox1 
      Height          =   375
      Left            =   5040
      TabIndex        =   16
      Top             =   3720
      Visible         =   0   'False
      Width           =   1935
      _ExtentX        =   3413
      _ExtentY        =   661
      _Version        =   393217
      Enabled         =   -1  'True
      TextRTF         =   $"Form1back.frx":0000
   End
   Begin VB.CommandButton cmdStore 
      Caption         =   "Store to Database"
      Height          =   375
      Left            =   5160
      TabIndex        =   15
      Top             =   4440
      Width           =   1935
   End
   Begin VB.TextBox Text2 
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   3255
      Left            =   360
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   14
      Top             =   4920
      Width           =   6735
   End
   Begin VB.Frame Frame2 
      Caption         =   "Status and Instructions"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1455
      Left            =   360
      TabIndex        =   12
      Top             =   2760
      Width           =   6735
      Begin VB.Label statusLabel 
         Caption         =   "Please type password and specify a command. Then click <Execute Command>"
         Height          =   975
         Left            =   240
         TabIndex        =   13
         Top             =   360
         Width           =   6255
      End
   End
   Begin VB.CommandButton cmdConnect 
      Caption         =   "Execute Command"
      Height          =   375
      Left            =   368
      TabIndex        =   5
      Top             =   4440
      Width           =   2055
   End
   Begin VB.Frame Frame3 
      Caption         =   "Connect to"
      BeginProperty Font 
         Name            =   "Verdana"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1455
      Left            =   360
      TabIndex        =   6
      Top             =   1080
      Width           =   3135
      Begin VB.TextBox password 
         BeginProperty Font 
            Name            =   "Wingdings"
            Size            =   8.25
            Charset         =   2
            Weight          =   400
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   285
         IMEMode         =   3  'DISABLE
         Left            =   1080
         PasswordChar    =   "l"
         TabIndex        =   2
         Text            =   "ned0304"
         Top             =   960
         Width           =   1695
      End
      Begin VB.ComboBox whichPort 
         Height          =   315
         ItemData        =   "Form1back.frx":0084
         Left            =   1080
         List            =   "Form1back.frx":0091
         Style           =   2  'Dropdown List
         TabIndex        =   1
         Top             =   480
         Width           =   855
      End
      Begin VB.Label Label2 
         AutoSize        =   -1  'True
         Caption         =   "COM Port"
         Height          =   195
         Left            =   240
         TabIndex        =   8
         Top             =   480
         Width           =   690
      End
      Begin VB.Label Label1 
         AutoSize        =   -1  'True
         Caption         =   "Password"
         Height          =   195
         Left            =   240
         TabIndex        =   7
         Top             =   960
         Width           =   690
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Command Options"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1455
      Left            =   3720
      TabIndex        =   0
      Top             =   1080
      Width           =   3375
      Begin VB.OptionButton optCommand 
         Caption         =   "Change gadget's password"
         Height          =   255
         Index           =   2
         Left            =   2040
         TabIndex        =   9
         Top             =   480
         Width           =   2295
      End
      Begin VB.OptionButton optCommand 
         Caption         =   "Erase memory"
         Height          =   255
         Index           =   1
         Left            =   360
         TabIndex        =   4
         Top             =   960
         Width           =   1335
      End
      Begin VB.OptionButton optCommand 
         Caption         =   "Read memory"
         Height          =   255
         Index           =   0
         Left            =   360
         TabIndex        =   3
         Top             =   480
         Value           =   -1  'True
         Width           =   1335
      End
      Begin VB.OptionButton optCommand 
         Caption         =   "Change data acquistion password"
         Height          =   255
         Index           =   3
         Left            =   2040
         TabIndex        =   10
         Top             =   960
         Width           =   2775
      End
   End
   Begin VB.Label Label3 
      Alignment       =   2  'Center
      Caption         =   "Digital Attendance Recording System"
      BeginProperty Font 
         Name            =   "Tahoma"
         Size            =   18
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   360
      TabIndex        =   11
      Top             =   240
      Width           =   6735
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim temp As String
Dim signal As String
Dim commandWord As String
Dim counter As Integer
Dim numClasses As Integer
Dim readMem(511) As Byte

Dim state As Integer
    Const checkingPassword = 11
    Const checkingCommand = 22
    Const sendingNumClasses = 33
    Const sendingMemory = 55
    Const erasingMemory = 44
    Const done = 99

Dim array1(131) As Byte
Dim numAttendances As Integer
Dim subj(4 * 46 - 1) As String
Dim dat(4 * 46 - 1) As Date
Dim att(4 * 46 - 1, 69) As Boolean


Private Sub Command2_Click()
Text3 = vbNullString
Dim i As Integer
For i = 1 To 80
    Text3 = Text3 & "0"
    If i <= 9 Then Text3 = Text3 & "0"
    Text3 = Text3 & i & " "
Next
End Sub

Private Sub Form_Load()
    whichPort.ListIndex = 0

'----------------temp array
numClasses = 12
array1(0) = 87
array1(1) = 145
array1(2) = 254
array1(3) = 191
array1(4) = 235
array1(5) = 251
array1(6) = 239
array1(7) = 95
array1(8) = 219
array1(9) = 158
array1(10) = 255
array1(11) = 114
array1(12) = 36
array1(13) = 31
array1(14) = 254
array1(15) = 55
array1(16) = 255
array1(17) = 217
array1(18) = 227
array1(19) = 254
array1(20) = 121
array1(21) = 199
array1(22) = 34
array1(23) = 241
array1(24) = 248
array1(25) = 255
array1(26) = 127
array1(27) = 118
array1(28) = 207
array1(29) = 55
array1(30) = 191
array1(31) = 199
array1(32) = 239
array1(33) = 33
array1(34) = 17
array1(35) = 224
array1(36) = 39
array1(37) = 34
array1(38) = 239
array1(39) = 68
array1(40) = 150
array1(41) = 243
array1(42) = 45
array1(43) = 235
array1(44) = 17
array1(45) = 245
array1(46) = 63
array1(47) = 248
array1(48) = 126
array1(49) = 255
array1(50) = 246
array1(51) = 255
array1(52) = 255
array1(53) = 255
array1(54) = 255
array1(55) = 96
array1(56) = 0
array1(57) = 255
array1(58) = 255
array1(59) = 255
array1(60) = 255
array1(61) = 255
array1(62) = 255
array1(63) = 255
array1(64) = 255
array1(65) = 255
array1(66) = 49
array1(67) = 228
array1(68) = 184
array1(69) = 117
array1(70) = 238
array1(71) = 62
array1(72) = 130
array1(73) = 7
array1(74) = 204
array1(75) = 135
array1(76) = 247
array1(77) = 50
array1(78) = 46
array1(79) = 252
array1(80) = 191
array1(81) = 255
array1(82) = 255
array1(83) = 255
array1(84) = 255
array1(85) = 255
array1(86) = 255
array1(87) = 255
array1(88) = 20
array1(89) = 112
array1(90) = 253
array1(91) = 251
array1(92) = 255
array1(93) = 247
array1(94) = 255
array1(95) = 199
array1(96) = 223
array1(97) = 255
array1(98) = 231
array1(99) = 36
array1(100) = 129
array1(101) = 253
array1(102) = 189
array1(103) = 255
array1(104) = 255
array1(105) = 239
array1(106) = 223
array1(107) = 247
array1(108) = 255
array1(109) = 255
array1(110) = 0
array1(111) = 0
array1(112) = 255
array1(113) = 255
array1(114) = 255
array1(115) = 255
array1(116) = 255
array1(117) = 255
array1(118) = 255
array1(119) = 255
array1(120) = 255
array1(121) = 5
array1(122) = 0
array1(123) = 254
array1(124) = 255
array1(125) = 247
array1(126) = 255
array1(127) = 127
array1(128) = 255
array1(129) = 255
array1(130) = 247
array1(131) = 223
'----------------temp array
   
End Sub


Private Sub cmdConnect_Click()

'if not already open then open the COM port
    If P1.PortOpen = False Then
    'select the COM port to open
        P1.RThreshold = 1
        P1.InputLen = 1
        ''''''''''''''''''' other settings pending ''''''''''''''''
        P1.CommPort = whichPort.ItemData(whichPort.ListIndex)
        P1.PortOpen = True
    End If
    
'send the null terminated password
    P1.Output = (password & Chr(0) & Command)
    'whichPort.Enabled = False
    state = checkingPassword    'change the state
    
'commandWord
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
    For counter = optCommand.LBound To optCommand.UBound
        If optCommand(counter).Value = True Then temp = counter
    Next
    Select Case CInt(temp)
        Case 0: commandWord = "S"
        Case 1: commandWord = "E"
        Case 2: commandWord = "G"
        Case 3: commandWord = "D"
    End Select
''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

End Sub

Private Sub P1_OnComm()


If P1.CommEvent = comEvReceive Then
    Select Case state
        
        Case checkingPassword:
        '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
            signal = P1.Input                 'read back the acc/rej signal
            If (signal = "R") Then            'if rejected
                temp = MsgBox("Incorrect password!" & vbCrLf & vbCrLf & _
                              "Please provide correct password.", vbCritical)
                statusLabel = "Incorrect password! " & vbCrLf & vbCrLf & _
                              "Please provide correct password."
            ElseIf (signal = "A") Then        'if accepetd
                statusLabel = "Password accepted. Processing command ..."
                P1.Output = commandWord     'send the command
                state = checkingCommand     'change the state
            End If
            cmdStore.Enabled = False     'disable the database button
        '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
        
        Case checkingCommand:
        '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
            signal = P1.Input               'read back the acc/rej signal
            If (signal = "R") Then          'if rejected
                temp = MsgBox("Invalid command!" & vbCrLf & vbCrLf & _
                              "Please specify a valid command.", vbCritical)
                statusLabel = "Invalid command!" & vbCrLf & vbCrLf & _
                              "Please specify a valid command."
            ElseIf (signal = "A") Then      'if accepetd
                Select Case commandWord
                    Case "S":   state = sendingNumClasses   'change the state
                    Case "E":   state = erasingMemory       'change the state
                End Select
            End If
        '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

        Case sendingNumClasses:
        '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
            numClasses = CByte(AscB(P1.Input))      'read numClasses
            state = sendingMemory       'change the state
            counter = 0                 'initialize the memory counter
        '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

        Case sendingMemory:
        '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
            signal = P1.Input
            readMem(counter) = CByte(Asc(signal))    'read the attendance data string

            If Not counter = (numClasses * 11 - 1) Then
                counter = counter + 1   'advance the memory counter
            Else
                state = done            'change the state
                P1.PortOpen = False
                cmdStore.Enabled = True 'enable the database button
                
                statusLabel = "Data of " & numClasses & " classes is acquired from gadget's memory. " & _
                              "Click <Store to Database> to permanently store them in the attendance database. " & vbCrLf & vbCrLf & _
                              "You may now empty the gadget by specifying the Erase command."

                extractInformation
            End If
        '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

        Case erasingMemory:
        '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
            numClasses = CByte(AscB(P1.Input))      'read numClasses
            state = done            'change the state
            statusLabel = "Data of " & numClasses & " classes is erased from gadget's memory. " & vbCrLf & vbCrLf & _
                          "Please quit the program and turn off the gadget"
            P1.PortOpen = False
        '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

    End Select
End If
End Sub

Private Sub extractInformation()
    Text2 = vbNullString
    numAttendances = 0
    Dim howManyPeriods, j As Integer
    howManyPeriods = 0
    
    For j = 0 To 131
        readMem(j) = array1(j)
    Next
    
    Dim mainCount As Integer
    mainCount = 0
    For counter = 0 To numClasses - 1
        howManyPeriods = (readMem(counter * 11 + 1) And 3) + 1
        numAttendances = numAttendances + howManyPeriods
      
        Dim s As Byte
            s = Fix(readMem(counter * 11) / (2 ^ 4))
        Dim m As Byte
            m = Fix((readMem(counter * 11) And 15) + 1)
        Dim d As Byte
            d = Fix((readMem(counter * 11 + 1) / 2 ^ 3)) + 1
        Dim y As Byte
            y = Fix(readMem(counter * 11 + 1) And 4)
            y = Fix(y / (2 ^ 2))
        Dim dat_date As Date
            dat_date = DateSerial(2007 + y, m, d)
        Dim dat_str As String
            dat_str = CStr(Day(dat_date) & "-" & MonthName(Month(dat_date), True) & "-" & Year(dat_date))
        
'Attendance---------------------------------
        Dim att9(8), i As Byte
            For i = 0 To 8
                att9(i) = readMem(counter * 11 + 2 + i)
            Next
        Dim PA(69) As Boolean
        Dim bitN, byteN, temp1 As Byte
            bitN = 7: byteN = 0
            For i = 0 To 69
                temp1 = att9(byteN)
                temp1 = Fix(temp1 And (2 ^ bitN))
                temp1 = Fix(temp1 / (2 ^ bitN))
                PA(i) = CBool(temp1)
                If bitN = 0 Then
                    bitN = 7
                    byteN = byteN + 1
                Else
                    bitN = bitN - 1
                End If
            Next
'Attendance---------------------------------
        
        For j = 1 To howManyPeriods
            Select Case s
                Case 0: subj(mainCount) = "SSD"
                Case 1: subj(mainCount) = "Opto"
                Case 2: subj(mainCount) = "VLSI"
                Case 3: subj(mainCount) = "LCS"
                Case 4: subj(mainCount) = "CS-2"
                Case 5: subj(mainCount) = "DSP"
                Case 6: subj(mainCount) = "MPAL"
                Case 7: subj(mainCount) = "CCN"
                Case 8: subj(mainCount) = "NM"
            End Select
            
            dat(mainCount) = dat_date
            Text2 = Text2 & mainCount & Chr(9) & subj(mainCount) & Chr(9) & dat_str & Chr(9)
            For i = 0 To 69
                att(mainCount, i) = PA(i)
                If PA(i) = True Then
                    Text2 = Text2 & "P"
                Else
                    Text2 = Text2 & "a"
                End If
                If (i + 1) Mod 4 = 0 Then Text2 = Text2 & " "
            Next
            Text2 = Text2 & vbCrLf
            mainCount = mainCount + 1
        Next
    Next
End Sub

Private Sub Command1_Click()

Dim fso As New Scripting.FileSystemObject
Dim conn As New ADODB.Connection
Dim RS As New ADODB.Recordset
conn.Open "Provider=Microsoft.Jet.OLEDB.4.0;" & _
          "Data Source=C:\DARS Database\DAR.mdb;" & _
          "Persist Security Info=False"

Dim i, j As Integer
For j = 0 To numAttendances - 1
    RS.Open "[all subjects]", conn, adOpenForwardOnly, adLockPessimistic, adCmdTable
    RS.AddNew
    RS.Fields(0) = subj(j)
    RS.Fields(1) = dat(j)
    For i = 0 To 69
        RS.Fields(2 + i) = att(j, i)
    Next
    RS.Update
    RS.Close
    
'    If Not fso.FileExists("C:\DARS Database\DAR.csv") Then
'        fso.CreateTextFile(
    
    
Next

'RichTextBox1.SaveFile("dd",pla)
End Sub
