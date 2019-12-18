#include "Join_Execution.h"
#include "../Filter_Executor/Filter_Executor.h"
#include <stdlib.h>

struct Tuple{
  uint64_t element;
  uint64_t row_id;
};

struct Result{
  int relation;
  uint64_t row_id;
};

struct Rel_Tuple{
  struct Result* row_ids;
  uint64_t value;
};

struct Intermediate_Result{
  int relations_in_result[4];
  int num_of_results;
  int num_of_relations;
  struct Result** row_ids;
};

typedef struct {
  Tuple_Ptr tuples;
  uint64_t num_of_tuples;
} Relation;

typedef Relation* RelationPtr;

typedef struct Intermediate_Result* Intermediate_Result_Ptr;

Intermediate_Result_Ptr Create_Intermediate_Result(){
  Intermediate_Result_Ptr Intermediate_Result = (Intermediate_Result_Ptr)malloc(sizeof(Intermediate_Result));
  Intermediate_Result->num_of_results=0;
  for(int i =0;i<3;i++)
    Intermediate_Result->relations_in_result[i]=0;
  return Intermediate_Result;
}




static void Execute_Self_Join(Join_Ptr Join,Table_Ptr Relations) {

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
  Setup_Column_Pointers(Results,num_of_columns,num_of_tuples);

  for(int i=0;i<num_of_tuples;i++){
    if(Old_Array[column_1][i].element==Old_Array[column_2][i].element){
      for(int j =0;j<num_of_columns;j++){
        Results[j][counter].element=Old_Array[j][i].element;
        Results[j][counter].row_id=Old_Array[j][i].row_id;
      }
      counter++;
    }


  }
  Set_Shell_Array(Relation,Results);

  free(Old_Array[0]);
  free(Old_Array);
}

static int find_value_from_row_id(Tuple_Ptr* Array,int col,int row_id,int num_of_tuples){
  for(int i =0;i<num_of_tuples;i++){
    if(row_id==Array[col][num_of_tuples].row_id)
      return Array[col][num_of_tuples].element;
  }
}

static int Check_if_relations_already_in_result(Join_Ptr Join,Intermediate_Result_Ptr Intermediate_Result){
  if(Intermediate_Result->relations_in_result[Get_Relation_1(Join)]==1 && Intermediate_Result->relations_in_result[Get_Relation_2(Join)]==1)
    return 1;
  return 0;
}

static struct Rel_Tuple* Make_Relation_For_Scan(int relation,int column,Intermediate_Result_Ptr old_result, Table_Ptr Relations){
  Shell_Ptr Shell_Array = Get_Table_Array(Relations);
  Shell_Ptr Current_Shell = Get_Shell_by_index(Shell_Array,relation);
  int num_of_tuples = Get_num_of_tuples(Current_Shell);
  Tuple_Ptr* Array = Get_Shell_Array(Current_Shell);


  struct Rel_Tuple* Rel = (struct Rel_Tuple*)malloc(old_result->num_of_results*sizeof(struct Rel_Tuple));
  Rel->row_ids=(struct Result*)malloc(old_result->num_of_relations* sizeof(struct Result*));
  for(int i=0;i<old_result->num_of_results;i++){
    Rel->row_ids=old_result->row_ids[i];
    for(int j =0;j<old_result->num_of_relations;j++)
      if(old_result->row_ids[i][j].relation==relation)
        Rel->value=find_value_from_row_id(Array,column,old_result->row_ids[i][j].row_id,num_of_tuples);
  }
  return Rel;
}

static void Execute_Scan_Join(Join_Ptr Join, Intermediate_Result_Ptr Intermediate_Result, Table_Ptr Relations){

  int rel_1 = Get_Relation_1(Join);
  int col_1 = Get_Column_1(Join);
  struct Rel_Tuple* Rel_1 = Make_Relation_For_Scan(rel_1, col_1, Intermediate_Result, Relations);

  int col_2 = Get_Column_2(Join);
  int rel2=Get_Relation_2(Join);
  struct Rel_Tuple* Rel_2 = Make_Relation_For_Scan(rel_1, col_1, Intermediate_Result, Relations);


  struct Result** result_temp = malloc(Intermediate_Result->num_of_relations*sizeof(struct Result*));
  for(int i =0; i<Intermediate_Result->num_of_results; i++){
    result_temp[i]=malloc(sizeof(struct Result));
  }

  int num_of_results=0;
  for(int i=0; Intermediate_Result->num_of_results; i++){
    if(Rel_1[i].value==Rel_2[i].value){
      num_of_results++;
      for(int j=0; j<Intermediate_Result->num_of_relations; j++)
        result_temp[i]=Rel_1[i].row_ids;
    }
  }

  struct Result** result_new = malloc(Intermediate_Result->num_of_relations* sizeof(struct Result*));
  for(int i =0;i<num_of_results;i++){
    result_new[i]=malloc(sizeof(struct Result));
  }

  for(int i =0;i<num_of_results;i++){
    for(int j = 0; j<Intermediate_Result->num_of_relations; j++){
      result_new[i][j].row_id=result_temp[i][j].row_id;
      result_new[i][j].relation=result_temp[i][j].relation;
    }
  }


  free(result_temp);
  struct Result** temp = Intermediate_Result->row_ids;
  for(int i =0; i<Intermediate_Result->num_of_results; i++)
    free(temp[0]);
  free(temp);

  Intermediate_Result->row_ids=result_new;
  Intermediate_Result->num_of_results=num_of_results;
}

static void Execute_Normal_Join(Join_Ptr Join,Intermediate_Result_Ptr Intermediate_Result, Table_Ptr Relations ){

  //two relations that will be fed into Sort and then JOIN
  //REL_1,REL_2

  if(Intermediate_Result->relations_in_result[Get_Relation_1(Join)]==1){
    // get rel_1 out of intermediate result and make rel_2 out of the table

  }
  else if(Intermediate_Result->relations_in_result[Get_Relation_2(Join)]==1){
    // get rel_2 out of intermediate result and make rel_1 out of the table;
  }

  else{

  }


}


void Execute_Joins(Execution_Queue_Ptr Execution_Queue,Table_Ptr Relations){

  Intermediate_Result_Ptr Intermediate_Result = NULL;
  Join_Ptr Last_Join = NULL;
  // we will also keep the element of the last join;

  for(Join_Ptr Current_Join = Pop_Next_join(Execution_Queue);
      Current_Join!=NULL;
      Current_Join=Pop_Next_join(Execution_Queue)){

    if(Is_Self_Join(Current_Join))
      Execute_Self_Join(Current_Join,Relations);

    else if(Check_if_relations_already_in_result(Current_Join,Intermediate_Result))
        Execute_Scan_Join(Current_Join,Intermediate_Result,Relations);

    else if (Is_Same_Column_used(Last_Join,Current_Join)){

    }
      //execute join with same column

    else{
     Execute_Normal_Join(Current_Join,Intermediate_Result,Relations)
    }

  }

}