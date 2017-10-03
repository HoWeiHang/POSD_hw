INC_DIR = include

all: hw2

hw2: main.o SimpleObject.o Atom.o Variable.o Number.o
ifeq (${OS}, Windows_NT)
	g++ -o hw2 main.o SimpleObject.o Atom.o Variable.o Number.o -lgtest
else
	g++ -o hw2 main.o SimpleObject.o Atom.o Variable.o Number.o -lgtest -lpthread
endif
	
main.o: main.cpp utAtom.h utVariable.h utTerm.h
	g++ -std=gnu++0x -c main.cpp
SimpleObject.o: $(INC_DIR)/simpleObject.h SimpleObject.cpp
	g++ -std=gnu++0x -c SimpleObject.cpp
Atom.o: $(INC_DIR)/atom.h Atom.cpp
	g++ -std=gnu++0x -c Atom.cpp
Variable.o: $(INC_DIR)/variable.h Variable.cpp
	g++ -std=gnu++0x -c Variable.cpp
Number.o: $(INC_DIR)/Number.h Number.cpp
	g++ -std=gnu++0x -c number.cpp

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw2
endif
