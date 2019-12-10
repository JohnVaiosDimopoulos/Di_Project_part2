#ifndef MULTI_JOIN_TABLE_ALLOCATOR_H
#define MULTI_JOIN_TABLE_ALLOCATOR_H

#include "../Argument_Data/Arguments_Data.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Table_Allocator* Table_AllocatorPtr;
typedef struct Table* Table_Ptr;
typedef struct Shell* Shell_Ptr;

Table_AllocatorPtr Create_Table_Allocator(Argument_Data_Ptr);
Table_Ptr Allocate_Table(Table_AllocatorPtr Table_Allocator);
void Fill_Table(Table_Ptr Table, Table_AllocatorPtr Table_Allocator);

void Print_Table(Table_Ptr);
Shell_Ptr Get_Table_Array(Table_Ptr);


uint64_t Get_num_of_tuples(Shell_Ptr);
uint64_t Get_num_of_columns(Shell_Ptr);

void Delete_Table_Allocator(Table_AllocatorPtr);
void Delete_Table(Table_Ptr);


#endif //MULTI_JOIN_TABLE_ALLOCATOR_H
