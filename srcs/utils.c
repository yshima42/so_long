#include "../includes/so_long.h"

void	array_loop(char **map, t_conf *conf, void f(char c, t_conf *conf))
{
	size_t	x;
	size_t	y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			f(map[y][x], conf);
		}
	}
}

int	ft_open_readfile(char *readfile)
{
	int fd;

	fd = open(readfile, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

// think if you need to return char** or int
char	**lst_to_array(t_list *buf, size_t height, char **map)
{
	t_list	*t_buf;
	size_t	i;
	
	t_buf = buf;
	map = (char **)malloc(sizeof(char *) * height + 1);
	if (!map)
		exit(EXIT_FAILURE);//need perror??
	i = 0;
	while (t_buf)
	{
		map[i] = ft_strdup(t_buf->content);
		t_buf = t_buf->next;
		i++;
	}
	map[i] = NULL;
	ft_lstclear(&buf, free);
	return (map);
}

size_t	file_to_lst(int fd, t_list **buf)
{
	char	*line;
	size_t	l_count;
	
	l_count = 0;
	while(1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (l_count == 0)
			*buf = ft_lstnew(line);
		else
			ft_lstadd_back(buf, ft_lstnew(line));
		l_count++;
	}
	return (l_count);
}

void ft_swap(char *a, char *b)
{
	char tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}