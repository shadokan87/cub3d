#include "cublib.h"

void    fill_color(var_t *var, int i)
{
    if (ft_strcmp(var->ParamSliced[i], "F"))
    {
        var->F_color[0] = ft_atoi(ft_split(var->ParamSliced[i + 1], ',')[0]);
        var->F_color[1] = ft_atoi(ft_split(var->ParamSliced[i + 1], ',')[1]);
        var->F_color[2] = ft_atoi(ft_split(var->ParamSliced[i + 1], ',')[2]);
        return ;         
    }
    var->C_color[0] = ft_atoi(ft_split(var->ParamSliced[i + 1], ',')[0]);
    var->C_color[1] = ft_atoi(ft_split(var->ParamSliced[i + 1], ',')[1]);
    var->C_color[2] = ft_atoi(ft_split(var->ParamSliced[i + 1], ',')[2]);
}

void   fillLoopParams(var_t *var)
{
    int i;

    i = 0;
    while (var->ParamSliced[i] != NULL)
    {
        if (ft_strcmp(var->ParamSliced[i], "R"))
        {
            var->s_w = ft_atoi(var->ParamSliced[i + 1]);
            var->s_h = ft_atoi(var->ParamSliced[i + 2]);
        }
        if (ft_strcmp(var->ParamSliced[i], "NO"))
            var->text_paths[2] = ft_strdup(var->ParamSliced[i + 1]);
        if (ft_strcmp(var->ParamSliced[i], "SO"))
			var->text_paths[3] = ft_strdup(var->ParamSliced[i + 1]);
        if (ft_strcmp(var->ParamSliced[i], "WE"))
            var->text_paths[4] = ft_strdup(var->ParamSliced[i + 1]);
        if (ft_strcmp(var->ParamSliced[i], "EA"))
            var->text_paths[5] = ft_strdup(var->ParamSliced[i + 1]);
        if (ft_strcmp(var->ParamSliced[i], "S"))
            var->text_paths[6] = ft_strdup(var->ParamSliced[i + 1]);
        if (ft_strcmp(var->ParamSliced[i], "F") || ft_strcmp(var->ParamSliced[i], "C"))
            fill_color(var, i);
		else if (i <= 8 &&i != 7)
			var->text_paths[i] = NULL;
        i++;
    }
} 

int	getred(int rgb, var_t *var)
{
	char str[3];
	char *hex;
	int i = 0;

	hex = ft_putnbr_base(rgb, HEXD);
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

	hex = ft_putnbr_base(rgb, HEXD);
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

	hex = ft_putnbr_base(rgb, HEXD);
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