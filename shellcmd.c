/**
 * @file shellcmd.c
 * @brief The commands for shell.
 *
 * @author Ceci Kurdelak (ckurdelak20@georgefox.edu)
 */

#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "shellcmd.h"

int shell_cmd_pwd(char* current_dir) {
    printf("%s\n", current_dir);
    fflush(stdout);
    return 0;
}

int shell_cmd_cd(char* path) {
    return chdir(path);
}

int shell_cmd_echo(char* args[], int last_exit_status) {
    // if args[1] is $?, print last exit status
    if (strcmp(args[1], "$?") == 0) {
        printf("%d\n", last_exit_status);
    }
    // else if no args, print \n
    else if (args[1] == NULL) {
        printf("\n");
    }
    // else print args
    else {
        char* current_arg = NULL;
        // if args[1] is -n, do not print \n
        if (strcmp(args[1], "-n") == 0) {
            // print args[2]
            // TODO loop
            printf("%s", args[2]);
        }
        // else print \n
        else {
            // print args[1]
            // TODO loop
            printf("%s\n", args[1]);
        }
    }


    // Write arguments to standard output, followed by a newline;
    // If no arguments are provided, only the newline is written;
    // If the first argument supplied to echo is -n, omit the trailing newline.

    return 0;
}
