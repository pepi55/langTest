CC = g++ -std=c++11
DEBUG = -ggdb
FLAGS = -march=native -pipe -W -Wall -pedantic
LFLAGS = -lSDL2 -lSDL2_image
VPATH = ./src:./src/sdl:./src/util

SOURCES = ./src/main.cpp \
					./src/util/LUtilSDL.cpp \
					./src/sdl/LTextureSDL.cpp

OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS_DEBUG = $(SOURCES:.cpp=$(DEBUG).o)

EXECUTABLE = runWithPrimus

.DEFAULT_GOAL:= debug

.PHONY: clean

release: $(OBJECTS)
	@echo "================="
	@echo "Linking target $@"
	@$(CC) -O2 $(FLAGS) $(LFLAGS) $^ -o $(EXECUTABLE)
	@echo "================="
	@echo "Linking finished"
	@echo "================="

%.o: %.cpp
	@echo "================="
	@echo "Compiling $<"
	@$(CC) -O2 $(FLAGS) -c $< -o $@

debug: $(OBJECTS_DEBUG)
	@echo "================="
	@echo "Linking target $@"
	$(CC) $(DEBUG) $(FLAGS) $(LFLAGS) $^ -o $(EXECUTABLE)-debug
	@echo "================="
	@echo "Linking finished"
	@echo "================="

%$(DEBUG).o: %.cpp
	@echo "================="
	@echo "Compiling $<"
	$(CC) $(DEBUG) $(FLAGS) -c $< -o $@

clean:
ifneq ("$(wildcard $(EXECUTABLE)-debug)", "")
	@echo "================="
	@echo "Removing $(OBJECTS_DEBUG)"
	@rm $(OBJECTS_DEBUG)
	@echo "================="
	@echo "Removing $(EXECUTABLE)-debug"
	@rm $(EXECUTABLE)-debug
	@echo "================="
else ifneq ("$(wildcard $(EXECUTABLE))", "")
	@echo "================="
	@echo "Removing $(OBJECTS)"
	@rm $(OBJECTS)
	@echo "================="
	@echo "Removing $(EXECUTABLE)"
	@rm $(EXECUTABLE)
	@echo "================="
endif
