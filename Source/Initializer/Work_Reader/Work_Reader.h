#ifndef MULTI_JOIN_WORK_READER_H
#define MULTI_JOIN_WORK_READER_H

#include "../Argument_Data/Arguments_Data.h"
#include "../Table_Allocator/Table_Allocator.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Batch* Batch_Ptr;
typedef struct Query* Query_Ptr;

void Delete_Batch(Batch_Ptr);
void Delete_Query(Query_Ptr);
Query_Ptr Pop_Next_Query_from_Batch(Batch_Ptr);
Batch_Ptr Read_next_Batch(FILE*);
int Get_num_of_Queries(Batch_Ptr);
char* Get_Query_Relations(Query_Ptr);
char* Get_Query_Predicates(Query_Ptr);
char* Get_Query_Projections(Query_Ptr);

#endif
