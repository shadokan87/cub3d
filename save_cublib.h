#ifndef cublib_h
# define cublib_h

# include <string.h>

# include <unistd.h>
# include <stdlib.h>
# include "gnl_working/get_next_line.h"
# include "ft_fprintf/lprintf.h"
# include <mlx.h>
# include <math.h>
# include <unistd.h>
# include <stdint.h>

# define rotspeed 0.1
# define movespeed 0.1

typedef struct var_s
{

	//sprite
	double vmove;
	double spritex;
	double spritey;
	double invdet;
	double transformx;
	double transformy;
	int vmovescreen;
	int spritescreenx;
	int spriteheight;
	int drawstarty;
	int drawendy;
	int spritewidth;
	int drawstartx;
	int drawendx;
	int texx;
	int texy;
	//sprite
	//var
	double posx;
	double posy;
	double dirx;
	double diry;
	double planex;
	double planey;
	double time;
	double oldtime;
	double camerax;
	double raydirx;
	double raydiry;
	double sidedistx;
	double sidedisty;
	double deltadistx;
	double deltadisty;
	double perpwalldist;
	char *hextable[255];
	float step;
	int screenshot;
	int mapx;
	int mapy;
	int stepx;
	int stepy;
	int hit;
	int wallx;
	int ompx;
	int ompy;
	int tex_y;
	int texpos;
	int tex_x;
	int tex_h;
	int tex_w;
	int **spritequeue;
	int *queue;
	double *dist;
	void *t_img;
	int *t_addr;
	int spritehit;
	int side;
	int lineheight;
	int drawstart;
	int drawend;
	int *img_data;
	int color;
	int		esc;
	int		w;
	int		a;
	int		s;
	int		d;
	int		l_r;
	int		r_r;
	void	*img;
	int t_endian;
	int **colormap;
	int t_bpp;
	int t_line;
	int	endian;
	int	bpp;
	int	line;
	int	offset;
	int	x;
	int	s_h;
	int	s_w;
	int m_width;
	int m_height;
	char **text_paths;
	int **loaded_text;
	int **loaded_addr;
    char *paramfile;
    int f_color[3];
    int c_color[3];
    char **paramsliced;
	double zbuffer[10000];
	int y;
	int spritenum;
	int *sx;
	int *sy;
	double spritex;
	double spritey;
	int *spriteorder;
	char	*addr;
	void	*mlx_ptr;
    void	*mlx_win;
	int **map;
	int	o_drawstart;
	int o_drawend;
	int o_x;
	void *spritevar;
}	var_t;

void	init_struct(var_t *var, char **argv);
void	initcolormap(var_t *var);
void	inithextable(var_t *var);
void	checkcolor(var_t *var);
void getmapfromparamfile(var_t *var);
char **convspace(char **str);
char	**convmap(char **str);
int	containspace(char *str);
char *norestrict_removes(char *str);
char *rmspace(char *str);
void checkmap(char **str, var_t *var);
void checkmiddle(char **str, var_t *var);
void	lineisok(char *str, var_t *var);
int issymbol(char c);
int checktop(char *str);
int checkbottom(char *str);
char	**getmapstr(var_t *var);
int	skip(char ***split);
void duplicate_map(var_t *var, char **str2);
void	initspritequeue(var_t *var);
int	getmapwidth(char **str);
int getmapheight(char **str);
int *init_to_fill(var_t *var);
int	spacecount(char *str);
int	**copymap(int height, int width, int index, var_t *var);
int		start(var_t *var);
int		run(var_t *var);
void drawbmp (char *filename, var_t *var);
void	writecolor(var_t *var, int extrabytes, int fd);
void	writeheader(int fd, unsigned int *headers);
unsigned int	*getheader(int width, int height, int paddedsize);
int	load_text(var_t *var);
int	listen_keys(var_t *var);
int	movement(var_t *var);
void	l_r(var_t *var);
void	x_y(var_t *var);
void	fwd_bckwrd(var_t *var);
int	move_is_possible(int pos);
int		key_released(int keycode, var_t *var);
int		key_pressed(int keycode, var_t *var);
void	init_keys(var_t *var, int key_number);
void	raycast(var_t *var);
void	draw(var_t *var);
int	convhex(char *hex);
void	draw_texture(var_t *var);
void	draw_info(var_t *var);
void	cls(var_t *var);
void	hit(var_t *var);
void	draw_sprite(var_t *var, int sx, int sy);
void	init_sprite_var(var_t *var, int sx, int sy);
double	*getdist(var_t *var);
double	*sortqueue(var_t *var, double *dist);
int *cpy(var_t *var, int *tab);
void	step(var_t *var);
void	init_raycast(var_t *var);
int	verline(var_t *var, int x, int draw_start, int draw_end, int color);
void	pixel_put(var_t *var, int x, int y, int color);
void	pixel_put_fd(var_t *var, int color, int fd);
int	getgreen(int rgb, var_t *var);
int	getblue(int rgb, var_t *var);
int	getred(int rgb, var_t *var);
void   fillloopparams(var_t *var);
void    fill_color(var_t *var, int i);
int  ft_strcmp(char *str, char *str2);
void    getparamfile(int fd, char **line, var_t *var);
char *removes(char *str, var_t *var);
int	nospacegetmapindex(char *str);
int     ft_tolower(int c);
int	getmapindex(var_t *var);
int	iswall(char c);
char *remove_extraspaces(char *str);
int		rgb_int(int red, int green, int blue);
void    *ft_memset(void *b, int c, size_t len);
void	closegame(var_t *var, char *message);

































#endif
