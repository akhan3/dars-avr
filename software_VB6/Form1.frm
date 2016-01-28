VERSION 5.00
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Object = "{3B7C8863-D78F-101B-B9B5-04021C009402}#1.2#0"; "RICHTX32.OCX"
Begin VB.Form Form1 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "D.A.R.S - Data Acqiusition Interface"
   ClientHeight    =   5055
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
   ScaleHeight     =   5055
   ScaleWidth      =   7470
   WhatsThisHelp   =   -1  'True
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   3000
      Left            =   6600
      Top             =   4200
   End
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
   Begin RichTextLib.RichTextBox Text2 
      Height          =   2775
      Left            =   360
      TabIndex        =   15
      Top             =   5040
      Visible         =   0   'False
      Width           =   6735
      _ExtentX        =   11880
      _ExtentY        =   4895
      _Version        =   393217
      ScrollBars      =   2
      TextRTF         =   $"Form1.frx":0000
   End
   Begin VB.CommandButton cmdStore 
      Caption         =   "Store to Database"
      Enabled         =   0   'False
      Height          =   350
      Left            =   2040
      TabIndex        =   14
      Top             =   2760
      Width           =   1575
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
      Top             =   3360
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
      Height          =   350
      Left            =   360
      TabIndex        =   5
      Top             =   2760
      Width           =   1575
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
      Height          =   1575
      Left            =   360
      TabIndex        =   6
      Top             =   1080
      Width           =   3255
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
         Left            =   1200
         PasswordChar    =   "l"
         TabIndex        =   2
         Text            =   "ned0304"
         Top             =   960
         Width           =   1695
      End
      Begin VB.ComboBox whichPort 
         Height          =   315
         ItemData        =   "Form1.frx":007B
         Left            =   1200
         List            =   "Form1.frx":0088
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
      Height          =   2055
      Left            =   3720
      TabIndex        =   0
      Top             =   1080
      Width           =   3375
      Begin VB.OptionButton optCommand 
         Caption         =   "Change gadget's password"
         Enabled         =   0   'False
         Height          =   255
         Index           =   2
         Left            =   360
         TabIndex        =   9
         Top             =   1200
         Width           =   2295
      End
      Begin VB.OptionButton optCommand 
         Caption         =   "Erase memory"
         Height          =   255
         Index           =   1
         Left            =   360
         TabIndex        =   4
         Top             =   840
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
         Enabled         =   0   'False
         Height          =   255
         Index           =   3
         Left            =   360
         TabIndex        =   10
         Top             =   1560
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
    Const ERROR1 = 199

Dim numAttendances As Integer
Dim subj(4 * 46 - 1) As String
Dim dat(4 * 46 - 1) As Date
Dim att(4 * 46 - 1, 69) As Boolean


Private Sub Form_Load()
    whichPort.ListIndex = 0
End Sub


Private Sub cmdConnect_Click()
    
    On Error GoTo errorHandler
    cmdConnect.Enabled = False

'select the COM port to open
''''''''''''''''''''''''''''
    P1.Settings = "9600,n,8,1"
    P1.Handshaking = comNone
    P1.RThreshold = 1
    P1.SThreshold = 0
    P1.InputLen = 1
    P1.InBufferSize = 512
    P1.OutBufferSize = 512
    P1.CommPort = whichPort.ItemData(whichPort.ListIndex)
    P1.PortOpen = True

    
'send the null terminated password
''''''''''''''''''''''''''''''''''
    P1.Output = password & Chr(0)
    state = checkingPassword    'change the state
    Timer1.Enabled = True
    
'commandWord
''''''''''''
    For counter = optCommand.LBound To optCommand.UBound
        If optCommand(counter).Value = True Then temp = counter
    Next
    Select Case CInt(temp)
        Case 0: commandWord = "S"
        Case 1: commandWord = "E"
        Case 2: commandWord = "G"
        Case 3: commandWord = "D"
    End Select
    
    Exit Sub

