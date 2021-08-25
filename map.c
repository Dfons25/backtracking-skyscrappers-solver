#include "strs.h"
#include "map.h"

int	get_lines(char **map)
{
	int	line;

	line = 0;
	while (*map++)
		line++;
	return (line);
}

int extra_validations(char **map, int col, int idx)
{
	if (ft_strlen(map[0]) != 5) {
	printf("\n>>%s<<", map[0]);
	printf("%d 0", ft_strlen(map[0]));
		return (0);
	}
	if (!ft_str_is_printable(map[0])){
	ft_putstr("1");
		return (0);
	}
	if (get_lines(map) != ft_catoi(map[0][0])){
	ft_putstr("2");
		return (0);
	}
	while (col < 5)
	{
		idx = col + 1;
		while (idx < 5)
		{
			if (map[0][col] == map[0][idx]){
				ft_putstr("3");
				return (0);
				}
			idx++;			
		}
		col++;
	}
	return (1);
}

int	is_valid_map(char **map)
{
	int	idx;
	int	col;
	int	init_size;
	int	one_rock;

	one_rock = 0;
	init_size = ft_strlen(map[1]);
	if (extra_validations(map, 0, 1) == 0)
		return (0);
	idx = 1;
	while (map[idx])
	{
		if (ft_strlen(map[idx]) != init_size)
			return (0);
		col = 0;
		while (col < init_size)
		{
			if (map[idx][col] == map[0][2])
				one_rock = 1;
			col++;
		}
		idx++;
	}
	if (one_rock == 0)
		return (0);
	return (1);
}