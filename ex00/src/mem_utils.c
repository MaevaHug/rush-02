/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahug <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 06:25:11 by mahug             #+#    #+#             */
/*   Updated: 2025/02/15 08:13:10 by mahug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

int	init_buffer(char **buffer)
{
	*buffer = (char *)malloc(sizeof(char) * 1);
	if (!*buffer)
		return (0);
	(*buffer)[0] = '\0';
	return (1);
}

static int	str_append(char **dst, char *src, int src_len)
{
	char	*new_str;
	int		dst_len;

	if (!dst || !*dst || !src || src_len < 0)
		return (0);
	dst_len = ft_strlen(*dst);
	new_str = (char *)malloc(sizeof(char) * (dst_len + src_len + 1));
	if (!new_str)
		return (0);
	ft_strlcpy(new_str, *dst, dst_len + 1);
	ft_strlcpy(new_str + dst_len, src, src_len + 1);
	free(*dst);
	*dst = new_str;
	return (1);
}

int	append_to_content(char **content, char *buffer, int bytes_read)
{
	return (str_append(content, buffer, bytes_read));
}

int	append_to_result(char **result, char *value)
{
	return (str_append(result, value, ft_strlen(value)));
}

char	*ft_strdup(char *src)
{
	char	*dup;
	int		i;

	dup = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
