#include <stdio.h>
#include <stddef.h> // 添加这行来包含stddef.h头文件
#include "linenoise.h"

int main() {
  char* line;
  linenoiseHistoryLoad("history.txt"); // 加载历史记录

  while ((line = linenoise(">> ")) != NULL) {
    if (line[0] != '\0') {
      printf("执行命令: %s\n", line);
      linenoiseHistoryAdd(line); // 添加到历史记录
      linenoiseHistorySave("history.txt"); // 保存历史记录
    }

    linenoiseFree(line);
  }

  linenoiseHistorySave("history.txt"); // 保存历史记录;
  return 0;
}