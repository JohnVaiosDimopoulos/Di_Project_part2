#include "Query_Executor.h"

static void Tokenizer(Query_Ptr Query) {



}


// we dont know how this will be done
void Execute_Query(Query_Ptr Query, Table_Ptr Relations){
  printf("Execute Query %s\n", Get_Query_Relations(Query));
  Tokenizer(Query);
}

