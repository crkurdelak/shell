/**
 * @file shell.h
 * @brief Function prototypes for the shell.
 *
 * @author Ceci Kurdelak (ckurdelak20@georgefox.edu)
 */

#ifndef SHELL_H
#define SHELL_H

// TODO add function prototypes
/**
 * Forks the current process and tries to execute the given command as a program.
 * @param cmd the command entered by the user
 * @return 0 if successful, else returns 1
 */
int fork_and_exec(char* cmd);


/**
 * Extracts an array of args from the given command string.
 * @param cmd the command entered by the user
 * @return an array of args extracted from the user command
 */
char** get_args(char* cmd);

#endif /* SHELL_H */
