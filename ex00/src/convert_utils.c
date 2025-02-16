/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahug <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 07:50:08 by mahug             #+#    #+#             */
/*   Updated: 2025/02/16 16:56:59 by mahug            ###   ########.fr       */
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

int	add_powered_number_es(int power, t_dict *dict, char **result)
{
	(void)dict;
	if (power == 6 && !append_to_result(result, "millones"))
		return (0);
	if (power == 9 && !append_to_result(result, "billones"))
		return (0);
	if (power == 12 && !append_to_result(result, "trillones"))
		return (0);
	if (power == 15 && !append_to_result(result, "cuatrillones"))
		return (0);
	if (power == 18 && !append_to_result(result, "quintillones"))
		return (0);
	if (power == 21 && !append_to_result(result, "sextillones"))
		return (0);
	if (power == 24 && !append_to_result(result, "septillones"))
		return (0);
	if (power == 27 && !append_to_result(result, "octillones"))
		return (0);
	if (power == 30 && !append_to_result(result, "nonillones"))
		return (0);
	if (power == 33 && !append_to_result(result, "decillones"))
		return (0);
	if (power == 36 && !append_to_result(result, "undecillones"))
		return (0);
	return (1);
}
