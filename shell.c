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
        int is_bg = get_args(cmd, args);

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
            last_exit_status = shell_cmd_pwd(current_dir);
        }

        // if the first token of cmd is "cd"
        else if (strcmp(args[0], "cd") == 0) {
            last_exit_status = shell_cmd_cd(args[1]);
        }

        else if (strcmp(args[0], "echo") == 0) {
            last_exit_status = shell_cmd_echo(args, last_exit_status);
        }

        // else try to fork and exec what they typed
        else {
            last_exit_status = fork_and_exec(args, is_bg);
        }
    }

   exit(0);
}


int fork_and_exec(char* args[], int is_bg) {
    int exit_code = 0;
    // fork the current process
    pid_t fork_pid = fork();

    // if this is a child process
    if (fork_pid == 0) {
        // try to execute the command as a program
        int exec_result = execvp(args[0], args);
        printf("error: could not execute command %s\n", args[0]);
        exit_code = 1;
        exit(1);
    }
    else {
        // do not wait for child if current process is a background job
        if(is_bg == 0) {
            // wait for child process to finish
            int wait_status;
            pid_t changed_pid = waitpid(fork_pid, &wait_status, 0);
            exit_code = WEXITSTATUS(wait_status);
        }
    }
    return exit_code;
}


int get_args(char* cmd, char* args_array[]) {
    int is_bg = 0;     // 1 if the command is a background job, else 0
    // check if last char is &
    int cmd_len = strlen(cmd);
    char* last_char = &cmd[cmd_len - 2];
    if (strcmp(last_char, "&\n") == 0) {
        is_bg = 1;
    }
    char* current_token = strtok(cmd, " \n");
    int i = 0;
    while (current_token) {
        // if token is &, do not put in array
        if (strcmp(current_token, "&") != 0) {
            // put current token in array
            args_array[i] = current_token;
        }
        i++;
        // get new token
        current_token = strtok(NULL, " \n");
    }
    return is_bg;
}
