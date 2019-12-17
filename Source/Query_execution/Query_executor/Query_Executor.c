#include "Query_Executor.h"
#include "../Query_parser/Query_parser.h"
#include "../Preparator/Preparator.h"
#include "./Filter_Executor/Filter_Executor.h"


struct Tuple{
  uint64_t data;
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

  //3.execute the query based on the preparation
  //execute filters first
  Execute_Filters(New_Table, Parsed_Query);

  //just checking
//  Filter_Ptr Filter = Get_Filter_by_index(Get_Filters(Parsed_Query), 0);
//  int rel = Get_Filter_Relation(Filter);
//  Shell_Ptr Shell = Get_Shell_by_index(Get_Table_Array(New_Table), rel);
//  uint64_t num_of_tuples = Get_num_of_tuples(Shell);
//  uint64_t num_of_columns = Get_num_of_columns(Shell);
//  Tuple_Ptr *Tuples = Get_Shell_Array(Shell);
//  FILE *fp1 = fopen("test1", "w");
//  int j = 0;
//  fprintf(fp1, "REL %d\n", rel);
//  for(int i =0; i< num_of_tuples * num_of_columns;i++){
//    fprintf(fp1,"(%llu)", Tuples[0][i].row_id);
//    fprintf(fp1, "%llu|", Tuples[0][i].data);
//    j++;
//    if(j == num_of_columns) {
//      fprintf(fp1, "\n");
//      j = 0;
//    }
//  }
//  fclose(fp1);
//  Delete_Filter_Outcome(Outcome);
  //1.input the execution tree + the relations we need to
  //2.get the result as an output

  Delete_Queue(Queue);
  Delete_Parsed_Query(Parsed_Query);
  Delete_Table(New_Table);


}

