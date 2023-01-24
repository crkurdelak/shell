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
    // TODO implement shell

    /*
    Your first (and intentionally very minimal) version of the shell should do the following:
    Write a shell$ prompt to standard output;
    Read a user command (max length 255 characters) from standard input;
    "Execute" the command by simply writing the command back to standard output;
    If the command is exit, then exit; else, repeat from step 1.
     */

    char* cmd[255];     // input buffer
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
        // TODO get just the command as string without extra nulls

        // branching logic to handle specific, well-defined commands
        // if command is "exit", exit = true TODO figure out string comparison in C (not a syscall)
        if (strcmp(cmd, "exit") == 0) {
            quit = true;
        }
        else if (strcmp(cmd, "") == 0) {
            // TODO handle empty input (pressing enter)
            // print a newline
            //write(STDOUT_FILENO, "\n", 1);
        }
        // TODO implement more specific commands in v2 and v3
        // else write command back to stdout
        else {
            // TODO find out why it's printing twice
            write(STDOUT_FILENO, cmd, 255);
        }
    }

    return 0; // SYSCALL: SYS_exit
    SYS_exit;
}
