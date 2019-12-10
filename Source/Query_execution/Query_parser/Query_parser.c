#include "Query_parser.h"
#include "../../Util/Utilities.h"
#include <stdlib.h>
#include <string.h>


struct Join{
  int rel1;
  int col1;
  int rel2;
  int col2;
};


struct Filter{
  int rel;
  int col;
  char* type;
  int amount;
};

struct Parsed_Query{
  int* relations;
  Join_Ptr Joins;
  Filter_Ptr Filters;
};


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


Parsed_Query_Ptr Parse_Query(Query_Ptr Query){
  int cnt = Count_Relations(Query);
  int* rel = Convert_Relations_to_Ints(Query,cnt);
}

