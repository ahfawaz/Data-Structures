#pragma once
/*
Becareful when using this header.
For every CPP file it is linked to is extra time for compiling per CPP file.
Also when adding a macro it will do the same thing.
*/

//Safe Maco Functions
#define SafeRelease(x) if(x) x->Release() 
#define SafeDelete(x) if(x) delete x

//Macro IDs
#define NO_ID -256

//Error Values
#define INVALID_SIZE_F {-512.0f, -512.0f}

//Defualt values
#define DISCARD_ALL -1
#define CLEAR_COLOR D2D1::ColorF(1.0f, 0.0f, 0.0f)
#define DEFAULT_RECT_DRAW_SIZE 100.0F

//Vector Macros
#define RENDER_TARGET_CENTER(_target_size) {_target_size.width / 2.0f, _target_size.height / 2.0f}
