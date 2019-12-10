#ifndef MULTI_JOIN_QUERY_PARSER_H
#define MULTI_JOIN_QUERY_PARSER_H

#include "../../Query/Query.h"

typedef struct Parsed_Query* Parsed_Query_Ptr;
typedef struct Join* Join_Ptr;
typedef struct Filter* Filter_Ptr;

Parsed_Query_Ptr Parse_Query(Query_Ptr);

//Parsed_Query Accessors//
Join_Ptr Get_Joins(Parsed_Query_Ptr Parsed_Query);
Filter_Ptr Get_Filters(Parsed_Query_Ptr Parsed_Query);

//Filter Accessors//
int Get_Relation(Filter_Ptr Filter);
int Get_Column(Filter_Ptr Filter);
int Get_Amount(Filter_Ptr Filter);
char* Get_Type(Filter_Ptr Filter);

//Join Accessors//
int Get_Relation_1(Join_Ptr Join);
int Get_Column_1(Join_Ptr Join);
int Get_Relation_2(Join_Ptr Join);
int Get_Column_2(Join_Ptr Join);

#endif //MULTI_JOIN_QUERY_PARSER_H
