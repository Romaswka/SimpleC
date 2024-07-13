#include "STD_CFunctions.h"

inline Size cstringLength(CString cstr)
{
	Size length = 0;
	while (cstr[length] != '\0')
	{
		++length;
	}
	return length;
}

inline Void copyData(Byte buffer[], Index bufferStart, Byte source[], Index sourceStart, Size byteSize)
{
	buffer += bufferStart;
	source += sourceStart;
	while(byteSize >= sizeof(Data))
	{
		byteSize -= sizeof(Data);
		*(Data*)(buffer + byteSize) = *(Data*)(source + byteSize);
	}
	if(byteSize >= sizeof(UInt32))
	{
		byteSize -= sizeof(UInt32);
		*(UInt32*)(buffer + byteSize) = *(UInt32*)(source + byteSize);
	}
	if(byteSize >= sizeof(UInt16))
	{
		byteSize -= sizeof(UInt16);
		*(UInt16*)(buffer + byteSize) = *(UInt16*)(source + byteSize);
	}
	if (byteSize != 0)
	{
		*buffer = *source;
	}
}

inline Void shiftDataRight(Byte buffer[], Size dataSize, Index shiftFrom, Size shiftTo)
{
	Size byteSize = dataSize - shiftFrom;

	if(shiftTo >= byteSize)
	{
		copyData(buffer, dataSize - 1 + shiftTo, buffer, shiftFrom, byteSize);
		return;
	}

	buffer += dataSize;

	while (byteSize >= sizeof(Data))
	{
		*(Data*)(buffer + shiftTo - sizeof(Data)) = *(Data*)(buffer - sizeof(Data));
		byteSize -= sizeof(Data);
		buffer -= sizeof(Data);
	}
	if (byteSize >= sizeof(UInt32))
	{
		*(UInt32*)(buffer + shiftTo - sizeof(UInt32)) = *(UInt32*)(buffer - sizeof(UInt32));
		byteSize -= sizeof(UInt32);
		buffer -= sizeof(UInt32);
	}
	if(byteSize >= sizeof(UInt16))
	{
		*(UInt16*)(buffer + shiftTo - sizeof(UInt16)) = *(UInt16*)(buffer - sizeof(UInt16));
		byteSize -= sizeof(UInt16);
		buffer -= sizeof(UInt16);
	}
	if(byteSize != 0)
	{
		*(buffer + 1) = *(buffer - 1);
	}
}

inline Size SizeToCString(Size value, CString buffer)
{
	if(value < 10)
	{
		buffer[0] = (Char)value + '0';
		buffer[1] = '\0';
		return 1;
	}

	Index i = 0;

	while (value != 0)
	{
		buffer[i] = value % 10 + '0';
		value /= 10;
		++i;
	}

	buffer[i] = '\0';
	
	swapBytes(buffer, i - 1);

	return i;
}

inline Size IntToCString(IntMax value, CString buffer)
{
	Bool neg = False;
	if(value < 0)
	{
		neg = True;
		buffer[0] = '-';
		++buffer;
		value = -value;
	}

	return SizeToCString(value, buffer) + neg;
}

inline Void swapBytes(Byte buffer[], Index bufferEnd)
{
	Char temp;
	for(Index i = 0; i < bufferEnd; ++i)
	{
		temp = buffer[i];
		buffer[i] = buffer[bufferEnd];
		buffer[bufferEnd] = temp;
		--bufferEnd;
	}
}

inline Size calculateCountDigits(Float64 value)
{
	Size digits = 1;
	while (value > 9.0)
	{
		value /= 10;
		++digits;
	}
	return digits;
}

inline Float64 pow(Float64 value, Size times)
{
	if(value == 1 || times == 0)
	{ 
		return 1;
	}
	if(value == 0 || times == 1)
	{
		return value;
	}

	Float64 temp = value;

	for(Size i = 1; i < times; ++i)
	{
		value *= temp;
	}

	return value;
}

