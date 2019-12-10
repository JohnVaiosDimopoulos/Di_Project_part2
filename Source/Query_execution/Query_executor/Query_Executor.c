#include "Query_Executor.h"
#include "../../Util/Utilities.h"
#include "../Query_parser/Query_parser.h"
#include <stdio.h>
#include <string.h>








void Execute_Query(Query_Ptr Query, Table_Ptr Relations){

  //1.Parse the query
  Parsed_Query_Ptr Parsed_Query = Parse_Query(Query);

  //2.do the preparations
    //1.give row ids
    //2.make the execution tree

  //3.execute the query based on the preparation
    //1.input the execution tree + the relations we need to
    //2.get the result as an output


}

