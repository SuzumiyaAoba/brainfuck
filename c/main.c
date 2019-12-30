#include <stdio.h>
#include <stdlib.h>

#define MAX_CODE_SIZE 60000
#define MAX_BUF_SIZE 30000

int read_code(char *file, char *code) {
  FILE *fp = fopen(file, "r");
  if (fp == NULL) {
    printf("cannot read file: %s\n", file);
    exit(1);
  }

  char c;
  int code_size;
  while ((c = fgetc(fp)) != EOF) {
    code[code_size++] = c;
  }
  
  fclose(fp);

  return code_size;
}

int main(int argc, char **argv) {
  
  if (argc < 2) {
    printf("few arguments");
    exit(1);
  }

  char* code = malloc(sizeof(char) * MAX_CODE_SIZE);
  int code_size = read_code(argv[1], code);

  char buf[MAX_BUF_SIZE] = { 0 };
  int dptr = 0;
  int loop = 0;

  for (int iptr = 0; iptr < code_size; iptr++) {
    switch (code[iptr]) {
    case '>':
      dptr++;
      break;
    case '<':
      dptr--;
      break;
    case '+':
      buf[dptr]++;
      break;
    case '-':
      buf[dptr]--;
      break;
    case '.':
      putchar(buf[dptr]);
      break;
    case ',':
      buf[dptr] = getchar();
      break;
    case '[':
      if (buf[dptr] == 0) {
        while (code[++iptr] != ']' || loop > 0) {
          if (code[iptr] == '[') {
            loop++;
          } else if (code[iptr] == ']') {
            loop--;
          }
        }
      }
      break;
    case ']':
      if (buf[dptr] != 0) {
        while (code[--iptr] != '[' || loop > 0) {
          if (code[iptr] == ']') {
            loop++;
          } else if (code[iptr] == '[') {
            loop--;
          }
        }
      }
      break;
    }
  }
}
