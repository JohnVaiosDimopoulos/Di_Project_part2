
#ifndef SORT_JOIN_ARGUMENTS_DATA_H
#define SORT_JOIN_ARGUMENTS_DATA_H

typedef struct Arguments_Data* Argument_Data_Ptr;

Argument_Data_Ptr Create_Argument_Data(const char *, const char *);
const char* Get_Init_FileName(Argument_Data_Ptr Data);
const char* Get_Work_FileName(Argument_Data_Ptr Data);
void Delete_Argument_Data(Argument_Data_Ptr);

#endif //SORT_JOIN_ARGUMENTS_DATA_H
