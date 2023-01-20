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
        //      output prompt to stdout "shell$ " (SYSCALL: SYS_write)
        SYS_write(cout, prompt, 7);
        //      read user command from stdin      (SYSCALL: SYS_read)
        SYS_read(cin, cmd, 255);

        // branching logic to handle specific, well-defined commands
        //      if command is "exit", exit = true TODO figure out string comparison in C (not a syscall)

        // TODO handle empty input (pressing enter)
        // TODO implement more specific commands in v2 and v3
        // else write command back to stdout
        SYS_write(cout, cmd, 255);
    }

    return 0; // SYSCALL: SYS_exit
    SYS_exit;
}
