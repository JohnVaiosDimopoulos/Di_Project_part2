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

struct Filters_Outcome{
  int num_of_filters;
  Filter_Result_Ptr Filter_Result;
};

typedef struct Filters_Outcome* Filters_Outcome_Ptr;


int Is_Rel_in_Filter_result_and_not_used(int relation,Filters_Outcome_Ptr Outcome);
int Get_Num_of_results(Filters_Outcome_Ptr,int);

//Filters_Outcome_Ptr Execute_Filters(Table_Ptr, Parsed_Query_Ptr, int *, int);
void Execute_Filters(Table_Ptr, Parsed_Query_Ptr);
void Delete_Filter_Results(Filter_Result_Ptr Results,int num_of_filters);
void Delete_Filter_Outcome(Filters_Outcome_Ptr Outcome);

uint64_t* Get_Filter_Results(Filters_Outcome_Ptr Outcome);


#endif //MULTI_JOIN_FILTER_EXECUTOR_H
