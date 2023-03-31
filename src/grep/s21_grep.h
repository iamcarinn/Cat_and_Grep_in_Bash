#ifndef SRC_GREP_S21_GREP_H
#define SRC_GREP_S21_GREP_H
#define _GNU_SOURCE

#include <fcntl.h>  // для работы с файлами, например open
#include <getopt.h>
#include <regex.h>
#include <stdbool.h>  //содержит четыре макроса для работы с типом данных bool
#include <stdio.h>  // содержит определения макросов, константы и объявления функций и типов, используемых для различных операций стандартного ввода и вывода
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // набор символических констант

typedef struct {
  bool e;
  bool i;
  bool v;
  bool c;
  bool l;
  bool n;
  bool h;
  bool s;
  bool f;
  bool o;
} GrepInfo;

void parser(int argc, char *argv[]);
void open_file(char *argv[], GrepInfo *options, char *find_str, int many_files,
               char *find_file);
void grep(GrepInfo *options, FILE *fp, char *argv[], char *find_str,
          int many_files, char *find_file);
int open_file_flagf(char *find_str, char *find_file);

#endif  // SRC_GREP_S21_GREP_H
