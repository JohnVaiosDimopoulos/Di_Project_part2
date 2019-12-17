#ifndef MULTI_JOIN_JOIN_EXECUTION_H
#define MULTI_JOIN_JOIN_EXECUTION_H

#include "../../Execution_Queue/Execution_Queue.h"
#include "../Filter_Executor/Filter_Executor.h"
//#include "./Intermediate_Result/Intermediate_Result.h"

void Execute_Joins(Execution_Queue_Ptr Execution_Queue,Table_Ptr Relations);


#endif //MULTI_JOIN_JOIN_EXECUTION_H
