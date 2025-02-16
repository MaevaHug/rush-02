/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahug <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 07:10:07 by mahug             #+#    #+#             */
/*   Updated: 2025/02/16 11:05:59 by mahug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

void	free_dict(t_dict *dict)
{
	int	i;

	if (!dict)
		return ;
	i = 0;
	while (dict[i].key)
	{
		free(dict[i].key);
		free(dict[i].value);
		i++;
	}
	free(dict);
	dict = NULL;
}

int	validate_dict(char *content, int *n_entries)
{
	int	i;
	int	line_len;

	*n_entries = 0;
	line_len = 0;
	i = 0;
	while (content[i])
	{
		if (content[i] == '\n')
		{
			if (line_len > 0)
				(*n_entries)++;
			line_len = 0;
		}
		else
			line_len++;
		i++;
	}
	if (i == 0 || content[i - 1] != '\n')
		return (0);
	return (1);
}

int	init_dict(t_dict **dict, int n_entries)
{
	*dict = (t_dict *)malloc(sizeof(t_dict) * (n_entries + 1));
	if (!*dict)
		return (0);
	(*dict)[n_entries].key = NULL;
	(*dict)[n_entries].value = NULL;
	return (1);
}

static char	*get_value_from_dict(t_dict *dict, char *key, int len)
{
	int	i;

	i = 0;
	while (dict[i].key)
	{
		if (ft_strlen(dict[i].key) == len && !ft_strncmp(dict[i].key, key, len))
			return (dict[i].value);
		i++;
	}
	return (NULL);
}

int	add_dict_value_to_result(t_dict *dict, char *key, int len, char **result)
{
	char	*value;

	value = get_value_from_dict(dict, key, len);
	if (!value)
		return (0);
	// if (**result != '\0')
	// {
	// 	if (!append_to_result(result, " "))
	// 		return (0);
	// }
	if (!append_to_result(result, value))
		return (0);
	return (1);
}
