#include "Query_Executor.h"
#include "../Query_parser/Query_parser.h"
#include "../Preparator/Preparator.h"
#include "./Filter_Executor/Filter_Executor.h"

void Execute_Query(Query_Ptr Query, Table_Ptr Table){

  //1.Parse the query
  Parsed_Query_Ptr Parsed_Query = Parse_Query(Query);
  int num_of_relations = Get_Num_of_Relations(Parsed_Query);
  int *relations = Get_Relations(Parsed_Query);


  //2.do the preparations
  Execution_Queue_Ptr Queue = Prepare_Execution_Queue(Parsed_Query);
  Print_Queue(Queue);

  //3.execute the query based on the preparation
  //execute filters first
  Filters_Outcome_Ptr Outcome = Execute_Filters(Table, Parsed_Query, relations, num_of_relations);
  Delete_Filter_Outcome(Outcome);
  //1.input the execution tree + the relations we need to
  //2.get the result as an output

  Delete_Queue(Queue);
  Delete_Parsed_Query(Parsed_Query);


}

