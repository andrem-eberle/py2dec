CC=g++

SRC=$(wildcard py2dec/*.cpp)
SRC+=$(wildcard py2dec/*.c)

OBJ=$(patsubst %.cpp,obj/%.o,$(SRC))
OBJ+=$(patsubst %.c,obj/%.o,$(CSRC))

CXXFLAGS=-fmax-errors=3 -Wno-format -Wno-write-strings -Wno-delete-incomplete -ggdb -DUSE_INTERMEDIATE_LANGUAGE

obj/%.o: %.cpp
	$(CC) $(CXXFLAGS) $(patsubst obj/%.o,%.cpp,$@) -c -o $(patsubst %.o,%.o, $@)

all: $(OBJ)
	echo $(OBJ)
	$(CC) $(OBJ) -o bin/py2dec

clean:
	rm -rf $(OBJ)


