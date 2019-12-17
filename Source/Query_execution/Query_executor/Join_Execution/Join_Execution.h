#ifndef MULTI_JOIN_JOIN_EXECUTION_H
#define MULTI_JOIN_JOIN_EXECUTION_H

#include "../../Execution_Queue/Execution_Queue.h"
#include "../Filter_Executor/Filter_Executor.h"
//#include "./Intermediate_Result/Intermediate_Result.h"

void Execute_Joins(Execution_Queue_Ptr Execution_Queue,Filter_Result_Ptr Filter_Results,Table_Ptr Relations,int* relation_map);


#endif //MULTI_JOIN_JOIN_EXECUTION_H
