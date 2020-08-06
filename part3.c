#include "cublib.h"

int checkTop(char *str)
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
		if (!isWall(str[i]))
				return (0);
		i++;
	}
	return (1);
}

int isSymbol(char c)
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

void	lineIsOk(char *str, var_t *var)
{
	int i;
	
	i = 0;
	if (str[i] && str[i] == ' ')
	{
		while (str[i] && str[i] == ' ')
			i++;
	}
	if (!isWall(str[i]))
		closeGame(var, "MAP_NOT_CLOSED");	
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		if (!isSymbol(str[i]))
			closeGame(var,"MAP_SYMBOL_UNKNOWN");
		i++;
	}
	if (!isWall(str[i - 1]))
		closeGame(var, "MAP_NOT_CLOSED");
}

void checkMiddle(char **str, var_t *var)
{
	int i;
	int y;

	i = 0;
	y = 0;
	while (str[i + 1])
	{
		lineIsOk(str[i], var);
		i++;
	}
}

void checkMap(char **str, var_t *var)
{
	int i;

	i = 0;
	if (!checkTop(str[0]))
		closeGame(var, "MAP_NOT_CLOSED");
	checkMiddle(str, var);
	while (str[i])
		i++;
	if (!(checkBottom(str[i - 1])))
		closeGame(var, "MAP_NOT_CLOSED");
}