inline Size FloatToCString(Float64 value, CString buffer, Size accuracy)
{
	Index endWholePart, i = 0;
	Bool addExponent = False;
	Size digitsCount, resultSize;

	if(value < 0.0)
	{
		buffer[0] = '-';
		++buffer;
		value = -value;
	}
	if(value < 1.0)
	{
		buffer[0] = '0';
		endWholePart = 1;
	}
	else if(value - (Float64)SIZE_MAX < 1.0)
	{
		endWholePart = SizeToCString((Size)value, buffer);
	}
	else
	{	
		addExponent = True;
		digitsCount = calculateCountDigits(value);
		value /= pow(10.0, digitsCount);
		buffer[0] = (Size)value % 10 + '0';
		endWholePart = 1;
	}

	resultSize = endWholePart;

	if (value != (Size)value && accuracy != 0)
	{
		buffer[endWholePart] = '.';

		++endWholePart;

		while (i < accuracy && value > 0.0)
		{
			value *= 10;
			buffer[endWholePart + i] = (Size)value % 10 + '0';
			value -= (Size)value;
			++i;
		}

		resultSize += i + 1;

		if (addExponent)
		{
			buffer[resultSize] = 'e';
			buffer[resultSize + 1] = '+';

			resultSize += SizeToCString(digitsCount, buffer + resultSize + 2) + 2;
		}
	}

	buffer[resultSize] = '\0';

	return resultSize;
}

inline CString findÑoincidence(CString buffer, Size bufferSize, CString find, Size findSize)
{
	Index j;

	Size end = bufferSize - findSize + 1;

	for (Index i = 0; i < end; ++i)
	{
		for (j = 0; j < findSize; ++j)
		{
			if (buffer[i + j] != find[j])
			{
				break;
			}
		}

		if (j == findSize)
		{
			return buffer + i;
		}
	}

	return NULL;
}

inline CString findFirst(CString buffer, Size bufferSize, Char find)
{
	CString iterator = buffer, end = buffer + bufferSize;
	while (iterator < end && *iterator != find)
	{
		++iterator;
	}

	if(*iterator == find)
	{
		return iterator;
	}

	return NULL;
}

inline Bool moveAccordSize(Link(Void) buffer, Link(Void) source, UInt8 size)
{
	if(size > sizeof(Data) || size == 0)
	{
		return False;
	}

	if(size == sizeof(Data))
	{
		*((Data*)buffer.object) = *((Data*)source.object);
		size -= sizeof(Data);
	}

	if(size >= sizeof(UInt32))
	{
		*((UInt32*)buffer.object) = *((UInt32*)source.object);
		size -= sizeof(UInt32);
	}

	if (size >= sizeof(UInt16))
	{
		*((UInt16*)buffer.object) = *((UInt16*)source.object);
		size -= sizeof(UInt16);
	}

	if(size != 0)
	{
		*((UInt8*)buffer.object) = *((UInt8*)source.object);
		size -= sizeof(UInt8);
	}

	return True;
}

inline Bool equalData(Byte buffer[], Index bufferStart, Byte source[], Index sourceStart, Size bytes)
{
	buffer += bufferStart;
	source += sourceStart;

	while (bytes >= sizeof(Data))
	{
		if(*(Data*)buffer != *(Data*)source)
		{
			return False;
		}
		bytes -= sizeof(Data);
		buffer += sizeof(Data);
		source += sizeof(Data);
	}
	if (bytes >= sizeof(UInt32))
	{
		if (*(UInt32*)buffer != *(UInt32*)source)
		{
			return False;
		}
		bytes -= sizeof(UInt32);
		buffer += sizeof(UInt32);
		source += sizeof(UInt32);
	}
	while (bytes >= sizeof(UInt16))
	{
		if (*(UInt16*)buffer != *(UInt16*)source)
		{
			return False;
		}
		bytes -= sizeof(UInt16);
		buffer += sizeof(UInt16);
		source += sizeof(UInt16);
	}
	if(bytes != 0 && *buffer != *source)
	{
		return False;
	}

	return True;
}
