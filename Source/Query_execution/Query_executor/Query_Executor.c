#include "Query_Executor.h"
#include <string.h>
#include "../Query_parser/Query_parser.h"
#include "../Preparator/Preparator.h"


struct Tuple{
  uint64_t data;
  uint64_t row_id;
};

static void Execute_Filter(Tuple_Ptr *New, Shell_Ptr Shell, Filter_Ptr Filter, FILE *fp) {
  //get filter content
  int rel = Get_Filter_Relation(Filter);
  int col = Get_Filter_Column(Filter);
  char type[2];
  strcpy(type, Get_Type(Filter));
  int con = Get_Constant(Filter);

  int tuples = 0;

  for(int i =0; i < Get_num_of_tuples(Shell); i++){
    Tuple_Ptr current = Get_Shell_Array_by_index(Shell, col, i);
    for(int j =0; j < Get_num_of_columns(Shell); j++) {
      Tuple_Ptr Tuples = Get_Shell_Array_by_index(Shell, j, i);
	  uint64_t data_to_check = Get_Data(current);
	  uint64_t data = Get_Data(Tuples);
	  uint64_t row = Get_Row_id(Tuples);
	  switch(type[0]) {
	  case '<':
        if(data_to_check < con) {
          fprintf(fp, "(%llu)%llu|", row, data);
		  New[0][tuples].data = data;
		  New[0][tuples].row_id = row;
		  tuples++;
		}
        break;
	  case '>':
        if(data_to_check > con) {
          fprintf(fp, "(%llu)%llu|", row, data);
		  New[0][tuples].data = data;
		  New[0][tuples].row_id = row;
		  tuples++;
		}
        break;
	  case '=':
        if(data_to_check ==  con) {
          fprintf(fp, "(%llu)%llu|", row, data);
		  New[0][tuples].data = data;
		  New[0][tuples].row_id = row;
		  tuples++;
		}
        break;
	  }
	}
    fprintf(fp,"\n");
  }
}

static Tuple_Ptr* Execute_Filters(Table_Ptr Table, Parsed_Query_Ptr Parsed_Query, int *relations, int num_of_relations) {
  int num_of_filters = Get_Num_of_Filters(Parsed_Query); 

  if(num_of_filters) {
    FILE *fp = fopen("test", "w");
    Tuple_Ptr *Array;
    for (int i = 0; i < num_of_filters; i++) {
      Filter_Ptr Filter = Get_Filter_by_index(Get_Filters(Parsed_Query), i);

      int rel = relations[Get_Filter_Relation(Filter)];
  //    printf("rel %d\n", rel);
      Shell_Ptr Shell = Get_Shell_by_index(Get_Table_Array(Table), rel);
      uint64_t num_of_tuples = Get_num_of_tuples(Shell);
      uint64_t num_of_columns = Get_num_of_columns(Shell);
      //allocate array
      Array = (Tuple_Ptr*)malloc(num_of_columns * sizeof(Tuple_Ptr));
      Array[0]= (Tuple_Ptr)malloc((num_of_columns * num_of_tuples)* sizeof(struct Tuple));
	  fprintf(fp, "REL %d\n", i);
      Execute_Filter(Array, Shell, Filter, fp);

      //just for checking the array  
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
      fclose(fp);
    }

    return Array;
  } 
  printf("QUERY HAS NO FILTERS\n");
  return NULL;
}

void Execute_Query(Query_Ptr Query, Table_Ptr Table){

  //1.Parse the query
  Parsed_Query_Ptr Parsed_Query = Parse_Query(Query);
  int num_of_relations = Get_Num_of_Relations(Parsed_Query);
  int *relations = Get_Relations(Parsed_Query);
  Execution_Queue_Ptr Queue = Prepare_Execution_Queue(Parsed_Query);
  Print_Queue(Queue);
  Delete_Queue(Queue);


  //execute filters first
  Tuple_Ptr *Array = Execute_Filters(Table, Parsed_Query, relations, num_of_relations);
  
  Delete_Parsed_Query(Parsed_Query);

  //2.do the preparations
    //2.make the execution queue

  //3.execute the query based on the preparation
    //1.input the execution tree + the relations we need to
    //2.get the result as an output

}

