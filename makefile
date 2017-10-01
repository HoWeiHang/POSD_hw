INC_DIR = include

all: hw2

hw2: main.o Shapes.o Sort.o SimpleObject.o Atom.o Variable.o Number.o
ifeq (${OS}, Windows_NT)
	g++ -o hw2 main.o Shapes.o Sort.o SimpleObject.o Atom.o Variable.o Number.o -lgtest
else
	g++ -o hw2 main.o Shapes.o Sort.o SimpleObject.o Atom.o Variable.o Number.o -lgtest -lpthread
endif
	
main.o: main.cpp utSort.h utAtom.h utVariable.h utTerm.h
	g++ -std=gnu++0x -c main.cpp
Shapes.o: $(INC_DIR)/Shapes.h Shapes.cpp
	g++ -std=gnu++0x -c Shapes.cpp
Sort.o: $(INC_DIR)/Sort.h Sort.cpp
	g++ -std=gnu++0x -c Sort.cpp
SimpleObject.o: $(INC_DIR)/SimpleObject.h SimpleObject.cpp
    g++ -std=gnu++0x -c SimpleObject.cpp
Atom.o: $(INC_DIR)/Atom.h Atom.cpp
    g++ -std=gnu++0x -c Atom.cpp
Variable.o: $(INC_DIR)/Variable.h Variable.cpp
    g++ -std=gnu++0x -c Variable.cpp
Number.o: $(INC_DIR)/Number.h Number.cpp
g++ -std=gnu++0x -c Number.cpp

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw2
endif
