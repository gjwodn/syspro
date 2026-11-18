#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int child, pid, fd, status;

    if (argc < 3) {
        fprintf(stderr, "사용법: %s 출력파일 명령어 [인자...]\n", argv[0]);
        exit(1);
    }

    pid = fork();
    if (pid == 0) {
        fd = open(argv[1], O_CREAT | O_TRUNC | O_WRONLY, 0660);
        if (fd < 0) {
            perror("open 실패");
            exit(1);
        }
        dup2(fd, 1);
        close(fd);
        execvp(argv[2], &argv[2]);
        fprintf(stderr, "%s: 실행 불가\n", argv[2]);
        exit(1);
    } else {
        child = wait(&status);
        printf("[%d] child process %d end \n", getpid(), child);
    }
    return 0;
}
