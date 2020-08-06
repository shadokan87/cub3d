#include "cublib.h"

void	draw(var_t *var)
{
	draw_info(var);
	var->color = rgb_int(185, 94, 255);
	if (var->side == 1)
		var->color = var->color / 2;
		verline(var, var->x, var->drawStart, var->drawEnd, var->color);
}

void	raycast(var_t *var)
{
	var->x = 0;
	int i = 0;
	while (var->x < var->s_w)
	{
		var->cameraX = 2 * var->x / (double)var->s_w - 1;
		var->rayDirX = var->dirX + var->planeX * var->cameraX;
		var->rayDirY = var->dirY + var->planeY * var->cameraX;
		var->mapX = (int)var->posX;
		var->mapY = (int)var->posY;
		var->deltaDistX = fabs(1 / var->rayDirX);
		var->deltaDistY = fabs(1 / var->rayDirY);
		var->hit = 0;
		var->spriteHit = 0;
		step(var);
		hit(var);
		verline(var, var->x, 0, var->s_h / 2, rgb_int(var->C_color[0], var->C_color[1], var->C_color[2]));
		verline(var, var->x, var->s_h / 2, var->s_h, rgb_int(var->F_color[0], var->F_color[1], var->F_color[2]));
		if (var->hit == 1)
			draw(var);
		if (var->hit > 1)
			draw_texture(var);
		var->zBuffer[var->x] = var->perpWallDist;
		var->x++;
	}
}

void	init_keys(var_t *var, int key_number)
{
	int *ptr;

	ptr = &var->ESC;
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
		closeGame(var, "ESC_PRESSED");
	else if (keycode == 13)
		var->W = 1;
	else if (keycode == 0)
		var->A = 1;
	else if (keycode == 1)
		var->S = 1;
	else if (keycode == 2)
		var->D = 1;
	else if (keycode == 123)
		var->L_R = 1;
	else if (keycode == 124)
		var->R_R = 1;
	return (0);	
}

int		key_released(int keycode, var_t *var)
{
	if (keycode == 53)
		var->ESC = 0;
	else if (keycode == 13)
		var->W = 0;
	else if (keycode == 0)
		var->A = 0;
	else if (keycode == 1)
		var->S = 0;
	else if (keycode == 2)
		var->D = 0;
	else if (keycode == 123)
		var->L_R = 0;
	else if (keycode == 124)
		var->R_R = 0;
	return (0);
}