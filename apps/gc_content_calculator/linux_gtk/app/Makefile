CC = gcc
OBJ =  obj/main.o obj/DB.o obj/interface_functions.o obj/nucleotide_functions.o obj/sqlite3.o obj/util.o obj/about.o
FLAGS_OBJ = -c -Wall -Wextra `pkg-config --libs --cflags gtk+-3.0` -ldl -lpthread -o
FLAGS_BIN = `pkg-config --libs --cflags gtk+-3.0` -ldl -lpthread

gc_content_calculator: main.o DB.o interface_functions.o nucleotide_functions.o sqlite3.o util.o about.o
	mkdir -p gc_content_calculator
	$(CC) -o bin/gc_content_calculator $(OBJ) $(FLAGS_BIN)
	cp bin/gc_content_calculator gc_content_calculator && cp -r interface gc_content_calculator
	chmod +x gc_content_calculator/gc_content_calculator
	rm -r obj && rm -r bin
	clear

main.o: main.c interface_functions.h nucleotide_functions.h sqlite3.h structures.h util.h DB.h about.h
	mkdir -p bin && mkdir -p obj
	$(CC) main.c $(FLAGS_OBJ) obj/main.o

DB.o: DB.c structures.h util.h sqlite3.h
	$(CC) DB.c $(FLAGS_OBJ) obj/DB.o

interface_functions.o: interface_functions.c structures.h util.h 
	$(CC) interface_functions.c $(FLAGS_OBJ) obj/interface_functions.o

nucleotide_functions.o: nucleotide_functions.c structures.h util.h
	$(CC) nucleotide_functions.c $(FLAGS_OBJ) obj/nucleotide_functions.o

sqlite3.o: sqlite3.c
	$(CC) -c sqlite3.c -Wall -Wextra -o obj/sqlite3.o

util.o: util.c structures.h sqlite3.h
	$(CC) util.c $(FLAGS_OBJ) obj/util.o

about.o: about.c structures.h
	$(CC) about.c $(FLAGS_OBJ) obj/about.o

