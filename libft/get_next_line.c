/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexa <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:48:24 by alexa             #+#    #+#             */
/*   Updated: 2023/02/09 22:48:45 by alexa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_malloc_count(char *stock)
{
	int	i;

	i = 0;
	if (f_strchr(stock, '\n') == NULL)
		return (ft_strlen(stock));
	while (stock[i] != '\n' && stock[i] != '\0')
		i++;
	return (i + 1);
}

char	*ft_get_the_line(char *stock)
{
	char	*line;
	int		i;
	int		len;

	line = NULL;
	len = ft_malloc_count(stock);
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (stock[i] && i < len)
	{
		line[i] = stock[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

void	ft_get_the_spare(char *buffer)
{
	int	i;
	int	j;

	i = 0;
	while (buffer[i] != '\n')
		i++;
	i = i + 1;
	j = 0;
	while (i < BUFFER_SIZE)
	{
		buffer[j] = buffer[i];
		i++;
		j++;
	}
	buffer[j] = '\0';
}

char	*ft_line_results(int ret, char *stock, char *buffer)
{
	char		*line;

	line = NULL;
	if (ft_strlen(stock) == 0)
	{
		free(stock);
		return (NULL);
	}
	line = ft_get_the_line(stock);
	if (ret > 0)
		ft_get_the_spare(buffer);
	free(stock);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*stock;
	int			ret;

	stock = NULL;
	if ((read(fd, buffer, 0) == -1) || BUFFER_SIZE <= 0)
		return (NULL);
	ret = 1;
	stock = f_strjoin(stock, buffer);
	while (f_strchr(stock, '\n') == NULL && ret > 0)
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret < 0)
		{
			free(stock);
			return (NULL);
		}
		buffer[ret] = '\0';
		stock = f_strjoin(stock, buffer);
	}
	return (ft_line_results(ret, stock, buffer));
}
