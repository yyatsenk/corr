/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lable_command_maintain.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 19:18:55 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/05/08 19:18:56 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cor.h"

t_un_label		*init_u_label(char *name, int pos_y, int pos_x)
{
	t_un_label	*u_label;

	u_label = (t_un_label*)malloc(sizeof(t_un_label));
	u_label->name = name;
	u_label->pos_y = pos_y;
	u_label->pos_x = pos_x;
	u_label->next = NULL;
	return (u_label);
}

t_un_label		*add_new_u_l(t_un_label *new, t_un_label *begin)
{
	t_un_label	*copy;

	copy = begin;
	if (!begin)
		return (new);
	while (begin->next)
		begin = begin->next;
	begin->next = new;
	return (copy);
}

t_command		*add_c(t_command *new, t_command *begin)
{
	t_command	*copy;

	copy = begin;
	if (!begin)
		return (new);
	while (begin->next)
		begin = begin->next;
	begin->next = new;
	new->prev = begin;
	return (copy);
}

t_command		*init_c(char **name, int position, int size, int is_label)
{
	t_command	*com;

	com = (t_command*)malloc(sizeof(t_command));
	com->name = *name;
	com->size = size;
	com->is_label = is_label;
	com->position = position;
	com->a_code.one.l_name = NULL;
	com->a_code.two.l_name = NULL;
	com->a_code.three.l_name = NULL;
	com->a_code.one.num_of_bytes = 0;
	com->a_code.two.num_of_bytes = 0;
	com->a_code.three.num_of_bytes = 0;
	com->c_code.one = NULL;
	com->c_code.two = NULL;
	com->c_code.three = NULL;
	com->c_code.result = 0;
	com->next = NULL;
	com->prev = NULL;
	com->down_un = NULL;
	return (com);
}
