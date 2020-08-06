#include "cublib.h"

void	hit(var_t *var)
{
	while (var->hit == 0)
	{
		if (var->sidedistx < var->sidedisty)
		{
			var->sidedistx += var->deltadistx;
			var->mapx += var->stepx;
			var->side = 0;
		}
		else
		{
			var->sidedisty += var->deltadisty;
			var->mapy += var->stepy;
			var->side = 1;
		}
		if (var->map[var->mapx][var->mapy] > 0)
		{
			var->hit = var->map[var->mapx][var->mapy];
			var->wallx = var->hit;
		}
	}
	if (var->side == 0)
		var->perpwalldist = (var->mapx - var->posx + (1 - 
		var->stepx) / 2) / var->raydirx;
	else
		var->perpwalldist = (var->mapy - var->posy + (1 - var->stepy) / 2) / var->raydiry;	
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
	var->lineheight = (int)(var->s_h / var->perpwalldist);
	var->drawstart = -var->lineheight / 2 + var->s_h / 2;
	if (var->drawstart < 0)
		var->drawstart = 0;
	var->drawend = var->lineheight / 2 + var->s_h / 2;
	if (var->drawend >= var->s_h)
		var->drawend = var->s_h - 1;
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
		wallx = var->posy + var->perpwalldist * var->raydiry;
	else
		wallx = var->posx + var->perpwalldist * var->raydirx;
	wallx -= floor(wallx);

	texx = (int)(wallx * (double)var->tex_w);
	if (var->side == 0 && var->raydirx > 0)
		texx = var->tex_w - texx - 1;
	if (var->side == 1 && var->raydiry < 0)
		texx = var->tex_w - texx - 1;
	
	step = 1.0 * var->tex_h / var->lineheight;
	texpos = (var->drawstart - var->s_h / 2 + var->lineheight / 2) * step;
	char *dst;
	int color;
	while (var->drawstart < var->drawend)
	{
		dst = var->addr + (var->drawstart * var->line + var->x * (var->bpp / 8));
		texy = (int)texpos;
		texpos += step;
		pixel_put(var, var->x, var->drawstart, var->loaded_addr[var->hit][64 * texy + texx]);
		var->drawstart++;
	}

}

int	convhex(char *hex)
{
	int i;

	i = 0;
	while (!(ft_strcmp(hex, ft_putnbr_base(i, hexd))))
		{
			if (i > 255)
			{
				return (255);
			}
			i++;
		}
	return (i);
}