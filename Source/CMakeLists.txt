cmake_minimum_required(VERSION 3.15)
project(Multi_join)

set(CMAKE_C_STANDARD 99)

add_executable(Multi_join main.c Initializer/Argument_Data/Arguments_Data.c Initializer/Argument_Data/Arguments_Data.h Initializer/Argument_Manager/Argument_Manager.c Initializer/Argument_Manager/Argument_Manager.h Util/Utilities.c Util/Utilities.h Initializer/Table_Allocator/Table_Allocator.c Initializer/Table_Allocator/Table_Allocator.h Basic_Structs/Basic_Structs.h)