#include "cublib.h"

void	hit(var_t *var)
{
	while (var->hit == 0)
	{
		if (var->sideDistX < var->sideDistY)
		{
			var->sideDistX += var->deltaDistX;
			var->mapX += var->stepX;
			var->side = 0;
		}
		else
		{
			var->sideDistY += var->deltaDistY;
			var->mapY += var->stepY;
			var->side = 1;
		}
		if (var->map[var->mapX][var->mapY] > 0)
		{
			var->hit = var->map[var->mapX][var->mapY];
			var->wallx = var->hit;
		}
	}
	if (var->side == 0)
		var->perpWallDist = (var->mapX - var->posX + (1 - 
		var->stepX) / 2) / var->rayDirX;
	else
		var->perpWallDist = (var->mapY - var->posY + (1 - var->stepY) / 2) / var->rayDirY;	
}

void	cls(var_t *var)
{
	int x = 0;
	while (x < var->s_w)
	{
		verline(var, x, 0, var->s_h, 0);
		x++;
	}
}

void	draw_info(var_t *var)
{
	var->lineHeight = (int)(var->s_h / var->perpWallDist);
	var->drawStart = -var->lineHeight / 2 + var->s_h / 2;
	if (var->drawStart < 0)
		var->drawStart = 0;
	var->drawEnd = var->lineHeight / 2 + var->s_h / 2;
	if (var->drawEnd >= var->s_h)
		var->drawEnd = var->s_h - 1;
}

void	draw_texture(var_t *var)
{
	draw_info(var);
	int texx;
	int texy;
	double wallx;
	double step;
	double texpos;
		
	if (var->side == 0)
		wallx = var->posY + var->perpWallDist * var->rayDirY;
	else
		wallx = var->posX + var->perpWallDist * var->rayDirX;
	wallx -= floor(wallx);

	texx = (int)(wallx * (double)var->tex_w);
	if (var->side == 0 && var->rayDirX > 0)
		texx = var->tex_w - texx - 1;
	if (var->side == 1 && var->rayDirY < 0)
		texx = var->tex_w - texx - 1;
	
	step = 1.0 * var->tex_h / var->lineHeight;
	texpos = (var->drawStart - var->s_h / 2 + var->lineHeight / 2) * step;
	char *dst;
	int color;
	while (var->drawStart < var->drawEnd)
	{
		dst = var->addr + (var->drawStart * var->line + var->x * (var->bpp / 8));
		texy = (int)texpos;
		texpos += step;
		pixel_put(var, var->x, var->drawStart, var->loaded_addr[var->hit][64 * texy + texx]);
		var->drawStart++;
	}

}

int	convHex(char *hex)
{
	int i;

	i = 0;
	while (!(ft_strcmp(hex, ft_putnbr_base(i, HEXD))))
		{
			if (i > 255)
			{
				return (255);
			}
			i++;
		}
	return (i);
}