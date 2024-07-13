#ifndef _DATATYPES_H_

#define _DATATYPES_H_

#include <stdint.h>

typedef void Void;

typedef int8_t Int8;
typedef int16_t Int16;
typedef int32_t Int32;
typedef int64_t Int64;

typedef uint8_t UInt8;
typedef uint16_t UInt16;
typedef uint32_t UInt32;
typedef uint64_t UInt64;

typedef intmax_t IntMax;
typedef uintmax_t Size;

#define abs(val) ((val) >= 0 ? (val) : (-(val)))

typedef _Bool Bool;
#define True 1
#define False 0

typedef float Float32;
typedef double Float64;

typedef char Char;
typedef char* CString;

typedef UInt8 IOType;

typedef void* Data;
typedef Size Index;
typedef UInt8 Byte;

#define connect(A, B) A##B
#define defineLinkType(type) typedef union {type* const object;} connect(Link, type)
#define Link(type) connect(Link, type)
#define RValue(type, ...) ((type[]){__VA_ARGS__})
#define to_obj(link) (*(link.object))
#define to_link(type, var) (connect(Link, type)){(&(var))}
#define null(type) (connect(Link, type)){NULL}
#define DL(link) to_link(Data, (link).object)
#define function(return_type, name, ...) return_type(*name)(__VA_ARGS__)

defineLinkType(Void);
defineLinkType(Data);

defineLinkType(Char);

defineLinkType(Int8);
defineLinkType(Int16);
defineLinkType(Int32);
defineLinkType(Int64);

defineLinkType(UInt8);
defineLinkType(UInt16);
defineLinkType(UInt32);
defineLinkType(UInt64);

defineLinkType(IntMax);
defineLinkType(Size);

defineLinkType(Bool);

defineLinkType(Float32);
defineLinkType(Float64);

defineLinkType(Byte);
defineLinkType(Index);

#ifdef _FORBID_C_TYPES_

#define int _forbidden_type_
#define char _forbidden_type_
#define float _forbidden_type_
#define unsigned _forbidden_type_
#define long _forbidden_type_
#define double _forbidden_type_
#define short _forbidden_type_
#define void _forbidden_type_
#define _Bool _forbidden_type_

#endif

#endif