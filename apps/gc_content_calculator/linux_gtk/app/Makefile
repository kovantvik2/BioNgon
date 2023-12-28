CC = gcc
OBJ =  obj/main.o obj/DB.o obj/interface_functions.o obj/nucleotide_functions.o obj/sqlite3.o obj/util.o obj/about.o
FLAGS_OBJ = -c -Wall -Wextra `pkg-config --libs --cflags gtk+-3.0` -ldl -lpthread -o
FLAGS_BIN = `pkg-config --libs --cflags gtk+-3.0` -ldl -lpthread

gc_content_calculator: $(OBJ)
	mkdir -p gc_content_calculator
	$(CC) -o bin/gc_content_calculator $^ $(FLAGS_BIN)
	cp bin/gc_content_calculator gc_content_calculator && cp -r interface gc_content_calculator
	chmod +x gc_content_calculator/gc_content_calculator
	rm -rf obj bin
	clear
	@echo "Build successful! Check for the gc_content_calculator folder. It should contain an executable file and a folder with the interface. Have a nice job!"

obj/main.o: main.c interface_functions.h nucleotide_functions.h sqlite3.h structures.h util.h DB.h about.h
	mkdir -p bin && mkdir -p obj
	$(CC) $< $(FLAGS_OBJ) $@

obj/DB.o: DB.c structures.h util.h sqlite3.h
	$(CC) $< $(FLAGS_OBJ) $@

obj/interface_functions.o: interface_functions.c structures.h util.h 
	$(CC) $< $(FLAGS_OBJ) $@

obj/nucleotide_functions.o: nucleotide_functions.c structures.h util.h
	$(CC) $< $(FLAGS_OBJ) $@

obj/sqlite3.o: sqlite3.c
	$(CC) -c $< -Wall -Wextra -o $@

obj/util.o: util.c structures.h sqlite3.h
	$(CC) $< $(FLAGS_OBJ) $@

obj/about.o: about.c structures.h
	$(CC) $< $(FLAGS_OBJ) $@

