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
    
    // �������Ƿ�Ϸ�
    if (argc != 3) {
        printf("Usage: %s [-c | -w] input-file\n", argv[0]);
        return 1;
    }
    // ���ļ�
    fp = fopen(argv[2], "r");
    if (fp == NULL) {
        printf("Cannot open file: %s\n", argv[2]);
        return 2;
    }
    
    // ���ݲ��������ַ����򵥴���
    if (strcmp(argv[1], "-c") == 0) {
        count = countChar(fp);
        printf("�ַ���: %d\n", count);
    } else if (strcmp(argv[1], "-w") == 0) {
        count = countWord(fp);
        printf("������: %d\n", count);
    } else {
        printf("Invalid option: %s\n", argv[1]);
        return 1;
    }
    
    fclose(fp);
    return 0;
}

// �����ļ����ַ���
int countChar(FILE *fp) {
    int count = 0;
    char ch = getChar(fp);
    while (ch != EOF) {
        count++;
        ch = getChar(fp);
    }
    return count;
}

// �����ļ��е�����
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

// ��ȡһ���ַ��������ո��Ʊ���ͻ��з�
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
