#include "./Initializer/Argument_Manager/Argument_Manager.h"
#include "./Initializer/Table_Allocator/Table_Allocator.h"
#include "./Initializer/Work_Reader/Work_Reader.h"
#include "./Util/Utilities.h"
#include <stdio.h>


int main(int argc, char** argv){
  Arg_Manager_Ptr Manager = Create_ArgManager(argc,argv);
  Argument_Data_Ptr Arg_Data = Get_Argument_Data(Manager);

  printf(" Dir:%s \n Init:%s \n Work:%s\n",Get_Dir_Name(Arg_Data),Get_Init_FileName(Arg_Data),Get_Work_FileName(Arg_Data));

  Table_AllocatorPtr Table_Allocator = Create_Table_Allocator(Arg_Data);
  Table_Ptr Table = Allocate_Table(Table_Allocator);
  Fill_Table(Table,Table_Allocator);
  
  Print_Table(Table);

  Work_Ptr Work = Read_Work_File(Arg_Data);

  Delete_ArgManager(Manager);
  Delete_Argument_Data(Arg_Data);
  Delete_Table_Allocator(Table_Allocator);
  Delete_Table(Table);
  Delete_Work(Work);
}

