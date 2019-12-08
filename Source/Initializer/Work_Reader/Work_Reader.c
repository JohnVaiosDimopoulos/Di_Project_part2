#include "Work_Reader.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../Util/Utilities.h"

struct Batch {
  char *Relation;
  char *Predicates;
  char *Projection;
};

struct Work {
  Batch_Ptr Batch;
  char **Buffer;
  int counter;
  int num_of_batches;
};

static Work_Ptr Create_Work(int lines) {
  Work_Ptr Work = (Work_Ptr)malloc(sizeof(struct Work));
  Work->num_of_batches = lines;
  Work->counter = 0;
  Work->Buffer = (char**)malloc(lines * sizeof(char*));
  Work->Batch = (Batch_Ptr)malloc(lines * sizeof(struct Batch));
  return Work;
}

static void Tokenizer(char *buffer, Batch_Ptr Batch) {
  char* temp = Allocate_and_Copy_Str(buffer);
  char* token = strtok(temp, "|");


  for(int i = 0; i < 3; i++) {
    if (token == NULL) break;
	switch(i) {
	case 0:
      Batch->Relation = Allocate_and_Copy_Str(token);
      break;
	case 1:
      Batch->Predicates = Allocate_and_Copy_Str(token);
      break;
	case 2:
      Batch->Projection = Allocate_and_Copy_Str(token);
      break;
    }
    token = strtok(NULL, "|");
  }
  free(temp);
}

static void Insert_Batch(char *buffer, Work_Ptr Work) {
  size_t len = strlen(buffer);
  Work->Buffer[Work->counter] = Allocate_and_Copy_Str(buffer);
  Tokenizer(buffer, &(Work->Batch[Work->counter]));
  Work->counter++;
}

static void Print_Batch(Batch_Ptr Batch) {
  printf("\t%s\n\t%s\n\t%s\n\n", Batch->Relation, Batch->Predicates, Batch->Projection);
}

static void Print_Work(Work_Ptr Work) {
  printf("\n\n\tPRINT\n");
  for(int i = 0; i < Work->counter; i++) {
    printf("%s\n", Work->Buffer[i]);
	Print_Batch(&(Work->Batch[i]));
  }
}

static void Delete_Batch(Batch_Ptr Batch, int counter) {
  for(int i = 0; i < counter; i++) {
    free(Batch[i].Relation);
    free(Batch[i].Predicates);
    free(Batch[i].Projection);
  }

  free(Batch);
}

void Delete_Work(Work_Ptr Work) {
  for(int i = 0; i < Work->counter; i++) {
    free(Work->Buffer[i]);
  }
  free(Work->Buffer);
  Delete_Batch(Work->Batch, Work->counter);
  free(Work);
}

Work_Ptr Read_Work_File(Argument_Data_Ptr Arg_Data) {

  const char *path = construct_Path(Get_Work_FileName(Arg_Data), Get_Dir_Name(Arg_Data));

  FILE *fp;
  Open_File_for_Read(&fp, path);

  int lines = Count_File_Lines(fp);
  char *line_buffer = NULL;
  size_t line_buffer_size = 0;
  Work_Ptr Work = Create_Work(lines);
  Open_File_for_Read(&fp, path);

  for(int i = 0; i < 8; i++) {
    int read = getline(&line_buffer, &line_buffer_size, fp);
    char* command = malloc(sizeof(char) * line_buffer_size);
    sprintf(command, "%s", line_buffer);
    Insert_Batch(command, Work);
    free(command);
  }

  Print_Work(Work);
  free(line_buffer);
  free(path);
  fclose(fp);

  return Work;
}
