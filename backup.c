#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

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

int	get_file_size(char	*file_name)
{
	int		fd;
	char	*c;
	int		size;

	size = 0;
	c = (char	*)malloc(sizeof(char));
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		perror("r1");
		exit(1);
	}
	while (read(fd, c, 1))
	{
		size++;
	}
	free(c);
	return (size);
}

char	*dict_reader(char	*file_name, int	file_size)
{
	int		file_descriptor;
	int 	sz;
	char	*c;

	c = (char	*)malloc(file_size * sizeof(char));
	file_descriptor = open(file_name, O_RDONLY);
	sz = read(file_descriptor, c, file_size);
	c[sz] = '\0';
	return (c);
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

int	get_line_number(char	*full_text)
{
	int	i;
	int	lines;

	i = 0;
	lines = 0;
	while (full_text[i] != '\0')
	{
		if (full_text[i] == '\n')
		{
			lines++;
		}
		i++;
	}
	return (lines + 1);
}

char	**paragraph_split(char	*full_text, int	start, int	end)
{
	int		i;
	int		line_number;
	char	**dict;
	int		dict_idx;

	i = 0;
	line_number = get_line_number(full_text);
	dict = (char	**)malloc(sizeof(char	*) * line_number);
	dict_idx = 0;
	while (full_text[i] != '\0')
	{
		if (full_text[i] == '\n')
		{
			dict[dict_idx] = (char	*)malloc(sizeof(char) * (end - start) + 1);
			while (start <= end)
			{
				dict[dict_idx] = ft_concat(dict[dict_idx], full_text[start]);
				start++;
			}
			dict_idx++;
		}
		i++;
		end++;
	}
	return (dict);
}

int	ft_str_is_printable(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		if ((str[idx] < 32 || str[idx] > 126) && str[idx] != '\n')
			return (0);
		idx++;
	}
	return (1);
}
int	get_lines(char **map)
{
	int	line;

	line = 0;
	while (*map++)
		line++;
	return (line);
}

int	ft_catoi(char	c)
{
	return (c - '0');
}

int extra_validations(char **map, int col, int idx)
{
	if (ft_strlen(map[0]) != 5)
		return (0);
	if (!ft_str_is_printable(map[0]))
		return (0);
	if (get_lines(map) != ft_catoi(map[0][0]))
		return (0);
	while (col < 5)
	{
		idx = col + 1;
		while (idx < 5)
		{
			if (map[0][col] == map[0][idx])
				return (0);
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

int	smallest_num(int	a, int	b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_strcmp(char s1, char s2)
{
	if (s1 == s2)
		return (0);
	return (1);
}

int	mid_loop(char **map, int	line, int	col, int	aux_range)
{	
	int	temp_line;
	int	temp_col;
	int	found;

	found = 0;
	temp_line = line;
	while (temp_line <= line + aux_range)
	{
		temp_col = col;
		while (temp_col <= col + aux_range)
		{
			if (ft_strcmp(map[temp_line][temp_col], map[0][2]) == 0)
			{
				found = 1;
			}
			temp_col++;
		}	
		temp_line++;
	}
	return (found);
}

int	biggest_square(char **map, int	*coord_init, int	max_line, int	max_col)
{
	int	max_range;
	int	aux_range;

	aux_range = 0;
	max_range = smallest_num(max_line - coord_init[0], max_col - coord_init[1]);
	while (aux_range < max_range)
	{
		if (mid_loop(map, coord_init[0], coord_init[1], aux_range) == 1)
			return (aux_range);
		aux_range++;
	}
	return (aux_range - 1);
}

void fill_square(char **map, int	line, int	col, int	max_range)
{
	int	range;
	int	aux_range;

	range = 0;
	aux_range = 0;
	while (range < max_range)
	{
		aux_range = 0;
		while (aux_range < max_range)
		{
			map[line + range][col + aux_range] = map[0][3];
			aux_range++;
		}
		range++;
	}
}

void print_board(char **map)
{
	int	idx;

	idx = 1;
	while (map[idx])
	{
		ft_putstr(map[idx]);
		idx++;
	}
}

void	check_board(char **map, int	coord_init[2])
{
	int	*coord_sqr[2];
	int	biggest;
	int	temp_biggest;

	biggest = 0;
	temp_biggest = 0;
	while (coord_init[0] < ft_catoi(map[0][0]))
	{
		coord_init[1] = 0;
		while (coord_init[1] < ft_strlen(map[1]))
		{
			temp_biggest = biggest_square(map, coord_init,
					ft_catoi(map[0][0]), ft_strlen(map[1]));
			if (biggest < temp_biggest)
			{
				biggest = temp_biggest;
				coord_sqr[0] = (int) coord_init[0];
				coord_sqr[1] = (int) coord_init[1];
			}
			coord_init[1]++;
		}
		coord_init[0]++;
	}
	fill_square(map, coord_sqr[0], coord_sqr[1], biggest);
}

int	main(int	argn, char	**argv)
{
	char	*file_name;
	int idx;
	char	*full_text;
	char	**map;
	int	coord_init[2];

	idx = 1;
	if (argn > 1)
	{
		while (idx < argn)
		{
			full_text = dict_reader(argv[idx], get_file_size(argv[idx]));
			map = paragraph_split(full_text, 0, 0);
			if (is_valid_map(map) == 0)
				ft_putstr("map error");
			coord_init[0] = 1;
			coord_init[1] = 2;
			check_board(map, coord_init);
			print_board(map);
			free(full_text);
			free(map);
			idx++;
			put_char('\n');
		}
	}	
}
