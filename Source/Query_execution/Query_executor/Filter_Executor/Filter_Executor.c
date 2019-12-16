#include "Filter_Executor.h"
#include "string.h"

void Delete_Filter_Results(Filter_Result_Ptr Results,int num_of_filters) {
  for(int i=0;i<num_of_filters;i++){
    free(Results[i].row_id);
  }
  free(Results);
}

void Delete_Filter_Outcome(Filters_Outcome_Ptr Outcome){
  Delete_Filter_Results(Outcome->Filter_Result,Outcome->num_of_filters);
  free(Outcome);
}

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

Filters_Outcome_Ptr  Execute_Filters(Table_Ptr Table, Parsed_Query_Ptr Parsed_Query, int *relations, int num_of_relations) {
  int num_of_filters = Get_Num_of_Filters(Parsed_Query);

  if(num_of_filters) {
    Filter_Result_Ptr Array = (Filter_Result_Ptr)malloc(num_of_filters * sizeof(struct Filter_Result));

    for (int i = 0; i < num_of_filters; i++) {
      Filter_Ptr Filter = Get_Filter_by_index(Get_Filters(Parsed_Query), i);
      int rel = relations[Get_Filter_Relation(Filter)];
      Shell_Ptr Shell = Get_Shell_by_index(Get_Table_Array(Table), rel);
      uint64_t num_of_tuples = Get_num_of_tuples(Shell);
      uint64_t num_of_columns = Get_num_of_columns(Shell);

      //allocate array
	  Array[i].relation = rel;
      Array[i].row_id = (uint64_t*)malloc(num_of_tuples * sizeof(uint64_t));
      Array[i].filter_used=0;

      Execute(&Array[i], Shell, Filter);
//      for (int j = Array[i].num_of_results; j < num_of_tuples; j++) {
//        free(&(Array[i].row_id[j]));
//	  }
    }

    Filters_Outcome_Ptr Outcome = (Filters_Outcome_Ptr)malloc(sizeof(struct Filters_Outcome));
    Outcome->num_of_filters=Get_Num_of_Filters(Parsed_Query);
    Outcome->Filter_Result=Array;
    return Outcome;
  }

  printf("QUERY HAS NO FILTERS\n");
  return NULL;
}


int Is_Rel_in_Filter_result_and_not_used(int relation,Filters_Outcome_Ptr Outcome){
  if (Outcome==NULL)
    return 0;
  for(int i =0;i<Outcome->num_of_filters;i++){
    if(Outcome->Filter_Result[i].relation==relation && Outcome->Filter_Result[i].filter_used==0)
      return 1;
  }
  return 0;
}

int Get_Num_of_results(Filters_Outcome_Ptr Outcome,int relation ){
  for(int i =0;i<Outcome->num_of_filters;i++){
    if(Outcome->Filter_Result[i].relation==relation)
      return Outcome->Filter_Result[i].num_of_results;
  }
}




