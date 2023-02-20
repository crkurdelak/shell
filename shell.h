/**
 * @file shell.h
 * @brief Function prototypes for the shell.
 *
 * @author Ceci Kurdelak (ckurdelak20@georgefox.edu)
 */

#ifndef SHELL_H
#define SHELL_H

/**
 * Forks the current process and tries to execute the given command as a program.
 * @param args the arguments entered by the user
 * @param is_bg 1 if the new process is a background job, else 0
 * @return 0 if successful, else returns 1
 */
int fork_and_exec(char* args[], int is_bg);


/**
 * Extracts an array of args from the given command string.
 * @param cmd the command entered by the user
 * @param args_array the array in which to store the args
 * @return 1 if the job is a background job, else return 0
 */
int get_args(char* cmd, char* args_array[]);

#endif /* SHELL_H */
