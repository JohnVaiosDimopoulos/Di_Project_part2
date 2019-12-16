#include "Join_Execution.h"
#include "../Filter_Executor/Filter_Executor.h"
#include <stdlib.h>

struct Tuple{
  uint64_t value;
  uint64_t row_id;
};

typedef struct Tuple* Tuple_ptr;


static int Is_rel_in_intermediate_result(Intermediate_Result_ptr Intermediate_Result,int relation){
  if(Intermediate_Result==NULL)
    return 0;
  for(int i =0;i<Intermediate_Result->num_of_relations_in_result;i++){
    if(Intermediate_Result->relations_in_the_result[i]==relation)
      return 1;
  }

  return 0;
}

static void Execute_Self_Join(Join_Ptr Join,Filters_Outcome_Ptr Filter_Outcome,Intermediate_Result_ptr Intermediate_Result) {

  Tuple_ptr Array1,Array2;

  if(Is_Rel_in_Filter_result_and_not_used(Get_Relation_1(Join),Filter_Outcome)){

    int size = Get_Num_of_results(Filter_Outcome,Get_Relation_1(Join));
    Array1 = (Tuple_ptr)malloc(size*sizeof(struct Tuple));
    Array2 = (Tuple_ptr)malloc(size*sizeof(struct Tuple));

    for(int i =0;i<size;i++){
      Array1[i]
    }

  }
  else if (Is_rel_in_intermediate_result(Intermediate_Result,Get_Relation_1(Join))){
    Array1=(Tuple_ptr)malloc(Intermediate_Result->num_of_results* sizeof(struct Tuple));
    Array2=(Tuple_ptr)malloc(Intermediate_Result->num_of_results* sizeof(struct Tuple));


  }

/*
   for(int i =0;i<num_of_rows;i++){
    if(col1.value == col2.value)
      result.insert(rows[i]);
   }

   return result;
*/
}

static int Check_if_relations_already_in_result(Join_Ptr Join,Intermediate_Result_ptr Intermediate_Result){
/*    if(Is_in_result(Rel1) && Is_in_result(Rel2))
         return 1;
    return 0*/
}

static void Execute_Scan_Join(Join_Ptr Join,Intermediate_Result_ptr old_result){
/*
 * also input the intermediate result as old_result;
 * Make row_id/value pairs for rel1 based on join column=  t1(rid|v)
 * Make row_id/value paits for rel2 based on join column=  t2(rid|v)
 * result new_result;
 * for(int i=0;i<num_of_rows_of_the_result;i++){
 *  row_tuple = old_res[i];
 *  if(t1[row_pair[1]==t2[row_pair[2]){
 *  new_result.insert(row_pair);
 *  }
 * }
*/
}


void Execute_Joins(Execution_Queue_Ptr Execution_Queue,Filter_Result_Ptr Filter_Results,Table_Ptr Relations){

  Intermediate_Result_ptr Intermediate_Result = NULL;
  Join_Ptr Last_Join = NULL;
  // we will also keep the data of the last join;

  for(Join_Ptr Current_Join = Pop_Next_join(Execution_Queue);
      Current_Join!=NULL;
      Current_Join=Pop_Next_join(Execution_Queue)){

    if(Is_Self_Join(Current_Join))
      Execute_Self_Join(Current_Join,Filter_Results,Intermediate_Result);

    else if(Check_if_relations_already_in_result(Current_Join,Intermediate_Result))
        Execute_Scan_Join(Current_Join,Intermediate_Result);

    else if (Is_Same_Column_used(Last_Join,Current_Join)){}
      //execute join with same column

    else{
      //normal_join
    }

  }

}