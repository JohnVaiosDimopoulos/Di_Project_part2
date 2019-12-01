#include "Table_Allocator.h"
#include <stdlib.h>
#include "../../Util/Utilities.h"

struct Table_Allocator{
  char* Init_Filename;
  char* Dir_Name;
};

struct Table {
  Shell_Ptr *Array;
  int num_of_shells;
};

struct Shell {
  uint64_t num_of_tuples;
  uint64_t num_of_columns;
  uint64_t *Array;
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

  const char *path = construct_Path(Table_Allocator->Init_Filename, Table_Allocator->Dir_Name);
  printf("\nname = %s\n" , path);

  FILE *fp = fopen(path, "r");
  Open_File_for_Read(&fp, path);

  //create shell
  char file[5];
  Shell_Ptr *save = Table->Array;
  printf("Array = %lu\n", Table->Array);
  for(int i = 0; i < Table->num_of_shells; i++) {
    fscanf(fp, "%s", file);
    const char *filename = construct_Path(file, Table_Allocator->Dir_Name);
    Table->Array = Create_Shell(filename);
    Table->Array++;
  }
  Table->Array = save;
  printf("Array after = %lu\n", Table->Array);

  fclose(fp);

  return Table;
}

int Get_Table_Data(Table_Ptr Table){
  return Table->Array[0]->num_of_tuples;
}

void Delete_Table(Table_Ptr Table){
//  Delete_Shell(Table->Array);
//  free(Table->Array);
  free(Table);
}

void Fill_Shell(Shell_Ptr Shell, const char *filename) {
  printf("\nFILE = %s\n", filename);
  FILE* fp = fopen (filename, "rb");

  fseek(fp, 0, SEEK_END);
  long lSize = ftell(fp);
  // go back to the beginning of the file
  rewind(fp);
  printf("Size found to be %ld Bytes\n",lSize);

  if(fread(&Shell->num_of_tuples, sizeof(uint64_t), 1, fp) <0 ) {
      printf("error in open\n");
      exit(1);
  }
  if(fread(&Shell->num_of_columns, sizeof(uint64_t), 1, fp) <0 ) {
      printf("error in open\n");
      exit(1);
  }
  printf("%llu, %llu\n", Shell->num_of_tuples, Shell->num_of_columns);

  Shell->Array = malloc(Shell->num_of_columns * sizeof(uint64_t*));
  uint64_t column_pointer = 2 * sizeof(uint64_t); //skip num of tuples and num of columns
  for(int i = 0; i < Shell->num_of_columns; i++) {
	Shell->Array[i] = column_pointer;
	printf("column %d: %llu \n", i, Shell->Array[i]);
	column_pointer += Shell->num_of_tuples * sizeof(uint64_t);
  }
  fclose(fp);
}

Shell_Ptr Create_Shell(const char *filename) {
  Shell_Ptr Shell = (Shell_Ptr)malloc(sizeof(struct Shell));

  Fill_Shell(Shell, filename);
  return Shell;
}

void Delete_Shell(Shell_Ptr Shell) {
//  for(int i = 0; i < Shell->num_of_columns; i++)
//    free(Shell->Array[i]);
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
