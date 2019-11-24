all: Source.o Folder.o
	g++ -o bin Source.o Folder.o

Source.o: Project1/Source.cpp
	g++ Project1/Source.cpp
	
Folder.o: Project1/Folder.cpp
	g++ -c Project1/Folder.cpp
	
clean:
	rm -f *.o 