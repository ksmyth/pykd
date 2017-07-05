#pragma once

void
__cdecl
CdeclVoidFunc();

void 
__cdecl
CdeclFunc( int a, float b);

int
__cdecl
CdeclFuncReturn( int a, char* b );

long long
__cdecl
CdeclFuncLong( unsigned long long a );

float
__cdecl
CdeclFuncFloat( float a, float b );

double
__cdecl
CdeclFuncDouble( double a, double b );

void
__stdcall
StdcallFunc( int a, float b );

short
__stdcall
StdcallFuncRet( char a, long b);

long long
__stdcall
StdcallFuncLong( unsigned long long a, unsigned long long b);

float
__stdcall
StdcallFuncFloat(float a, float b);

double
__stdcall
StdcallFuncDouble(double a, double b);


double
__fastcall
FastcallFunc( int a, float b );

bool
OverloadedFunc(int a);

bool
OverloadedFunc(int a, int b);

class FuncTestClass
{
public:
    void method();
    static void __cdecl staticMethod();
};

extern void ( *CdeclFuncPtr)( int a, float b);

extern void (FuncTestClass::*MethodPtr)();
extern void (__cdecl*CdeclStaticMethodPtr)();

extern FuncTestClass FuncReturnClass();

void FuncAccessViolation();
int FuncWithSeh(long long a);
void FuncStdException();
int FuncWithTry(int a);


