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
    // TODO exit statuses
    return 0;
}

int shell_cmd_cd(char* path) {
    chdir(path);
    // TODO exit statuses
    return 0;
}

int shell_cmd_echo() {
    // TODO implement echo
    // TODO handle echo $?
    // TODO exit statuses
    return 0;
}
