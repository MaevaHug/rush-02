/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahug <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 06:20:36 by mahug             #+#    #+#             */
/*   Updated: 2025/02/15 07:44:26 by mahug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

int	open_file(char *file, int *fd)
{
	if (!file)
		*fd = STDIN_FILENO;
	else
		*fd = open(file, O_RDONLY);
	return (*fd != -1);
}

void	close_file(int fd)
{
	if (fd > 0)
		close(fd);
}

int	read_file_and_get_content(int fd, char **content)
{
	char	buffer[BUFFER_SIZE];
	int		bytes_read;

	if (!init_buffer(content))
		return (0);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		if (!append_to_content(content, buffer, bytes_read))
		{
			free(*content);
			*content = NULL;
			return (0);
		}
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read == -1)
	{
		free(*content);
		*content = NULL;
		return (0);
	}
	return (1);
}
