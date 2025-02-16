/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string2_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahug <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:24:57 by mahug             #+#    #+#             */
/*   Updated: 2025/02/16 11:42:06 by mahug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

int	ft_str_is_numeric(char *str)
{
	if (!*str)
		return (0);
	while (*str >= '0' && *str <= '9')
		str++;
	return (*str == '\0');
}

void	ft_putstr_nl_fd(char *str, int fd)
{
	while (*str)
		write(fd, str++, 1);
	write(fd, "\n", 1);
}
