#ifndef SORT_JOIN_UTILITIES_H
#define SORT_JOIN_UTILITIES_H
#include <stdio.h>
#include <stdint.h>
char* Allocate_and_Copy_Str(const char*);
int Open_File_for_Read(FILE**,const char*);
int Open_File_for_Write(FILE**,const char*);
int generic_swap(void*,void*,int);
const char* construct_Path(const char* , const char*);
#endif //SORT_JOIN_UTILITIES_H
