assign4.exe : assign4.o dir.o fat.o
	g++ -o assign4.exe assign4.o dir.o fat.o

assign4.o : assign4.c assign4.h
	g++ -c assign4.c
	
dir.o : dir.c assign4.h
	g++ -c dir.c

fat.o : fat.c assign4.h
	g++ -c fat.c
