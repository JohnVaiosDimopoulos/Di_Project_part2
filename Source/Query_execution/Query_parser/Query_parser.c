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
  int num_of_relations;

  Join_Ptr Joins;
  int num_of_joins;

  Filter_Ptr Filters;
  int num_of_filters;

  Projection_Ptr Projections;
  int num_of_projections;
};


static Parsed_Query_Ptr Allocate_Parsed_query(){
  Parsed_Query_Ptr Parsed_Query = (Parsed_Query_Ptr)malloc(sizeof(struct Parsed_Query));
  Parsed_Query->Filters=NULL;
  Parsed_Query->Joins=NULL;
  Parsed_Query->relations=NULL;
  Parsed_Query->Projections=NULL;

  return Parsed_Query;
}

void Delete_Parsed_Query(Parsed_Query_Ptr Parsed_Query){
  free(Parsed_Query->relations);
  free(Parsed_Query->Joins);
  free(Parsed_Query->Filters);
  free(Parsed_Query->Projections);
  free(Parsed_Query);
}

//RELATIONS 
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

static void Setup_Relations(Parsed_Query_Ptr Parsed_Query, Query_Ptr Query){
  int cnt = Count_Relations(Query);
  int* rel = Convert_Relations_to_Ints(Query, cnt);
  Parsed_Query->relations = rel;
  Parsed_Query->num_of_relations = cnt;
}

//JOINS AND FILTERS
static int Count_Predicates(Query_Ptr Query) {
  char* temp = Allocate_and_Copy_Str(Get_Query_Predicates(Query));
  char* token = strtok(temp, "&");
  int cnt = 0;

  while(token != NULL ) {
    cnt++;
    token = strtok(NULL, "&");
  }
  free(temp);
  return cnt;
}

static Join_Ptr Fill_Joins(Query_Ptr Query, int cnt) {
  //tokenize
  Join_Ptr join = (Join_Ptr)malloc(cnt * sizeof(struct Join));
  char *temp_join[cnt];

  char *temp_query = Allocate_and_Copy_Str(Get_Query_Predicates(Query));
  char *token = strtok(temp_query, "&");
  for(int i = 0; i < cnt; i++) {
	temp_join[i] = (char*)malloc(strlen(token) * sizeof(char));
	strcpy(temp_join[i], token);
    token = strtok(NULL, "&");
  }
  free(temp_query);

  for(int i = 0; i < cnt; i++) {
    printf("preds: %s\n", temp_join[i]);
	if(strstr(temp_join[i], "<") || strstr(temp_join[i], ">"))
      printf("\tfilter\n");
	else
      printf("\tjoin\n");
//	  if(strstr(temp_join[i], "."))
//    Tokenize_rel_col(&(proj[i].rel), &(proj[i].col), temp_proj[i]);
    free(temp_join[i]);
  }

  return join;
}

static void Setup_Joins_And_Filters(Parsed_Query_Ptr Parsed_Query, Query_Ptr Query){
  int cnt = Count_Predicates(Query);
  printf("\npredicates = %d\n", cnt);

  Parsed_Query->Joins = Fill_Joins(Query, cnt);
  //just for checking
//  for(int i = 0; i < cnt; i++) {
//    printf("#%d rel: %d, col: %d\n", i, Parsed_Query->Projections[i].rel, Parsed_Query->Projections[i].col);
//  }
}


//PROJECTIONS
static int Count_Projections(Query_Ptr Query) {
  char* temp = Allocate_and_Copy_Str(Get_Query_Projections(Query));
  char* token = strtok(temp, " ");
  int cnt = 0;

  while(token != NULL ) {
    cnt++;
    token = strtok(NULL, " ");
  }
  free(temp);
  return cnt;
}

static void Tokenize_rel_col(int *rel, int *col, char *str) {
	//separate relation from column
	char *temp = (char*)malloc(strlen(str) * sizeof(char));
	strcpy(temp, str);
	char *tok = strtok(temp, ".");
    *rel = atoi(tok);
    tok = strtok(NULL, ".");
    *col = atoi(tok);

    free(temp);
}

static Projection_Ptr Fill_Projection_Array(Query_Ptr Query, int cnt) {
  //tokenize
  Projection_Ptr proj = (Projection_Ptr)malloc(cnt * sizeof(struct Projection));
  char *temp_proj[cnt];

  char *temp_query = Allocate_and_Copy_Str(Get_Query_Projections(Query));
  char *token = strtok(temp_query, " ");
  for(int i = 0; i < cnt; i++) {
	temp_proj[i] = (char*)malloc(strlen(token) * sizeof(char));
	strcpy(temp_proj[i], token);
    token = strtok(NULL, " ");
  }
  free(temp_query);

  for(int i = 0; i < cnt; i++) {
    Tokenize_rel_col(&(proj[i].rel), &(proj[i].col), temp_proj[i]);
    free(temp_proj[i]);
  }

  return proj;
}

static void Setup_Projections(Parsed_Query_Ptr Parsed_Query, Query_Ptr Query){
  int cnt = Count_Projections(Query);
  Parsed_Query->num_of_projections = cnt;

  Parsed_Query->Projections = Fill_Projection_Array(Query, cnt);
  //just for checking
//  for(int i = 0; i < cnt; i++) {
//    printf("#%d rel: %d, col: %d\n", i, Parsed_Query->Projections[i].rel, Parsed_Query->Projections[i].col);
//  }
}

Parsed_Query_Ptr Parse_Query(Query_Ptr Query){
  Parsed_Query_Ptr Parsed_Query = Allocate_Parsed_query();
  //relations
  Setup_Relations(Parsed_Query, Query);

  Setup_Joins_And_Filters(Parsed_Query,Query);
  Setup_Projections(Parsed_Query,Query);
  return Parsed_Query;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//Parsed Query Accessors//

Join_Ptr Get_Joins(Parsed_Query_Ptr Parsed_Query){
  return Parsed_Query->Joins;
}

int Get_Num_of_Joins(Parsed_Query_Ptr Parsed_Query){
  return Parsed_Query->num_of_joins;
}

Filter_Ptr Get_Filters(Parsed_Query_Ptr Parsed_Query){
  return Parsed_Query->Filters;
}

int Get_Num_of_Filters(Parsed_Query_Ptr Parsed_Query){
  return Parsed_Query->num_of_filters;
}

int* Get_Relations(Parsed_Query_Ptr Parsed_Query){
  return Parsed_Query->relations;
}

int Get_Num_of_Relations(Parsed_Query_Ptr Parsed_Query){
  return Parsed_Query->num_of_relations;
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
