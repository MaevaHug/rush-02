/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_blocks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahug <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:46:46 by mahug             #+#    #+#             */
/*   Updated: 2025/02/16 17:18:26 by mahug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

int	handle_power_es(t_block block, t_dict *dict, char **result)
{
	if (!add_separator(" ", result))
		return (0);
	if (ft_strncmp(block.nb, "001", 3) == 0 || block.power == 3)
	{
		if (!add_powered_number('1', block.power, dict, result))
			return (0);
	}
	else
	{
		if (!add_powered_number_es(block.power, dict, result))
			return (0);
	}
	return (1);
}

int	convert_blocks_es(
		t_block *blocks, int n_blocks, t_dict *dict, char **result)
{
	int	i;

	i = 0;
	while (i < n_blocks)
	{
		if (!blocks[i].is_silent)
		{
			if (!convert_block_es(&blocks[i], dict, result))
				return (0);
			if (blocks[i].power > 0)
			{
				if (!handle_power_es(blocks[i], dict, result))
					return (0);
			}
		}
		i++;
	}
	return (1);
}

int	convert_blocks_en(
		t_block *blocks, int n_blocks, t_dict *dict, char **result)
{
	int	i;

	i = 0;
	while (i < n_blocks)
	{
		if (!blocks[i].is_silent)
		{
			if (!convert_block_en(&blocks[i], dict, result))
				return (0);
			if (blocks[i].power > 0)
			{
				if (!add_separator(" ", result)
					|| !add_powered_number('1', blocks[i].power, dict, result))
					return (0);
			}
		}
		i++;
	}
	return (1);
}

int	convert_blocks(t_block *blocks, int n_blocks, t_dict *dict, char **result)
{
	int	i;

	i = 0;
	while (i < n_blocks)
	{
		if (!blocks[i].is_silent)
		{
			if (!convert_block(&blocks[i], dict, result))
				return (0);
			if (blocks[i].power > 0)
			{
				if (!add_separator(" ", result)
					|| !add_powered_number('1', blocks[i].power, dict, result))
					return (0);
			}
		}
		i++;
	}
	return (1);
}
