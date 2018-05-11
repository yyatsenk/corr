/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dem_code_one_arg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 12:19:54 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/05/09 12:19:55 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cor.h"

static void norm_help(int arg_code, t_command *comm, int *size, int *error)
{
	if (arg_code == 1 && (!check_reg(comm->str, size, comm)))
			*error = 1;
	if (arg_code == 2 && (!check_dir(size, comm)))
			*error = 2;
}

int one_arg(int arg_code, int *size, t_command *comm)
{
	int error;

	error = 0;
	norm_help(arg_code, comm, size, &error);
	if (arg_code == 3 && (!check_ind(comm->str, size, comm, comm->str_orig)))
			error = 3;
	if (arg_code == 4 && !check_dir(size, comm) &&\
		!check_ind(comm->str, size, comm, comm->str_orig))
			error = 4;
	if (arg_code == 5 && (!check_reg(comm->str, size, comm) &&\
		!check_ind(comm->str, size, comm, comm->str_orig)))
			error = 5;
	if (arg_code == 6 && (!check_reg(comm->str, size, comm)&&\
		!check_dir(size, comm)))
			error = 6;
	if (arg_code == 7 && (!check_reg(comm->str, size, comm) &&\
		!check_dir(size, comm) &&\
		!check_ind(comm->str, size, comm, comm->str_orig)))
			error = 7;
	if (error != 0)
	{
		printf("Args error (%i)\n", error);
		exit(1);
	}
	return (1);
}

int ft_decimal_code(t_command_code code)
{
	int i;
	int res;
	char *str_b_num;

	i = 0;
	res = 0;
	str_b_num = join_cooler(code);
	while (str_b_num[i])
	{
		if (str_b_num[i] == '1')
			res += pow(2, ((i - 7) * (-1)));
		i++;
	}
	return (res);
}
