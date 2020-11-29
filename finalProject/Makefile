all: clean check_basics_tests check_io_tests
.PHONY: all

check_io_tests: file_io check_io
	gcc target/file_io.o target/check_io.o -lcheck -lm -lpthread -lrt -o build/check_file_io

check_basics_tests: basic_functions check_basics
	gcc target/basic_functions.o target/check_basics.o -lcheck -lm -lpthread -lrt -o build/check_basics_tests

basic_functions:
	gcc -c src/basic_functions.c -o target/basic_functions.o

file_io:
	gcc -c src/file_io.c -o target/file_io.o

check_basics:
	gcc -c tests/check_basics.c -o target/check_basics.o

check_io:
	gcc -c tests/check_io.c -o target/check_io.o

.PHONY: clean
clean:
	rm target/*.o
	rm build/*

