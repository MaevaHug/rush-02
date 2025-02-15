/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_block.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahug <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 07:49:56 by mahug             #+#    #+#             */
/*   Updated: 2025/02/15 08:16:09 by mahug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

static int	process_hundreds(char *nb, t_dict *dict, char **result)
{
	if (!add_dict_value_to_result(dict, nb, 1, result))
		return (0);
	if (!add_powered_number('1', 2, dict, result))
		return (0);
	return (1);
}

static int	process_tens(char *nb, t_dict *dict, char **result)
{
	if (nb[0] == '1')
		return (add_dict_value_to_result(dict, nb, 2, result));
	else
		return (add_powered_number(nb[0], 1, dict, result));
}

static int	process_units(char *nb, t_dict *dict, char **result)
{
	return (add_dict_value_to_result(dict, nb, 1, result));
}

int	convert_block(t_block *block, t_dict *dict, char **result)
{
	if (block->nb[0] != '0')
	{
		if (!process_hundreds(&block->nb[0], dict, result))
			return (0);
	}
	if (block->nb[1] != '0')
	{
		if (!process_tens(&block->nb[1], dict, result))
			return (0);
		if (block->nb[1] == '1')
			return (1);
	}
	if (block->nb[2] != '0' || block->len == 1)
	{
		if (!process_units(&block->nb[2], dict, result))
			return (0);
	}
	return (1);
}
