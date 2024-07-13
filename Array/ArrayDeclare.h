#ifndef _ARRAYDECLARE_H_
#define	_ARRAYDECLARE_H_

#include "Array.h"

struct _Array
{
	Byte* data;
	Size length, capacity;
};

#define unpackSelf _Array* self = object.self 
#define increaseCapacity(self, val) self->capacity += self->capacity * 3 / 2 + val

#endif