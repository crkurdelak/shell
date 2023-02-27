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
            // print args[2]-end
            int i = 2;
            current_arg = args[i];
            while(current_arg) {
                printf("%s", current_arg);
                i++;
                current_arg = args[i];
            }
        }
        // else print \n
        else {
            // print args[1]-end
            int i = 1;
            current_arg = args[i];
            while(current_arg) {
                printf("%s", current_arg);
                i++;
                current_arg = args[i];
            }
            printf("\n");
        }
    }
    return 0;
}
