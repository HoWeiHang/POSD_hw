.PHONY: all clean 

all: clean hw7

hw7: *.o
ifeq (${OS}, Windows_NT)
	g++ -o hw7 $^ -lgtest
else
	g++ -o hw7 $^ -lgtest -lpthread
endif
	
*.o: *.cpp
	g++ -std=gnu++0x -c $^

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw7
endif
