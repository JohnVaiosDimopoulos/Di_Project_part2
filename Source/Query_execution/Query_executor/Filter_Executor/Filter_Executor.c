#include "Filter_Executor.h"
#include "string.h"


static void Execute(Filter_Result_Ptr Results, Shell_Ptr Shell, Filter_Ptr Filter) {

  //get filter content
  int rel = Get_Filter_Relation(Filter);
  int col = Get_Filter_Column(Filter);
  char type[2];
  strcpy(type, Get_Type(Filter));
  int con = Get_Constant(Filter);

  int tuples = 0;

  for(int i =0; i < Get_num_of_tuples(Shell); i++){

    Tuple_Ptr current = Get_Shell_Array_by_index(Shell, col, i);
    uint64_t data_to_check = Get_Data(current);
    Tuple_Ptr Tuples = Get_Shell_Array_by_index(Shell, 0, i);
    uint64_t row = Get_Row_id(Tuples);

    switch(type[0]) {
      case '<':
        if(data_to_check < con) {
          Results->row_id[tuples] = row;
          tuples++;
        }
        break;
      case '>':
        if(data_to_check > con) {
          Results->row_id[tuples] = row;
          tuples++;
        }
        break;
      case '=':
        if(data_to_check ==  con) {
          Results->row_id[tuples] = row;
          tuples++;
        }
        break;
    }
  }
  Results->num_of_results = tuples;
}

Filter_Result_Ptr* Execute_Filters(Table_Ptr Table, Parsed_Query_Ptr Parsed_Query, int *relations, int num_of_relations) {
  int num_of_filters = Get_Num_of_Filters(Parsed_Query);

  if(num_of_filters) {
    Filter_Result_Ptr *Array = (Filter_Result_Ptr*)malloc(num_of_filters * sizeof(Filter_Result_Ptr));

    for (int i = 0; i < num_of_filters; i++) {
      Filter_Ptr Filter = Get_Filter_by_index(Get_Filters(Parsed_Query), i);
      int rel = relations[Get_Filter_Relation(Filter)];
      Shell_Ptr Shell = Get_Shell_by_index(Get_Table_Array(Table), rel);
      uint64_t num_of_tuples = Get_num_of_tuples(Shell);
      uint64_t num_of_columns = Get_num_of_columns(Shell);

      //allocate array
      Array[i] = (Filter_Result_Ptr)malloc(sizeof(struct Filter_Result));
	  Array[i]->relation = rel;
	  Array[i]->filter_used=0;
      Array[i]->row_id = (uint64_t*)malloc(num_of_tuples * sizeof(uint64_t));

      Execute(Array[i], Shell, Filter);
    }
    return Array;
  }

  printf("QUERY HAS NO FILTERS\n");
  return NULL;
}
