.PHONY: all clean 

all: clean hw4

hw4: *.o
ifeq (${OS}, Windows_NT)
	g++ -o hw4 $^ -lgtest
else
	g++ -o hw4 $^ -lgtest -lpthread
endif
	
*.o: *.cpp
	g++ -std=gnu++0x -c $^

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw4
endif
