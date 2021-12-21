using System;
using System.Runtime.InteropServices;

public class PInvoke
{
    // code
    [DllImport("user32.dll", CharSet = CharSet.Unicode)]
    public static extern int MessageBoxW(int n1, String s, String c, int n2);     
    public static void Main()
    {
        // code
        MessageBoxW(0, "MessageBox() called as UNICODE-API", "Win32 UNICODE-API", 0);
    }
}

/*
 STEPS TO RUN:
1. csc.exe PInvoke.cs
*/
