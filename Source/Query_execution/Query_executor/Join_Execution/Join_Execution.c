#include "Join_Execution.h"
#include <stdlib.h>





static void Execute_Self_Join(Join_Ptr Join,Filter_Result_Ptr Filter_Results) {
/*
    if(is in the filters result and the filter is not used yet){
        get the row_ids/value for each column based on the filter
    }

    else if(is the relation in the indermediate result){
      get the row_ids/value for each column based on the result
    }


   for(int i =0;i<num_of_rows;i++){
    if(col1.value == col2.value)
      result.insert(rows[i]);
   }

   return result;*/
}

static int Check_if_relations_already_in_result(Join_Ptr Join){
/*    if(Is_in_result(Rel1) && Is_in_result(Rel2))
         return 1;
    return 0*/
}

static void Execute_Scan_Join(Join_Ptr Join){
/*
 * also input the intermediate result as old_result;
 * Make row_id/value pairs for rel1 based on join column=t1 (rid|v)
 * Make row_id/value paits for rel2 based on join column=t2 (rid|v)
 * result new_result;
 * for(int i=0;i<num_of_rows_of_the_result;i++){
 *  row_tuple = old_res[i];
 *  if(t1[row_pair[1]==t2[row_pair[2]){
 *  new_result.insert(row_pair);
 *  }
 * }


*/
}



void Execute_Joins(Execution_Queue_Ptr Execution_Queue,Filter_Result_Ptr Filter_Results){

  // if at any point we get a null result return null
  Join_Ptr Last_Join = NULL;
  // we will also keep the data of the last join;

  for(Join_Ptr Current_Join = Pop_Next_join(Execution_Queue);
      Current_Join!=NULL;
      Current_Join=Pop_Next_join(Execution_Queue)){

    if(Is_Self_Join(Current_Join)){
      //execute_Self_Join
    }

    else if(Check_if_relations_already_in_result(Current_Join)){
        Execute_Scan_Join(Current_Join);
    }

    else if (Is_Same_Column_used(Last_Join,Current_Join)){
      //execute join with same column

    }

    else{

      //normal_join
    }

  }

}