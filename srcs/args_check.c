#include "../includes/so_long.h"

int	extension_check(char *filename)
{
	char	*dot_ptr;

	dot_ptr = ft_strchr(filename, '.');
	if (dot_ptr == NULL)
		return (-1);
	else
	{
		if (ft_strncmp(dot_ptr, ".bar", 4))
			return (-1);
	}
	return (0);
}

void	args_check(int ac, char **av)
{
	if (ac != 2)
	{
		ft_putstr_fd("Error(Args): ./so_long xxx.bar", 2);
		exit (EXIT_SUCCESS);
	}
	if (extension_check(av[1]) == -1)
	{
		ft_putstr_fd("Error(Args): ./so_long xxx.bar", 2);
		exit (EXIT_SUCCESS);
	}
}
