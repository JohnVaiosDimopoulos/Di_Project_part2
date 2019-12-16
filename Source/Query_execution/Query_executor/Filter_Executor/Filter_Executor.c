#include "Filter_Executor.h"
#include "string.h"


static void Execute(Tuple_Ptr *New, Shell_Ptr Shell, Filter_Ptr Filter) {

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
            New[0][tuples].data = data;
            New[0][tuples].row_id = row;
            tuples++;
          }
          break;
        case '>':
          if(data_to_check > con) {
            New[0][tuples].data = data;
            New[0][tuples].row_id = row;
            tuples++;
          }
          break;
        case '=':
          if(data_to_check ==  con) {
            New[0][tuples].data = data;
            New[0][tuples].row_id = row;
            tuples++;
          }
          break;
      }
    }
//    fprintf(fp,"\n");
  }
}

Tuple_Ptr* Execute_Filters(Table_Ptr Table, Parsed_Query_Ptr Parsed_Query, int *relations, int num_of_relations) {
  int num_of_filters = Get_Num_of_Filters(Parsed_Query);

  if(num_of_filters) {
    Tuple_Ptr *Array;

    for (int i = 0; i < num_of_filters; i++) {
      Filter_Ptr Filter = Get_Filter_by_index(Get_Filters(Parsed_Query), i);
      int rel = relations[Get_Filter_Relation(Filter)];
      printf("rel %d\n", rel);
      Shell_Ptr Shell = Get_Shell_by_index(Get_Table_Array(Table), rel);
      uint64_t num_of_tuples = Get_num_of_tuples(Shell);
      uint64_t num_of_columns = Get_num_of_columns(Shell);

      //allocate array
      Array = (Tuple_Ptr*)malloc(num_of_columns * sizeof(Tuple_Ptr));
      Array[0]= (Tuple_Ptr)malloc((num_of_columns * num_of_tuples)* sizeof(struct Tuple));

      Execute(Array, Shell, Filter);
    }

    return Array;
  }

  printf("QUERY HAS NO FILTERS\n");
  return NULL;
}
