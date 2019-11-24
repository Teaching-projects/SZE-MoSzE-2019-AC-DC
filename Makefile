all: Project1/Source.o Project1/Folder.o
	g++ -o bin Project1/Source.o Project1/Folder.o

Source.o: Project1/Source.cpp
	g++ Project1/Source.cpp
	
Folder.o: Project1/Folder.cpp
	g++ -c Project1/Folder.cpp
	
clean:
	rm -f Project1/*.o 