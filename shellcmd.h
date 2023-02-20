/**
 * @file shellcmd.h
 * @brief Function prototypes for shellcmd.
 *
 * @author Ceci Kurdelak (ckurdelak20@georgefox.edu)
 */

#ifndef SHELL_SHELLCMD_H
#define SHELL_SHELLCMD_H

#endif //SHELL_SHELLCMD_H

/**
 * Prints the current working directory.
 * @param current_dir the current working directory
 * @return 0 if successful, else return nonzero
 */
int shell_cmd_pwd(char* current_dir);

/**
 * Changes the current working directory to the given path.
 * @param path the path to the new workinf directory
 * @return 0 if successful, else return nonzero
 */
int shell_cmd_cd(char* path);

/**
 * Prints arguments according to the following guidelines:

    Write arguments to standard output, followed by a newline;
    If no arguments are provided, only the newline is written;
    If the first argument supplied to echo is -n, omit the trailing newline.

 * @param args the arguments
 * @param last_exit_status the exit status of the last command
 * @return 0 if successful, else return nonzero
 */
int shell_cmd_echo(char* args[], int last_exit_status);