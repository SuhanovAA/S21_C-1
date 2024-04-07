FLAGS=-Wall -Werror -Wextra -std=c11
CC=gcc $(FLAGS)
FILE=s21_matrix
FILETEST=tests/*
FILEREPORT=s21_test_report
FILETESTO=s21_test
DIRREPORT=report
LIB=$(FILE).a
COVFLAG=-fprofile-arcs -ftest-coverage

OS = $(shell uname)

ifeq ($(OS), Darwin)
	TESTFLAGS=-pthread -lm -lcheck
	OPEN_CMD=open
else
	TESTFLAGS=-pthread -lcheck_pic -lrt -lm -lsubunit
	OPEN_CMD=xdg-open
endif


all: clean $(FILE).a gcov_report

o_files:
	$(CC) -c *.c

$(FILE).a: o_files
	ar rcs $(LIB) *.o

test: clang $(FILE).a
	$(CC) $(FILETEST).c $(FILE).a -o $(FILETESTO) $(TESTFLAGS)
	./$(FILETESTO)

gcov_report: $(FILE).a
	$(CC) $(COVFLAG) $(FILETEST).c *.c -o $(FILEREPORT) $(TESTFLAGS)
	./$(FILEREPORT)
	lcov -t "$(FILE)" -o test.info -c -d .  
	genhtml -o $(DIRREPORT) test.info
	$(OPEN_CMD) $(DIRREPORT)/index.html

rep: gcov_report

clean:
	rm -rf *.o *.a *.gcno *.gcda *.info $(DIRREPORT) $(FILETESTO) $(FILEREPORT)
	make clang

#style
cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h tests/*.c tests/*.h

clang:
	clang-format -style=Google -i *.c *.h tests/*.c tests/*.h

check: cpp clang

leaks: test
	leaks -atExit -- ./s21_test

#install for OS
install_macOS:
	brew install gcc
	brew install lcov
	brew install pkg-config

brsw:
	eval /opt/goinfre/$(USERNAME)/homebrew/bin/brew shellenv; \
	brew update --force --quiet; \
	chmod -R go-w "$(brew --prefix)/share/zsh"

install_brew:
	cd /opt/goinfre/$(USERNAME); \
	mkdir homebrew; \
	git clone https://github.com/Homebrew/brew homebrew; \
	make brsw