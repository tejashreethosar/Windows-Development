using System;
using System.Runtime.InteropServices;

public class PInvoke
{
    // code
    [DllImport("user32.dll", EntryPoint = "MessageBoxW", CharSet = CharSet.Unicode)]
    public static extern int MyMessageBox(int n1, String s, String c, int n2);     
    public static void Main()
    {
        // code
        MyMessageBox(0, "MessageBox() called as UNICODE-API", "Win32 UNICODE-API", 0);
    }
}

/*
 STEPS TO RUN:
1. csc.exe PInvoke.cs
*/
