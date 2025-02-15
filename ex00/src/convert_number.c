/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_number.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahug <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 07:49:43 by mahug             #+#    #+#             */
/*   Updated: 2025/02/15 08:15:27 by mahug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

static t_block	get_block(char *nb_str, int nb_len, int block_len, int offset)
{
	t_block	block;
	int		i;

	block.len = block_len;
	block.power = nb_len - block_len - offset;
	block.is_silent = (block_len != 1);
	i = 0;
	while (i < 3 - block_len)
	{
		block.nb[i] = '0';
		i++;
	}
	while (i < 3)
	{
		block.nb[i] = nb_str[block_len - 3 + i];
		if (block.nb[i] != '0')
			block.is_silent = 0;
		i++;
	}
	return (block);
}

static int	parse_nb_str_into_blocks(
	char *nb_str, t_block **blocks, int *n_blocks)
{
	int	nb_len;
	int	offset;
	int	i_block;
	int	block_len;

	nb_str = remove_leading_zeros(nb_str);
	nb_len = ft_strlen(nb_str);
	*n_blocks = (nb_len + 2) / 3;
	*blocks = (t_block *)malloc(sizeof(t_block) * (*n_blocks));
	if (!*blocks)
		return (0);
	i_block = 0;
	offset = 0;
	while (offset < nb_len)
	{
		block_len = (nb_len - offset) % 3;
		if (block_len == 0)
			block_len = 3;
		(*blocks)[i_block++] = get_block(
				nb_str + offset, nb_len, block_len, offset);
		offset += block_len;
	}
	return (1);
}

static int	convert_blocks(
	t_block *blocks, int n_blocks, t_dict *dict, char **result)
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
				if (!add_powered_number('1', blocks[i].power, dict, result))
					return (0);
			}
		}
		i++;
	}
	return (1);
}

int	convert_number(char *nb_str, t_dict *dict, char **result)
{
	t_block	*blocks;
	int		n_blocks;

	if (!init_buffer(result))
		return (0);
	if (!parse_nb_str_into_blocks(nb_str, &blocks, &n_blocks))
		return (0);
	if (!convert_blocks(blocks, n_blocks, dict, result))
	{
		free(blocks);
		return (0);
	}
	free(blocks);
	return (1);
}
