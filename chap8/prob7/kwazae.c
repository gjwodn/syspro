#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

extern char **environ;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    if (strcmp(argv[1], "-e") == 0) {
        if (argc == 2) {
            for (int i = 0; environ[i] != NULL; i++) {
                printf("%s\n", environ[i]);
            }
        } else {
            char *val = getenv(argv[2]);
            if (val != NULL) {
                printf("%s = %s\n", argv[2], val);
            }
        }
    } else if (strcmp(argv[1], "-u") == 0) {
        uid_t ruid = getuid();
        uid_t euid = geteuid();
        struct passwd *rpw = getpwuid(ruid);
        struct passwd *epw = getpwuid(euid);

        printf("My Realistic User ID : %d(%s)\n", ruid, rpw ? rpw->pw_name : "");
        printf("My Valid User ID : %d(%s)\n", euid, epw ? epw->pw_name : "");
    } else if (strcmp(argv[1], "-g") == 0) {
        gid_t rgid = getgid();
        gid_t egid = getegid();
        struct group *rgr = getgrgid(rgid);
        struct group *egr = getgrgid(egid);

        printf("My Realistic Group ID : %d(%s)\n", rgid, rgr ? rgr->gr_name : "");
        printf("My Valid Group ID : %d(%s)\n", egid, egr ? egr->gr_name : "");
    } else if (strcmp(argv[1], "-i") == 0) {
        printf("my process number : [%d]\n", getpid());
    } else if (strcmp(argv[1], "-p") == 0) {
        printf("my parent's process number : [%d]\n", getppid());
    }

    return 0;
}
