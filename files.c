#include <fcntl.h>
#include "strs.h"
#include "files.h"

int	get_file_size(char	*file_name)
{
	int		fd;
	char	*c;
	int		size;

	size = 0;
	c = (char *) malloc(sizeof (char));
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		perror("map error");
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
	int		sz;
	char	*c;

	c = (char *)malloc (file_size * sizeof(char));
	file_descriptor = open(file_name, O_RDONLY);
	sz = read(file_descriptor, c, file_size);
	c[sz] = '\0';
	return (c);
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
	dict = (char **)malloc(sizeof(char *) * line_number);
	dict_idx = 0;
	while (full_text[i] != '\0')
	{
		if (full_text[i] == '\n')
		{
			dict[dict_idx] = (char *) malloc(sizeof(char) * (end - start) + 1);
			dict[dict_idx] = "";
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
