#ifndef MULTI_JOIN_TABLE_ALLOCATOR_H
#define MULTI_JOIN_TABLE_ALLOCATOR_H

#include "../Argument_Data/Arguments_Data.h"

typedef struct Table_Allocator* Table_AllocatorPtr;
typedef struct Table* Table_Ptr;
typedef struct Shell* Shell_Ptr;

Table_AllocatorPtr Create_Table_Allocator(Argument_Data_Ptr);
int Get_num_of_Tables(Table_AllocatorPtr);
//const char* Get_Table_FileName(Table_AllocatorPtr);
//const char* Get_Table_DirName(Table_AllocatorPtr);
void Delete_Table_Allocator(Table_AllocatorPtr);

Table_Ptr Create_Table(Table_AllocatorPtr);
int Get_Table_Data(Table_Ptr);
void Delete_Table(Table_Ptr);

//struct Shell Create_Shell(Table_Ptr, const char*);
Shell_Ptr Create_Shell(Table_Ptr, const char*);

void Delete_Shell(Shell_Ptr);


#endif //MULTI_JOIN_TABLE_ALLOCATOR_H
