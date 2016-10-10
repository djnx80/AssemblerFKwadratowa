// AssemblerFKwadratowa.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <bitset>

void ShowDecHexBin(int);
int mathAdd(int, int);
int mathSub(int, int);
int mathMul(int, int);
int mathDiv(int, int);
int mathDivFloat(int, int);


using namespace std;

int main()
{

	// a*x*x + b*x + c
	// delta = b*b - 4*a*c
//	ShowDecHexBin(mathAdd(5, 10));
	ShowDecHexBin(mathDivFloat(5, 10));
	getchar();
	return 0;
}

void ShowDecHexBin(int number) {
	cout << dec << number;
	cout << "\tHex:" << hex << number;
	cout << "\tBin:" << bitset<16>(number) << endl;
}
int mathAdd(int a, int b) {
	int result;
	cout << dec << a << "+" << dec << b << "=";
	__asm {
		mov eax, a
		mov ebx, b
		add eax, ebx
		mov result, eax
	}
	return result;
}
int mathSub(int a, int b) {
	int result;
	cout << dec << a << "-" << dec << b << "=";
	__asm {
		mov eax, a
		mov ebx, b
		sub eax, ebx
		mov result, eax
	}
	return result;
}
int mathDiv(int a, int b) {
	int result;
	cout << dec << a << "/" << dec << b << "=";
	__asm {
		mov eax, a
		mov ebx, b
		cmp ebx, 0		// sprawdz czy b=0; jak tak to nie dziel
		jz Zero_NoDiv
		mov edx, 0	// przed dzieleniem trzeba wyzerowac rejestr edx
		div ebx
		mov result, eax
		jmp endHere

		Zero_NoDiv :
		mov result, 0
			endHere :
	}
	return result;
}

int mathDivFloat(int a, int b) {
	int result;
	cout << dec << a << "/" << dec << b << "=";
	__asm {
//		mov eax, a
		mov ebx, b
		cmp ebx, 0		// sprawdz czy b=0; jak tak to nie dziel
		jz Zero_NoDiv

		mov edx, 0	// przed dzieleniem trzeba wyzerowac rejestr edx

//		fild a
//		fild b
		push a


		fdivp   st(1), st(0)  // st0 = st1 / st0 

		sub esp,4
		fstp [esp]
		pop eax
		mov result, eax

	//	add esp,4
		jmp endHere

		Zero_NoDiv :
		mov result, 0
			endHere :
	}
	return result;
}

/*
push    dword ptr 5;     // fild needs a memory location, the trick is
fild[esp];           // to use the stack as a temp. storage
fild[esp];           // now st0 and st1 both contain (float) 5
add     esp, 4;          // better not screw up the stack
fadd    st(0), st(0);    // st0 = st0 + st0 = 10
fdivp   st(1), st(0);    // st0 = st1 / st0 = 5 / 10 = 0.5
sub     esp, 4;          // again, let's make some room on the stack
fstp[esp];           // store the content of st0 into [esp]
pop     eax;             // get 0.5 off the stack
mov     res, eax;        // move it into res (main's local var)
add     esp, 4;          // preserve the stack

*/


int mathMul(int a, int b) {
	int result;
	cout << dec << a << "*" << dec << b << "=";
	__asm {
		mov eax, a
		mov ebx, b
		mul ebx
		mov result, eax
	}
	return result;
}
