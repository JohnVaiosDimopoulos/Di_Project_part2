#include "Work_Reader.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../Util/Utilities.h"

void Read_Work_File(Argument_Data_Ptr Arg_Data) {
  const char *path = construct_Path(Get_Work_FileName(Arg_Data), Get_Dir_Name(Arg_Data));
  printf("\n\n\t%s\n", path);

  FILE *fp;
  Open_File_for_Read(&fp, path);

  int lines = Count_File_Lines(fp);
  printf("lines = %d\n", lines);

  char *line_buffer = NULL;
  size_t line_buffer_size = 0;

  Open_File_for_Read(&fp, path);

  for(int i = 0; i < lines; i++) {
    int read = getline(&line_buffer, &line_buffer_size, fp);
    char* command = malloc(sizeof(char) * line_buffer_size);
//    sscanf(line_buffer, "%s ", command);
    sprintf(command, "%s", line_buffer);
    printf("%s \n", command);
//    printf("%s \n", line_buffer);
    free(command);
  }
  fclose(fp);
}
