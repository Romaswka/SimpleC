#ifndef _PREPARINGS_H_

#define _PREPARINGS_H_

#include <DataTypes.h>

#include <STD_CFunctions.h>

Size(* const allocate)(Link(Data) buffer, Size bytesCount);

Bool(* const destroy)(Link(Data) buffer);

#define setAllocate(fun) Size(* const allocate)(Link(Data) buffer, Size bytesCount) = fun

#define setDestroy(fun) Bool(* const destroy)(Link(Data) buffer) = fun

#endif