#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *src, *dst;
	int c;

	if(argc != 3) {
		fprintf(stderr, "How to use: %s source_file target_file\n", argv[0]);
		return 1;
	}

	if((src = fopen(argv[1], "r")) == NULL) {
		perror("Source file open error");
		return 1;
	}

	if((dst = fopen(argv[2], "a")) == NULL) {
		perror("Target file open error");
		fclose(src);
		return 1;
	}

	while((c = fgetc(src)) != EOF) {
		fputc(c, dst);
	}

	fclose(src);
	fclose(dst);
	return 0;
}
