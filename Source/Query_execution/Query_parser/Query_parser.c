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
  char type[2];
  int constant;
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

static void Tokenize_to_rel_and_col(int *rel, int *col, char *str) {
	char *temp = (char*)malloc(strlen(str) * sizeof(char));
	strcpy(temp, str);
	char *tok = strtok(temp, ".");
    *rel = atoi(tok);
    tok = strtok(NULL, ".");
    *col = atoi(tok);

    free(temp);
}

static int it_is_Join(int *second_col, int *constant, char *predicates, char *type) {
  char *token;
  if(strstr(predicates, "<")) {
    token = strtok(predicates, "<");
    token = strtok(NULL, "<");
	*constant = atoi(token);
	strcpy(type, "<");
	return 0;
  } else if(strstr(predicates, ">")) {
    token = strtok(predicates, ">");
    token = strtok(NULL, ">");
	*constant = atoi(token);
	strcpy(type, ">");
	return 0;
  } else {
    token = strtok(predicates, "=");
    token = strtok(NULL, "=");
    if(strstr(token, ".")) {
      Tokenize_to_rel_and_col(&second_col[0], &second_col[1], token);
	  return 1;
    } else {
	  *constant = atoi(token);
	  strcpy(type, "=");
	  return 0;
    }
  }
}

static Parsed_Query_Ptr Fill_Predicates(Query_Ptr Query, int cnt, Parsed_Query_Ptr Parsed_Query) {
  char *temp_query = Allocate_and_Copy_Str(Get_Query_Predicates(Query));
  char *token = strtok(temp_query, "&");

  char *temp_pred[cnt];
  for(int i = 0; i < cnt; i++) {
	temp_pred[i] = (char*)malloc(strlen(token) * sizeof(char));
	strcpy(temp_pred[i], token);
    token = strtok(NULL, "&");
  }
  free(temp_query);

  int join_first_col[cnt][2];
  int filter_first_col[cnt][2];
  int second_col[cnt][2];
  char type_array[cnt][2];
  int constants[cnt];
  int num_of_filters = 0;
  int num_of_joins = 0;
  for(int i = 0; i < cnt; i++) {

    char *predicate = Allocate_and_Copy_Str(temp_pred[i]);
    char type[2];
    if(it_is_Join(second_col[num_of_joins], &constants[num_of_filters], predicate, type)) {
      Tokenize_to_rel_and_col(&join_first_col[num_of_joins][0], &join_first_col[num_of_joins][1], temp_pred[i]);
	  num_of_joins++;
	} else {
      Tokenize_to_rel_and_col(&filter_first_col[num_of_filters][0], &filter_first_col[num_of_filters][1], temp_pred[i]);
	  strcpy(type_array[num_of_filters], type);
	  num_of_filters++;
	}

    free(temp_pred[i]);
    free(predicate);
  }
  //joins
  Parsed_Query->Joins = (Join_Ptr)malloc(num_of_joins * sizeof(struct Join));
  for(int i = 0; i < num_of_joins; i++) {
  Parsed_Query->Joins[i].rel1 = join_first_col[i][0];
  Parsed_Query->Joins[i].col1 = join_first_col[i][1];
  Parsed_Query->Joins[i].rel2 = second_col[i][0];
  Parsed_Query->Joins[i].col2 = second_col[i][1];
  }
  Parsed_Query->num_of_joins = num_of_joins;
  //filters
  Parsed_Query->Filters = (Filter_Ptr)malloc(num_of_filters * sizeof(struct Filter));
  for(int i = 0; i < num_of_filters; i++) {
   Parsed_Query->Filters[i].rel = filter_first_col[i][0];
   Parsed_Query->Filters[i].col = filter_first_col[i][1];
   Parsed_Query->Filters[i].constant = constants[i];
   strcpy(Parsed_Query->Filters[i].type, type_array[i]);
  }
  Parsed_Query->num_of_filters = num_of_filters;
  return Parsed_Query;  
}             
              
static void Setup_Joins_And_Filters(Parsed_Query_Ptr Parsed_Query, Query_Ptr Query){
  int cnt = Count_Predicates(Query);
  Parsed_Query = Fill_Predicates(Query, cnt, Parsed_Query);//Parsed_Query->Joins, Parsed_Query->Filters);
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

static Projection_Ptr Fill_Projection_Array(Query_Ptr Query, int cnt) {
  //tokenize
  char *temp_proj[cnt];

  char *temp_query = Allocate_and_Copy_Str(Get_Query_Projections(Query));
  char *token = strtok(temp_query, " ");
  for(int i = 0; i < cnt; i++) {
	temp_proj[i] = (char*)malloc(strlen(token) * sizeof(char));
	strcpy(temp_proj[i], token);
    token = strtok(NULL, " ");
  }
  free(temp_query);

  Projection_Ptr proj = (Projection_Ptr)malloc(cnt * sizeof(struct Projection));
  for(int i = 0; i < cnt; i++) {
    Tokenize_to_rel_and_col(&(proj[i].rel), &(proj[i].col), temp_proj[i]);
    free(temp_proj[i]);
  }

  return proj;
}

static void Setup_Projections(Parsed_Query_Ptr Parsed_Query, Query_Ptr Query){
  int cnt = Count_Projections(Query);
  Parsed_Query->num_of_projections = cnt;
  Parsed_Query->Projections = Fill_Projection_Array(Query, cnt);
}


void Print_Parsed_Query(Parsed_Query_Ptr Parsed_Query) {
  printf("===RELATIONS===\n");
  for (int i = 0; i < Parsed_Query->num_of_relations; i++) {
    printf("%d:%d \t", i, Parsed_Query->relations[i]);
  }
  printf("\n");

  printf("===JOINS===\n");
  for (int i = 0; i < Parsed_Query->num_of_joins; i++) {
    printf("%d: %d.%d = %d.%d\t",
           i,
           Parsed_Query->Joins[i].rel1,
           Parsed_Query->Joins[i].col1,
           Parsed_Query->Joins[i].rel2,
           Parsed_Query->Joins[i].col2);
  }
  printf("\n");

  printf("===FILTERS===\n");
  if (Parsed_Query->num_of_filters != 0) {
    for (int i = 0; i < Parsed_Query->num_of_filters; i++) {
      printf("%d: %d.%d %s %d",
             i,
             Parsed_Query->Filters[i].rel,
             Parsed_Query->Filters[i].col,
             Parsed_Query->Filters[i].type,
             Parsed_Query->Filters[i].constant);
    }
    printf("\n");
  }

  printf("===PROJECTIONS===\n");
  for (int i = 0; i < Parsed_Query->num_of_projections; i++) {
    printf("%d: %d.%d\t", i, Parsed_Query->Projections[i].rel, Parsed_Query->Projections[i].col);
  }
  printf("\n\n");

}


Parsed_Query_Ptr Parse_Query(Query_Ptr Query){
  Parsed_Query_Ptr Parsed_Query = Allocate_Parsed_query();
  //relations
  Setup_Relations(Parsed_Query, Query);

  //joins and filters
  Setup_Joins_And_Filters(Parsed_Query,Query);

  //projections
  Setup_Projections(Parsed_Query,Query);
  Print_Parsed_Query(Parsed_Query);
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

Filter_Ptr Get_Filter_by_index(Filter_Ptr Filter, int i) {
  return &Filter[i];
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

int Get_Constant(Filter_Ptr Filter){
  return Filter->constant;
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
