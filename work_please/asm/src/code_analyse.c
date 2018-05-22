/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_analyse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 12:48:35 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/05/09 12:48:36 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cor.h"

static void		help_me(t_i_j n_c_set, char *str, t_command *c_copy)
{
	if ((!n_c_set.comm_is_set || !n_c_set.name_is_set))
	{
		if (c_copy->is_label == 1)
			ft_printf("Syntax error at token\
	[TOKEN][%03i:%03li] LABEL \"%s:\"\n",\
	g_num_str, (ft_strstr(str, c_copy->name) - str) + 1,\
	c_copy->name);
		else
			ft_printf("Syntax error at token\
	[TOKEN][%03i:%03li] COMMAND \"%s\"\n",\
				g_num_str, (ft_strstr(str, c_copy->name) - str) + 1,\
				c_copy->name);
		exit(1);
	}
	if (ft_strlen(n_c_set.name) > 128 || ft_strlen(n_c_set.comment) > 2048)
	{
		ft_printf("Too long name or comment\n");
		exit(1);
	}
}

int				code_analyse(int fd, char *str, t_command **comm, t_i_j n_c_set)
{
	t_command	*command;
	t_command	*c_copy;
	char		*my_str;
	int			i;

	i = 0;
	my_str = NULL;
	command = init_c(&my_str, 0, 0, 0);
	check_line(str, command);
	free(str);
	c_copy = command;
	while (c_copy->next && i != 1 && (++i))
		c_copy = c_copy->next;
	help_me(n_c_set, str, c_copy);
	while (get_next_line(fd, &str) != 0)
	{
		g_num_str++;
		if (str && str[0] != '\0' && str[0] != '#')
			check_line(str, command);
		free(str);
	}
	lable_is_there(command);
	*comm = command;
	return (1);
}
