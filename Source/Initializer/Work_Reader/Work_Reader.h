#ifndef MULTI_JOIN_WORK_READER_H
#define MULTI_JOIN_WORK_READER_H

#include "../Argument_Data/Arguments_Data.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Work* Work_Ptr;

Work_Ptr Read_Work_File(Argument_Data_Ptr);
void Delete_Work(Work_Ptr);

#endif
