#pragma once

//All Memory Leak Detection is from MSDN documentation:
//https://docs.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2019
//Memory Leak Detections
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

//#define MEM_LEAK_DECTECTION

//A debug version of new for mem leak detection
#ifdef MEM_LEAK_DECTECTION
#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#endif
#else
#define DBG_NEW new
#endif

//This kinda looks really bad....
