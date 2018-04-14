#make file for my assignment 2
FLAGS=  -g -std=c++11
CC=g++


main:main.o huffman.o
	$(CC) $(FLAGS) -o $@ $^

main.o:main.cpp huffman.cpp huffman.h
	$(CC) $(FLAGS) -c $^

huffman.o:huffman.cpp huffman.h
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
	rm -f *.o  *.hdr
