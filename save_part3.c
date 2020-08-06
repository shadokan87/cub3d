#include "cublib.h"

int checktop(char *str)
{
	int i;
	int y;
	int count;

	i = 0;
	y = 0;
	count = 0;
	if (str[i] && str[i] == ' ')
	{
		while (str[i] && str[i] == ' ')
			i++;
	}
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		if (!iswall(str[i]))
				return (0);
		i++;
	}
	return (1);
}

int issymbol(char c)
{
	if (c == '4')
		return (1);
	else if (c == '5')
		return (1);
	else if (c == '6')
		return (1);
	else if (c == '2')
		return (1);
	else if (c == '1')
		return (1);
	else if (c == '3')
		return (1);
	else if (c == '0')
		return (1);
	return (0);
}

void	lineisok(char *str, var_t *var)
{
	int i;
	
	i = 0;
	if (str[i] && str[i] == ' ')
	{
		while (str[i] && str[i] == ' ')
			i++;
	}
	if (!iswall(str[i]))
		closegame(var, "map_not_closed");	
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		if (!issymbol(str[i]))
			closegame(var,"map_symbol_unknown");
		i++;
	}
	if (!iswall(str[i - 1]))
		closegame(var, "map_not_closed");
}

void checkmiddle(char **str, var_t *var)
{
	int i;
	int y;

	i = 0;
	y = 0;
	while (str[i + 1])
	{
		lineisok(str[i], var);
		i++;
	}
}

void checkmap(char **str, var_t *var)
{
	int i;

	i = 0;
	if (!checktop(str[0]))
		closegame(var, "map_not_closed");
	checkmiddle(str, var);
	while (str[i])
		i++;
	if (!(checkbottom(str[i - 1])))
		closegame(var, "map_not_closed");
}