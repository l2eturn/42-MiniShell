/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvutt@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 03:22:05 by slimvutt          #+#    #+#             */
/*   Updated: 2025/09/07 03:22:05 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_store(int fd, char *store)
{
	int		byte_count;
	char	*buff;

	buff = ft_calloc_gnl(sizeof(char), (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	byte_count = 1;
	while (!(ft_strchr_gnl(store, '\n')) && byte_count != 0)
	{
		byte_count = read(fd, buff, BUFFER_SIZE);
		if (byte_count < 0)
		{
			free(buff);
			free(store);
			return (NULL);
		}
		buff[byte_count] = 0;
		store = ft_strjoin_gnl(store, buff);
	}
	free(buff);
	return (store);
}

char	*get_aline(char *store)
{
	char	*line;
	int		i;

	i = 0;
	if (store[0] == 0)
		return (NULL);
	while (store[i] && store[i] != '\n')
		i ++;
	line = ft_calloc_gnl(sizeof(char), (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (store[i] && store[i] != '\n')
	{
		line[i] = store[i];
		i ++;
	}
	if (store[i] == '\n')
	{
		line[i] = store[i];
		i ++;
	}
	line[i] = '\0';
	return (line);
}

char	*update_store(char *store)
{
	int		i;
	int		upd_index;
	char	*upd_store;

	i = 0;
	while (store[i] && store[i] != '\n')
		i ++;
	if (!store[i])
	{
		free(store);
		return (NULL);
	}
	upd_store = malloc(sizeof(char) * (ft_strlen_gnl(store) - i + 1));
	if (!upd_store)
	{
		free(upd_store);
		return (NULL);
	}
	i ++;
	upd_index = 0;
	while (store[i])
		upd_store[upd_index++] = store[i++];
	upd_store[upd_index] = '\0';
	free(store);
	return (upd_store);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*store[FD_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	store[fd] = get_store(fd, store[fd]);
	if (!store[fd])
		return (NULL);
	line = get_aline(store[fd]);
	store[fd] = update_store(store[fd]);
	return (line);
}
