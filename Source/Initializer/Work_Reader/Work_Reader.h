#ifndef MULTI_JOIN_WORK_READER_H
#define MULTI_JOIN_WORK_READER_H

#include "../Argument_Data/Arguments_Data.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Batch* Batch_Ptr;
typedef struct Query* Query_Ptr;

void Read_Work_File(Argument_Data_Ptr);
void Delete_Batch(Batch_Ptr);

#endif
