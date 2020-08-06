#include "cublib.h"

void    *ft_memset(void *b, int c, size_t len)
{
        unsigned long   i_array_b;
        unsigned char   *a;

        i_array_b = 0;
        a = (unsigned char *)b;
        while (i_array_b < len)
        {
                a[i_array_b] = (unsigned char)c;
                i_array_b++;
        }
        b = a;
        return (b);
}

int		rgb_int(int red, int green, int blue)
{
	int	rgb;

	rgb = red;
	rgb = (rgb << 8) + green;
	rgb = (rgb << 8) + blue;
	return (rgb);
}

char *remove_extraspaces(char *str)
{
    char *return_value;
    int i;
    int y;

    i = 0;
    y = 0;
    if (!(return_value = malloc(sizeof(char) * strlen(str))))
        return (0);
    while (str[i])
    {
        if (!(str[i] && str[i] == ' ' && str[i - 1] == ' '))
       {
        return_value[y] = str[i];
        y++;
       }
       i++;
    }
    return (return_value);
}

int	iswall(char c)
{
	if (c == '4')
		return (1);
	else if (c == '5')
		return (5);
	else if (c == '3')
		return (3);
	else if (c == '2')
		return (2);
	else if (c == '1')
		return (1);
	return (0);
}

int	getmapindex(var_t *var)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (var->paramfile && var->paramfile[i])
	{
		if (iswall(var->paramfile[i]) && var->paramfile[i + 1] == ' ' && iswall(var->paramfile[i + 2]))
			return (i);
		i++;
	}
	return (-1);
}

int	main(int argc, char **argv)
{
	var_t var;

	if (!(argc >= 2 && argc <= 3))
	{
		ft_fprintf(1, "please use [--save] argument to save the first frame into a bmp file\nfollowed by a .cub file or directly the .cub file to launch the game");
		exit(0);
	}
	init_struct(&var, argv);
	if ((var.mlx_ptr = mlx_init()) == null)
		return (exit_failure);
	if (var.s_w > 1914)
		var.s_w = 1914;
	if (var.s_h > 924)
		var.s_h = 924;
	if ((var.mlx_win = mlx_new_window(var.mlx_ptr, var.s_w, var.s_h, "cub3d")) == null)
	return (exit_failure);
	init_raycast(&var);
	init_keys(&var, 5);
	start(&var);
	return (exit_success);
}
