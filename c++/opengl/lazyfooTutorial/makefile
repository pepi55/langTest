CC = g++ -std=c++11
DEBUG = -g
FLAGS = -march=native -pipe -W -Wall -pedantic
LFLAGS = -lGL -lGLU -lglut -lIL -lILU -lGLEW
VPATH = ./src:./src/util:./src/prim:./src/tex:./src/ogl:./src/vertex

SOURCES = ./src/main.cpp \
					./src/util/LUtil.cpp \
					./src/tex/LTexture.cpp

OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS_DEBUG = $(SOURCES:.cpp=$(DEBUG).o)

EXECUTABLE = runWithPrimus

.DEFAULT_GOAL:= debug

.PHONY: clean

release: $(OBJECTS)
	$(CC) -O2 $(FLAGS) $(LFLAGS) $^ -o $(EXECUTABLE)

%.o: %.cpp
	$(CC) -O2 $(FLAGS) -c $< -o $@

debug: $(OBJECTS_DEBUG)
	$(CC) $(DEBUG) $(FLAGS) $(LFLAGS) $^ -o $(EXECUTABLE)-debug

%$(DEBUG).o: %.cpp
	$(CC) $(DEBUG) $(FLAGS) -c $< -o $@

clean:
ifneq ("$(wildcard $(EXECUTABLE)-debug)", "")
	rm $(OBJECTS_DEBUG)
	rm $(EXECUTABLE)-debug
else ifneq ("$(wildcard $(EXECUTABLE))", "")
	rm $(OBJECTS)
	rm $(EXECUTABLE)
endif
