#include "Table_Allocator.h"
#include <stdlib.h>
#include "../../Util/Utilities.h"

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
    int file_lines = Count_File_Lines(FilePtr);
    free(Init_File);
    return file_lines;
  }
}


Table_Ptr Allocate_Table(Table_AllocatorPtr Table_Allocator){
  int num_of_tables = Get_num_of_Tables(Table_Allocator);
  printf("num of tables = %d\n", num_of_tables);
  Table_Ptr Table = (Table_Ptr)malloc(sizeof(Table));
  Table->Array = malloc(num_of_tables * sizeof(struct Shell));
  Table->num_of_shells = num_of_tables;
  return Table;
}

static char* Get_File_Name(char* line_buffer,int size){
  char* file_Name = malloc(sizeof(char)*size);
  sscanf(line_buffer, "%s\n", file_Name);
  return file_Name;
}

static void Fill_Shell(const char* FileName, Shell_Ptr Shell){
  //1.open file
  FILE* Table_File;
  if(Open_File_for_Read(&Table_File,FileName)){
    u_int64_t num_of_columns=0;
    u_int64_t num_of_row=0;
    //2.read num_of_tuples and num_of_columns
    //doesnt work;
    fscanf(Table_File,"%lu %lu",&num_of_row,&num_of_columns);
    printf("%lu,%lu\n",num_of_row,num_of_columns);
  }
}


void Fill_Table(Table_Ptr Table, Table_AllocatorPtr Table_Allocator) {

  FILE *Init_File;
  char *line_buffer = NULL;
  size_t line_buffer_size = 0;

  //1.construct initFilePath
  const char *Init_File_Path = construct_Path(Table_Allocator->Init_Filename, Table_Allocator->Dir_Name);
  //2.open init file
  if (Open_File_for_Read(&Init_File, Init_File_Path)) {
    //3.read line by line
    for (int i = 0; i < Table->num_of_shells; i++) {
      int read = getline(&line_buffer, &line_buffer_size, Init_File);
      char* File_Name = Get_File_Name(line_buffer,read);
      const char *file_Path = construct_Path(File_Name, Table_Allocator->Dir_Name);
      printf("%s\n",file_Path);
      Fill_Shell(file_Path, &Table->Array[i]);
      free(file_Path);
      free(File_Name);
    }
    free(line_buffer);
  }
  free(Init_File_Path);
}

  void Delete_Table(Table_Ptr Table) {
    free(Table->Array);
    free(Table);
  }

//const char* Get_Table_FileName(Table_AllocatorPtr Table){
//  return Table->Init_Filename;
//}
//
//const char* Get_Table_DirName(Table_AllocatorPtr Table){
//  return Table->Dir_Name;
//}

