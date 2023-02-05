#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	main(int ac, char **av, char **envp)
{
	return (execve(av[1], &av[1], envp));
}
