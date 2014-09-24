OBJS = main.cpp src/LUtil.cpp
OBJ_NAME = runWithPrimus

CC = g++
COMPILER_FLAGS = -std=c++0x -W -Wall -pedantic
LINKER_FLAGS = -lGL -lGLU -lglut

all: $(OBJS)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(OBJS) -o $(OBJ_NAME)
