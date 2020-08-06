#include "cublib.h"

void	pixel_put_fd(var_t *var, int color, int fd)
{
	int blue;
	int green;
	int red;

	red = getred(color, var);
	blue = getblue(color, var);
	green = getgreen(color, var);
	if (red > 255)
		red = 255;
	if (red < 0)
		red = 0;
	if (green > 255)
		green = 255;
	if (green < 0)
		green = 0;
    if (blue > 255)
		blue = 255;
	if (blue < 0)
		blue = 0;
	ft_fprintf(fd, "%c", blue);
	ft_fprintf(fd, "%c", green);
	ft_fprintf(fd, "%c", red);
}

void	pixel_put(var_t *var, int x, int y, int color)
{
	char *dst;

	dst = var->addr + (y * var->line + x * (var->bpp / 8));
	*(unsigned int*)dst = color;
}

int	verline(var_t *var, int x, int draw_start, int draw_end, int color)
{
	int swap;

	if (draw_end < draw_start)
	{
		swap = draw_start;
		draw_start = draw_end;
		draw_end = swap;
	}
	if (draw_end < 0 || draw_start >= var->s_h || x < 0 || x >= var->s_w)
		return (0);
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= var->s_w)
		draw_end = var->s_h - 1;
	while (draw_start < draw_end)
	{
		pixel_put(var, x, draw_start, color);
		draw_start++;
	}
	return (1);
}

void	init_raycast(var_t *var)
{
	var->s_w = var->s_w;
	var->s_h = var->s_h;
	var->img = mlx_new_image(var->mlx_ptr, var->s_w, var->s_h);
	var->addr = mlx_get_data_addr(var->img, &var->bpp, &var->line, &var->endian);
	var->dirX = -1;
	var->dirY = 0;
	var->planeX = 0;
	var->planeY = 0.66;
	var->time = 0;
}

void	step(var_t *var)
{
	if (var->rayDirX < 0)
	{
		var->stepX = -1;
		var->sideDistX = (var->posX - var->mapX) * var->deltaDistX;
	}
	else
	{
		var->stepX = 1;
		var->sideDistX = (var->mapX + 1.0 - var->posX) * var->deltaDistX;
	}
	if (var->rayDirY < 0)
	{
		var->stepY = -1;
		var->sideDistY = (var->posY - var->mapY) * var->deltaDistY;
	}
	else
	{
		var->stepY = 1;
		var->sideDistY = (var->mapY + 1.0 - var->posY) * var->deltaDistY;
	}
}