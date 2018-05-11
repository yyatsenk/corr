/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   be_valid_dude.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 13:45:05 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/05/09 13:45:09 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cor.h"

int check_com_or_name(char *str, t_i_j *n_c_set, int fd)
{
	if (!ft_strncmp(str, ".co", 3))
	{
		if(!check_comment(str, &n_c_set->comment, fd))
			return (0);
		n_c_set->comm_is_set = 1;
	}
	else if (!ft_strncmp(str, ".na", 3))
	{
		if(!check_name(str, &n_c_set->name, fd))
			return (0);
		n_c_set->name_is_set = 1;
	}
	return (1);
}


static void skip_all_shit(char **str_copy, int fd)
{
	char *str;

	str = *str_copy;
	while (*str_copy && (!ft_strncmp(*str_copy, "#", 1) || !ft_strcmp(*str_copy, "")))
	{
		free(*str_copy);
		get_next_line(fd, str_copy);
		g_num_str++;
	}
}

static void skip_all_shit_2(char **str_copy, int fd)
{
	char *str;

	str = *str_copy;
	while (*str_copy && (!ft_strncmp(*str_copy, "#", 1) || !ft_strcmp(*str_copy, "")))
	{
		free(*str_copy);
		if (get_next_line(fd, str_copy) != 0)
			g_num_str++;
		else
		{
			printf("Syntax error at token [TOKEN][%03i:%03i] END \"(null)\"\n", g_num_str + 1, 1);
			exit(1);
		}
	}
}

static void check_n_c(t_i_j *n_c_set)
{
	if (!n_c_set->comm_is_set && !n_c_set->name_is_set)
	{
		printf("No name, no comment :(\n");
		exit(1);
	}
}

int be_valid_dude(int fd, t_command **command, t_i_j *n_c_set)
{
	int i;
	char *str;

	i = 0;
	get_next_line(fd, &str);
	g_num_str++;
	skip_all_shit(&str, fd);
	if (!check_com_or_name(str, n_c_set, fd))
		return (0);
	free(str);
	get_next_line(fd, &str);
	g_num_str++;
	skip_all_shit(&str, fd);
	if (!check_com_or_name(str, n_c_set, fd))
		return (0);
	if (n_c_set->comm_is_set && n_c_set->name_is_set && (++g_num_str))
		get_next_line(fd, &str);
	skip_all_shit_2(&str, fd);
	check_n_c(n_c_set);
	if (!code_analyse(fd, str, command, *n_c_set))
		return (0);
	return (1);
}
