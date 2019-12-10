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

struct Projection{
  int rel;
  int col;
};

struct Parsed_Query{
  int* relations;
  Join_Ptr Joins;
  Filter_Ptr Filters;
  Projection_Ptr Projection;
};


static Parsed_Query_Ptr Allocate_Parsed_query(){
  Parsed_Query_Ptr Parsed_Query = (Parsed_Query_Ptr)malloc(sizeof(struct Parsed_Query));
  Parsed_Query->Filters=NULL;
  Parsed_Query->Joins=NULL;
  Parsed_Query->relations=NULL;
}

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

static void Setup_Joins_And_Filters(Parsed_Query_Ptr Parsed_Query,Query_Ptr Query){

}

static void Setup_Projections(Parsed_Query_Ptr Parsed_Query,Query_Ptr Query){

}

static void Setup_Relation(Parsed_Query_Ptr Parsed_Query,Query_Ptr Query){
  int cnt = Count_Relations(Query);
  int* rel = Convert_Relations_to_Ints(Query,cnt);
  Parsed_Query->relations = rel;
}

Parsed_Query_Ptr Parse_Query(Query_Ptr Query){
  Parsed_Query_Ptr Parsed_Query = Allocate_Parsed_query();
  Setup_Relation(Parsed_Query,Query);
  Setup_Joins_And_Filters(Parsed_Query,Query);
  Setup_Projections(Parsed_Query,Query);
  return Parsed_Query;
}


//Parsed Query Accessors//

Join_Ptr Get_Joins(Parsed_Query_Ptr Parsed_Query){
  return Parsed_Query->Joins;
}

Filter_Ptr Get_Filters(Parsed_Query_Ptr Parsed_Query){
  return Parsed_Query->Filters;
}


//Filter Accessors//

int Get_Filter_Relation(Filter_Ptr Filter){
  return Filter->rel;
}

int Get_Filter_Column(Filter_Ptr Filter){
  return  Filter->col;
}

int Get_Amount(Filter_Ptr Filter){
  return Filter->amount;
}

char* Get_Type(Filter_Ptr Filter){
  return Filter->type;
}


// Join Accessors//

int Get_Relation_1(Join_Ptr Join){
  return Join->rel1;
}

int Get_Column_1(Join_Ptr Join){
  return Join->col1;
}

int Get_Relation_2(Join_Ptr Join){
  return Join->col2;
}

int Get_Column_2(Join_Ptr Join){
  return Join->rel2;
}

//Projection Accessors//

int Get_Projection_Relation(Projection_Ptr Projection){
  return Projection->rel;
}

int Get_Projection_Column(Projection_Ptr Projection){
  return Projection->col;
}