errorHandler:
    Select Case Err.Number
        Case comPortInvalid:
            temp = "COM" & P1.CommPort & " is not available on this computer."
            whichPort.RemoveItem (P1.CommPort - 1)
            whichPort.ListIndex = 0
        Case comPortAlreadyOpen:
            temp = "Could not open port beacuse COM" & P1.CommPort & " is already opened by some other application."
        Case Else
            temp = "Unexpected error encountered!" & vbCrLf & Err.Description & vbCrLf & "The appliation will now terminate"
            MsgBox temp, vbCritical, "Error"
            End
    End Select
    
    Timer1.Enabled = False
    cmdConnect.Enabled = True
    If P1.PortOpen = True Then P1.PortOpen = False
    MsgBox temp, vbCritical, "Error"
    statusLabel = temp
End Sub

Private Sub P1_OnComm()

On Error GoTo errorHandler

If P1.CommEvent = comEvReceive Then
    Select Case state
        Case checkingPassword:
        '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
            signal = P1.Input               'read back the acc/rej signal
            
            If (signal = "R") Then          'if rejected
                Timer1.Enabled = False      'stop the timer
                P1.PortOpen = False         'close the port
                cmdConnect.Enabled = True
                state = ERROR1              'change the state
                temp = "Incorrect password!" & vbCrLf & vbCrLf & "Please provide correct password."
                MsgBox temp, vbCritical, "Error"
                statusLabel = temp
            
            ElseIf (signal = "A") Then      'if accepetd
                Timer1.Enabled = False      'stop the timer
                Timer1.Enabled = True       'start the timer
                P1.Output = commandWord     'send the command
                state = checkingCommand     'change the state
                statusLabel = "Password accepted. Processing command ..."
            End If
        
        Case checkingCommand:
        '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
            signal = P1.Input               'read back the acc/rej signal
            
            If (signal = "R") Then          'if rejected
                Timer1.Enabled = False      'stop the timer
                P1.PortOpen = False         'close the port
                cmdConnect.Enabled = True
                state = ERROR1              'change the state
                temp = "Invalid command!" & vbCrLf & vbCrLf & "Please specify a valid command."
                MsgBox temp, vbCritical, "Error"
                statusLabel = temp

            
            ElseIf (signal = "A") Then      'if accepetd
                Timer1.Enabled = False      'stop the timer
                Timer1.Enabled = True       'start the timer
                Select Case commandWord
                    Case "S":   state = sendingNumClasses   'change the state
                    Case "E":   state = erasingMemory       'change the state
                End Select
            End If

        Case sendingNumClasses:
        '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
            signal = P1.Input
            numClasses = CByte(AscB(signal))      'read numClasses
            state = sendingMemory       'change the state
            Timer1.Enabled = False      'stop the timer
            Timer1.Enabled = True       'start the timer
            counter = 0                 'initialize the memory counter

        Case sendingMemory:
        '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
            signal = P1.Input
            readMem(counter) = CByte(Asc(signal))    'read the attendance data string

            If Not counter = (numClasses * 11 - 1) Then
                counter = counter + 1   'advance the memory counter
                Timer1.Enabled = False      'stop the timer
                Timer1.Enabled = True       'start the timer
            Else
                state = done            'change the state
                Timer1.Enabled = False      'stop the timer
                P1.PortOpen = False
                cmdConnect.Enabled = True
                cmdStore.Enabled = True 'enable the database button
                
                statusLabel = "Data of " & numClasses & " classes is acquired from gadget's memory. " & _
                              "Click <Store to Database> to permanently store them in the attendance database. " & vbCrLf & vbCrLf & _
                              "You may now empty the memory by specifying the Erase command."

                extractInformation      ''''''call the subroutine
            End If

        Case erasingMemory:
        '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
            numClasses = CByte(AscB(P1.Input))      'read numClasses
            state = done            'change the state
            Timer1.Enabled = False      'stop the timer
            cmdConnect.Enabled = False
            cmdStore.Enabled = False
            P1.PortOpen = False
            statusLabel = "Data of " & numClasses & " classes is erased from gadget's memory. " & vbCrLf & vbCrLf & _
                          "Please quit the application and turn off the gadget."
            
    End Select
End If
Exit Sub

