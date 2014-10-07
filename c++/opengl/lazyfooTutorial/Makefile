CC = g++
FLAGS = $(CFLAGS) -std=c++0x -W -Wall -pedantic
LDFLAGS = -lGL -lGLU -lglut -lIL -lILU

SOURCES = main.cpp src/LUtil.cpp src/LTexture.cpp
OBJECTS = $(SOURCES: .cpp = .o)
EXECUTABLE = runWithPrimus

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(FLAGS) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(FLAGS) $< -o $@
