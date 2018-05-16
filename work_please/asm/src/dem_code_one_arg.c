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

static void	norm_help(int arg_code, t_command *comm, int *size, int *error)
{
	if (arg_code == 1 && (!check_reg(comm->str, size, comm)))
		*error = 1;
	if (arg_code == 2 && (!check_dir(size, comm)))
		*error = 2;
}

int			one_arg(int a_c, int *size, t_command **c)
{
	int		error;

	error = 0;
	norm_help(a_c, *c, size, &error);
	if (a_c == 3 && (!check_ind(&((*c)->str), size, *c)))
		error = 3;
	if (a_c == 4 && !check_dir(size, *c) &&\
		!check_ind(&((*c)->str), size, *c))
		error = 4;
	if (a_c == 5 && (!check_reg(((*c)->str), size, *c) &&\
		!check_ind(&((*c)->str), size, *c)))
		error = 5;
	if (a_c == 6 && (!check_reg(((*c)->str), size, *c) &&\
		!check_dir(size, *c)))
		error = 6;
	if (a_c == 7 && (!check_reg(((*c)->str), size, *c) &&\
		!check_dir(size, *c) &&\
		!check_ind(&((*c)->str), size, *c)))
		error = 7;
	if (error != 0)
	{
		ft_printf("Args error (%i)\n", error);
		exit(1);
	}
	return (1);
}

int			ft_decimal_code(t_command_code code)
{
	int		i;
	int		res;
	char	*str_b_num;

	i = 0;
	res = 0;
	str_b_num = join_cooler(&code);
	while (str_b_num[i])
	{
		if (str_b_num[i] == '1')
			res += my_pow(2, ((i - 7) * (-1)));
		i++;
	}
	free(str_b_num);
	return (res);
}
