#include "./Initializer/Argument_Manager/Argument_Manager.h"
#include <stdio.h>

int main(int argc, char** argv){
  Arg_Manager_Ptr Manager = Create_ArgManager(argc,argv);
  Argument_Data_Ptr Arg_Data = Get_Argument_Data(Manager);

  printf(" Dir:%s \n Init:%s \n Work:%s\n",Get_Dir_Name(Arg_Data),Get_Init_FileName(Arg_Data),Get_Work_FileName(Arg_Data));

  Delete_ArgManager(Manager);
  Delete_Argument_Data(Arg_Data);
}

