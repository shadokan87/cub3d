#include "cublib.h"

void getmapfromparamfile(var_t *var)
{
	int i;
	int index;
	char **str;
	int newsize;

	str = getmapstr(var);
	index = getmapindex(var);
	i = 0;
	if (containspace(str[0]))
		str = convmap(str);
	checkmap(str, var);
	var->m_width = getmapwidth(str);
	ft_fprintf(1, "width = %d\n", var->m_width);
	if (!(var->m_height = getmapheight(str)))
		closegame(var, "map_not_closed");
	str = convspace(str);
		while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
	duplicate_map(var, str);
	if (var->posx == -1 || var->posy == -1)
		closegame(var, "no_player_start");
	initspritequeue(var);
}

void	checkcolor(var_t *var)
{
	int i = 0;
	while (i < 3)
	{
		if (!(var->f_color[i] > -1 && var->f_color[i] < 256))
			closegame(var, "color_error");
			i++;
	}
	i = 0;
	while (i < 3)
	{
		if (!(var->c_color[i] > -1 && var->c_color[i] < 256))
			closegame(var, "color_error");
			i++;
	}
}

void	inithextable(var_t *var)
{
	int i;

	i = 0;
	while (i <= 255)
	{
		var->hextable[i] = ft_putnbr_base(i, hexd);
		i++;
	}
}

void	initcolormap(var_t *var)
{
	int i;

	i = 0;
	var->colormap = malloc(sizeof(int *) * var->m_height);
	while (i < var->m_height)
  	{
    var->colormap[i] = malloc(sizeof(int) * var->m_width);
    i++;
  	}
}

void	init_struct(var_t *var, char **argv)
{
	int fd;
    char *line;
    int i;

	i = -1;
	inithextable(var);
	var->posx = -1;
	var->posy = -1;
    var->paramfile = null;
	var->paramsliced = null;
	var->screenshot = 0;
	var->mlx_win = null;
	var->mlx_ptr = null;
	var->addr = null;
	if (ft_strcmp(argv[1], "--save"))
		var->screenshot = 1;
    fd = open(argv[var->screenshot == 1 ? 2 : 1], o_rdonly);
    getparamfile(fd, &line, var);
	getmapfromparamfile(var);
	initcolormap(var);
    while (var->paramfile[++i])
		var->paramfile[i] == '\n' ? (var->paramfile[i] = ' ') : 0;
    var->paramsliced = ft_split(var->paramfile, ' ');
    if (!(var->text_paths = malloc(sizeof(char *) * 9)))
        return ;
	fillloopparams(var);
	checkcolor(var);
}