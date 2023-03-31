#include "s21_cat.h"

int main(int argc, char *argv[]) {
  parser(argc, argv);
  return 0;
}

void parser(int argc, char *argv[]) {
  bool err = 0;
  CatInfo options = {0, 0, 0, 0, 0, 0};  // создаем структуру и зануляем ее
  int opt = 0;                           // значение флага
  int option_index = 0;  // значение длинного флага

  static struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                         {"number", 0, 0, 'n'},
                                         {"squeeze-blank", 0, 0, 's'},
                                         {0, 0, 0, 0}};
  while ((opt = getopt_long(argc, argv, "+benstvTE", long_options,
                            &option_index)) != -1) {
    switch (opt) {
      case 'b':
        options.b = 1;
        break;
      case 'e':
        options.e = 1;
        options.v = 1;
        break;
      case 'n':
        options.n = 1;
        break;
      case 's':
        options.s = 1;
        break;
      case 't':
        options.t = 1;
        options.v = 1;
        break;
      case 'v':
        options.v = 1;
        break;
      case 'T':
        options.t = 1;
        break;
      case 'E':
        options.e = 1;
        break;
      default:
        fprintf(stderr,
                "cat: illegal option -- %c\nusage: cat [-benstuv] [file ...]\n",
                opt);
        err = 1;
        break;
    }
  }
  if (!err) {
    while (optind < argc) {
      open_file(argv, &options);
      optind++;
    }
  }
}

void open_file(char *argv[], CatInfo *options) {
  FILE *fp = NULL;
  if (options->b == 1 && options->n == 1)
    options->n = 0;  // так как b и n противоречат друг другу

  if ((fp = fopen(argv[optind], "r++")) == NULL) {
    fprintf(stderr, "cat: %s: No such file or directory\n", argv[optind]);
  } else {
    kitty(options, fp);
    fclose(fp);
  }
}

void kitty(CatInfo *options, FILE *fp) {
  int current = 0;  // текущий символ
  int count = 1;    // для нумерации строк
  int first = 1;    // проверка на первый вход в файл
  char last = ' ';  // предыдущий символ
  int n = 0;
  int flag1 = 0;
  int flag2 = 0;
  while ((current = fgetc(fp)) != EOF) {
    // -s - схлопывает повторяющиеся пустые строки до одной
    if (options->s) {
      if (current == '\n') n++;
      if (current != '\n') n = 0;
    }

    if (options->s == 0 || n < 3) {
      // -n - нумерует все строки при выводе содержимого файла
      if (options->n == 1) {
        if (last == '\n' || first == 1) printf("%6d\t", count++);
      }

      // -e - показывает непечатаемые символы, кроме табуляции и конца строки.
      if (options->e == 1 && current == '\n') {
        printf("$");
        flag1 = 1;
      }
    }

    if (current != '\n') {
      // -b - нумерует все строки, кроме пустых при выводе содержимого файла
      if (options->b == 1) {
        if (last == '\n' || first == 1) {
          printf("%6d\t", count++);
        }
      }

      // -t - отображает вкладки в файле как “^I”
      if (options->t == 1 && current == '\t') {
        printf("^I");
        flag2 = 1;
      }

      // -v  — показывает непечатаемые символы, кроме табуляции и конца строки
      if (options->v == 1) {
        if (current < 32 && current != 9 && current != 10)
          printf("^%c", current + 64);
        else if (current > 127 && current < 160)
          printf("M-^%c", current - 64);
        else if (current == 127)
          printf("^%c", current - 64);
        else if (!(current == 9 && options->t) &&
                 !(current == 10 && options->e))
          printf("%c", current);
      } else if (flag1 == 0 && flag2 == 0)
        printf("%c", current);

    } else {
      if (n < 3) printf("\n");
    }
    flag1 = 0;
    flag2 = 0;
    last = current;
    first = 0;
  }
}
