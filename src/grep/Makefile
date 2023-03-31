CC = gcc
CFLAGS = -Wall -Werror -Wextra

all : s21_grep

s21_grep :
	$(CC) $(CFLAGS) -o s21_grep s21_grep.c

clean :
	rm -f s21_grep

rebuild :
	$(MAKE) clean
	$(MAKE) all

.PHONY: s21_grep