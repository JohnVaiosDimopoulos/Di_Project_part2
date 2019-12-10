#include "Query_Executor.h"
#include "../Util/Utilities.h"
#include <stdio.h>
#include <string.h>

static int Count_Relations(Query_Ptr Query, char **rel) {
  char* temp = Allocate_and_Copy_Str(Get_Query_Relations(Query));
  char* token = strtok(temp, " ");
  int cnt = 0;
  while(token != NULL ) {
//    printf( "%s\n", token );
	cnt++;
    token = strtok(NULL, " ");
  }
  free(temp);

  //tokenize
  rel = (char**)malloc(cnt * sizeof(char*));
  for(int i = 0; i < cnt; i++)
	  rel[i] = (char*)malloc(3 * sizeof(char));

  temp = Allocate_and_Copy_Str(Get_Query_Relations(Query));
  token = strtok(temp, " ");
  for(int i = 0; i < cnt; i++) {
//    printf("%s\n", token);
	strcpy(rel[i], token);
//    printf("%s\n", rel[i]);
    token = strtok(NULL, " ");
  }
  free(temp);
  for(int i =0;i<cnt;i++)
    free(rel[i]);
  free(rel);
  return cnt;
}


// we dont know how this will be done
void Execute_Query(Query_Ptr Query, Table_Ptr Relations){
  printf("Execute Query %s\n", Get_Query_Relations(Query));
  char** rel;
  int cnt = Count_Relations(Query, rel);
  printf("cnt = %d\n", cnt);
//  for(int i = 0; i < cnt; i++)
//    printf("rel = %s\n", rel[i]);

//  for(int i = 0; i < cnt; i++)
//    free(rel[i]);
//  free(rel);

//  char rel[3];
//  for(int i = 0; i < cnt; i++) {
//    sscanf(Get_Query_Relations(Query), "%s", rel);
//	printf("rel: %s\n", rel);
//  }

//  char *rel = Tokenize_Relations(Query);
  //while(rel != NULL) {
//  for(int i = 0; i < 2; i++) {
//    rel = Tokenize_Relations(Query);
//    printf("%s\n", rel);
//  }
}

