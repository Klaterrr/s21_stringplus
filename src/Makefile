all: s21_string.o
	make s21_string.a
	make test
	./test
	make gcov_report

my_test:
	rm -rf my_test.o s21_string.o my_tests
	gcc -c my_test.c -o my_test.o
	gcc -c s21_string.c -o s21_string.o -lm
	gcc s21_string.o my_test.o -o my_tests -lm
	./my_tests

test: s21_string.a
	gcc -Wall -Werror -Wextra test.c -o test -L. -l:s21_string.a -lcheck -lm -lsubunit -pthread -fprofile-arcs -ftest-coverage

s21_string.a: s21_string.o
	ar rcs s21_string.a s21_string.o

gcov_report:
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory out

s21_string.o:
	gcc -Wall -Werror -Wextra -c s21_string.c -o s21_string.o

clean:
	rm -rf s21_string main.o s21_string.o s21_string.a test out coverage.info test.gcda test.gcno