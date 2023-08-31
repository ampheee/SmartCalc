CC=gcc
FLAGS=-std=c11 -Wall -Werror -Wextra
PROGRAM_NAME=s21_smart_calc
TESTS_NAME=tests_$(PROGRAM_NAME)
MODULES_SRC=modules/
MODULES=$(MODULES_SRC)parse.c	$(MODULES_SRC)queue.c	$(MODULES_SRC)stack.c	\
		$(MODULES_SRC)arithmetics.c	$(MODULES_SRC)debug.c
BONUS=bonus/
CREDIT=$(BONUS)credit/
DEPOSIT=$(BONUS)deposit/

LIBS = `pkg-config --libs --cflags gtk+-3.0` -lm

OS=$(shell uname)
ifeq ($(OS), Darwin)
	CHECK_LIBS=-lcheck
else
	CHECK_LIBS=-lcheck	-lpthread	-lpthread	-lrt	-lm	-lsubunit
endif

all: clean uninstall install run

$(PROGRAM_NAME).a:
	@rm -rf *.o *.a
	$(CC) $(FLAGS)	$(LIBS) -c $(MODULES_SRC)*.c $(CREDIT)*.c $(DEPOSIT)*.c
	ar rc $(PROGRAM_NAME).a *.o
.PHONY : $(PROGRAM_NAME).a

install:	$(PROGRAM_NAME).a
	$(CC)	$(PROGRAM_NAME).a -o ../build/$(PROGRAM_NAME)	$(LIBS) #$(FLAGS)
	rm -rf *.o
.PHONY : install

run:
	../build/$(PROGRAM_NAME)
.PHONY : run

uninstall:
	rm -rf ../build/*
.PHONY : uninstall

clean_my:
	rm -rf *.o *.a	report/ $(TESTS_NAME) *.out *.gcda *.gcno *.dSYM gcov_* *.*.gch $(TESTS_NAME).c	coverage.info
.PHONY : clean

dvi:
	open readme.html
.PHONY : dvi

dist: clean
		tar -cf $(PROGRAM_NAME).tar ./*
.PHONY : dist

test: $(MODULES)
	checkmk	$(TESTS_NAME).check	|	$(CC)	$(FLAGS)	$^	-xc	-	$(CHECK_LIBS)	$(LIBS)	-o	$(TESTS_NAME)	--coverage
	rm -rf  $(TESTS_NAME)-*
.PHONY : test

gcov_report:	clean	test
	./$(TESTS_NAME)
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory gcov_report
	rm -rf	*.gcno	*.gcda gcov_rep gcov_rep.* coverage.info
	chmod -x *.* Makefile
	open gcov_report/index.html
.PHONY : gcov_report

clang:
	@cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.c $(MODULES)*.c $(BONUS)*.c	*.h
	clang-format -i *.c $(MODULES)*.c $(BONUS)*.c	*.h
.PHONY : clang

gtk_mac:
	brew install gtk+3
.PHONY : gtk_mac

gtk_linux:
	sudo apt-get install libgtk-3-dev
.PHONY : gtk_linux