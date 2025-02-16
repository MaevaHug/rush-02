/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_block_es.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahug <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 09:20:00 by mahug             #+#    #+#             */
/*   Updated: 2025/02/16 10:14:14 by mahug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

static int	process_hundreds(t_block block, t_dict *dict, char **result)
{
	if (!add_separator(" ", result))
		return (0);
	if (ft_strncmp(block.nb, "100", 3) == 0)
		return (add_dict_value_to_result(dict, block.nb, 3, result));
	else if (block.nb[0] == '1')
		return (append_to_result(result, "ciento"));
	else
		return (add_powered_number(block.nb[0], 2, dict, result));
}

static int	process_tens(t_block block, t_dict *dict, char **result)
{
	if (!add_separator(" ", result))
		return (0);
	if (block.nb[1] == '1' || block.nb[1] == '2')
		return (add_dict_value_to_result(dict, &block.nb[1], 2, result));
	else
		return (add_powered_number(block.nb[1], 1, dict, result));
}

static int	process_units(t_block block, t_dict *dict, char **result)
{
	if (block.nb[1] != '0')
	{
		if (!add_separator(" y ", result))
			return (0);
	}
	else
	{
		if (!add_separator(" ", result))
			return (0);
	}
	return (add_dict_value_to_result(dict, &block.nb[2], 1, result));
}

int	convert_block_es(t_block *block, t_dict *dict, char **result)
{
	if (block->nb[0] != '0')
	{
		if (!process_hundreds(*block, dict, result))
			return (0);
	}
	if (block->nb[1] != '0')
	{
		if (!process_tens(*block, dict, result))
			return (0);
		if (block->nb[1] == '1' || block->nb[1] == '2')
			return (1);
	}
	if (block->nb[2] != '0' || block->len == 1)
	{
		if (!process_units(*block, dict, result))
			return (0);
	}
	return (1);
}
