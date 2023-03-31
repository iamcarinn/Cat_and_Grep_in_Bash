#ifndef SRC_CAT_S21_CAT_H
#define SRC_CAT_S21_CAT_H
#define _GNU_SOURCE

#include <fcntl.h>  // для работы с файлами, например open
#include <getopt.h>
#include <stdbool.h>  //содержит четыре макроса для работы с типом данных bool
#include <stdio.h>  // содержит определения макросов, константы и объявления функций и типов, используемых для различных операций стандартного ввода и вывода
#include <stdlib.h>  // содержит функции, занимающиеся выделением памяти
#include <string.h>  // для сравнения строк, чтобы учитывать полные имена флагов
#include <unistd.h>  // набор символических констант

typedef struct {
  bool b;
  bool e;
  bool n;
  bool s;
  bool t;
  bool v;
} CatInfo;

void parser(int argc, char *argv[]);
void open_file(char *argv[], CatInfo *options);
void kitty(CatInfo *ptions, FILE *fp);

#endif  // SRC_CAT_S21_CAT_H