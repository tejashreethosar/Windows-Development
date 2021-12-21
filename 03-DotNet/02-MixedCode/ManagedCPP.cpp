#include<stdio.h>
#using<mscorlib.dll>
using namespace System;

int main(void)
{
	// code
	printf("This line is printed by printf().\n");
	Console::WriteLine("This line is printed by WriteLine() in Console type.\n");
	return 0;
}

/*
STEPS TO RUN:
1. cl.exe /clr .\ManagedCPP.cpp
2. ManagedCPP.exe
*/