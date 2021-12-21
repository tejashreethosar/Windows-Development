using System;
using System.Drawing;                   // for colors and brushes
using System.Windows.Forms;             // Win32 SDK's Window is .NET's Form

public class CSharpWindow : Form
{
    public CSharpWindow()
    {
        // code
        Icon = new Icon("BookImg.ico"); // icon of the window
        Text = "C# Window";             // caption of the window
        Width = 800;                    // width of the window
        Height = 600;                   // height of the window
        BackColor = Color.Black;        // background color of the window
        ResizeRedraw = true;            // CS_HREDRAW | CS_VREDRAW

        this.KeyDown += new KeyEventHandler(MyKeyDown);
        this.MouseDown += new MouseEventHandler(MyMouseDown);
    }

    protected override void OnPaint(PaintEventArgs pea)         // WM_PAINT
    {
        // code
        Graphics graphics = pea.Graphics;                       // HDC hdc
        StringFormat string_format = new StringFormat();
        string_format.Alignment = StringAlignment.Center;       //DT_CENTER
        string_format.LineAlignment = StringAlignment.Center;   //DT_VCENTER

        String str = "Hello World !!!";
        graphics.DrawString(str, Font, new SolidBrush(System.Drawing.Color.Green), ClientRectangle, string_format);     //DrawText() of Win32
    }

    void MyKeyDown(object sender, KeyEventArgs e)
    {
        // code
        MessageBox.Show("Some key of keyboard is pressed.");
    }

    void MyMouseDown(object sender, MouseEventArgs e)
    {
        MessageBox.Show("Some button of mouse is clicked.");
    }

    public static void Main()
    {
        // code
        Application.Run(new CSharpWindow());
    }
}

/*
 STEPS TO RUN:
1. csc.exe /t:winexe CSharpWindow.cs
2. CSharpWindow.exe

NOTE:
This is linked icon, so the .exe file and the .ico file should be in the same directory.
*/
