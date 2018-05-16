/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 12:34:02 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/05/09 12:34:03 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cor.h"

static void		set_com(t_command **com, char *arg,\
	t_op command, char *str_orig)
{
	t_command	*copy;

	copy = *com;
	while (copy->next)
		copy = copy->next;
	copy->str = arg;
	copy->command_op = command;
	copy->str_orig = str_orig;
	g_arg_num++;
}

static void		help(char *str, char *str_orig, int size, t_command **comm)
{
	check_end_line(str, str_orig);
	(*comm)->c_code.result = ft_decimal_code((*comm)->c_code);
	g_arg_num = 0;
	(*comm)->size = size;
}

int				check_args(t_op command, char *str,\
	t_command **comm, char *str_orig)
{
	int			i;
	int			size;
	int			read;

	read = 0;
	if (!(i = 0) && (*comm)->is_label)
		return (1);
	size = command.cod_octal;
	set_com(comm, arg_cat(str, &i), command, str_orig);
	one_arg(command.one, &size, comm);
	read++;
	comma_find(str, &i, command, read);
	if (command.two != 0 && (read++))
	{
		set_com(comm, arg_cat(str, &i), command, str_orig);
		one_arg(command.two, &size, comm);
		comma_find(str, &i, command, read);
	}
	if (command.three != 0 && (read++))
	{
		set_com(comm, arg_cat(str, &i), command, str_orig);
		one_arg(command.three, &size, comm);
	}
	help(&str[i], str_orig, size, comm);
	return (1);
}
