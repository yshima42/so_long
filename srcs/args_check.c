#include "../includes/so_long.h"

int	extension_check(char *filename)
{
	char *dot_ptr;
	
	dot_ptr = ft_strchr(filename, '.');
	if(dot_ptr == NULL)
		return (-1);
	else
	{
		if(ft_strncmp(dot_ptr, ".bar", 4))
			return (-1);
	}
	return (0);
}

void	args_check(int ac, char **av)
{
	if(ac != 2)
	{
		printf("You need two args: ./so_long xxx.bar");
		exit (0);
	}
	if(extension_check(av[1]) == -1)
	{
		printf("You need to have xxx.bar file");
		exit (0);
	}
}