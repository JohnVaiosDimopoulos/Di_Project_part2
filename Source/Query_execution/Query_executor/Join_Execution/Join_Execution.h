#ifndef MULTI_JOIN_JOIN_EXECUTION_H
#define MULTI_JOIN_JOIN_EXECUTION_H

#include "../../Execution_Queue/Execution_Queue.h"
#include "../Filter_Executor/Filter_Executor.h"

struct Result_Node{
  uint64_t * row_ids;
  int relation;
};

typedef struct Result_Node* Result_Node_Ptr;

struct Intermediate_Result{
  uint64_t * relations_in_the_result;
  int num_of_results;
  int num_of_relations_in_result;
  Result_Node_Ptr Rows
};

typedef struct Intermediate_Result* Intermediate_Result_ptr;






void Execute_Joins(Execution_Queue_Ptr Execution_Queue,Filter_Result_Ptr Filter_Results,Table_Ptr Relations);


#endif //MULTI_JOIN_JOIN_EXECUTION_H
