using System;
using System.Runtime.InteropServices;

public class PInvoke
{
    // code
    [DllImport("user32.dll")]
    public static extern int MessageBoxA(int n1, String s, String c, int n2);     
    public static void Main()
    {
        // code
        MessageBoxA(0, "MessageBox() called as ANSI-API", "Win32 ANSI-API", 0);
    }
}

/*
 STEPS TO RUN:
1. csc.exe PInvoke.cs
*/
