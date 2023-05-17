#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include "../mlx/mlx.h"

# define EVENT_KEYPRESS 2
# define EVENT_KEYRELEASE 3
# define EVENT_DESTROY 17

# define KEY_ESC 53
# define KEY_AR	124
# define KEY_AL	123
# define KEY_AU	126
# define KEY_AD	125
# define KEY_W	13
# define KEY_A	0
# define KEY_S	1
# define KEY_D	2

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;