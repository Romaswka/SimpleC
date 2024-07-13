#include "ArrayDeclare.h"

const Size ArrayTypeSize = sizeof(struct _Array);

inline Void ArraySetFields(struct _Array* self, Byte* data, Size length, Size capacity)
{
    self->data = data;
    self->capacity = capacity;
    self->length = length;
}

inline Void ArrayDefault(Array object)
{
    unpackSelf;

    ArraySetFields(self, NULL, 0, 0);
}

Bool ArrayInit(Array object, Byte data[], Size bytes)
{
    unpackSelf;

    self->capacity = allocate(to_link(Data, self->data), bytes);

    if(self->capacity != 0)
    {
        self->length = bytes;
        copyData(self->data, 0, data, 0, bytes);
        return True;
    }
    
    self->length = 0;

    return False;
}

inline Bool ArrayOther(Array object, Array other)
{
    return ArrayInit(object, other.self->data, other.self->length);
}

Bool ArrayClear(Array object)
{
    unpackSelf;
    
    if(destroy(to_link(Data, self->data)))
    {
        self->length = self->capacity = 0;
        return True;
    }

    return False;
}

inline Void* ArrayStart(Array object)
{
    return object.self->data;
}

inline const Void* ArrayEnd(Array object)
{
    return object.self->data + object.self->length;
}

inline Bool ArrayAssign(Array object, Byte data[], Size bytes)
{
    if(object.self->data == NULL)
    {
        return ArrayInit(object, data, bytes);
    }
    else if(object.self->capacity >= bytes)
    {
        unpackSelf;
        copyData(self->data, 0, data, 0, bytes);
        return True;
    }
    else
    {
        return ArrayClear(object) && ArrayInit(object, data, bytes);
    }
}

inline Bool ArrayAssignOther(Array object, Array other)
{
    return ArrayAssign(object, other.self->data, other.self->length);
}

inline Void* ArrayReallocate(Array object, Size newSize)
{
    unpackSelf;

    Byte* temp = self->data;
    self->data = NULL;

    Size tempCapacity = self->capacity;
    self->capacity = allocate(to_link(Data, self->data), newSize);

    if (self->capacity != 0)
    {
        return temp;
    }        
    
    self->data = temp;
    self->capacity = tempCapacity;

    return NULL;
}

inline Bool ArrayChangeCapacity_s(Array object, Size newCapacity, Size copy)
{
    unpackSelf;

    Byte* temp = ArrayReallocate(object, newCapacity);

    if(temp == NULL)
    {
        return False;
    }
    
    copyData(self->data, 0, temp, 0, copy);
    return True;
}

inline Bool ArrayPushBack(Array object, Byte pushed[], Size bytes)
{
    unpackSelf;

    if(self->data == NULL)
    {
        return ArrayInit(object, pushed, bytes);
    }  
    else if(self->capacity - self->length < bytes)
    {
        increaseCapacity(self, bytes);
        if(ArrayChangeCapacity_s(object, self->capacity, self->length) == False)
        {
            return False;
        }
    }

    copyData(self->data, self->length, pushed, 0, bytes);

    self->length += bytes;

    return True;
}

inline Bool ArrayPushByte(Array object, Byte pushed)
{
    unpackSelf;

    if (self->data == NULL)
    {
        ArrayReallocate(object, 1);
        if(self->data == NULL)
        {
            return False;
        }
    }
    else if(self->length == self->capacity)
    {
        increaseCapacity(self, 1);
        if(ArrayChangeCapacity_s(object, self->capacity, self->length) == False)
        {
            return False;
        }
    }

    self->data[self->length] = pushed;

    ++self->length;

    return True;
}

inline Bool ArrayPushOther(Array object, Array other)
{
    return ArrayPushBack(object, other.self->data, other.self->length);
}

