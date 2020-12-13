all: clean check_basics_tests check_io_tests check_convolution_tests full_program
.PHONY: all

full_program: basic_functions file_io convolution main
	gcc target/main.o target/basic_functions.o target/file_io.o target/convolution.o -o build/main.x

cuda_full_program: basic_functions file_io convolution cuda_main
	nvcc target/cumain.o target/basic_functions.o target/file_io.o target/convolution.o -o build/cuda_main.x -lm -std=c99

check_basics_tests: basic_functions check_basics
	gcc target/basic_functions.o target/check_basics.o -lcheck -o build/check_basics_tests

check_io_tests: basic_functions file_io check_io
	gcc target/file_io.o target/check_io.o target/basic_functions.o -lcheck -o build/check_file_io

check_convolution_tests: basic_functions convolution check_convolution
	gcc target/convolution.o target/check_convolution.o target/basic_functions.o -lcheck -o build/check_convolution

basic_functions:
	gcc -c src/basic_functions.c -o target/basic_functions.o -std=c99

file_io:
	gcc -c src/file_io.c -o target/file_io.o -std=c99

convolution:
	gcc -c src/convolution.c -o target/convolution.o -std=c99

main:
	gcc -c src/main.c -o target/main.o -std=c99

cuda_main:
	nvcc -c src/cuda_convolution.cu -o target/cuda_main.o -lm -std=c99

check_basics:
	gcc -c tests/check_basics.c -o target/check_basics.o

check_io:
	gcc -c tests/check_io.c -o target/check_io.o

check_convolution:
	gcc -c tests/check_convolution.c -o target/check_convolution.o

.PHONY: clean
clean:
	rm target/*.o
	rm build/*

