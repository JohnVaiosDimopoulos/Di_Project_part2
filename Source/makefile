CC = gcc
CFLAGS  = -g -Wall

main: main.o Initializer/Argument_Manager/Argument_Manager.o Initializer/Argument_Data/Arguments_Data.o Initializer/Table_Allocator/Table_Allocator.o Util/Utilities.o
	$(CC) $(CFLAGS) -o main main.o Argument_Manager.o Arguments_Data.o Table_Allocator.o Utilities.o

main.o: main.c Initializer/Argument_Manager/Argument_Manager.h Initializer/Argument_Data/Arguments_Data.h Initializer/Table_Allocator/Table_Allocator.h Util/Utilities.h
	$(CC) -c main.c 


Util/Utilities.o: Util/Utilities.c Util/Utilities.h
	$(CC) -c Util/Utilities.c


Initializer/Table_Allocator/Table_Allocator.o: Initializer/Table_Allocator/Table_Allocator.c Initializer/Table_Allocator/Table_Allocator.h
	$(CC) -c Initializer/Table_Allocator/Table_Allocator.c 

Initializer/Argument_Data/Arguments_Data.o: Initializer/Argument_Data/Arguments_Data.c Initializer/Argument_Data/Arguments_Data.h
	$(CC) -c Initializer/Argument_Data/Arguments_Data.c 

Initializer/Argument_Manager/Argument_Manager.o: Initializer/Argument_Manager/Argument_Manager.c Initializer/Argument_Manager/Argument_Manager.h
	$(CC) -c Initializer/Argument_Manager/Argument_Manager.c 
	
clean:
	$(RM) main *.o 
