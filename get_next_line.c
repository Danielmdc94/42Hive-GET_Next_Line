/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 12:42:43 by dpalacio          #+#    #+#             */
/*   Updated: 2022/01/17 18:34:42 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//ssize_t read(int fd, void *buf, size_t count);
#include <stdio.h>

int	get_next_line(const int fd, char **line)
{
	static char	*placeholder[FD_MAX];
	char		buff[BUFF_SIZE + 1];
	char		*temp;
	ssize_t		buff_len;
	int			i;

	if (fd < 0 || fd > FD_MAX || !line)
		return (-1);
	buff_len = read(fd, buff, BUFF_SIZE);
	while (buff_len > 0)
	{
		buff[buff_len] = '\0';
		if (!placeholder[fd])
			placeholder[fd] = ft_strdup(buff);
		else
		{
			temp = ft_strjoin(placeholder[fd], buff);
			free(placeholder[fd]);
			placeholder[fd] = temp;
		}
		if (ft_strchr(placeholder[fd], '\n'))
			break ;
		buff_len = read(fd, buff, BUFF_SIZE);
	}
	if (buff_len == 0 && placeholder[fd] == NULL)
	{
		ft_memdel((void **)placeholder);
		return (0);
	}
	else if (buff_len < 0)
	{
		ft_memdel((void **)placeholder);
		return (-1);
	}
	else
	{
		i = 0;
		while (placeholder[fd][i] != '\n' && placeholder[fd][i] != '\0')
			i++;
		if (placeholder[fd][i] == '\n')
		{
			*line = ft_strsub(placeholder[fd], 0, i);
			temp = ft_strdup(&((placeholder[fd])[i + 1]));
			free(placeholder[fd]);
			placeholder[fd] = temp;
		}
		else
		{
			*line = placeholder[fd];
			ft_memdel((void **)&placeholder[fd]);
		}
		printf("%s\n", *line);
		return (1);
	}
}