inline Bool ArrayInsert(Array object, Index place, Byte insertable[], Size bytes)
{
    unpackSelf;

    if(self->length <= place + bytes || bytes == 0)
    {
        return False;
    }

    if(self->capacity - self->length < bytes)
    {
        increaseCapacity(self, bytes);
        
        Byte* temp = ArrayReallocate(object, self->capacity);

        if(temp == NULL)
        {
            return False;
        }

        copyData(self->data, 0, temp, 0, place);
        copyData(self->data, place + bytes, temp, place, self->length - place);
        
        destroy(to_link(Data, temp));
    }
    else
    {
        shiftDataRight(self->data, self->length, place, bytes);
    }
    
    copyData(self->data, place, insertable, 0, bytes);

    self->length += bytes;

    return True;
}

inline Bool ArrayInsertOther(Array object, Index place, Array other)
{
    return ArrayInsert(object, place, other.self->data, other.self->length);
}

inline Bool ArrayPopBack(Array object, Size bytes)
{
    unpackSelf;
    
    if(bytes > self->length)
    {
        return False;
    }

    self->length -= bytes;

    return True;
}

inline Bool ArrayCut(Array object, Index start, Size bytes)
{
    unpackSelf;
    
    if(bytes == 0 || self->length <= start + bytes)
    {
        return False;
    }

    copyData(self->data, start, self->data, start + bytes, self->length - start - bytes);

    self->length -= bytes;

    return True;
}

inline Bool ArrayCutSlice(Array object, Index start, Index end)
{
    unpackSelf;
    
    if(start >= end || end >= self->length || start >= self->length)
    {
        return False;
    }

    copyData(self->data, start, self->data, end, self->length - end);
    
    self->data -= end - start;

    return True;
}

inline Bool ArrayEqualizeCapacity(Array object)
{
    unpackSelf;

    if(self->length == self->capacity)
    {
        return False;
    }

    ArrayChangeCapacity_s(object, self->length, self->length);

    return True;
}

inline Bool ArrayChangeCapacity(Array object, Size newCapacity)
{
    unpackSelf;

    if (newCapacity == self->capacity)
    {
        return False;
    }

    Size copy, temp = self->length;

    if(newCapacity < self->length)
    {
        self->length = copy = newCapacity;
    }
    else
    {
        copy = self->length;
    }

    if(ArrayChangeCapacity_s(object, newCapacity, copy) == False)
    {
        self->length = temp;
        return False;
    }

    return True;
}

inline Bool ArrayPopFront(Array object)
{
    unpackSelf;
    
    if(self->length == 0)
    {
        return False;
    }
    
    copyData(self->data, 0, self->data, 1, self->length - 1);

    --self->length;

    return True;
}

inline Bool ArrayInsertByte(Array object, Index place, Byte insertable)
{
    unpackSelf;
    
    if(place >= self->length)
    {
        return False;
    }

    if(self->capacity == self->length)
    {
        increaseCapacity(self, 1);
        
        Byte* temp = ArrayReallocate(object, self->capacity);
        
        if(temp == NULL)
        {
            return False;
        }

        copyData(self->data, 0, temp, 0, place);
        copyData(self->data, place + 1, temp, place, self->length - place);
    }
    else
    {
        shiftDataRight(self->data, self->length, place, 1);
    }

    self->data[place] = insertable;

    ++self->length;

    return True;
}

inline Bool ArrayCutByte(Array object, Index place)
{
    unpackSelf;
    
    if(self->length <= place)
    {
        return False;
    }

    copyData(self->data, place, self->data, place + 1, self->length - place - 1);

    --self->length;

    return True;
}

inline Byte* ArrayAt(Array object, Index place)
{
    unpackSelf;
    
    if(place >= self->length)
    {
        return NULL;
    }

    return self->data + place;
}

inline Bool ArraySetAt(Array object, Index place, Byte value)
{
    unpackSelf;

    if(place >= self->length)
    {
        return False;
    }

    self->data[place] = value;

    return True;
}

inline Bool ArrayEqual(Array object, Byte data[], Size bytes)
{
    unpackSelf;
    
    if(self->length != bytes)
    {
        return False;
    }

    return equalData(self->data, 0, data, 0, bytes);
}

inline Bool ArrayEqualOther(Array object, Array other)
{
    return ArrayEqual(object, other.self->data, other.self->length);
}
