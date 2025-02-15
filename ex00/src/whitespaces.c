/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whitespaces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahug <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 07:38:53 by mahug             #+#    #+#             */
/*   Updated: 2025/02/15 07:41:12 by mahug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

static int	ft_isspace(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

static char	*normalize_spaces(char *str)
{
	int	i;
	int	j;
	int	prev_is_space;

	i = 0;
	j = 0;
	while (str[i])
	{
		prev_is_space = (i == 0 || ft_isspace(str[i - 1]));
		if (!ft_isspace(str[i]) || !prev_is_space)
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}

char	*trim_whitespaces(char *str, int start, int mid, int end)
{
	int	i;

	if (start)
	{
		while (*str && ft_isspace(*str))
			str++;
	}
	if (mid)
		str = normalize_spaces(str);
	if (end)
	{
		i = ft_strlen(str) - 1;
		while (i >= 0 && ft_isspace(str[i]))
			str[i--] = '\0';
	}
	return (str);
}
