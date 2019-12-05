#include "Work_Reader.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../Util/Utilities.h"

struct Work{
  char **Batch;
  int counter;
  int num_of_batches;
};

Work_Ptr Create_Work(int lines) {
  Work_Ptr Work = (Work_Ptr)malloc(sizeof(struct Work));
  Work->num_of_batches = lines;
  Work->counter = 0;
  Work->Batch = (char**)malloc(lines * sizeof(char*));

  return Work;
}

void Insert_Batch(char *buffer, Work_Ptr Work) {
  size_t len = strlen(buffer);
  Work->Batch[Work->counter] = (char*)malloc(len * sizeof(char));
  strcpy(Work->Batch[Work->counter], buffer);
//  printf("%s<-buffer\n", Work->Batch[Work->counter]);
//  printf("len = %ld\n", len);
  Work->counter++;
}

void Print_Work(Work_Ptr Work) {
  printf("\n\n\tPRINT\n");
  for(int i = 0; i < Work->counter; i++) {
    printf("%s\n", Work->Batch[i]);
  }
}

void Delete_Work(Work_Ptr Work) {
  for(int i = 0; i < Work->counter; i++)
    free(Work->Batch[i]);

  free(Work->Batch);
  free(Work);
}

Work_Ptr Read_Work_File(Argument_Data_Ptr Arg_Data) {
  const char *path = construct_Path(Get_Work_FileName(Arg_Data), Get_Dir_Name(Arg_Data));
  printf("\n\n\t%s\n", path);

  FILE *fp;
  Open_File_for_Read(&fp, path);

  int lines = Count_File_Lines(fp);
  printf("lines = %d\n", lines);

  char *line_buffer = NULL;
  size_t line_buffer_size = 0;

  Work_Ptr Work = Create_Work(lines);
  printf("num of batches %d\n", Work->num_of_batches);

  Open_File_for_Read(&fp, path);

  for(int i = 0; i < lines; i++) {
    int read = getline(&line_buffer, &line_buffer_size, fp);
    char* command = malloc(sizeof(char) * line_buffer_size);
    sprintf(command, "%s", line_buffer);
//    printf("%s", command);

    Insert_Batch(command, Work);
    free(command);
  }
  Print_Work(Work);
  fclose(fp);

  return Work;
//////////////////////////////////////////////
//////////////////////////////////////////////
//	char* token = strtok(command, "|");
//
//    // Keep printing tokens while one of the
//    // delimiters present in str[].
//    while (token != NULL) {
//        printf("%s\n", token);
//        token = strtok(NULL, "|");
//    }
//////////////////////////////////////////////
//////////////////////////////////////////////
}
