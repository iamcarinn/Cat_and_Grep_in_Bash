#include "s21_grep.h"

int main(int argc, char *argv[]) {
  parser(argc, argv);
  return 0;
}

void parser(int argc, char *argv[]) {
  GrepInfo options = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  char find_str[4096] = {0};  // для шаблонов
  char find_file[4096] = {0};  // для названия файла при флаге -f

  bool err = 0;

  int opt = 0;  // значение флага
  while ((opt = getopt_long(argc, argv, "e:ivclnhsf:o", NULL, NULL)) != -1) {
    switch (opt) {
      case 'e':
        options.e = 1;
        if (find_str[0] != '\0') strcat(find_str, "|");
        strcat(find_str, optarg);
        break;
      case 'i':
        options.i = 1;
        break;
      case 'v':
        options.v = 1;
        break;
      case 'c':
        options.c = 1;
        break;
      case 'l':
        options.l = 1;
        break;
      case 'n':
        options.n = 1;
        break;
      case 'h':
        options.h = 1;
        break;
      case 's':
        options.s = 1;
        break;
      case 'f':
        options.f = 1;
        strcat(find_file, optarg);
        break;
      case 'o':
        options.o = 1;
        break;
      default:
        fprintf(stderr, "ERROR\n");
        err = 1;
        break;
    }
  }

  if (!options.f && !options.e && argv[optind] != NULL)
    strcat(find_str, argv[optind]);
  if (options.f || options.e) optind--;

  // проверка на несколько файлов
  int many_files = 0;
  if (argc - optind > 2) many_files = 1;

  if (!err) {
    while (optind + 1 < argc) {
      open_file(argv, &options, find_str, many_files, find_file);
      optind++;
    }
  }
}

void open_file(char *argv[], GrepInfo *options, char *find_str, int many_files,
               char *find_file) {
  FILE *fp = NULL;

  if ((fp = fopen(argv[optind + 1], "r++")) == NULL) {
    if (!options->s) {
      fprintf(stderr, "grep: %s: No such file or directory\n",
              argv[optind + 1]);
    }
  } else {
    grep(options, fp, argv, find_str, many_files, find_file);
    fclose(fp);
  }
}

int open_file_flagf(char *find_str, char *find_file) {
  FILE *fp = NULL;
  int i = 0;

  if ((fp = fopen(find_file, "r")) != NULL) {
    int c;

    if (find_str[0] != '\0') strcat(find_str, "|");

    while (find_str[i] != '\0') {
      i++;
    }
    while ((c = fgetc(fp)) != EOF) {
      if (c == 13 || c == 10) find_str[i++] = '|';
      if (c != 13 && c != 10) find_str[i++] = c;
    }
    fclose(fp);
  } else {
    fprintf(stderr, "grep: %s: No such file or directory\n", find_file);
    i = -1;
  }

  if (find_str[i - 1] == '|') find_str[i - 1] = '\0';
  return i;
}

void grep(GrepInfo *options, FILE *fp, char *argv[], char *find_str,
          int many_files, char *find_file) {
  regex_t regex;
  regmatch_t pm[1];  // для флага -o
  char str[1024];    // строка, которую будем выводить
  int f_patt = 0;  // проверка на ошибку в функции open_file_flagf()

  // если флаг -f
  if (options->f) {
    f_patt = open_file_flagf(find_str, find_file);
  }

  if (f_patt != -1) {
    int l = REG_EXTENDED;
    if (options->i) {
      l = REG_EXTENDED | REG_ICASE;
    }

    int a = regcomp(&regex, find_str, l);

    int count_str = 0;  // счетчик строк
    int was = 0;        // счетчик успехов
    int was_file = 0;   // наличие успеха в файле

    if (a == 0) {
      while ((!feof(fp)) && fgets(str, 1024, fp)) {
        int b = regexec(&regex, str, 1, pm, 0);
        count_str++;
        if ((!options->v && b == 0) || (options->v && b != 0)) {
          was++;
          was_file = 1;

          if (options->v) options->o = 0;

          if (!options->c && !options->l) {
            // выводим название файла, если их больше 1-ого
            if (many_files && !options->h) {
              printf("%s:", argv[optind + 1]);
            }

            if (options->n) {
              printf("%d:", count_str);
            }

            if (options->o) {
              int step = 0;
              while (regexec(&regex, str + step, 1, pm, 0) == 0) {
                char *buff = strndup(str + step + pm[0].rm_so,
                                     pm[0].rm_eo - pm[0].rm_so);
                printf("%s", buff);
                if (buff[strlen(buff) - 1] != '\n') {
                  printf("\n");
                }
                free(buff);
                step = step + pm[0].rm_eo;
              }
            } else
              printf("%s", str);

            if (feof(fp) && !options->o) {
              printf("\n");
            }
          }
        }
      }

      if (options->c) {
        if (many_files && !options->h) {
          printf("%s:", argv[optind + 1]);
        }
        if (!options->l)
          printf("%d\n", was);
        else
          printf("%d\n", was_file);
      }

      if (options->l && was > 0) {
        printf("%s\n", argv[optind + 1]);
      }
    } else {
      fprintf(stderr, "ERROR\n");
    }
    regfree(&regex);
  }
}
