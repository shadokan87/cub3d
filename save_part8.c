#include "cublib.h"


int	move_is_possible(int pos)
{
	if (pos == 1 || pos == 4)
		return (0);
	return (1);
}

void	fwd_bckwrd(var_t *var)
{
if (var->w)
    {
      if(var->map[(int)(var->posx + var->dirx * movespeed)][(int)(var->posy)] == 0) 
	  	var->posx += var->dirx * movespeed * 0.5;
      if(var->map[(int)(var->posx)][(int)(var->posy + var->diry * movespeed)] == 0)
	  	var->posy += var->diry * movespeed * 0.5;
    }
	if (var->s)
	{
		if (var->map[(int)(var->posx - var->dirx * movespeed)]
                         [(int)(var->posy)] == 0)
                         var->posx -= var->dirx * movespeed * 0.5;
		if (var->map[(int)(var->posx)][(int)(var->posy - var->diry * movespeed)] == 0)
			var->posy -= var->diry * movespeed * 0.5;
	}
}

void	x_y(var_t *var)
{
if (var->a)
	{
		if (var->map[(int)(var->posx)][(int)(var->posy + var->dirx * movespeed)] == 0)
			var->posy += var->dirx * movespeed * 0.5;
		if (var->map[(int)(var->posx - var->diry * movespeed)][(int)(var->posy)] == 0)
			var->posx -= var->diry * movespeed * 0.5;
	}
	if (var->d)
	{
		if (var->map[(int)(var->posx)][(int)(var->posy - var->dirx * movespeed)] == 0)
			var->posy -= var->dirx * movespeed * 0.5;
		if (var->map[(int)(var->posx + var->diry * movespeed)][(int)(var->posy)] == 0)
			var->posx += var->diry * movespeed * 0.5;
	}
}

void	l_r(var_t *var)
{
	double old_dir;
	double old_plane;
	double rot_speed;

	old_dir = var->dirx;
	old_plane = var->planex;
	rot_speed = 0.1;
	if (var->r_r)
	{
		var->dirx = (var->dirx * cos(-rotspeed)) - var->diry * sin(-rotspeed);
		var->diry = (old_dir * sin(-rotspeed) + var->diry * cos(-rotspeed));
		var->planex = (var->planex * cos(-rotspeed) - var->planey * sin(-rotspeed));
     	var->planey = (old_plane * sin(-rotspeed) + var->planey * cos(rotspeed));
	}
	if (var->l_r)
	{
		var->dirx = (var->dirx * cos(rotspeed)) - var->diry * sin(rotspeed);
		var->diry = (old_dir * sin(rotspeed) + var->diry * cos(rotspeed));
		var->planex = (var->planex * cos(rotspeed) - var->planey * sin(rotspeed));
     	var->planey = (old_plane * sin(rotspeed) + var->planey * cos(rotspeed));
	}
}

int	movement(var_t *var)
{
	fwd_bckwrd(var);
	x_y(var);
	l_r(var);
}