/**
 * @file shell.c
 * @brief A command-line shell program.
 *
 * A command-line shell program that uses system calls to directly invoke
 * operating system services, rather than relying on C library calls.
 *
 * @author Ceci Kurdelak (ckurdelak20@georgefox.edu)
 */

#include <errno.h>
#include <sys/syscall.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
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
        memset(cmd, '\0', 255);

        // clear out working directory buffer
        memset(current_dir, '\0', 255);

        // get the current working directory
        getcwd(current_dir, 255);

        // the prompt consists of the current working directory and "$ "
        // output prompt to stdout
        printf("%s$ ", current_dir);
        fflush(stdout);

        // read user command from stdin
        read(STDIN_FILENO, cmd, 255);

        // the args from the user's command
        char* args[255];
        memset(args, '\0', 255);
        get_args(cmd, args);

        // branching logic to handle specific, well-defined commands
        // TODO implement more specific commands in v3
        // if the command is empty
        if (strcmp(cmd, "\n") == 0) {
            // this does not print a newline
        }
        // if command is "exit", exit = true
        else if (strcmp(args[0], "exit") == 0) {
            quit = true;
        }

        // prints the current working directory
        else if (strcmp(args[0], "pwd") == 0) {
            printf("%s\n", current_dir);
            fflush(stdout);
        }

        // if the first token of cmd is "cd"
        else if (strcmp(args[0], "cd") == 0) {
            // change working directory using chdir(path)
            // split input on " " character
            // second token is path
            char* path = args[1];
            chdir(path);
        }

        // else try to fork and exec what they typed
        else {
            fork_and_exec(args);
        }
    }

   exit(0);
}


int fork_and_exec(char* args[]) {
    // fork the current process
    pid_t fork_pid = fork();

    // if this is a child process
    if (fork_pid == 0) {
        // try to execute the command as a program
        int exec_result = execvp(args[0], args);
        printf("error: could not execute command %s\n", args[0]);
        exit(1);
    }
    else {
        // wait for child process to finish
        pid_t changed_pid = waitpid(fork_pid, NULL, 0);
    }
    return 0;
}


void get_args(char* cmd, char* args_array[]) {
    char* current_token = strtok(cmd, " \n");
    int i = 0;
    while (current_token) {
        // put current token in array
        args_array[i] = current_token;
        i++;
        // get new token
        current_token = strtok(NULL, " \n");
    }
}
