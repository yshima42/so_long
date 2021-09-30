#ifndef SO_LONG_H
# define SO_LONG_H

#include <stdint.h>

#include "../libft/libft.h"
#include "../mlx_linux/mlx.h"

typedef	struct s_player
{
	int	pos_y;
	int	pos_x;
	size_t	n_steps;
	size_t	collectibles;
} t_player;

typedef	struct s_map
{
	char	**map;
	size_t	width;
	size_t	height;
	/* uint8_t	map_flag; */
	size_t	n_collectibles;
	size_t	n_players;
	size_t	n_exit;
}	t_map;

typedef struct s_images
{
	void	*empty;
	void	*wall;
	void	*collectible;
	void	*exit;
	void	*player;
	void	*player_2;
	int		size;
}	t_images;

typedef struct s_conf
{
    void		*mlx;
	void		*win;
	t_map		map;
	t_images	images;
	t_player	player;
}	t_conf;

/* # define FLAG_EMPTY 		1 << 0 // 0000 0001
# define FLAG_WALL 			1 << 1 // 0000 0010
# define FLAG_COLLECTIBLE 	1 << 2 // 0000 0100
# define FLAG_EXIT 			1 << 3 // 0000 1000
# define FLAG_PLAYER 		1 << 4 // 0001 0000 */

# define VALID_CHAR 		"01CEP"

# define IMG_EMPTY 			"images/empty.xpm"
# define IMG_WALL 			"images/wall8.xpm"
# define IMG_COLLECTIBLE	"images/bitcoin_colored.xpm"
# define IMG_EXIT 			"images/exit13.xpm"
# define IMG_PLAYER 		"images/player1.xpm"
# define IMG_PLAYER_2		"images/player2.xpm"

# define CHIP_SIZE 			32
# define SCREAN_SIZE 		20

# define ESC_KEY 65307
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100

//utils.c
void	array_loop(char **map, t_conf *conf, char *f(char c, t_conf *conf));
int	    ft_open_readfile(char *readfile);
char	**lst_to_array(t_list *buf, size_t height, char **map);
size_t	file_to_lst(int fd, t_list **buf);
void    ft_swap(char *a, char *b);

//free.c
char	**ft_arrayfree(char **tab);
int	free_all_exit(t_conf *conf);

//map_check.c
void    rectangular_check(char **map, t_conf *conf);
void    wall_check(char **map, t_conf *conf);
char	*invalid_char_check(char c, t_conf *conf);
char	*inmap_char_count(char c,  t_conf *conf);
void	n_char_check(char **map, t_conf *conf);

//args_check.c
int	extension_check(char *filename);
void	args_check(int ac, char **av);

//sl_utils.c
void	*chr_to_imgptr(char c, t_conf *conf);
void	array_to_screan(char **map, t_conf *conf);
void	chip_set(t_conf *conf);
void	initialize_conf(t_conf *conf);
void    step_counter(t_conf *conf);

//player_move.c
void    player_move(int keycode, t_conf *conf);
void	step_to_next(char *current_pos, char *next_pos, t_conf *conf);
void	game_complete(char *a, char *b, t_conf *conf);
void	collect_item(char *a, char *b, t_conf *conf);
int next_pos_check(char next_pos_c, char check_c);

//error_output.c
void maperror_output(char **map, char *output);
void wall_no_rectangular(char **map, t_conf *conf);

//delete later
void    destructor_leaks(void);

#endif