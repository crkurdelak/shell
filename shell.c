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
#include "shell.h"

/**
 * @brief Main entry point of the shell.
 *
 * @return The exit status of the shell.
 */
int main() {
    // input buffer
    char cmd[255];
    char* prompt = "shell$ ";
    bool quit = false;

    // while not exit:
    while (!quit) {
        // clear out input buffer
        for (int i = 0; i < 255; i++) {
            cmd[i] = NULL;
        }

        // output prompt to stdout "shell$ " (SYSCALL: SYS_write)
        write(STDOUT_FILENO, prompt, 7);
        // read user command from stdin      (SYSCALL: SYS_read)
        read(STDIN_FILENO, cmd, 255);

        // branching logic to handle specific, well-defined commands
        // if command is "exit", exit = true
        if (strcmp(cmd, "exit\n") == 0) {
            quit = true;
        }
        else if (strcmp(cmd, "\n") == 0) {
            // this does not print a newline
        }
        // TODO implement more specific commands in v2 and v3
        // else write command back to stdout
        else {
            write(STDOUT_FILENO, cmd, 255);
        }
    }

    //return 0; // SYSCALL: SYS_exit
    SYS_exit;
}
