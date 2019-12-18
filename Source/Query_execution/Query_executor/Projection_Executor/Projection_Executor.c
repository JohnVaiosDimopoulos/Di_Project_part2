#include "Projection_Executor.h"
#include "../Query_Executor.h"
#include "../../Query_parser/Query_parser.h"
#include "../../Preparator/Preparator.h"
#include "../Filter_Executor/Filter_Executor.h"
#include "../Join_Execution/Join_Execution.h"
#include <stdlib.h>

//struct Tuple{
//  uint64_t element;
//  uint64_t row_id;
//};

void Execute_Projections(Intermediate_Result_Ptr Res, Parsed_Query_Ptr Parsed_Query, Table_Ptr Table) {

  int num_of_proj = Get_Num_of_Projections(Parsed_Query);
  Projection_Ptr Proj = Get_Projections(Parsed_Query);
  for(int i = 1; i < num_of_proj; i++) {

    Projection_Ptr current_proj = Get_Proj_by_index(Proj, i);
	int rel = *Get_Projection_Relation(current_proj);
    int col = *Get_Projection_Column(current_proj);

    printf("\n\nproj: %d.%d, ", rel, col);

	if(Res) {

	  int num_of_res = Res->num_of_results;
      printf("num of res = %d\n", num_of_res);
      struct Result** row_ids = Res->row_ids;
      printf("rel in intermediate %d\n", row_ids[0][rel].relation);

      int *Relation = Get_Relations(Parsed_Query);
	  int initial_rel = Relation[rel];
      printf("rel in original array %d\n", initial_rel);


	  Shell_Ptr Shell = Get_Table_Array(Table);
	  Shell_Ptr current_shell = Get_Shell_by_index(Shell, initial_rel);

	  uint64_t sum = 0;

      //if this relation is in the intermediate struct
	  if(Res->relations_in_result[rel]) {
        printf("exists -> %d\n", Res->relations_in_result[rel]);
	    
	    //copy result_row_ids
		uint64_t result_row_ids[num_of_res];
        for(int j = 0; j < num_of_res; j++){
          result_row_ids[j] = row_ids[j][rel].row_id;
//          printf("row_id (intermdt) %d ", result_row_ids[j]);
	      Tuple_Ptr current_tuple = Get_Shell_Array_by_index(current_shell, col, result_row_ids[j]);
	      sum += current_tuple->element;
//          printf("table-> %llu %llu sum:%llu\n", current_tuple->row_id, current_tuple->element, sum);
      }
	  // get the sum from the array
	  } else {
        
        printf("doesnt exist\n");
		return;
      }
      printf("%llu\n", sum);

    } else printf("NULL\n");
  }
}
