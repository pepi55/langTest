################################################################
#
##CC = gcc -std=c99
#CC = g++ -std=c++11
#FLAGS = -march=native -pipe -W -Wall -pedantic
#LFLAGS = -lGL -lGLU -lglut -lIL -lILU
#
#SOURCES = main.cpp src/LUtil.cpp src/LTexture.cpp
#OBJECTS = $(SOURCES:.cpp=.o)
#EXECUTABLE = runWithPrimus
#DEBUGGER = gdb
#
#all: $(SOURCES) $(EXECUTABLE)
#
#$(EXECUTABLE): $(OBJECTS)
#	$(CC) -O2 $(FLAGS) $(LDFLAGS) $(OBJECTS) -o $@
#
#debug: $(SOURCES) $(DEBUGGER)
#
#$(DEBUGGER): $(OBJECTS)
#	$(CC) -g$(DEBUGGER) $(FLAGS) $(LDFLAGS) $(OBJECTS) -o $@
#
#.cpp.o:
#	$(CC) $(FLAGS) $(LDFLAGS) $(SOURCES) $< -o $@
#
################################################################

CC = g++ -std=c++11
FLAGS = -march=native -pipe -W -Wall -pedantic
LFLAGS = -lGL -lGLU -lglut -lIL -lILU

OBJECTS = main.o LUtil.o LTexture.o
EXECUTABLE = runWithPrimus
DEBUGGER = gdb

.DEFAULT_GOAL:= debug

.PHONY: clean

release: $(OBJECTS)
	$(CC) -O2 $(FLAGS) $(LFLAGS) $(OBJECTS) -o $(EXECUTABLE)

debug: $(OBJECTS)
	$(CC) -g$(DEBUGGER) $(FLAGS) $(LFLAGS) $(OBJECTS) -o $(EXECUTABLE)-debug

main.o: main.cpp src/LUtil.hpp src/LOpenGL.hpp
	$(CC) -c $(FLAGS) main.cpp

LTexture.o: src/LTexture.cpp src/LOpenGL.hpp src/LRect.hpp
	$(CC) -c $(FLAGS) src/LTexture.cpp

LUtil.o: src/LUtil.cpp src/LUtil.hpp src/LTexture.hpp src/LOpenGL.hpp
	$(CC) -c $(FLAGS) src/LUtil.cpp

clean:
	@if [ -f '$(EXECUTABLE)' ]; then \
		rm -f *.o $(EXECUTABLE); \
		echo "removed $(EXECUTABLE)"; \
	fi
	@if [ -f '$(EXECUTABLE)-debug' ]; then \
		rm -f *.o $(EXECUTABLE)-debug; \
		echo "removed $(EXECUTABLE)-debug"; \
	fi
