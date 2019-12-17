#include "Join_Execution.h"
#include "../Filter_Executor/Filter_Executor.h"
#include <stdlib.h>

struct Tuple{
  uint64_t data;
  uint64_t row_id;
};



static void Execute_Self_Join(Join_Ptr Join,Table_Ptr Relations) {

  //1.get the rel from the table
  int relation = Get_Relation_1(Join);
  int column_1 = Get_Column_1(Join);
  int column_2 = Get_Column_2(Join);
  Shell_Ptr Relations_Array = Get_Table_Array(Relations);
  Shell_Ptr Relation = Get_Shell_by_index(Relations_Array,relation);
  Tuple_Ptr* Old_Array = Get_Shell_Array(Relation);
  int num_of_tuples=Get_num_of_tuples(Relation);
  int num_of_columns=Get_num_of_columns(Relation);
  int counter=0;


  Tuple_Ptr* Results = (Tuple_Ptr*)malloc((num_of_columns*sizeof(Tuple_Ptr)));
  Results[0] =(Tuple_Ptr)malloc((num_of_columns*num_of_tuples)* sizeof(struct Tuple));

  //setup_pointers;


  for(int i=0;i<num_of_tuples;i++){
    if(Old_Array[column_1][i].data==Old_Array[column_2][i].data)
      for(int j =0;j<num_of_columns;j++){
        Results[j][counter].data=Old_Array[j][i].data;
        Results[j][counter].row_id=Old_Array[j][i].row_id;
        counter++;
      }
  }




}


//static int Check_if_relations_already_in_result(Join_Ptr Join,Intermediate_Result_ptr Intermediate_Result){
//  if(Is_rel_in_intermediate_result(Intermediate_Result,Get_Relation_1(Join)) && Is_rel_in_intermediate_result(Intermediate_Result,Get_Relation_2(Join)))
//    return 1;
//  return 0;
//}


//static void Execute_Scan_Join(Join_Ptr Join,Intermediate_Result_ptr old_result){
/*
// * also input the intermediate result as old_result;
// * Make row_id/value pairs for rel1 based on join column=  t1(rid|v)
// * Make row_id/value paits for rel2 based on join column=  t2(rid|v)
// * result new_result;
// * for(int i=0;i<num_of_rows_of_the_result;i++){
// *  row_tuple = old_res[i];
// *  if(t1[row_pair[1]==t2[row_pair[2]){
// *  new_result.insert(row_pair);
// *  }
// * }
//*/
//}



void Execute_Joins(Execution_Queue_Ptr Execution_Queue,Table_Ptr Relations){

//  Intermediate_Result_ptr Intermediate_Result = NULL;
  Join_Ptr Last_Join = NULL;
  // we will also keep the data of the last join;

  for(Join_Ptr Current_Join = Pop_Next_join(Execution_Queue);
      Current_Join!=NULL;
      Current_Join=Pop_Next_join(Execution_Queue)){

    if(Is_Self_Join(Current_Join))
      Execute_Self_Join(Current_Join,Relations);

//    else if(Check_if_relations_already_in_result(Current_Join,Intermediate_Result))
//        Execute_Scan_Join(Current_Join,Intermediate_Result);

    else if (Is_Same_Column_used(Last_Join,Current_Join)){}
      //execute join with same column

    else{
      //normal_join
    }

  }

}