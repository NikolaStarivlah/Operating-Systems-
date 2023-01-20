/*
 * Q3.c
 *
 *  Created on: October. 3rd, 2022
 *      Author: Nikola Starivlah
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {

	FILE *filePointer;


	filePointer = fopen(argv[1], "r");
	if (filePointer == NULL) {
		exit(EXIT_FAILURE);
	}

	int sTime = time(NULL);
	char *rTime = argv[2];
	int numberOfSec = atoi(rTime);
	int lastTimePrinted = time(NULL);

	numberOfSec = numberOfSec * 60;
	long int previousResult = -1;
	while (time(NULL) <= sTime + numberOfSec) {

		if (time(NULL) - lastTimePrinted >= 11) {
			filePointer = fopen(argv[1], "r");
			fseek(filePointer, 0L, SEEK_END);

			long int result = ftell(filePointer);

			lastTimePrinted = time(NULL);

			printf("the file is currently %lu\n", result);
			fflush(stdout);

			previousResult = result;

		}

	}
	return 0;
}
