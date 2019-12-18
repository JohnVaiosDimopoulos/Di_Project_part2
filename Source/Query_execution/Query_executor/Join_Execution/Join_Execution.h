#ifndef MULTI_JOIN_JOIN_EXECUTION_H
#define MULTI_JOIN_JOIN_EXECUTION_H

#include "../../Execution_Queue/Execution_Queue.h"
#include "../Filter_Executor/Filter_Executor.h"

struct Result{
  int relation;
  uint64_t row_id;
};

struct Rel_Tuple{
  struct Result* row_ids;
  uint64_t value;
};

struct Intermediate_Result{
  int relations_in_result[4];
  int num_of_results;
  int num_of_relations;
  struct Result** row_ids;
};

typedef struct Intermediate_Result* Intermediate_Result_Ptr;


Intermediate_Result_Ptr Execute_Joins(Execution_Queue_Ptr Execution_Queue, Table_Ptr Relations);
void Print_Intermediate(Intermediate_Result_Ptr Intermediate_Result);
void Delete_intermediate_Result(Intermediate_Result_Ptr Intermediate_Result);



#endif //MULTI_JOIN_JOIN_EXECUTION_H
