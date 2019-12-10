#ifndef MULTI_JOIN_QUERY_PARSER_H
#define MULTI_JOIN_QUERY_PARSER_H

#include "../../Query/Query.h"

typedef struct Parsed_Query* Parsed_Query_Ptr;
typedef struct Join Join_Ptr;
typedef struct Filter Filter_Ptr;

Parsed_Query_Ptr Parse_Query(Query_Ptr);

#endif //MULTI_JOIN_QUERY_PARSER_H
