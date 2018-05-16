/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 10:44:04 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/05/09 10:44:06 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cor.h"

void	set_data(t_command *c_copy, char **label_name, int bytes)
{
	if (c_copy->num < 0)
		c_copy->num = make_positive(c_copy->num, 2);
	if (g_arg_num == 1 && (c_copy->c_code.one = c_copy->str))
	{
		c_copy->a_code.one.num_of_bytes = bytes;
		c_copy->a_code.one.num_to_code = c_copy->num;
		c_copy->a_code.one.l_name = *label_name;
	}
	else if (g_arg_num == 2 && (c_copy->c_code.two = c_copy->str))
	{
		c_copy->a_code.two.num_of_bytes = bytes;
		c_copy->a_code.two.num_to_code = c_copy->num;
		c_copy->a_code.two.l_name = *label_name;
	}
	else if (g_arg_num == 3 && (c_copy->c_code.three = c_copy->str))
	{
		c_copy->a_code.three.num_of_bytes = bytes;
		c_copy->a_code.three.num_to_code = c_copy->num;
		c_copy->a_code.three.l_name = *label_name;
	}
}

void	set_dir(t_command *comm, char **label_name)
{
	if (g_arg_num == 1 && (comm->c_code.one = ft_strdup("10")))
	{
		comm->a_code.one.num_of_bytes = comm->command_op.size;
		comm->a_code.one.num_to_code = comm->num;
		comm->a_code.one.l_name = *label_name;
	}
	else if (g_arg_num == 2 && (comm->c_code.two = ft_strdup("10")))
	{
		comm->a_code.two.num_of_bytes = comm->command_op.size;
		comm->a_code.two.num_to_code = comm->num;
		comm->a_code.two.l_name = *label_name;
	}
	else if (g_arg_num == 3 && (comm->c_code.three = ft_strdup("10")))
	{
		comm->a_code.three.num_of_bytes = comm->command_op.size;
		comm->a_code.three.num_to_code = comm->num;
		comm->a_code.three.l_name = *label_name;
	}
}
