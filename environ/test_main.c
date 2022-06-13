#include <stdlib.h>
#include <stdio.h>
#include "env_module.h"

void check(void)
{
	system("leaks a.out");
}

int main(int argc, char **argv, char **envp)
{
	int			i = 0;
	t_env_list	*head;
	t_env_list	*temp;

	//atexit(check);
	printf("%s\n\n\n", getenv("PATH"));
	printf("%s\n\n\n", getenv("hello"));
	printf("------------------\n");
	head = set_env(envp);
	temp = head;
	while (temp)
	{
		printf("iD  : %s\n", temp->content.id);
		printf("CTX : %s\n\n", temp->content.content);
		temp = temp->next;
	}
	printf("---\n");
	printf("%s\n", get_env(head, "PATH"));
	printf("%s\n", get_env(head, "PAT"));
	printf("---\n");
	clear_env(&head);
	return (0);
}
