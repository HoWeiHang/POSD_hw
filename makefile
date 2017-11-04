.PHONY: all clean 

all: clean hw5

hw5: *.o
ifeq (${OS}, Windows_NT)
	g++ -o hw5 $^ -lgtest
else
	g++ -o hw5 $^ -lgtest -lpthread
endif
	
*.o: *.cpp
	g++ -std=gnu++0x -c $^

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw5
endif
