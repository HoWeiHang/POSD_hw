.PHONY: all clean 

all: clean hw3

hw3: *.o
ifeq (${OS}, Windows_NT)
	g++ -o hw3 $^ -lgtest
else
	g++ -o hw3 $^ -lgtest -lpthread
endif
	
*.o: *.cpp
	g++ -std=gnu++0x -c $^

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw3
endif
