/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_reg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 10:52:18 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/05/09 10:52:19 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cor.h"

static int		check_reg_help(long long reg, char *str, int i)
{
	if (reg > 16 || reg <= 0)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int				check_reg(char *str, int *size, t_command *command)
{
	int			i;
	long long	reg;
	t_command	*c_copy;
	char		*mem_test;

	c_copy = command;
	while (c_copy->next)
		c_copy = c_copy->next;
	i = 1;
	if (str && str[0] != 'r')
		return (0);
	reg = ft_atoi(&str[1]);
	if (!(check_reg_help(reg, str, i)))
		return (0);
	(*size)++;
	c_copy->num = reg;
	free(c_copy->str);
	c_copy->str = ft_strdup("01");
	mem_test = NULL;
	set_data(c_copy, &mem_test, 1);
	return (1);
}
