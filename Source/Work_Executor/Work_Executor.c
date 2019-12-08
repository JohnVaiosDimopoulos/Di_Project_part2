#include "Work_Executor.h"
#include "../Initializer/Work_Reader/Work_Reader.h"
#include "../Query_executor/Query_Executor.h"

void Star_Work(Table_Ptr Relations,Argument_Data_Ptr Argument_Data){

  Batch_Ptr Current_Batch;
  //while we have batches to read
  //the function will get the Next_Batch Struct and fill it
  /*
  while (Read_Work_File(Argument_Data)){
    for(int i =0;i<Get_num_of_Queries(Current_Bath);i++){
       Query_Ptr = Get_Query(Current_Bath,i);
       Execute_Query(Query_Ptr,Relations);
  }
   */
}
