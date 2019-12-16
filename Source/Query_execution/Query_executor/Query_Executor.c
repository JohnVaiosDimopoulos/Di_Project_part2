#include "Query_Executor.h"
#include "../Query_parser/Query_parser.h"
#include "../Preparator/Preparator.h"
#include "./Filter_Executor/Filter_Executor.h"

//      FILE *fp1 = fopen("test1", "w");
//      int j = 0;
//      for(int i =0;i< num_of_tuples * num_of_columns;i++) {
//        fprintf(fp1,"(%llu)", Array[0][i].row_id);
//        fprintf(fp1, "%llu|", Array[0][i].data);
//        j++;
//        if(j == num_of_columns) {
//          fprintf(fp1, "\n");
//          j = 0;
//        }
//      }
//      fclose(fp1);

void Execute_Query(Query_Ptr Query, Table_Ptr Table){

  //1.Parse the query
  Parsed_Query_Ptr Parsed_Query = Parse_Query(Query);
  int num_of_relations = Get_Num_of_Relations(Parsed_Query);
  int *relations = Get_Relations(Parsed_Query);


  //execute filters first
  //2.do the preparations
  Execution_Queue_Ptr Queue = Prepare_Execution_Queue(Parsed_Query);
  Print_Queue(Queue);

  //3.execute the query based on the preparation
  //Tuple_Ptr *Array = Execute_Filters(Table, Parsed_Query, relations, num_of_relations);
  Filter_Result_Ptr *Array = Execute_Filters(Table, Parsed_Query, relations, num_of_relations);
  //1.input the execution tree + the relations we need to
  //2.get the result as an output

  Delete_Queue(Queue);
  Delete_Parsed_Query(Parsed_Query);


}

