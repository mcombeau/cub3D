#include "cub3d.h"

static int	get_number_of_lines(char *path)
{
	int		fd;
	char	*line;
	int		line_count;

	line_count = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		printf("Error: Couldn't open the file\n");
	else
	{
		line = get_next_line(fd);
		while (line != NULL)
		{
			line_count++;
			free(line);
			line = get_next_line(fd);
		}
	}
	close(fd);
	return (line_count);
}

static void	fill_tab(int row, int column, int i, t_data *data)
{
	char	*line;

	line = get_next_line(data->map.fd);
	while (line != NULL)
	{
		data->map.file[row] = ft_calloc(ft_strlen(line) + 1, sizeof(char));
		if (!data->map.file[row])
			return (free_tab(data->map.file));
		while (line[i] != '\0')
			data->map.file[row][column++] = line[i++];
		data->map.file[row++][column] = '\0';
		column = 0;
		i = 0;
		free(line);
		line = get_next_line(data->map.fd);
	}
	data->map.file[row] = NULL;
}

void	parse_data(char *path, t_data *data)
{
	int		row;
	int		i;
	size_t	column;

	i = 0;
	row = 0;
	column = 0;
	data->map.line_count = get_number_of_lines(path);
	data->map.path = path;
	data->map.file = ft_calloc(data->map.line_count + 1, sizeof(char *));
	if (!(data->map.file))
		return ;
	data->map.fd = open(path, O_RDONLY);
	if (data->map.fd < 0)
		printf("Error: Couldn't open the file\n");
	else
	{
		fill_tab(row, column, i, data);
		close(data->map.fd);
	}
}