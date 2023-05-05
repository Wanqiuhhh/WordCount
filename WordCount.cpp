#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int count_zifu(char *line) {
    int count = 0;
    for (int i = 0; i < strlen(line); i++) {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] != ',') {
            count++;
        }
    }
    return count;
}

int count_word(char *line) {
    int count = 0;
    char *delimiters = " \t\n,";
    char *token = strtok(line, delimiters);
    while (token != NULL) {
        count++;
        token = strtok(NULL, delimiters);
    }
    return count;
}

int main(int argc, char *argv[]) {
    char *filename = "text.txt";
    char *parameter;
    if (argc > 1) {
        parameter = argv[1];
        if (argc > 2) {
            filename = argv[2];
        }
    } else {
        printf("Usage: %s [-c|-w] [input_file_name]\n", argv[0]);
        return 1;
    }

    FILE *fp;
    char line[MAX_LINE_LENGTH];
    int count = 0;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: cannot open file %s.\n", filename);
        return 1;
    }

    while (fgets(line, MAX_LINE_LENGTH, fp)) {
        if (strcmp(parameter, "-c") == 0) {
            count += count_zifu(line);
        } else if (strcmp(parameter, "-w") == 0) {
            count += count_word(line);
        } else {
            printf("Error: invalid parameter %s.\n", parameter);
            return 1;
        }
    }

    printf("%s count: %d\n", (strcmp(parameter, "-c") == 0) ? "Character" : "Word", count);

    fclose(fp);

    return 0;
}
