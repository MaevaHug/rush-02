/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahug <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 06:07:20 by mahug             #+#    #+#             */
/*   Updated: 2025/02/15 06:21:24 by mahug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

int	parse_args(int ac, char **av, char **file, char **nb_str)
{
	if (ac != 2 && ac != 3)
		return (0);
	if (ac == 2)
	{
		*file = "numbers.dict";
		*nb_str = av[1];
	}
	else
	{
		*file = av[1];
		*nb_str = av[2];
	}
	return (ft_str_is_numeric(*nb_str));
}
