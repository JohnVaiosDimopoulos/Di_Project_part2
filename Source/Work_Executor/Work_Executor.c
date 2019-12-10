#include "Work_Executor.h"
#include "../Work_Reader/Work_Reader.h"
#include "../Util/Utilities.h"
#include "../Query_execution/Query_executor/Query_Executor.h"

void Start_Work(Table_Ptr Relations,Argument_Data_Ptr Arg_Data){

  const char*path = construct_Path(Get_Work_FileName(Arg_Data), Get_Dir_Name(Arg_Data));
  printf("work: %s\n", path);
  FILE *fp;
  Open_File_for_Read(&fp, path);
  Batch_Ptr Current_Batch;
  Query_Ptr Current_Query;

  while((Current_Batch = Read_next_Batch(fp)) != NULL) {
	while(Get_num_of_Queries(Current_Batch)){
	  Current_Query = Pop_Next_Query_from_Batch(Current_Batch);
      Execute_Query(Current_Query, Relations);
      Delete_Query(Current_Query);
      free(Current_Query);
    }
    Delete_Batch(Current_Batch);
  }

  free(path);
  fclose(fp);

}