errorHandler:
    Select Case Err.Number
        Case 9:
            temp = "Program is stuck in inifinite loop and will now terminate." & vbCrLf & vbCrLf & _
            "This is perhaps due to the empty memory." & _
            Err.Description
            MsgBox temp, vbCritical, "Error"
            End
       Case Else:
            temp = "Unexpected error encountered!" & vbCrLf & Err.Description & vbCrLf & "The appliation will now terminate"
            MsgBox temp, vbCritical, "Error"
            End
    End Select
    
    Timer1.Enabled = False
    cmdConnect.Enabled = True
    If P1.PortOpen = True Then P1.PortOpen = False
    MsgBox temp, vbCritical, "Error"
    statusLabel = temp

End Sub

Private Sub extractInformation()
    temp = vbNullString
    numAttendances = 0
    Dim howManyPeriods, j As Integer
    howManyPeriods = 0
    
    Dim mainCount As Integer
    mainCount = 0
    For counter = 0 To numClasses - 1
forLoop1:
        howManyPeriods = (readMem(counter * 11 + 1) And 3) + 1
        Dim s As Byte
            s = Fix(readMem(counter * 11) / (2 ^ 4))
            If s >= 9 Then
                'howManyPeriods = 1
                GoTo invalidEntry
            End If
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
                Case Else:
                        subj(mainCount) = "----"
                    
            End Select
            
            dat(mainCount) = dat_date
            temp = temp & subj(mainCount) & "," & dat_str
            For i = 0 To 69
                att(mainCount, i) = PA(i)
                If PA(i) = True Then
                    temp = temp & ",P"
                Else
                    temp = temp & ",a"
                End If
            Next
            temp = temp & vbCrLf
            mainCount = mainCount + 1
       Next
invalidEntry:
    Next
    
    numAttendances = mainCount
    Dim temp2 As String
    temp2 = Now & vbCrLf & vbCrLf & "Subject,Date,"
    temp2 = temp2 & "001,002,003,004,005,006,007,008,009,010,011,012,013,014,016,017,018,019,020,021,022,023,024,025,026,027,028,029,031,032,033,034,035,036,038,039,040,041,042,043,044,045,047,048,049,050,051,052,053,054,055,056,058,059,060,061,063,064,065,066,067,068,069,070,305,306,307,308,309,310"
    temp2 = temp2 & vbCrLf
    temp2 = temp2 & temp
    Text2.Text = temp2
    Text2.SaveFile "C:\DARS Database\DAR.csv", 1
    
End Sub

Private Sub cmdStore_Click()

On Error GoTo errorHandler

Dim fso As New Scripting.FileSystemObject
Dim conn As New ADODB.Connection
Dim RSall As New ADODB.Recordset
Dim RS As New ADODB.Recordset
conn.Open "Provider=Microsoft.Jet.OLEDB.4.0;" & _
          "Data Source=C:\DARS Database\DAR.mdb;" & _
          "Persist Security Info=False"
RSall.Open "[all subjects]", conn, adOpenForwardOnly, adLockPessimistic, adCmdTable

Dim i, j As Integer
For j = 0 To numAttendances - 1
    RS.Open "[" & subj(j) & "]", conn, adOpenForwardOnly, adLockPessimistic, adCmdTable
    RS.AddNew
    RS.Fields(0) = dat(j)
    RSall.AddNew
    RSall.Fields(0) = subj(j)
    RSall.Fields(1) = dat(j)
    For i = 0 To 69
        RS.Fields(1 + i) = att(j, i)
        RSall.Fields(2 + i) = att(j, i)
    Next
    RS.Update
    RS.Close
    RSall.Update
Next
RSall.Close
Set RSall = Nothing
cmdStore.Enabled = False
statusLabel = "Database entry is successful." & vbCrLf & vbCrLf & _
              "You may now empty the memory by specifying the Erase command."
Exit Sub


errorHandler:
    temp = "Unexpected error encountered!" & vbCrLf & Err.Description & vbCrLf & "The appliation will now terminate"
    MsgBox temp, vbCritical, "Error"
    End

End Sub

Private Sub Timer1_Timer()
    Timer1.Enabled = False
    P1.PortOpen = False
    cmdConnect.Enabled = True
    
    temp = "Port response time out!" & vbCrLf & vbCrLf & "Check the COM port cable and connection." & vbCrLf & "Also make sure the gadget is powered on."
    MsgBox temp, vbCritical, "Error"
    statusLabel = temp
End Sub
