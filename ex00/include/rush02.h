/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush02.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahug <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 06:01:20 by mahug             #+#    #+#             */
/*   Updated: 2025/02/16 11:03:57 by mahug            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUSH02_H
# define RUSH02_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# define BUFFER_SIZE 1024

typedef enum e_lang		t_lang;
typedef enum e_error	t_error;
typedef struct s_dict	t_dict;
typedef struct s_block	t_block;

enum e_lang
{
	UNKNOW,
	EN,
	ES
};

enum e_error
{
	NO_ERROR,
	ERROR,
	DICT_ERROR
};

struct s_dict
{
	char	*key;
	char	*value;
};

struct s_block
{
	char	nb[3];
	int		len;
	int		power;
	int		is_silent;
};

// parse_args
int				parse_args(int ac, char **av, char **file, char **nb_str);

// parse_dict
int				parse_dict(char *file, t_lang *language, t_dict **dict);

// convert_number
int				convert_number(char *nb_str, t_dict *dict, char **result);

// convert_block
int				convert_block(t_block *block, t_dict *dict, char **result);

// convert_block_es
int	convert_block_es(t_block *block, t_dict *dict, char **result);

// convert_utils
int				add_separator(char *separator, char **result);
char			*remove_leading_zeros(char *str);
int				add_powered_number(
					char first_digit, int power, t_dict *dict, char **result);

// dict_utils
void			free_dict(t_dict *dict);
int				validate_dict(char *content, int *n_entries);
int				init_dict(t_dict **dict, int n_entries);
int				add_dict_value_to_result(
					t_dict *dict, char *key, int len, char **result);

// file_utils
int				open_file(char *file, int *fd);
void			close_file(int fd);
int				read_file_and_get_content(int fd, char **content);

// mem_utils
int				init_buffer(char **buffer);
int				append_to_content(char **content, char *buffer, int bytes_read);
int				append_to_result(char **result, char *value);
char			*ft_strdup(char *src);

// string_utils
int				ft_strlen(char *str);
int				ft_str_is_numeric(char *str);
unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size);
char			*ft_strchr(char *str, int c);
void			ft_putstr_nl_fd(char *str, int fd);
int				ft_strncmp(char *s1, char *s2, unsigned int n);
int				ft_strcmp(char *s1, char *s2);

// whitespaces
char			*trim_whitespaces(char *str, int start, int mid, int end);

#endif