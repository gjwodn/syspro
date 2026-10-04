#include <stdio.h>
#include <string.h>
#include "copy.h"

int main()
{
	char lines[5][MAXLINE];
	char temp[MAXLINE];
	int i = 0;
	int j;

	while(i < 5) {
		if(scanf("%s", lines[i]) == 1) {
			i++;
		}
	}

	for(i = 0; i < 4; i++) {
		for(j = i + 1; j < 5; j++) {
			if(strlen(lines[i]) < strlen(lines[j])) {
					copy(lines[i], temp);
					copy(lines[j], lines[i]);
					copy(temp, lines[j]);
			}
		}
	}

	for(i = 0; i < 5; i++) {
	printf("%s\n", lines[i]);
	}

	return 0;
}
