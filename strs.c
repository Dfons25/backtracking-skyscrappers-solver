#include <stdlib.h>
#include <unistd.h>
#include "strs.h"

void	put_char(char	c)
{
	write(1, &c, 1);
}

int	ft_strlen(char	*str)
{
	int	size;

	size = 0;
	while (*str++)
		size++;
	return (size);
}

void	ft_putstr(char	*str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		put_char(str[i]);
		i++;
	}
}

char	*ft_concat(char	*str1, char	c)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = malloc(ft_strlen(str1) + 2);
	while (str1[i])
	{
		new_str[i] = str1[i];
		i++;
	}
	new_str[i++] = c;
	new_str[i] = '\0';
	return (new_str);
}

int	ft_catoi(char	c)
{
	return (c - '0');
}
