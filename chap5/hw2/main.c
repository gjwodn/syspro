#include <stdio.h>
#include <stdlib.h>
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

    for (int i = total_lines; i >= 1; i--) {
        printf("%s\n", savedText[i]);
    }

    return 0;
}
