#include "client.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int main(void) {
	sayHelloWorld();

	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		printf("Current path: %s\n", cwd);
	}
	else {
		perror("getcwd() error");
		return 1;
	}

	return 0;
}

void sayHelloWorld() {
	printf("Hello World!\n");
}
