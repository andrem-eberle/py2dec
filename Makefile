CC=g++


SRC=$(wildcard py2dec/*.cpp)
SRC+=$(wildcard py2dec/*.c)

OBJ=$(patsubst %.cpp,obj/%.o,$(SRC))
OBJ+=$(patsubst %.c,obj/%.o,$(CSRC))

CXXFLAGS=-fmax-errors=3 -Wno-format -Wno-write-strings -Wno-delete-incomplete -ggdb -DUSE_INTERMEDIATE_LANGUAGE

.DEFAULT_GOAL := all

obj/%.o: %.cpp | obj/py2dec
	$(CC) $(CXXFLAGS) $(patsubst obj/%.o,%.cpp,$@) -c -o $(patsubst %.o,%.o, $@)

obj/py2dec:
	mkdir -p obj/py2dec

all: $(OBJ) | bin
	echo $(OBJ)
	$(CC) $(OBJ) -o bin/py2dec

bin:
	mkdir -p bin

clean:
	rm -rf $(OBJ)


