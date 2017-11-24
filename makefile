.PHONY: all clean 

all: clean hw6

hw6: *.o
ifeq (${OS}, Windows_NT)
	g++ -o hw6 $^ -lgtest
else
	g++ -o hw6 $^ -lgtest -lpthread
endif
	
*.o: *.cpp
	g++ -std=gnu++0x -c $^

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw6
endif
