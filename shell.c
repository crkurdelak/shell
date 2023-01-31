/**
 * @file shell.c
 * @brief A command-line shell program.
 *
 * A command-line shell program that uses system calls to directly invoke
 * operating system services, rather than relying on C library calls.
 *
 * @author Ceci Kurdelak (ckurdelak20@georgefox.edu)
 */

#include <sys/syscall.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"

/**
 * @brief Main entry point of the shell.
 *
 * @return The exit status of the shell.
 */
int main() {
    // input buffer
    char cmd[255];
    // buffer for current working directory
    char current_dir[255];
    bool quit = false;

    // while not exit:
    while (!quit) {
        // clear out input buffer
        for (int i = 0; i < 255; i++) {
            cmd[i] = NULL;
        }

        // clear out working directory buffer
        for (int i = 0; i < 255; i++) {
            current_dir[i] = NULL;
        }

        // get the current working directory
        getcwd(current_dir, 255);

        // the prompt consists of the current working directory and "$ "
        // output prompt to stdout
        printf("%s$ ", current_dir);
        fflush(stdout);

        // read user command from stdin
        read(STDIN_FILENO, cmd, 255);

        // branching logic to handle specific, well-defined commands
        // if command is "exit", exit = true
        if (strcmp(cmd, "exit\n") == 0) {
            quit = true;
        }
        // TODO implement more specific commands in v2 and v3

        else if (strcmp(cmd, "pwd\n") == 0) {
            printf("%s\n", current_dir);
            fflush(stdout);
        }

        // TODO implement cd (change current working directory)
        else if (strcmp(cmd, "cd\n") == 0) {
            // change working directory
        }

        else if (strcmp(cmd, "\n") == 0) {
            // this does not print a newline
        }

        // TODO implement running executable programs using fork and exec syscalls (block using
        //  wait call until programs are finished running)
        // else write command back to stdout
        else {
            write(STDOUT_FILENO, cmd, 255);
        }
    }

    //return 0; // SYSCALL: SYS_exit
    SYS_exit;
}
