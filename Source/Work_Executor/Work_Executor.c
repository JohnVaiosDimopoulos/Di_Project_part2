#include "Work_Executor.h"
#include "../Initializer/Work_Reader/Work_Reader.h"
#include "../Util/Utilities.h"
#include "../Query_executor/Query_Executor.h"

void Start_Work(Table_Ptr Relations,Argument_Data_Ptr Arg_Data){

  const char *path = construct_Path(Get_Work_FileName(Arg_Data), Get_Dir_Name(Arg_Data));
  FILE *fp;
  Open_File_for_Read(&fp, path);
  Read_Work_File(Arg_Data, Relations);
  Batch_Ptr Current_Batch;
  Query_Ptr Current_Query;

  while ((Current_Batch=Read_next_Batch(fp))!=NULL){
    while ((Current_Query=Pop_Next_Query_from_Batch(Current_Batch))!=NULL){
      Execute_Query(Current_Query,Relations);
      Delete_Query(Current_Query);
    }
    Delete_Batch(Current_Batch);
  }
  free(path);
  fclose(fp);

}
