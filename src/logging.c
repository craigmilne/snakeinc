#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "logging.h"

void logsExit(char *str) {
	system("reset");
	printf("%s\n", str);
	sleep(2);
	exit(1);
}
