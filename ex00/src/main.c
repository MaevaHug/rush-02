/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahug <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 06:05:29 by mahug             #+#    #+#             */
/*   Updated: 2025/02/15 08:15:02 by mahug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

int	clean_exit(t_dict *dict, char *result, t_error error)
{
	if (dict)
		free_dict(dict);
	if (result)
		free(result);
	if (error == NO_ERROR)
		return (EXIT_SUCCESS);
	if (error == DICT_ERROR)
		ft_putstr_nl_fd("Dict Error", 2);
	else
		ft_putstr_nl_fd("Error", 2);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	char	*file;
	char	*nb_str;
	t_dict	*dict;
	char	*result;

	dict = NULL;
	result = NULL;
	if (!parse_args(argc, argv, &file, &nb_str))
		return (clean_exit(dict, result, ERROR));
	if (!parse_dict(file, &dict))
		return (clean_exit(dict, result, DICT_ERROR));
	if (!convert_number(nb_str, dict, &result))
		return (clean_exit(dict, result, ERROR));
	ft_putstr_nl_fd(result, 1);
	return (clean_exit(dict, result, NO_ERROR));
}
