CC = g++
CFLAGS = -std=c++0x -W -Wall -pedantic
LDFLAGS = -lGL -lGLU -lglut

SOURCES = main.cpp src/LUtil.cpp src/LTexture.cpp
OBJECTS = $(SOURCES: .cpp = .o)
EXECUTABLE = runWithPrimus

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
