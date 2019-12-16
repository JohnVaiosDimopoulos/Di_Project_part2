#ifndef MULTI_JOIN_FILTER_EXECUTOR_H
#define MULTI_JOIN_FILTER_EXECUTOR_H

#include "stdint.h"
#include "../../Query_parser/Query_parser.h"
#include "../../../Initializer/Table_Allocator/Table_Allocator.h"


struct Filter_Result{
  int relation;
  int filter_used;
  int num_of_results;
  uint64_t * row_id;
};

typedef struct Filter_Result* Filter_Result_Ptr;

Filter_Result_Ptr *Execute_Filters(Table_Ptr, Parsed_Query_Ptr, int *, int);
void Delete_Filter_Result(Filter_Result_Ptr);

#endif //MULTI_JOIN_FILTER_EXECUTOR_H
