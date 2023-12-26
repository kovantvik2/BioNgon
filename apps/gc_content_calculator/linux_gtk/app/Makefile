CC = gcc


gc_content_calculator: main.o DB.o interface_functions.o nucleotide_functions.o sqlite3.o util.o about.o
	mkdir -p gc_content_calculator && mkdir -p gc_content_calculator/release
	$(CC) -o bin/gc_content_calculator obj/main.o obj/DB.o obj/interface_functions.o obj/nucleotide_functions.o obj/sqlite3.o obj/util.o obj/about.o `pkg-config --libs --cflags gtk+-3.0` -ldl -lpthread
	cp -r bin gc_content_calculator/release && cp -r interface gc_content_calculator
	chmod +x gc_content_calculator/release/bin/gc_content_calculator
	rm -r obj && rm -r bin

main.o: main.c interface_functions.h nucleotide_functions.h sqlite3.h structures.h util.h DB.h about.h
	mkdir -p bin && mkdir -p obj
	$(CC) -c main.c -Wall -Wextra `pkg-config --libs --cflags gtk+-3.0` -ldl -lpthread -o obj/main.o

DB.o: DB.c structures.h util.h sqlite3.h
	$(CC) -c DB.c -Wall -Wextra `pkg-config --libs --cflags gtk+-3.0` -ldl -lpthread -o obj/DB.o

interface_functions.o: interface_functions.c structures.h util.h 
	$(CC) -c interface_functions.c -Wall -Wextra `pkg-config --libs --cflags gtk+-3.0` -ldl -lpthread -o obj/interface_functions.o

nucleotide_functions.o: nucleotide_functions.c structures.h util.h
	$(CC) -c nucleotide_functions.c -Wall -Wextra `pkg-config --libs --cflags gtk+-3.0` -ldl -lpthread -o obj/nucleotide_functions.o

sqlite3.o: sqlite3.c
	$(CC) -c sqlite3.c -Wall -Wextra -o obj/sqlite3.o

util.o: util.c structures.h sqlite3.h
	$(CC) -c util.c -Wall -Wextra `pkg-config --libs --cflags gtk+-3.0` -ldl -lpthread -o obj/util.o

about.o: about.c structures.h
	$(CC) -c about.c -Wall -Wextra `pkg-config --libs --cflags gtk+-3.0` -ldl -lpthread -o obj/about.o

