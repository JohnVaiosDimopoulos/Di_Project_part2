#ifndef MULTI_JOIN_JOIN_EXECUTION_H
#define MULTI_JOIN_JOIN_EXECUTION_H

#include "../../Execution_Queue/Execution_Queue.h"
#include "../Filter_Executor/Filter_Executor.h"

void Execute_Joins(Execution_Queue_Ptr Execution_Queue,Filter_Result_Ptr Filter_Results);

#endif //MULTI_JOIN_JOIN_EXECUTION_H
