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

        // TODO get the first part of the command
        char** args = get_args(cmd);

        // branching logic to handle specific, well-defined commands
        // if command is "exit", exit = true
        if (strcmp(cmd, "exit\n") == 0) {
            quit = true;
        }
        // TODO implement more specific commands in v2 and v3

        // prints the current working directory
        else if (strcmp(cmd, "pwd\n") == 0) {
            printf("%s\n", current_dir);
            fflush(stdout);
        }

        // TODO implement cd (change current working directory)

        // if the first token of cmd is "cd"
        else if (strcmp(args[0], "cd") == 0) {
            // change working directory using chdir(path)
            // split input on " " character
            // second token is path
        }

        else if (strcmp(cmd, "\n") == 0) {
            // this does not print a newline
        }

        // TODO implement running executable programs using fork and exec syscalls (block using
        //  wait call until programs are finished running)
        // else try to fork and exec what they typed
        else {
            fork_and_exec(cmd);
        }
    }

    //return 0; // SYSCALL: SYS_exit
    SYS_exit;
}


int fork_and_exec(char** args) {
    //write(STDOUT_FILENO, cmd, 255);

    // fork the current process
    pid_t fork_pid = fork();

    // if this is a child process
    if (fork_pid == 0) {
        // try to execute the command as a program
        int exec_result = execvp(args[0], args);
        if (exec_result != 0) {
            // TODO error messages
            if (errno == 1) {
                printf("error: ");
            }
            else if (errno == 2) {
                printf("error: command %s not found\n", args[0]);
            }
        }
    }
    else {
        // wait for child process to finish
        pid_t changed_pid = waitpid(fork_pid, NULL, 0);
    }
}


char** get_args(char* cmd) {
    // TODO split using strtok and put them into args array
    // array to hold the args
    char* args[] = {};
    char* current_token;

    // copy cmd
    char* cmd_copy;
    // TODO fix problem here
    strcpy(cmd_copy, cmd);


    int i = 0;
    // while there are still tokens
    while (strlen(cmd_copy) > 0) {
        // split off first token
        current_token = strtok(cmd_copy, " ");
        // put it in array
        args[i] = current_token;
        i++;
    }

    return args;
}
