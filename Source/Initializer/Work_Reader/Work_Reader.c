#include "Work_Reader.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../Util/Utilities.h"

static int Count_File_Lines(FILE *FilePtr) {
  int num_of_lines = 0;
  for(int c = getc(FilePtr);; c=getc(FilePtr)){
    if (c == '\n')
      num_of_lines++;
    if (c == EOF) {
      num_of_lines++;
      break;
    }
  }
  rewind(FilePtr);
  fclose(FilePtr);
  return num_of_lines;
}

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
