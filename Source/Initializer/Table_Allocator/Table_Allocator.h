#ifndef MULTI_JOIN_TABLE_ALLOCATOR_H
#define MULTI_JOIN_TABLE_ALLOCATOR_H

#include "../Argument_Data/Arguments_Data.h"

typedef struct Table_Allocator* Table_AllocatorPtr;

Table_AllocatorPtr Create_Table_Allocator(Argument_Data_Ptr);
void Delete_Table_Allocator(Table_AllocatorPtr);


#endif //MULTI_JOIN_TABLE_ALLOCATOR_H
