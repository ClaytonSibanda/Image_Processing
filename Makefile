#make file for my assignment 2
FLAGS=  -g -Wall -std=c++11
CC=g++


imageops:imageops.o main.o
	$(CC) $(FLAGS) -o $@ $^

main.o:main.cpp imageops.cpp imageops.h
	$(CC) $(FLAGS) -c $^

imageops.o:imageops.cpp imageops.h
	$(CC) $(FLAGS) -c $^
run:
	./main $(INPUT) $(OUTPUT)

test:
	$(CC) $(FLAGS) -Wall -o tests tests.cpp huffman.cpp huffman.h
	./tests

run_test:
	./tests

build:
	mkdir SBNCLA002
	cp -r -t SBNCLA002 *.md *.cpp *.h .git Makefile
	tar -czvf SBNCLA002.tar.gz SBNCLA002



clean:
	rm -f *.o imageops
