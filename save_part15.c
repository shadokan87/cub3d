#include "cublib.h"

void	closegame(var_t *var, char *message)
{
	int i;

	i = -1;
	if (var->mlx_ptr)
		free(var->mlx_ptr);
	if (var->mlx_win)
		free(var->mlx_win);
	if (var->addr)
		free(var->addr);
	while (++i < var->spritenum && var->spritequeue)
		var->spritequeue[i] ? free(var->spritequeue[i]) : 0;
	message ? ft_fprintf(1, message) : 0;
	exit(0);
}