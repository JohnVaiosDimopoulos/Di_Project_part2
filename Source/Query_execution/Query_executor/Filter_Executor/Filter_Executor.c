#include "Filter_Executor.h"
#include "string.h"

struct Tuple{
  uint64_t data;
  uint64_t row_id;
};

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

static int Execute(Tuple_Ptr *New, Shell_Ptr Shell, Filter_Ptr Filter, FILE *fp) {

  //get filter content
  int rel = Get_Filter_Relation(Filter);
  int col = Get_Filter_Column(Filter);
  char type[2];
  strcpy(type, Get_Type(Filter));
  int con = Get_Constant(Filter);

  int cnt = 0;
  for(int i =0; i < Get_num_of_tuples(Shell); i++){

    Tuple_Ptr current = Get_Shell_Array_by_index(Shell, col, i);
	for(int j =0; j < Get_num_of_columns(Shell); j++) {
	  uint64_t data_to_check = Get_Data(current);
      Tuple_Ptr Tuples = Get_Shell_Array_by_index(Shell, j, i);
	  uint64_t data = Get_Data(Tuples);
      uint64_t row = Get_Row_id(Tuples);
      switch(type[0]) {
        case '<':
          if(data_to_check < con) {
            New[0][cnt].data = data;
            New[0][cnt].row_id = row;
            cnt++;
          }
          break;
        case '>':
          if(data_to_check > con) {
            New[0][cnt].data = data;
            New[0][cnt].row_id = row;
			cnt++;
          }
          break;
        case '=':
          if(data_to_check ==  con) {
            New[0][cnt].data = data;
            New[0][cnt].row_id = row;
			cnt++;
          }
          break;
      }
	}
  }
  cnt /=  Get_num_of_columns(Shell);
  return cnt;
}

void Execute_Filters(Table_Ptr Table, Parsed_Query_Ptr Parsed_Query) {
  int num_of_filters = Get_Num_of_Filters(Parsed_Query);

  if(num_of_filters) {
	FILE *fp = fopen("test", "w");
    for (int i = 0; i < num_of_filters; i++) {
      Filter_Ptr Filter = Get_Filter_by_index(Get_Filters(Parsed_Query), i);
      int rel = Get_Filter_Relation(Filter);
      Shell_Ptr Shell = Get_Shell_by_index(Get_Table_Array(Table), rel);
      uint64_t num_of_tuples = Get_num_of_tuples(Shell);
      uint64_t num_of_columns = Get_num_of_columns(Shell);

      //allocate array
      Tuple_Ptr *New = (Tuple_Ptr*)malloc(num_of_columns * sizeof(Tuple_Ptr));
      New[0]= (Tuple_Ptr)malloc((num_of_columns * num_of_tuples)* sizeof(struct Tuple));

      int tuples = Execute(New, Shell, Filter, fp);
      Tuple_Ptr *temp = Get_Shell_Array(Shell);
	  Set_Shell_Array(Shell, New);
	  Set_Shell_num_of_tuples(Shell, tuples);
	  //delete old shell
      free(temp[0]);
      free(temp);

	  //just for checking
//	  int j = 0;
//      fprintf(fp, "REL %d\n", rel);
//      for(int i =0; i< tuples * num_of_columns;i++){
//        fprintf(fp,"(%llu)", New[0][i].row_id);
//        fprintf(fp, "%llu|", New[0][i].data);
//        j++;
//        if(j == num_of_columns) {
//          fprintf(fp, "\n");
//          j = 0;
//        }
//      }
    }
	fclose(fp);
	return;
  }
  printf("QUERY HAS NO FILTERS\n");
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


uint64_t* Get_Filter_Results(Filters_Outcome_Ptr Outcome){
  return Outcome->Filter_Result->row_id;
}
