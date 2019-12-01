#include "Table_Allocator.h"
#include <stdlib.h>
#include <fcntl.h>
#include "../../Util/Utilities.h"
#include <unistd.h>


struct Table_Allocator{
  char* Init_Filename;
  char* Dir_Name;
};

struct Table {
  Shell_Ptr Array;
  int num_of_shells;
};

struct Shell {
  int num_of_tuples;
  int num_of_columns;
  int **Array;
};

Table_AllocatorPtr Create_Table_Allocator(Argument_Data_Ptr Data){
  Table_AllocatorPtr Table_Allocator = (Table_AllocatorPtr)malloc(sizeof(Table_Allocator));
  Table_Allocator->Dir_Name=Allocate_and_Copy_Str(Get_Dir_Name(Data));
  Table_Allocator->Init_Filename=Allocate_and_Copy_Str(Get_Init_FileName(Data));
  return Table_Allocator;
}

void Delete_Table_Allocator(Table_AllocatorPtr Table_Allocator){
  free(Table_Allocator->Init_Filename);
  free(Table_Allocator->Dir_Name);
  free(Table_Allocator);
}

static int Count_File_Lines(FILE *FilePtr) {
  int num_of_lines = 0;
  for(int c = getc(FilePtr);; c=getc(FilePtr)){
    if (c == '\n')
      num_of_lines++;
    if (c == EOF) {
      num_of_lines++;
      break;
    }
  }
  rewind(FilePtr);
  fclose(FilePtr);
  return num_of_lines;
}

int Get_num_of_Tables(Table_AllocatorPtr Table_Allocator){
  const char* Init_File = construct_Path(Table_Allocator->Init_Filename,Table_Allocator->Dir_Name);
//  printf("\n\n%s\n", Init_File);
  FILE* FilePtr;
  if(Open_File_for_Read(&FilePtr,Init_File)){
    return Count_File_Lines(FilePtr);
  }
  return -1;
}


Table_Ptr Create_Table(Table_AllocatorPtr Table_Allocator){
  int num_of_tables = Get_num_of_Tables(Table_Allocator);
  printf("num of tables = %d\n", num_of_tables);

  Table_Ptr Table = (Table_Ptr)malloc(sizeof(struct Table));
  Table->num_of_shells = num_of_tables;
  for(int i = 0; i < Table->num_of_shells; i++)
    Table->Array = Create_Shell(Table, Table_Allocator);

  return Table;
}

int Get_Table_Data(Table_Ptr Table){
    return Table->Array->num_of_tuples;
}

void Delete_Table(Table_Ptr Table){
  free(Table->Array);
  free(Table);
}




Shell_Ptr Create_Shell(Table_Ptr Table, Table_AllocatorPtr Table_Allocator) {
  //printf("create\n");
  Shell_Ptr Shell = malloc(sizeof(struct Shell));
  const char *name = construct_Path(Table_Allocator->Init_Filename, Table_Allocator->Dir_Name);

  printf("\n%s\n" ,name);
  int fd = open (name, O_RDONLY);
  int num;
  if(read(fd, &num, sizeof(int)) < 0) {
      printf("error in open\n");
      exit(1);
  }
  printf("%d\n", num);
  close(fd);

  Shell->num_of_columns = 1;
  Shell->num_of_tuples = 2;
  return Shell;
}

void Delete_Shell(Shell_Ptr Shell){
   for(int i = 0; i < Shell->num_of_columns; i++) {
       free(Shell->Array[i]);
   }
    free(Shell->Array);
    free(Shell);
}

//const char* Get_Table_FileName(Table_AllocatorPtr Table){
//  return Table->Init_Filename;
//}
//
//const char* Get_Table_DirName(Table_AllocatorPtr Table){
//  return Table->Dir_Name;
//}