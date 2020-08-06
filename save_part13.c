#include "cublib.h"

void    fill_color(var_t *var, int i)
{
    if (ft_strcmp(var->paramsliced[i], "f"))
    {
        var->f_color[0] = ft_atoi(ft_split(var->paramsliced[i + 1], ',')[0]);
        var->f_color[1] = ft_atoi(ft_split(var->paramsliced[i + 1], ',')[1]);
        var->f_color[2] = ft_atoi(ft_split(var->paramsliced[i + 1], ',')[2]);
        return ;         
    }
    var->c_color[0] = ft_atoi(ft_split(var->paramsliced[i + 1], ',')[0]);
    var->c_color[1] = ft_atoi(ft_split(var->paramsliced[i + 1], ',')[1]);
    var->c_color[2] = ft_atoi(ft_split(var->paramsliced[i + 1], ',')[2]);
}

void   fillloopparams(var_t *var)
{
    int i;

    i = 0;
    while (var->paramsliced[i] != null)
    {
        if (ft_strcmp(var->paramsliced[i], "r"))
        {
            var->s_w = ft_atoi(var->paramsliced[i + 1]);
            var->s_h = ft_atoi(var->paramsliced[i + 2]);
        }
        if (ft_strcmp(var->paramsliced[i], "no"))
            var->text_paths[2] = ft_strdup(var->paramsliced[i + 1]);
        if (ft_strcmp(var->paramsliced[i], "so"))
			var->text_paths[3] = ft_strdup(var->paramsliced[i + 1]);
        if (ft_strcmp(var->paramsliced[i], "we"))
            var->text_paths[4] = ft_strdup(var->paramsliced[i + 1]);
        if (ft_strcmp(var->paramsliced[i], "ea"))
            var->text_paths[5] = ft_strdup(var->paramsliced[i + 1]);
        if (ft_strcmp(var->paramsliced[i], "s"))
            var->text_paths[6] = ft_strdup(var->paramsliced[i + 1]);
        if (ft_strcmp(var->paramsliced[i], "f") || ft_strcmp(var->paramsliced[i], "c"))
            fill_color(var, i);
		else if (i <= 8 &&i != 7)
			var->text_paths[i] = null;
        i++;
    }
} 

int	getred(int rgb, var_t *var)
{
	char str[3];
	char *hex;
	int i = 0;

	hex = ft_putnbr_base(rgb, hexd);
	if (rgb == 0)
		return (0);
	str[0] = hex[0];
	str[1] = hex[1];
	str[2] = '\0';
	if (str[0] == '0' && str[1] == '0')
		str[1] = '\0';
	while (i < 255)
	{
		if (ft_strcmp(var->hextable[i], str))
			return (i);
			
		i++;
	}
	return (255);
}

int	getblue(int rgb, var_t *var)
{
	char str[3];
	char *hex;
	int i = 0;

	hex = ft_putnbr_base(rgb, hexd);
	if (rgb == 0)
		return (0);
	str[0] = hex[4];
	str[1] = hex[5];
	str[2] = '\0';
	if (str[0] == '0' && str[1] == '0')
		str[1] = '\0';
	while (i < 255)
	{
		if (ft_strcmp(var->hextable[i], str))
			return (i);
		i++;
	}
	return (255);
}

int	getgreen(int rgb, var_t *var)
{
	char str[3];
	char *hex;
	int i = 0;

	hex = ft_putnbr_base(rgb, hexd);
	if (rgb == 0)
		return (0);
	str[0] = hex[2];
	str[1] = hex[3];
	str[2] = '\0';
	if (str[0] == '0' && str[1] == '0')
		str[1] = '\0';
	while (i < 255)
	{
		if (ft_strcmp(var->hextable[i], str))
			return (i);
		i++;
	}
	return (255);
}