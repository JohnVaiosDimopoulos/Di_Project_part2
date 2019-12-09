#ifndef MULTI_JOIN_WORK_READER_H
#define MULTI_JOIN_WORK_READER_H

#include "../Argument_Data/Arguments_Data.h"
#include "../Table_Allocator/Table_Allocator.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Batch* Batch_Ptr;
typedef struct Query* Query_Ptr;

void Read_Work_File(Argument_Data_Ptr, Table_Ptr);
int Get_num_of_Queries(Batch_Ptr);
char* Get_Query_Relations(Query_Ptr);
char* Get_Query_Predicates(Query_Ptr);
char* Get_Query_Projections(Query_Ptr);

#endif
