/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_data_maintain.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 15:22:38 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/05/11 15:22:39 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cor.h"

t_all_data		*init_all_data(char *str)
{
	t_all_data	*obj_data;

	obj_data = (t_all_data*)malloc(sizeof(t_all_data));
	obj_data->str = str;
	obj_data->next = NULL;
	return (obj_data);
}

t_all_data		*add_all_data(t_all_data *new, t_all_data *begin)
{
	t_all_data	*copy;

	copy = begin;
	if (!begin)
		return (new);
	while (begin->next)
		begin = begin->next;
	begin->next = new;
	return (copy);
}

void			free_all_data(t_all_data *begin)
{
	t_all_data	*copy;

	while (begin)
	{
		free(begin->str);
		copy = begin;
		begin = begin->next;
		free(copy);
	}
}

void			print_all_data_free(t_all_data *begin)
{
	t_all_data	*copy;

	copy = begin;
	while (copy)
	{
		ft_printf("%s\n", copy->str);
		copy = copy->next;
	}
	free_all_data(begin);
}

void			init_i_j(t_i_j *n_c_set)
{
	n_c_set->name_is_set = 0;
	n_c_set->comm_is_set = 0;
	n_c_set->name = NULL;
	n_c_set->comment = NULL;
}
