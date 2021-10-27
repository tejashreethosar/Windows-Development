Imports System.Windows.Forms
Imports AutomationServerTypeLibForDotNet
Public Class VBAutomationClient
    Inherits Form
    Public Sub New()
        Dim MyIDispatch As Object
        Dim MyRef As New CMyMathClass
        MyIDispatch = MyRef
        Dim iNum1 = 175
        Dim iNum2 = 125
        Dim iSum = MyIDispatch.SumOfTwoIntegers(iNum1, iNum2)
        Dim str As String = String.Format("Sum of {0} and {1} is {2}.", iNum1, iNum2, iSum)
        MsgBox(str)
        Dim ISub = MyIDispatch.SubtractionOfTwoIntegers(iNum1, iNum2)
        str = String.Format("Subtraction of {0} and {1} is {2}.", iNum1, iNum2, ISub)
        MsgBox(str)
        End
    End Sub

    <STAThread()> Shared Sub Main()
        Application.EnableVisualStyles()
        Application.Run(New VBAutomationClient())
    End Sub

End Class
