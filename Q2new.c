/*
 * Q2.c
 *
 *  Created on: Oct. 2, 2022
 *      Author: nik
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// Main method
int main(int argc, char const *argv[]) {

    // Store source and destination file names
    char srcFile[250];
    char destFile[250];

    // Ask user for source file
    printf("Enter source filename:\n");

    fflush(stdout);

    // Prompt user for input, store as input file
    scanf("%s", srcFile);

    int inputFile = open(srcFile, O_RDONLY);
//
// // If file cannot be found, return and exit
    if (inputFile == -1) {
        printf("Error: File not found\n");
        return 1;
// //return 0;
    }

    // Ask user for destination file
    printf("Enter file destination:\n");

    fflush(stdout);

    // Prompt user for input, store as destination file
    scanf("%s", destFile);
    int outputFile = open(destFile, O_CREAT | O_WRONLY, O_TRUNC, 0777);
    if (outputFile == -1) {
        printf("Error: Cannot open '%s' file\n", destFile);
        return 1;
    }
    fflush(stdout);

    char buf[20 + 1];
    ssize_t n = 0;
    while ((n = read(inputFile, buf, 20)) > 0) {
        buf[n] = '\0';
        if ((write(outputFile, buf, n)) == -1) {
            perror("write");
            exit(1);
        }
    }
    if (n == -1) {
        perror("read");
        exit(1);
    }

    if (close(inputFile) == -1) {
        perror("close");
        exit(1);
    }
    if (close(outputFile) == -1) {
        perror("close");
        exit(1);
    }
    // Output to user that the file was copied correctly
    printf("Success: File has been copied to destination\n");

    return 0;
}

