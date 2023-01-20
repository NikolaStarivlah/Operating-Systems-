#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_OF_COMMANDS 10
#define COMMAND_LENGHT 100
#define DATA_LENGHT 4096

char *get_popen(char *commandStr) {
    FILE *pf;
    char command[COMMAND_LENGHT];
    char *data;
    data = malloc(sizeof(char) * DATA_LENGHT);

    // Execute a process listing
    sprintf(command, "%s", commandStr);

    // Setup our pipe for reading and execute our command.
    pf = popen(command, "r");

    // Error handling

    // Get the data from the process execution
    fgets(data, 4096, pf);

    // the data is now in 'data'

/*
    if (pclose(pf) != 0)
        fprintf(stderr, " Error: Failed to close command stream \n");
*/

    return data;
}

int main(int argc, char **argv) {
    // Check if log file name provided
    if (argc == 1) {
        printf("Usage: ./a.out <log_file_name>");
        return 1;
    }
    char commands[NUM_OF_COMMANDS][COMMAND_LENGHT];
    strcpy(commands[0], "lscpu | egrep 'Vendor ID|Model name'\0");
    strcpy(commands[1], "cat /etc/os-release\0");
    strcpy(commands[2], "uptime\0");
    strcpy(commands[3], "cat /proc/stat\0");
    strcpy(commands[4], "iostat -m\0");
    strcpy(commands[5], "pidstat\0");
    strcpy(commands[6], "last reboot\0");
    strcpy(commands[7], "cat /proc/stat | egrep 'processes'\0");
    strcpy(commands[8], "cat /proc/meminfo\0");
    strcpy(commands[9], "grep MemTotal /proc/meminfo\0");
    FILE *log = fopen(argv[1], "w");
    if (log == NULL) {
        printf("Unable to open file '%s' for logs\n", argv[1]);
        return 1;
    }
    for (int i = 0; i < 10; ++i) {
//        printf("command is '%s'\n", commands[i]);
        char *data = get_popen(commands[i]);
        printf("%s\n", data);
        fprintf(log, "%s\n", data);
    }

    fclose(log);
    return 0;
}
