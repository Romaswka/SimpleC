#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <Preparings.h>

struct _Array;

typedef struct _Array _Array;

typedef union
{
	const _Array *const self;
} Array;

const Size ArrayTypeSize;

#define dA(name) name = (Array){(Data[3]) {}}

#define defineIteratorType(type) typedef type* connect(Iterator, type)

#define ArrayIterator(type) connect(Iterator, type)

#define ATI(type, object) ((ArrayIterator(type)) ArrayStart(object))

extern inline Void ArrayDefault(Array object);

extern inline Bool ArrayInit(Array object, Byte data[], Size bytes);

extern inline Bool ArrayOther(Array object, Array other);

extern inline Bool ArrayClear(Array object);

extern inline Void* ArrayStart(Array object);

extern inline const Void* ArrayEnd(Array object);

extern inline Bool ArrayAssign(Array object, Byte data[], Size bytes);

extern inline Bool ArrayAssignOther(Array object, Array other);

extern inline Bool ArrayPushBack(Array object, Byte pushed[], Size bytes);

extern inline Bool ArrayPushByte(Array object, Byte pushed);

extern inline Bool ArrayPushOther(Array object, Array other);

extern inline Bool ArrayInsert(Array object, Index place, Byte insertable[], Size bytes);

extern inline Bool ArrayInsertOther(Array object, Index place, Array other);

extern inline Bool ArrayPopBack(Array object, Size bytes);

extern inline Bool ArrayCut(Array object, Index start, Size bytes);

extern inline Bool ArrayCutSlice(Array object, Index start, Index end);

extern inline Bool ArrayEqualizeCapacity(Array object);

extern inline Bool ArrayChangeCapacity(Array object, Size newCapacity);

extern inline Bool ArrayPopFront(Array object);

extern inline Bool ArrayInsertByte(Array object, Index place, Byte insertable);

extern inline Bool ArrayCutByte(Array object, Index place);

extern inline Byte* ArrayAt(Array object, Index place);

extern inline Bool ArraySetAt(Array object, Index place, Byte value);

extern inline Bool ArrayEqual(Array object, Byte data[], Size bytes);

extern inline Bool ArrayEqualOther(Array object, Array other);

#endif