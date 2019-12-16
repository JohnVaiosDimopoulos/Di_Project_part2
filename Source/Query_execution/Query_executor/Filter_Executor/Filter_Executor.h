#ifndef MULTI_JOIN_FILTER_EXECUTOR_H
#define MULTI_JOIN_FILTER_EXECUTOR_H

#include "stdint.h"
#include "../../Query_parser/Query_parser.h"
#include "../../../Initializer/Table_Allocator/Table_Allocator.h"

struct Tuple{
  uint64_t data;
  uint64_t row_id;
};

typedef struct Tuple* Tuple_Ptr;

Tuple_Ptr* Execute_Filters(Table_Ptr Table, Parsed_Query_Ptr Parsed_Query, int *relations, int num_of_relations);



#endif //MULTI_JOIN_FILTER_EXECUTOR_H
