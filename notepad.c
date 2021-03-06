typedef struct var_s
{
	//var
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	double time;
	double oldTime;
	double cameraX;
	double rayDirX;
	double rayDirY;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
	float step;
	int mapX;
	int mapY;
	int stepX;
	int stepY;
	int hit;
	int wallx;
	int tex_y;
	int texpos;
	int tex_x;
	int tex_h;
	int tex_w;
	void *t_img;
	int *t_addr;
	int side;
	int lineHeight;
	int drawStart;
	int drawEnd;
	int *img_data;
	int color;
	int		ESC;
	int		W;
	int		A;
	int		S;
	int		D;
	int		L_R;
	int		R_R;
	void	*img;
	int t_endian;
	int t_bpp;
	int t_line;
	int	endian;
	int	bpp;
	int	line;
	int	offset;
	int	x;
	int	s_h;
	int	s_w;
	char	*addr;
	void	*mlx_ptr;
    void	*mlx_win;
	int **map;
	int	o_drawStart;
	int o_drawEnd;
	int o_x;
}	var_t;