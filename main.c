#include "main.h"

**
 * main - Entery point
 *
 * Description: maain function of program
 *
 * @ac: integer variable to counting
 *
 * @argv: character pointer to pointer
 *
 * Return: integer when success
*/

int main(int ac, char **argv) {
    char *prompt = "(ABDO_Shell) $ ";
    char *lineptr = NULL;
    char *lineptr_copy = NULL;
    size_t n = 0;
    ssize_t nchars_read;
    const char *delim = " \n";
    int num_tokens = 0;
    char *token;
    int i;
    char *cwd = NULL;

    /* declaring void variables */
    (void)ac;

    /* Create a loop for the shell's prompt */
    while (1) {
        char *directory;

        cwd = getcwd(NULL, 0); /* Dynamically allocate buffer for current working directory */
        if (cwd != NULL) 
        {
            printf("(%s) %s", cwd, prompt); /* Display current working directory in prompt */
            free(cwd); /* Free allocated memory for cwd */
        } else {
            perror("getcwd");
            printf("%s", prompt);
        }

        nchars_read = getline(&lineptr, &n, stdin);

        /* check if the getline function failed or reached EOF or user used CTRL + D */
        if (nchars_read == -1) {
            printf("Exiting shell....\n");
            break;
        }

        /* Check if the user typed "exit" and break the loop if so */
        if (strcmp(lineptr, "exit\n") == 0) {
            printf("Exiting shell....\n");
            break;
        }

        /* Check if the user typed "cd" command */
        if (strncmp(lineptr, "cd", 2) == 0) {
            /* Skip "cd " part */
            directory = lineptr + 3;
            directory[strcspn(directory, "\n")] = '\0'; /* Remove newline character */
            if (chdir(directory) != 0) {
                perror("cd");
            }
            continue; /* Skip the rest of the loop and go back to prompt */
        }

        /* Allocate space for a copy of the lineptr */
        lineptr_copy = malloc(sizeof(char) * nchars_read);
        if (lineptr_copy == NULL) {
            perror("tsh: memory allocation error");
            return (-1);
        }
        /* Copy lineptr to lineptr_copy */
        strcpy(lineptr_copy, lineptr);

        /********** split the string (lineptr) into an array of words ********/
        /* calculate the total number of tokens */
        token = strtok(lineptr, delim);

        while (token != NULL) {
            num_tokens++;
            token = strtok(NULL, delim);
        }
        num_tokens++;

        /* Allocate space to hold the array of strings */
        argv = malloc(sizeof(char *) * num_tokens);

        /* Store each token in the argv array */
        token = strtok(lineptr_copy, delim);

        for (i = 0; token != NULL; i++) {
            argv[i] = malloc(sizeof(char) * strlen(token));
            strcpy(argv[i], token);

            token = strtok(NULL, delim);
        }
        argv[i] = NULL;

        /* Execute the command */
        execmd(argv);

        /* Free up allocated memory */
        free(lineptr_copy);
    }

    free(lineptr);

    return 0;
}

