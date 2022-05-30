#include <stdio.h>
#include <dirent.h>

int main(int argc, char **argv, char **envp)
{
	int i;
	DIR	*dir;
	struct dirent *dp;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	printf("%d\n", argc);

	if (argc == 2)
	{
		printf("\n\n");
		dir = opendir(argv[1]);
		dp = readdir(dir);
		while (dp)
		{
			printf("%s - %d\n", dp->d_name, dp->d_type);
			dp = readdir(dir);
		}

	}
	printf("\n\n");
	for (int i = 0; i < argc; i++)
	{
		printf("%2d : %s\n", i, argv[i]);
	}
	return 0;
}
