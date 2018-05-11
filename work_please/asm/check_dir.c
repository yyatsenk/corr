/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 11:55:21 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/05/09 11:55:23 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cor.h"

static int norm_help_0(char **lable_name, char *value, t_command *comm, t_command *comm_copy)
{
	*lable_name = ft_strsub(value, 1, ft_strlen(comm->str) - 1);
	if(!check_lable_name(*lable_name))
		return (0);
	if (check_duplicates(comm->down_un, *lable_name))
	{
		while (comm_copy->next)
			comm_copy = comm_copy->next;
		comm->down_un = add_new_u_l(init_u_label(*lable_name, g_num_str,\
			ft_strstr(comm->str_orig, comm->str)- comm->str_orig), comm->down_un);
	}
	free(value);
	return (1);
}

static int norm_help_1(long long *num, char *value)
{
	int i;

	i = -1;
	*num = ft_atoi(value);
	while (value[++i])
		if (!ft_isdigit(value[i]) && value[i] != '-')
			return (0);
		else if (value[i] == '-' && i != 0)
			return (0);
	return (1);
}

int check_dir(int *size, t_command *comm)
{
	char *lable_name;
	long long num;
	char *value;
	t_command *comm_copy;

	comm_copy = comm;
	num = -2147483648;
	lable_name = NULL;
	if (comm->str && comm->str[0] != '%')
		return (0);
	value = ft_strsub(comm->str, 1, ft_strlen(comm->str) - 1);
	if (value && value[0] == ':')
	{
		if (!norm_help_0(&lable_name, value, comm, comm_copy))
			return (0);
	}
	else
		if (!norm_help_1(&num, value))
			return (0);
	(*size) += comm->command_op.size;
	comm->num = num;
	set_dir(comm, lable_name);
	return (1);
}
