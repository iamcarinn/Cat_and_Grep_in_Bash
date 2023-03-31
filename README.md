# Cat_and_Grep_in_Bash
* Educational project "Schools 21".<br>
**Development of Bash text utilities: cat & grep in C programming languages.**

____

### cat Options
**TEMPLATE:** `cat [OPTION] [FILE]`
  
| No. | Options | Description | Status |
| ------ | ------ | ------ | ------ |
| 1 | -b (GNU: --number-nonblank) | numbers only non-empty lines | ✅     |
| 2 | -e implies -v (GNU only: -E the same, but without implying -v) | but also display end-of-line characters as $  | ✅     |
| 3 | -n (GNU: --number) | number all output lines | ✅     |
| 4 | -s (GNU: --squeeze-blank) | squeeze multiple adjacent blank lines | ✅     |
| 5 | -t implies -v (GNU: -T the same, but without implying -v) | but also display tabs as ^I  | ✅     |


### grep Options
**TEMPLATE:** `grep [OPTION] [TEMPLATE] [FILE]`

| No. | Options | Description | Status |
| ------ | ------ | ------ | ------ |
| 1 | -e | pattern | ✅     |
| 2 | -i | Ignore uppercase vs. lowercase.  | ✅     |
| 3 | -v | Invert match. | ✅     |
| 4 | -c | Output count of matching lines only. | ✅     |
| 5 | -l | Output matching files only.  | ✅     |
| 6 | -n | Precede each matching line with a line number. | ✅     |
| 7 | -h | Output matching lines without preceding them by file names. | ✅     |
| 8 | -s | Suppress error messages about nonexistent or unreadable files. | ✅     |
| 9 | -f file | Take regexes from a file. | ✅     |
| 10 | -o | Output the matched parts of a matching line. | ✅     |

## Usage

1. Clone this repository via
   - SSH `git@github.com:rynortheast/21-simple-bash-utils.git` or
   - HTTPS `https://github.com/rynortheast/21-simple-bash-utils.git`
2. Change code base if necessary
3. Working with s21_cat:
   - Run `make s21_cat` to build programm
   - Run `make test` to run main tests
4. Working with s21_grep:
   - Run `make s21_grep` to build programm
   - Run `make test` to run main tests
