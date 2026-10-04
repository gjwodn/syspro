#include <stdio.h>
#include <string.h>

void print_file(FILE *fp, int *line_number, int show_line_num) {
	int c;
	int is_start_of_line = 1;

	while((c = fgetc(fp)) != EOF) {
		if(show_line_num && is_start_of_line) {
			printf("%4d ", (*line_number)++);
			is_start_of_line = 0;
		}
		putchar(c);
		if(c == '\n') {
			is_start_of_line = 1;
		}
	}
}

int main(int argc, char *argv[])
{
	FILE *fp;
	int show_line_num = 0;
	int start_arg = 1;
	int line_number = 1;

	if(argc < 2) {
		fprintf(stderr, "How to use: %s [-n] file1 [file2 ...]\n", argv[0]);
		return 1;
	}

	if(strcmp(argv[1], "-n") == 0) {
		show_line_num = 1;
		start_arg = 2;

		if(argc < 3) {
			fprintf(stderr, "Error: No input file specified after -n\n");
			return 1;
		}
	}

	for(int i = start_arg; i < argc; i++) {
		if((fp = fopen(argv[i], "r")) == NULL) {
			fprintf(stderr, "Cannot open file: %s\n", argv[i]);
			continue;
		}

		print_file(fp, &line_number, show_line_num);
		fclose(fp);
	}

	return 0;
}
