#include "main.h"

/**
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

int main(int ac, char **argv)
{	char *prompt = "$", *lineptr = NULL, *lineptr_copy = NULL;
	size_t n = 0;
	ssize_t nchars_read;
	const char *delim = " \n";
	int num_tokens = 0, i;
	char *cwd = NULL, *directory, *token;
	(void)ac;
	while (1)
	{	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{	printf("(%s) %s", cwd, prompt);
		free(cwd); }
	else
	{	perror("getcwd");
		printf("%s", prompt); }
	nchars_read = getline(&lineptr, &n, stdin);
	if (nchars_read == -1)
	{	printf("Exiting shell....\n");
		break; }
	if (strcmp(lineptr, "exit\n") == 0)
	{	printf("Exiting shell....\n");
		break; }
	if (strncmp(lineptr, "cd", 2) == 0)
	{	directory = lineptr + 3;
		directory[strcspn(directory, "\n")] = '\0';
		if (chdir(directory) != 0)
			perror("cd");
		continue; }
	lineptr_copy = malloc(sizeof(char) * nchars_read);
	if (lineptr_copy == NULL)
	{	perror("tsh: memory allocation error");
		return (-1); }
	strcpy(lineptr_copy, lineptr);
	token = strtok(lineptr, delim);
	while (token != NULL)
	{	num_tokens++;
		token = strtok(NULL, delim); }
	num_tokens++;
	argv = malloc(sizeof(char *) * num_tokens);
	token = strtok(lineptr_copy, delim);
	for (i = 0; token != NULL; i++)
	{	argv[i] = malloc(sizeof(char) * strlen(token));
		strcpy(argv[i], token);
		token = strtok(NULL, delim); }
	argv[i] = NULL;
	execmd(argv);
	free(lineptr_copy); }
	free(lineptr);
	return (0); }
