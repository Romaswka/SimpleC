#ifndef _STD_CSTRINGFUNCTIONS_H_
#define _STD_CSTRINGFUNCTIONS_H_

#include <DataTypes.h>

extern inline Size cstringLength(CString buffer);

extern inline Void copyData(Byte buffer[], Index bufferStart, Byte source[], Index sourceStart, Size byteSize);

extern inline Void shiftDataRight(Byte buffer[], Size dataSize, Index bufferStart, Size shiftTo);

//buffer size could be 21 bytes or bigger
extern inline Size SizeToCString(Size value, CString buffer); 

//buffer size could be 21 bytes or bigger
extern inline Size IntToCString(IntMax value, CString buffer);

extern inline Void swapBytes(Byte buffer[], Index bufferEnd);

//buffer size = 1-21 char + accuracy + ('.', exponent) - optional;
extern inline Size FloatToCString(Float64 value, CString buffer, Size accuracy);

extern inline Bool equalData(Byte buffer[], Index bufferStart, Byte source[], Index sourceStart, Size bytes);

extern inline CString findCoincidence(CString buffer, Size bufferSize, CString find, Size findSize);

extern inline CString findFirst(CString buffer, Size bufferSize, Char find);

// size <= sizeof(Data)
extern inline Bool moveAccordSize(Link(Void) buffer, Link(Void) source, UInt8 size);

#endif
