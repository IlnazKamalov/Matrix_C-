CC=g++
SOURCE=s21_matrix_oop.cpp
GCOV_FLAGS=-fprofile-arcs -ftest-coverage
FLAGS=-Wall -Wextra -Werror -std=c++17 -lgtest -lgtest_main -lpthread

all: s21_matrix_oop.a

s21_matrix_oop.a:
	$(CC) -c $(SOURCE)
	ar rc s21_matrix_oop.a *.o
	ranlib s21_matrix_oop.a

test:
	$(CC) $(SOURCE) test.cpp $(FLAGS) $(GCOV_FLAGS) -o test
	./test

clean:
	rm -rf *.o *.gch *.a *.out test *.gcno *.gcda *.info html_report

style:
	clang-format --style=google -i $(SOURCE) s21_matrix_oop.h test.cpp
	clang-format --style=google -n $(SOURCE) s21_matrix_oop.h test.cpp

.PHONY: all s21_matrix_oop test style clean
