CC = gcc
CFLAGS = -Wall -Werror -Wextra

all : s21_cat

s21_cat :
	$(CC) $(CFLAGS) -o s21_cat s21_cat.c

clean :
	rm -f s21_cat

rebuild :
	$(MAKE) clean
	$(MAKE) all

.PHONY: s21_cat