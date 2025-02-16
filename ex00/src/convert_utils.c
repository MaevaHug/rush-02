/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahug <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 07:50:08 by mahug             #+#    #+#             */
/*   Updated: 2025/02/16 11:06:14 by mahug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

int	add_separator(char *separator, char **result)
{
	if (**result == '\0')
		return (1);
	else
		return (append_to_result(result, separator));
}

char	*remove_leading_zeros(char *str)
{
	while (*str == '0' && *(str + 1) != '\0')
		str++;
	return (str);
}

int	add_powered_number(char first_digit, int power, t_dict *dict, char **result)
{
	char	*powered;
	int		powered_len;
	int		i;

	powered_len = power + 1;
	powered = (char *)malloc(sizeof(char) * (powered_len + 1));
	if (!powered)
		return (0);
	powered[0] = first_digit;
	i = 1;
	while (i < powered_len)
		powered[i++] = '0';
	powered[i] = '\0';
	if (!add_dict_value_to_result(dict, powered, powered_len, result))
	{
		free(powered);
		return (0);
	}
	free(powered);
	return (1);
}
