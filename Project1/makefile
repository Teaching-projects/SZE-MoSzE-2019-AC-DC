all: Source.o Folder.o
	g++ -o bin Source.o Folder.o

Source.o: Source.cpp
	g++ -c Source.cpp
	
Folder.o: Folder.cpp
	g++ -c Folder.cpp
	
clean:
	rm -f *.o 