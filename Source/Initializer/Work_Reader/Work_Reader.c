#include "Work_Reader.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../Util/Utilities.h"

struct Query {
  char *Relation;
  char *Predicates;
  char *Projection;

  Query_Ptr next;
};

struct Batch {
  Query_Ptr Queries;
  Query_Ptr Last;
  int counter;
};

static Batch_Ptr Create_Batch() {
  Batch_Ptr Batch = (Batch_Ptr)malloc(sizeof(struct Batch));
  Batch->counter = 0;
  Batch->Queries = NULL;
  Batch->Last = NULL;
  printf("=================New Batch ===================\n\n");
  return Batch;
}

static Query_Ptr New_Query(char *buffer) {
  Query_Ptr Query = (Query_Ptr)malloc(sizeof(struct Query));
  Query->next = NULL;

  char* temp = Allocate_and_Copy_Str(buffer);
  char* token = strtok(temp, "|");
  for(int i = 0; i < 3; i++) {
    if (token == NULL) break;
	switch(i) {
	case 0:
      Query->Relation = Allocate_and_Copy_Str(token);
      break;
	case 1:
      Query->Predicates = Allocate_and_Copy_Str(token);
      break;
	case 2:
      Query->Projection = Allocate_and_Copy_Str(token);
      break;
    }
    token = strtok(NULL, "|");
  }
  free(temp);
  
  return Query;
}

static void Insert_Query(char *buffer, Batch_Ptr Batch) {
  size_t len = strlen(buffer);
  //if list is empty first and last are the same
  if(Batch->counter == 0) {
    Batch->Queries = New_Query(buffer);
	Batch->Last = Batch->Queries;
  } else {
    Query_Ptr pnode = Batch->Last;
    pnode->next = New_Query(buffer);
    Batch->Last = pnode->next; 
  }
  Batch->counter++;
//  printf("%s Inserted\n", buffer);
//  printf("%s \n", Batch->Queries->Relation);
//  printf("%s Inserted\n", Batch->Last->Relation);
}

static void Print_Query(Query_Ptr Query) {
  printf("\t%s\n\t%s\n\t%s\n", Query->Relation, Query->Predicates, Query->Projection);
}

static void Print_Batch(Batch_Ptr Batch) {
  printf("\n\tPRINT\n");
  Query_Ptr pnode = Batch->Queries;
  for(int i = 0; i < Batch->counter; i++) {
	Print_Query(pnode);
	pnode = pnode->next;
  }
  printf("\n");
}

void Delete_Query(Query_Ptr Query) {
  free(Query->Relation);
  free(Query->Predicates);
  free(Query->Projection);
}

void Delete_Batch(Batch_Ptr Batch) {
  Query_Ptr node = Batch->Queries;
  Query_Ptr temp = node;
  for(int i = 0; i < Batch->counter; i++) {
    Delete_Query(node);

    node = node->next;
	free(temp);
	temp = node;
  }
  free(Batch);
}

Query_Ptr Pop_Next_Query_from_Batch(Batch_Ptr Batch) {
  if(Batch->counter == 0) {
	  printf("LIST IS EMPTY, NO QUERY TO REMOVE\n");
	  return NULL;
  }
  //allocate and copy query
  Query_Ptr pnode = (Query_Ptr)malloc(sizeof(struct Query));
  pnode->Relation = Allocate_and_Copy_Str(Batch->Queries->Relation );
  pnode->Predicates = Allocate_and_Copy_Str(Batch->Queries->Predicates);
  pnode->Projection = Allocate_and_Copy_Str(Batch->Queries->Projection);

  //free the old one
  Query_Ptr temp = Batch->Queries;
  Batch->Queries = Batch->Queries->next;
  Delete_Query(temp);
  free(temp);

  Batch->counter--;
  return pnode;
}

Batch_Ptr Read_next_Batch(FILE *fp) {
  char *line_buffer = NULL;
  size_t line_buffer_size = 0;
  Batch_Ptr Batch = Create_Batch();

  //read batch line by line
  while(1) {
    int read = getline(&line_buffer, &line_buffer_size, fp);
    printf("%s\n", line_buffer);

	if(!strcmp(line_buffer, "F\n")) {/*printf("F found\n");*/ break;}

    char* command = malloc(sizeof(char) * line_buffer_size);
    sprintf(command, "%s", line_buffer);
    Insert_Query(command, Batch);
    free(command);
  }
  free(line_buffer);

  Print_Batch(Batch);
  return Batch;
}

int Count_Batches(FILE *FilePtr) {
  int num_of_batches = 0;
  for(int c = getc(FilePtr);; c=getc(FilePtr)){
    if (c == 'F')
      num_of_batches++;
    if (c == EOF) {
      break;
    }
  }
  rewind(FilePtr);
  return num_of_batches;
}

void Read_Work_File(Argument_Data_Ptr Arg_Data, Table_Ptr Relations) {




    Delete_Batch(Batch);
  }
  free(path);
  fclose(fp);
}

int Get_num_of_Queries(Batch_Ptr Batch) {
  return Batch->counter;
}
char* Get_Query_Relations(Query_Ptr Query) {
  return Query->Relation;
}
char* Get_Query_Predicates(Query_Ptr Query) {
  return Query->Predicates;
}
char* Get_Query_Projections(Query_Ptr Query) {
  return Query->Projection;
}
