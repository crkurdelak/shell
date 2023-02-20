/**
 * @file shell.c
 * @brief A command-line shell program.
 *
 * A command-line shell program that uses system calls to directly invoke
 * operating system services, rather than relying on C library calls.
 *
 * @author Ceci Kurdelak (ckurdelak20@georgefox.edu)
 */

#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "shell.h"
#include "shellcmd.h"

/**
 * @brief Main entry point of the shell.
 *
 * @return The exit status of the shell.
 */
int main() {
    int last_exit_status = 0;

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
            last_exit_status = shell_cmd_pwd(args[0]);
        }

        // if the first token of cmd is "cd"
        else if (strcmp(args[0], "cd") == 0) {
            last_exit_status = shell_cmd_cd(args[1]);
        }

        else if (strcmp(args[0], "echo") == 0) {
            // TODO implement echo
            last_exit_status = shell_cmd_echo();
        }

        // else try to fork and exec what they typed
        else {
            last_exit_status = fork_and_exec(args);
        }
    }

   exit(0);
}


int fork_and_exec(char* args[]) {
    int exit_code = 0;
    // fork the current process
    pid_t fork_pid = fork();

    // TODO Implement background jobs by supporting a trailing & metacharacter after any entered
    //  external program invocation. For example, executing cp largeFile.zip /mnt/floppy/ & runs
    //  cp in the background to permit copying a large file without blocking the shell. To
    //  achieve this, you'll need to not call wait when the & metacharacter is present.

    // if this is a child process
    if (fork_pid == 0) {
        // try to execute the command as a program
        int exec_result = execvp(args[0], args);
        printf("error: could not execute command %s\n", args[0]);
        exit(1);
    }
    else {
        // check for & as last arg
        // get length of array
        // count array entries until find null
        if() {
            // wait for child process to finish
            pid_t changed_pid = waitpid(fork_pid, NULL, 0);
        }
    }
    // TODO exit statuses
    return exit_code;
}


int get_args(char* cmd, char* args_array[]) {
    // check if last char is &
    char* current_token = strtok(cmd, " \n");
    int i = 0;
    while (current_token) {
        // if token is &, do not put in array
        // put current token in array
        args_array[i] = current_token;
        i++;
        // get new token
        current_token = strtok(NULL, " \n");
    }
    // return 1 if background (&) else return 0
    return 0;
}
