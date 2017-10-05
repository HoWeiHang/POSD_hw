.PHONY: all clean 

all: clean hw2

hw2: *.o
ifeq (${OS}, Windows_NT)
	g++ -o hw2 $^ -lgtest
else
	g++ -o hw2 $^ -lgtest -lpthread
endif
	
%.o: %.cpp
	g++ -std=gnu++0x -c $^

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw2
endif
