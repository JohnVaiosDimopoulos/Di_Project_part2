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
  uint64_t num_of_tuples;
  uint64_t num_of_columns;
  uint64_t **Array;
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

static int Get_num_of_Tables(Table_AllocatorPtr Table_Allocator){
  const char* Init_File = construct_Path(Table_Allocator->Init_Filename,Table_Allocator->Dir_Name);
  FILE* FilePtr;
  Open_File_for_Read(&FilePtr,Init_File);
  int file_lines = Count_File_Lines(FilePtr);
  free(Init_File);
  return file_lines;
}

Table_Ptr Allocate_Table(Table_AllocatorPtr Table_Allocator){
  int num_of_tables = Get_num_of_Tables(Table_Allocator);
  printf("num of tables = %d\n", num_of_tables);
  Table_Ptr Table = (Table_Ptr)malloc(sizeof(Table));
  Table->Array = malloc(num_of_tables * sizeof(struct Shell));
  Table->num_of_shells = num_of_tables;
  return Table;
}

Shell_Ptr Get_Table_Array(Table_Ptr Table) {
	return Table->Array;
}

static char* Get_File_Name(char* line_buffer, int size) {
  char* file_Name = malloc(sizeof(char)*size);
  sscanf(line_buffer, "%s\n", file_Name);
  return file_Name;
}

static void Print_Shell(Shell_Ptr Shell, FILE *fp) {
  fprintf(fp, "sizes: %llu %llu\n", Shell->num_of_tuples, Shell->num_of_columns);
  for(int i =0;i<Shell->num_of_tuples;i++){
    for(int j =0;j<Shell->num_of_columns;j++) {
      fprintf(fp, "%llu|", Shell->Array[j][i]);
	}
    fprintf(fp,"\n");
  }
}

void Print_Table(Table_Ptr Table) {
  FILE *fp;
  Open_File_for_Write(&fp, "data.txt");
  for(int i = 0; i < Table->num_of_shells; i++){
    fprintf(fp,"=====REL %d=====\n",i);
    Print_Shell(&Table->Array[i], fp);
    fprintf(fp,"================\n\n\n");
  }
}

static void Allocate_Shell(Shell_Ptr Shell){
  Shell->Array = malloc(Shell->num_of_columns * sizeof(uint64_t*));
  Shell->Array[0]=malloc((Shell->num_of_columns*Shell->num_of_tuples)* sizeof(uint64_t));
}

static void Read_from_File(uint64_t* data ,FILE* fp){

  if(fread(data, sizeof(uint64_t), 1, fp) < 0) {
    printf("error in open\n"); exit(1);
  }
}

static void Read_Data(Shell_Ptr Shell,FILE* fp){
  for(int i = 0; i < Shell->num_of_columns*Shell->num_of_tuples; i++) {
    Read_from_File(&Shell->Array[0][i],fp);
  }
}

static void Setup_Column_Pointers(Shell_Ptr Shell){
  int last_index = 0;
  for(int i =1;i<Shell->num_of_columns;i++){
    Shell->Array[i]=&Shell->Array[0][last_index+Shell->num_of_tuples];
    last_index+=Shell->num_of_tuples;
  }
}

static void Fill_Shell(const char* FileName, Shell_Ptr Shell){

  //1. open file
  FILE* fp = fopen (FileName, "rb");
  //2. read num_of_tuples and num_of_columns
  Read_from_File(&Shell->num_of_tuples,fp);
  Read_from_File(&Shell->num_of_columns,fp);
  //3. Allocate Space
  Allocate_Shell(Shell);
  //4.Read Data
  Read_Data(Shell,fp);
  //set up column pointers
  Setup_Column_Pointers(Shell);
  fclose(fp);
}


void Fill_Table(Table_Ptr Table, Table_AllocatorPtr Table_Allocator) {

  FILE *Init_File;
  char *line_buffer = NULL;
  size_t line_buffer_size = 0;

  //1.construct initFilePath
  const char *Init_File_Path = construct_Path(Table_Allocator->Init_Filename, Table_Allocator->Dir_Name);
  //2.open init file
  Open_File_for_Read(&Init_File, Init_File_Path);
  //3.read line by line

  for (int i = 0; i < Table->num_of_shells; i++) {
    int read = getline(&line_buffer, &line_buffer_size, Init_File);
    char* File_Name = Get_File_Name(line_buffer,read);
    const char *file_Path = construct_Path(File_Name, Table_Allocator->Dir_Name);
    Fill_Shell(file_Path, &Table->Array[i]);
    free(file_Path);
    free(File_Name);
  }
  free(line_buffer);
  free(Init_File_Path);
}

static void Delete_Shell(struct Shell Shell) {
  free(Shell.Array[0]);
  free(Shell.Array);
}

void Delete_Table(Table_Ptr Table) {
  for(int i =0;i<Table->num_of_shells;i++)
    Delete_Shell(Table->Array[i]);
  free(Table->Array);
  free(Table);
}

