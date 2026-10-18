#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void print_stat(char *pathname, char *file, int opt_i, int opt_p, int opt_q);
char* perm_to_str(mode_t mode, char *str);

int main(int argc, char *argv[]) {
    DIR *dp;
    struct dirent *dirp;
    char *dir = ".";
    int opt_i = 0, opt_p = 0, opt_q = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) opt_i = 1;
        else if (strcmp(argv[i], "-p") == 0) opt_p = 1;
        else if (strcmp(argv[i], "-Q") == 0) opt_q = 1;
        else {
            dir = argv[i];
        }
    }

    if ((dp = opendir(dir)) == NULL) {
        perror("opendir error");
        return 1;
    }

    while ((dirp = readdir(dp)) != NULL) {
        char pathname[1024];
        sprintf(pathname, "%s/%s", dir, dirp->d_name);
        print_stat(pathname, dirp->d_name, opt_i, opt_p, opt_q);
    }

    closedir(dp);
    return 0;
}

char* perm_to_str(mode_t mode, char *str) {
    strcpy(str, "----------");
    if (S_ISDIR(mode)) str[0] = 'd';
    else if (S_ISCHR(mode)) str[0] = 'c';
    else if (S_ISBLK(mode)) str[0] = 'b';
    else if (S_ISFIFO(mode)) str[0] = 'p';
    else if (S_ISLNK(mode)) str[0] = 'l';
    else if (S_ISSOCK(mode)) str[0] = 's';

    if (mode & S_IRUSR) str[1] = 'r';
    if (mode & S_IWUSR) str[2] = 'w';
    if (mode & S_IXUSR) str[3] = 'x';
    if (mode & S_IRGRP) str[4] = 'r';
    if (mode & S_IWGRP) str[5] = 'w';
    if (mode & S_IXGRP) str[6] = 'x';
    if (mode & S_IROTH) str[7] = 'r';
    if (mode & S_IWOTH) str[8] = 'w';
    if (mode & S_IXOTH) str[9] = 'x';

    return str;
}

void print_stat(char *pathname, char *file, int opt_i, int opt_p, int opt_q) {
    struct stat st;
    char perm[11];
    struct passwd *pw;
    struct group *gr;
    char *time_str;

    if (lstat(pathname, &st) == -1) {
        perror("lstat error");
        return;
    }

    perm_to_str(st.st_mode, perm);
    pw = getpwuid(st.st_uid);
    gr = getgrgid(st.st_gid);
    time_str = ctime(&st.st_mtime);

    char tbuf[64];
    strcpy(tbuf, time_str);
    if (strlen(tbuf) > 0 && tbuf[strlen(tbuf)-1] == '\n') {
        tbuf[strlen(tbuf)-1] = '\0';
    }
    char date_buf[32];
    if (strlen(tbuf) >= 19) {
        strncpy(date_buf, tbuf + 4, 12);
        date_buf[12] = '\0';
    } else {
        strcpy(date_buf, tbuf);
    }

    char display_name[256];
    strcpy(display_name, file);

    if (opt_p && S_ISDIR(st.st_mode)) {
        strcat(display_name, "/");
    }

    if (opt_q) {
        char temp[300];
        sprintf(temp, "\"%s\"", display_name);
        strcpy(display_name, temp);
    }

    printf("%ld ", (long)(st.st_blocks / 2));
    if (opt_i) {
        printf("%lu ", (unsigned long)st.st_ino);
    }
    printf("%s %ld %s %s %5ld %s %s\n",
           perm,
           (long)st.st_nlink,
           pw ? pw->pw_name : "unknown",
           gr ? gr->gr_name : "unknown",
           (long)st.st_size,
           date_buf,
           display_name);
}
