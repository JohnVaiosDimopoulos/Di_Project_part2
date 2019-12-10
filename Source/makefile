CC = gcc
CFLAGS  = -g -Wall

main: main.o Initializer/Argument_Manager/Argument_Manager.o Initializer/Argument_Data/Arguments_Data.o Initializer/Table_Allocator/Table_Allocator.o Util/Utilities.o Work_Reader/Work_Reader.o Work_Executor/Work_Executor.o Query_execution Batch/Batch.o Query/Query.o
	$(CC) $(CFLAGS) -o main main.o Argument_Manager.o Arguments_Data.o Table_Allocator.o Utilities.o Work_Reader.o Work_Executor.o Query_Executor.o Batch.o Query.o

main.o: main.c Initializer/Argument_Manager/Argument_Manager.h Initializer/Argument_Data/Arguments_Data.h Initializer/Table_Allocator/Table_Allocator.h Util/Utilities.h Work_Reader/Work_Reader.h Work_Executor/Work_Executor.h Query_execution Batch/Batch.h Query/Query.h
	$(CC) -c main.c 


Util/Utilities.o: Util/Utilities.c Util/Utilities.h
	$(CC) -c Util/Utilities.c


Query/Query.o: Query/Query.c Query/Query.h
	$(CC) -c Query/Query.c

Batch/Batch.o: Batch/Batch.c Batch/Batch.h
	$(CC) -c Batch/Batch.c

Query_Executor/Query_Executor.o: Query_execution Query_execution
	$(CC) -c Query_Executor/Query_Executor.c

Work_Executor/Work_Executor.o: Work_Executor/Work_Executor.c Work_Executor/Work_Executor.h
	$(CC) -c Work_Executor/Work_Executor.c

Work_Reader/Work_Reader.o: Work_Reader/Work_Reader.c Work_Reader/Work_Reader.h
	$(CC) -c Work_Reader/Work_Reader.c

Initializer/Table_Allocator/Table_Allocator.o: Initializer/Table_Allocator/Table_Allocator.c Initializer/Table_Allocator/Table_Allocator.h
	$(CC) -c Initializer/Table_Allocator/Table_Allocator.c 

Initializer/Argument_Data/Arguments_Data.o: Initializer/Argument_Data/Arguments_Data.c Initializer/Argument_Data/Arguments_Data.h
	$(CC) -c Initializer/Argument_Data/Arguments_Data.c 

Initializer/Argument_Manager/Argument_Manager.o: Initializer/Argument_Manager/Argument_Manager.c Initializer/Argument_Manager/Argument_Manager.h
	$(CC) -c Initializer/Argument_Manager/Argument_Manager.c 
	
clean:
	$(RM) main *.o 
