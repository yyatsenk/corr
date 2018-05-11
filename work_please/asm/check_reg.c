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

int check_reg(char *str, int *size, t_command *command)
{
	int i;
	long long reg;
	t_command *c_copy;

	c_copy = command;
	while (c_copy->next)
		c_copy = c_copy->next;		
	i = 1;
	if (str && str[0] != 'r')
		return (0);
	reg = ft_atoi(&str[1]);
	if (reg > 16 || reg <= 0)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	(*size)++;
	c_copy->num = reg;
	c_copy->str = ft_strdup("01");
	set_data(c_copy, NULL, 1);
	return (1);
}
