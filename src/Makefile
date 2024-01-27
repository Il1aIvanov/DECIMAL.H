FLAGS = -Wall -Werror -Wextra -std=c11 -g

OS = $(shell uname)

ifeq ($(OS), Darwin)
	TEST_FLAGS = -lcheck 
	OPEN = open 
endif

ifeq ($(OS), Linux)
	TEST_FLAGS = -lcheck -lsubunit -pthread -lrt -lm
	OPEN = xdg-open
endif

FUNCTIONS = s21_main_functions.c s21_supporting_functions.c s21_other_functions.c s21_comparison_operators.c s21_convertors.c

all: clean s21_decimal.a

s21_decimal.o: $(FUNCTIONS) s21_decimal.h
	gcc $(FLAGS) -c $(FUNCTIONS)

s21_decimal.a: s21_decimal.o
	ar rcs s21_decimal.a *.o
	ranlib s21_decimal.a
	rm -rf *.o

test: clean s21_decimal.a $(FUNCTIONS)
	gcc $(FLAGS) test.c $(FUNCTIONS) s21_decimal.a -o greport $(TEST_FLAGS)
	./greport

gcov_report:
	gcc $(FLAGS) -fprofile-arcs -ftest-coverage $(FUNCTIONS) test.c -o greport $(TEST_FLAGS)
	./greport
	lcov -t "teest" -o test.info -c -d .
	genhtml -o report test.info
	open ./report/index.html

valgrind:
	gcc $(FLAGS) test.c s21_decimal.a -o greport $(TEST_FLAGS)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./greport

format:
	clang-format -style=google -i *.c *.h

style:
	clang-format -style=google -n *.c *.h	


clean:
	rm -rf *.o *.a *.info coverage report *.out *.gcda test.out.dSYM
	rm -rf *.gcno html.report s21_decimal.h.gch report.out.dSYM greport.dSYM greport 
	