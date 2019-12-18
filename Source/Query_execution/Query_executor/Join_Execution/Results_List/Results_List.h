#ifndef SORT_JOIN_RESULTS_LIST_H
#define SORT_JOIN_RESULTS_LIST_H



#define LIMIT (1024 * 1024)
#define SIZE_OF_ARRAY_TUPLE (2 * 8)
#define LIST_SIZE ((LIMIT-12)/SIZE_OF_ARRAY_TUPLE)

#include <stdio.h>
#include <stdint.h>

typedef struct Result_List* List_Ptr;


List_Ptr Create_and_Initialize_List();
void Insert_Record(List_Ptr List, uint64_t id_1, uint64_t id_2);
void Delete_List(List_Ptr List);
void Print_List(List_Ptr List, FILE *fp);


#endif //SORT_JOIN_RESULTS_LIST_H
