#include "cublib.h"

int *cpy(var_t *var, int *tab)
{
	int *ret = malloc(sizeof(int) * 2);
	ret[0] = tab[0];
	ret[1] = tab[1];
	return (ret);
}

double	*sortqueue(var_t *var, double *dist)
{
	int i;
	double swap;
	double swap2;

	i = 1;
	while (i < var->spritenum)
	{
		if (dist[i - 1] < dist[i])
		{
			swap = dist[i - 1];
			dist[i - 1] = dist[i];
			dist[i] = swap;
			swap2 = var->spriteorder[i - 1];
			var->spriteorder[i - 1] = var->spriteorder[i];
			var->spriteorder[i] = swap2;
			i = 1;
 		}
		 else
		 i++;
	}
	return (dist);
}

double	*getdist(var_t *var)
{
	int i;
	double *dist;
	double swap;
	int swap2;

	dist = (double *)malloc(sizeof(double) * var->spritenum);
	var->spriteorder = malloc(sizeof(int) * var->spritenum);
	i = 0;
	while (i < var->spritenum)
	{
		dist[i] = ((var->posx - var->spritequeue[i][0]) *
		(var->posx - var->spritequeue[i][0])
		+ (var->posy - var->spritequeue[i][1])
		* (var->posy - var->spritequeue[i][1]));
		var->spriteorder[i] = i;
		i++;
	}
	return (sortqueue(var, dist));
}

void	init_sprite_var(var_t *var, int sx, int sy)
{
	var->vmove = 0.5;
	var->spritex = sx - var->posx;
	var->spritey = sy - var->posy;
	var->invdet = 1.0 / (var->planex * var->diry - var->dirx * var->planey);
	var->transformx = var->invdet * (var->diry * var->spritex - var->dirx * var->spritey);
	var->transformy = var->invdet * (-var->planey * var->spritex + var->planex * var->spritey);
	var->vmovescreen = (int)(var->vmove / var->transformy);
	var->spritescreenx = (int)((var->s_w / 2 * (1 + var->transformx / var->transformy)));
	var->spriteheight = abs((int)(var->s_h / (var->transformy)));
	var->drawstarty = -var->spriteheight / 2 + var->s_h / 2 + var->vmovescreen;
	if (var->drawstarty < 0)
		var->drawstarty = 0;
	var->drawendy = var->spriteheight / 2 + var->s_h / 2 + var->vmovescreen;
	if (var->drawendy >= var->s_h)
		var->drawendy = var->s_h - 1;
	var->spritewidth = abs((int)(var->s_h / (var->transformy)));
	var->drawstartx = -var->spritewidth / 2 + var->spritescreenx;
	if (var->drawstartx < 0)
		var->drawstartx = 0;
	var->drawendx = var->spritewidth / 2 + var->spritescreenx;
	if (var->drawendx >= var->s_w)
		var->drawendx = var->s_w - 1;
}

void	draw_sprite(var_t *var, int sx, int sy)
{
		int x;
		int y;
		int color;
		int d;

	init_sprite_var(var, sx, sy);
	x = var->drawstartx - 1;
	while (++x < var->drawendx)
	{
		if (var->transformy > 0 && x > 0 && x < var->s_w && var->transformy < var->zbuffer[x])
		{
			y = var->drawstarty - 1;
			var->texx = (int)(256 * (x - (-var->spritewidth / 2 + var->spritescreenx)) * var->tex_w/ var->spritewidth) / 256;

			while(++y < var->drawendy)
			{
				d = (y - var->vmovescreen) * 256 - var->s_h * 128 + var->spriteheight * 128;
				var->texy = ((d * var->tex_h / var->spriteheight) / 256);
				color = var->loaded_addr[6][(var->texx + var->texy * var->tex_w)];
				if ((color & 0x00ffffff) != 0) pixel_put(var, x, y, color);
			}
		}
	}	
}