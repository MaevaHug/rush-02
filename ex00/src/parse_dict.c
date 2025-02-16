/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dict.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahug <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 06:19:17 by mahug             #+#    #+#             */
/*   Updated: 2025/02/16 11:25:55 by mahug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

int	parse_dict_entry(char *entry, t_dict *dict_entry)
{
	char	*key;
	char	*value;

	key = entry;
	value = ft_strchr(entry, ':');
	if (!value)
		return (0);
	*value++ = '\0';
	key = trim_whitespaces(key, 0, 0, 1);
	value = trim_whitespaces(value, 1, 1, 1);
	if (!*key || !*value || !ft_str_is_numeric(key))
		return (0);
	dict_entry->key = ft_strdup(key);
	if (!dict_entry->key)
		return (0);
	dict_entry->value = ft_strdup(value);
	if (!dict_entry->value)
	{
		free(dict_entry->key);
		return (0);
	}
	return (1);
}

int	parse_dict_entries(char *content, t_dict *dict, int n_entries)
{
	char	*entry;
	char	*next_entry;
	int		i_entry;

	i_entry = 0;
	entry = content;
	while (entry && i_entry < n_entries)
	{
		next_entry = ft_strchr(entry, '\n');
		if (next_entry)
			*next_entry++ = '\0';
		if (ft_strlen(entry) > 0)
		{
			if (!parse_dict_entry(entry, &dict[i_entry]))
			{
				dict[i_entry].key = NULL;
				dict[i_entry].value = NULL;
				return (0);
			}
			i_entry++;
		}
		entry = next_entry;
	}
	return (1);
}

t_lang	get_dict_language(char *file)
{
	if (ft_strcmp(file, "numbers.dict") == 0)
		return (EN);
	else if (ft_strcmp(file, "numbers_esp.dict") == 0)
		return (ES);
	else
		return (UNKNOW);
}

int	parse_dict(char *file, t_lang *language, t_dict **dict)
{
	int		fd;
	char	*content;
	int		n_entries;

	if (!open_file(file, &fd))
		return (0);
	if (!read_file_and_get_content(fd, &content))
	{
		close_file(fd);
		return (0);
	}
	*language = get_dict_language(file);
	close_file(fd);
	if (!validate_dict(content, &n_entries) || !init_dict(dict, n_entries)
		|| !parse_dict_entries(content, *dict, n_entries))
	{
		free(content);
		return (0);
	}
	free(content);
	return (1);
}
