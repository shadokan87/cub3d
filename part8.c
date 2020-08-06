#include "cublib.h"


int	move_is_possible(int pos)
{
	if (pos == 1 || pos == 4)
		return (0);
	return (1);
}

void	fwd_bckwrd(var_t *var)
{
if (var->W)
    {
      if(var->map[(int)(var->posX + var->dirX * moveSpeed)][(int)(var->posY)] == 0) 
	  	var->posX += var->dirX * moveSpeed * 0.5;
      if(var->map[(int)(var->posX)][(int)(var->posY + var->dirY * moveSpeed)] == 0)
	  	var->posY += var->dirY * moveSpeed * 0.5;
    }
	if (var->S)
	{
		if (var->map[(int)(var->posX - var->dirX * moveSpeed)]
                         [(int)(var->posY)] == 0)
                         var->posX -= var->dirX * moveSpeed * 0.5;
		if (var->map[(int)(var->posX)][(int)(var->posY - var->dirY * moveSpeed)] == 0)
			var->posY -= var->dirY * moveSpeed * 0.5;
	}
}

void	x_y(var_t *var)
{
if (var->A)
	{
		if (var->map[(int)(var->posX)][(int)(var->posY + var->dirX * moveSpeed)] == 0)
			var->posY += var->dirX * moveSpeed * 0.5;
		if (var->map[(int)(var->posX - var->dirY * moveSpeed)][(int)(var->posY)] == 0)
			var->posX -= var->dirY * moveSpeed * 0.5;
	}
	if (var->D)
	{
		if (var->map[(int)(var->posX)][(int)(var->posY - var->dirX * moveSpeed)] == 0)
			var->posY -= var->dirX * moveSpeed * 0.5;
		if (var->map[(int)(var->posX + var->dirY * moveSpeed)][(int)(var->posY)] == 0)
			var->posX += var->dirY * moveSpeed * 0.5;
	}
}

void	l_r(var_t *var)
{
	double old_dir;
	double old_plane;
	double rot_speed;

	old_dir = var->dirX;
	old_plane = var->planeX;
	rot_speed = 0.1;
	if (var->R_R)
	{
		var->dirX = (var->dirX * cos(-rotSpeed)) - var->dirY * sin(-rotSpeed);
		var->dirY = (old_dir * sin(-rotSpeed) + var->dirY * cos(-rotSpeed));
		var->planeX = (var->planeX * cos(-rotSpeed) - var->planeY * sin(-rotSpeed));
     	var->planeY = (old_plane * sin(-rotSpeed) + var->planeY * cos(rotSpeed));
	}
	if (var->L_R)
	{
		var->dirX = (var->dirX * cos(rotSpeed)) - var->dirY * sin(rotSpeed);
		var->dirY = (old_dir * sin(rotSpeed) + var->dirY * cos(rotSpeed));
		var->planeX = (var->planeX * cos(rotSpeed) - var->planeY * sin(rotSpeed));
     	var->planeY = (old_plane * sin(rotSpeed) + var->planeY * cos(rotSpeed));
	}
}

int	movement(var_t *var)
{
	fwd_bckwrd(var);
	x_y(var);
	l_r(var);
}