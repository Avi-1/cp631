check_basics_tests: clean basic_functions check_basics
	gcc target/basic_functions.o target/check_basics.o -lcheck -lm -lpthread -lrt -o check_basics_tests

basic_functions:
	gcc -c src/basic_functions.c -o target/basic_functions.o

check_basics:
	gcc -c tests/check_basics.c -o target/check_basics.o

clean:
	rm target/*.o

