#include "Query_Executor.h"
#include "../Query_parser/Query_parser.h"
#include "../Preparator/Preparator.h"
#include "./Filter_Executor/Filter_Executor.h"
#include "./Join_Execution/Join_Execution.h"


struct Tuple{
  uint64_t element;
  uint64_t row_id;
};


void Execute_Query(Query_Ptr Query, Table_Ptr Table){

  //1.Parse the query
  Parsed_Query_Ptr Parsed_Query = Parse_Query(Query);
  int num_of_relations = Get_Num_of_Relations(Parsed_Query);
  int *relations = Get_Relations(Parsed_Query);


  //2.do the preparations
  Execution_Queue_Ptr Queue = Prepare_Execution_Queue(Parsed_Query);
  Print_Queue(Queue);
  Table_Ptr New_Table = Make_Table_For_Joins(Table,relations,num_of_relations);

  //execute filters first
  Execute_Filters(New_Table, Parsed_Query);

  //execute joins
  Execute_Joins(Queue,New_Table);

  Delete_Queue(Queue);
  Delete_Parsed_Query(Parsed_Query);
  Delete_Table(New_Table);


}

