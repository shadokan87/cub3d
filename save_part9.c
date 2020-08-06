#include "cublib.h"

void	draw(var_t *var)
{
	draw_info(var);
	var->color = rgb_int(185, 94, 255);
	if (var->side == 1)
		var->color = var->color / 2;
		verline(var, var->x, var->drawstart, var->drawend, var->color);
}

void	raycast(var_t *var)
{
	var->x = 0;
	int i = 0;
	while (var->x < var->s_w)
	{
		var->camerax = 2 * var->x / (double)var->s_w - 1;
		var->raydirx = var->dirx + var->planex * var->camerax;
		var->raydiry = var->diry + var->planey * var->camerax;
		var->mapx = (int)var->posx;
		var->mapy = (int)var->posy;
		var->deltadistx = fabs(1 / var->raydirx);
		var->deltadisty = fabs(1 / var->raydiry);
		var->hit = 0;
		var->spritehit = 0;
		step(var);
		hit(var);
		verline(var, var->x, 0, var->s_h / 2, rgb_int(var->c_color[0], var->c_color[1], var->c_color[2]));
		verline(var, var->x, var->s_h / 2, var->s_h, rgb_int(var->f_color[0], var->f_color[1], var->f_color[2]));
		if (var->hit == 1)
			draw(var);
		if (var->hit > 1)
			draw_texture(var);
		var->zbuffer[var->x] = var->perpwalldist;
		var->x++;
	}
}

void	init_keys(var_t *var, int key_number)
{
	int *ptr;

	ptr = &var->esc;
	while (key_number)
	{
		*ptr = 0;
		ptr++;
		key_number--;
	}
}

int		key_pressed(int keycode, var_t *var)
{
	if (keycode == 53)
		closegame(var, "esc_pressed");
	else if (keycode == 13)
		var->w = 1;
	else if (keycode == 0)
		var->a = 1;
	else if (keycode == 1)
		var->s = 1;
	else if (keycode == 2)
		var->d = 1;
	else if (keycode == 123)
		var->l_r = 1;
	else if (keycode == 124)
		var->r_r = 1;
	return (0);	
}

int		key_released(int keycode, var_t *var)
{
	if (keycode == 53)
		var->esc = 0;
	else if (keycode == 13)
		var->w = 0;
	else if (keycode == 0)
		var->a = 0;
	else if (keycode == 1)
		var->s = 0;
	else if (keycode == 2)
		var->d = 0;
	else if (keycode == 123)
		var->l_r = 0;
	else if (keycode == 124)
		var->r_r = 0;
	return (0);
}