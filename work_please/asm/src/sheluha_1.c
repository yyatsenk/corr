/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sheluha_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 11:16:11 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/05/09 11:16:12 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cor.h"

long long		my_pow(int base, int power)
{
	long long	rreturn;
	int			n;

	rreturn = 1;
	n = 0;
	if (power > 0)
	{
		while (n < power)
		{
			rreturn *= base;
			n++;
		}
	}
	else
	{
		while (n > power)
		{
			rreturn /= base;
			n--;
		}
	}
	return (rreturn);
}

static int		find_size(t_command *command, char *name, int pos)
{
	int			res;
	t_command	*copy;

	res = 0;
	copy = command;
	while (copy)
	{
		if (copy->name)
			if (!ft_strcmp(copy->name, name) && copy->is_label)
			{
				res = copy->position - pos;
				break ;
			}
		copy = copy->next;
	}
	return (res);
}

static int		find_this_shit(t_command *command, char *name)
{
	t_command	*copy;

	copy = command;
	while (copy)
	{
		if (copy->name)
			if (!ft_strcmp(copy->name, name) && copy->is_label)
				return (1);
		copy = copy->next;
	}
	return (0);
}

static void		norm_help(t_command *c_copy, t_command *command)
{
	t_un_label	*down_copy;
	char		*str_join;

	while (c_copy)
	{
		down_copy = c_copy->down_un;
		while (c_copy->down_un)
		{
			if (!find_this_shit(command, c_copy->down_un->name))
			{
				str_join = ft_strjoin("%:", c_copy->down_un->name);
				ft_printf("No such label %s while attempting to dereference\
	token [TOKEN][%03i:%03i] DIRECT_LABEL \"%s\"\n",\
				c_copy->down_un->name, c_copy->down_un->pos_y,\
				c_copy->down_un->pos_x + 1, str_join);
				free(str_join);
				exit(1);
			}
			c_copy->down_un = c_copy->down_un->next;
		}
		c_copy->down_un = down_copy;
		c_copy = c_copy->next;
	}
}

int				lable_is_there(t_command *command)
{
	t_command	*c_copy;

	c_copy = command;
	norm_help(c_copy, command);
	c_copy = command;
	while (c_copy)
	{
		if (c_copy->a_code.one.l_name)
			c_copy->a_code.one.num_to_code = find_size(command,\
				c_copy->a_code.one.l_name, c_copy->position);
		if (c_copy->a_code.two.l_name)
			c_copy->a_code.two.num_to_code = find_size(command,\
				c_copy->a_code.two.l_name, c_copy->position);
		if (c_copy->a_code.three.l_name)
			c_copy->a_code.three.num_to_code = find_size(command,\
				c_copy->a_code.three.l_name, c_copy->position);
		c_copy = c_copy->next;
	}
	return (1);
}
