#include <stdio.h>
#include <string.h>
#include "copy.h"

int main(void)
{
	char lines[5][MAXLINE];
	char temp[MAXLINE];
	int i = 0;
	int j;

	while(i < 5) {
		if(fgets(lines[i], MAXLINE, stdin) == NULL)
			return 1;

		lines[i][strcspn(lines[i], "\r\n")] = '\0';
		i++;
	}

	for(i = 0; i < 4; i++){
		for(j = 0; j < 4 - i; j++){
			if(strlen(lines[j]) < strlen(lines[j + 1])) {
				copy(lines[j], temp);
				copy(lines[j + 1], lines[j]);
				copy(temp, lines[j + 1]);
			}
		}
	}

	for(i = 0; i < 5; i++)
		printf("%s\n", lines[i]);

	return 0;
}
