#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t arrayInput(int array[30]) {
  printf("整数を入力してください（最大30個）。\n");
  printf("終了するには「n」を入力してください。\n> ");
  size_t count = 0;
  while (count < 30) {
    char input[255];
    char *endptr;
    int ch;
    if (fgets(input, sizeof input, stdin) == NULL)
      return 255;
    if (strchr(input, '\n') == NULL) {
      while ((ch = getchar()) != '\n' && ch != EOF) {
      };
      printf("入力が長すぎる可能性があります\n> ");
      continue;
    }
    if (strchr(input, 'n') != NULL) {
      if (count == 0) {
        printf("最低でも数値を1つ以上入力してください。\n> ");
        continue;
      }
      break;
    }
    errno = 0;
    long num = strtol(input, &endptr, 10);
    if (errno == ERANGE || num < INT_MIN || num > INT_MAX) {
      printf("数値が大きすぎるか小さすぎます\n> ");
      continue;
    }
    if (*endptr != '\n' || endptr == input) {
      printf("値が無効です\n> ");
      continue;
    }
    array[count] = (int)num;
    count++;
    if (count < 30) {
      printf("> ");
      continue;
    }
  }
  printf("入力完了!!\n");
  return count;
}

int main(void) {
  int array[30] = {};
  size_t array_size = arrayInput(array);
  if (array_size == 255) {
    return 1;
  }
  printf("入力値:{ ");
  for (size_t i = 0; i < array_size; i++) {
    if (i != 0) {
      printf(", ");
    }
    printf("%d", array[i]);
  }
  printf(" }\n");
  printf("ソートを実行...\n");

  for (size_t i = 1; i < array_size; i++) {
    for (size_t j = i; j > 0; j--) {
      if (array[j - 1] < array[j]) {
        int temp = array[j - 1];
        array[j - 1] = array[j];
        array[j] = temp;
      } else {
        break;
      }
    }
  }

  printf("結果:{ ");
  for (size_t i = 0; i < array_size; i++) {
    if (i != 0) {
      printf(", ");
    }
    printf("%d", array[i]);
  }
  printf(" }\n");

  return 0;
}