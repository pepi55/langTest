CC = g++ -std=c++11
FLAGS = -march=native -pipe -W -Wall -pedantic
LFLAGS = -lGL -lGLU -lglut -lIL -lILU -lGLEW

ODIR = obj/
SDIR = src/

OBJECTS = main.o LUtil.o LTexture.o

EXECUTABLE = runWithPrimus
DEBUGGER = gdb

.DEFAULT_GOAL:= debug

.PHONY: clean

release: $(OBJECTS)
	$(CC) -O2 $(FLAGS) $(LFLAGS) $^ -o $(EXECUTABLE)

debug: $(OBJECTS)
	$(CC) -g$(DEBUGGER) $(FLAGS) $(LFLAGS) $^ -o $(EXECUTABLE)-debug

%.o: $(SDIR)%.cpp $(SDIR)%.hpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm $(OBJECTS)
ifneq ("$(wildcard $(EXECUTABLE)-debug)", "")
	rm $(EXECUTABLE)-debug
else ifneq ("$(wildcard $(EXECUTABLE))", "")
	rm $(EXECUTABLE)
endif
