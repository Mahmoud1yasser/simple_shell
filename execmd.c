
#include "main.h"

**
 * execmd- Entery point
 *
 * Description: execution of progarm
 *
 * @argv: character pointer to pointer
 *
 * Return: 0
*/

void execmd(char **argv) {
    char *command = NULL, *actual_command = NULL;
    pid_t child_pid;

    if (argv) {
        /* get the command */
        command = argv[0];

        /* If the command is "cd", handle the change directory operation */
        if (strcmp(command, "cd") == 0) {
            /* Check if the argument for cd is provided */
            if (argv[1]) {
                /* Use chdir() to change the current working directory */
                if (chdir(argv[1]) == -1) {
                    perror("cd");
                }
            } else {
                printf("Usage: cd <directory>\n");
            }
            return;
        }

        /* generate the path to this command before passing it to execve */
        actual_command = get_location(command);

        /* fork a new process */
        child_pid = fork();

        if (child_pid == -1) {
            perror("Fork error");
            return;
        } else if (child_pid == 0) {
            /* Child process: execute the command with execve */
            if (execve(actual_command, argv, NULL) == -1) {
                perror("Error:");
            }
            exit(1); /* Make sure the child process exits */
        } else {
            /* Parent process: wait for the child process to complete */
            wait(NULL);
        }
    }
}

