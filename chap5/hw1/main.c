#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_LINES 100
#define MAX_LEN 256

int main(int argc, char *argv[]) {
    int fd;
    char savedText[MAX_LINES][MAX_LEN];
    int total_lines = 0;
    char buf;

    if (argc != 2) {
        fprintf(stderr, "How to use: %s <filename>\n", argv[0]);
        return 1;
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("File open error");
        return 1;
    }

    printf("File read success\n");

    int line_idx = 1;
    int char_idx = 0;

    while (read(fd, &buf, 1) > 0) {
        if (buf == '\n') {
            savedText[line_idx][char_idx] = '\0';
            line_idx++;
            char_idx = 0;
        } else {
            savedText[line_idx][char_idx++] = buf;
        }
    }
    
    if (char_idx > 0) {
        savedText[line_idx][char_idx] = '\0';
        total_lines = line_idx;
    } else {
        total_lines = line_idx - 1;
    }
    
    close(fd);

    printf("Total Line : %d\n", total_lines);
    printf("You can choose 1 ~ %d Line\n", total_lines);

    char input[100];
    printf("Pls 'Enter' the line to select : ");
    if (scanf("%s", input) != 1) {
        return 1;
    }

    if (strcmp(input, "*") == 0) {
        for (int i = 1; i <= total_lines; i++) {
            printf("%s\n", savedText[i]);
        }
    } 
    else if (strchr(input, '-') != NULL) {
        int start, end;
        sscanf(input, "%d-%d", &start, &end);
        for (int i = start; i <= end && i <= total_lines; i++) {
            if (i >= 1) {
                printf("%s\n", savedText[i]);
            }
        }
    } 
    else if (strchr(input, ',') != NULL) {
        char *token = strtok(input, ",");
        while (token != NULL) {
            int line_num = atoi(token);
            if (line_num >= 1 && line_num <= total_lines) {
                printf("%s\n", savedText[line_num]);
            }
            token = strtok(NULL, ",");
        }
    } 
    else {
        int line_num = atoi(input);
        if (line_num >= 1 && line_num <= total_lines) {
            printf("%s\n", savedText[line_num]);
        }
    }

    return 0;
}
