#include "Query_Executor.h"
#include "../Util/Utilities.h"
#include <stdio.h>
#include <string.h>



static int Count_Relations(Query_Ptr Query) {
  char* temp = Allocate_and_Copy_Str(Get_Query_Relations(Query));
  char* token = strtok(temp, " ");
  int cnt = 0;

  while(token != NULL ) {
	cnt++;
    token = strtok(NULL, " ");
  }
  free(temp);
  return cnt;
}

static int* Convert_Relations_to_Ints(Query_Ptr Query, int cnt) {
  //tokenize
  int *rel = (int*)malloc(cnt * sizeof(int));

  char *temp = Allocate_and_Copy_Str(Get_Query_Relations(Query));
  char *token = strtok(temp, " ");
  for(int i = 0; i < cnt; i++) {
    rel[i] = atoi(token);
    token = strtok(NULL, " ");
  }
  free(temp);
  return rel;
}


// we dont know how this will be done
void Execute_Query(Query_Ptr Query, Table_Ptr Relations){
  printf("Execute Query %s\n", Get_Query_Relations(Query));

  int cnt = Count_Relations(Query);
  printf("cnt = %d\n", cnt);

  int* rel = Convert_Relations_to_Ints(Query, cnt);
  printf("rels: ");
  for(int i = 0; i < cnt; i++)
    printf("%d ", rel[i]);
  printf("\n");

  //fetch relations from table
  for(int i = 0; i < cnt; i++) {
    Shell_Ptr Shell = Get_Table_Array(Relations);
    printf("%d: %llu %llu \n", i, Get_num_of_tuples(Get_Shell_by_index(Shell,rel[i])), Get_num_of_columns(Get_Shell_by_index(Shell,rel[i])));
  }

  free(rel);
}

