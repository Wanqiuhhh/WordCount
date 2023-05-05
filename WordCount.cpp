#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUF_SIZE 1024

int countChar(FILE *fp);
int countWord(FILE *fp);
char getChar(FILE *fp);

int main(int argc, char *argv[]) {
    int count = 0;
    FILE *fp;
    
    // 检查参数是否合法
    if (argc != 3) {
        printf("Usage: %s [-c | -w] input-file\n", argv[0]);
        return 1;
    }
    // 打开文件
    fp = fopen(argv[2], "r");
    if (fp == NULL) {
        printf("Cannot open file: %s\n", argv[2]);
        return 2;
    }
    
    // 根据参数计算字符数或单词数
    if (strcmp(argv[1], "-c") == 0) {
        count = countChar(fp);
        printf("字符数: %d\n", count);
    } else if (strcmp(argv[1], "-w") == 0) {
        count = countWord(fp);
        printf("单词数: %d\n", count);
    } else {
        printf("Invalid option: %s\n", argv[1]);
        return 1;
    }
    
    fclose(fp);
    return 0;
}

// 计算文件中字符数
int countChar(FILE *fp) {
    int count = 0;
    char ch = getChar(fp);
    while (ch != EOF) {
        count++;
        ch = getChar(fp);
    }
    return count;
}

// 计算文件中单词数
int countWord(FILE *fp) {
    int count = 0;
    char ch, prev_ch = ' ';
    while ((ch = getChar(fp)) != EOF) {
        if (ch == ' ' || ch == '\n' || ch == '\t' || ch == ',') {
            if (prev_ch != ' ' && prev_ch != '\n' && prev_ch != '\t' && prev_ch != ',') {
                count++;
            }
        }
        prev_ch = ch;
    }
    if (prev_ch != ' ' && prev_ch != '\n' && prev_ch != '\t' && prev_ch != ',') {
        count++;
    }
    return count;
}

// 读取一个字符，包括空格、制表符和换行符
char getChar(FILE *fp) {
    static char buf[MAX_BUF_SIZE];
    static int pos = 0;
    static int len = 0;

    if (pos == len) {
        len = fread(buf, sizeof(char), MAX_BUF_SIZE, fp);
        pos = 0;
    }
    if (pos == len) {
        return EOF;
    }
    return buf[pos++];
}
