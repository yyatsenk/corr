/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ind.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 12:06:50 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/05/09 12:06:51 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cor.h"

static int if_num(char *str, int *num_copy)
{
	int len_of_num;
	int len_of_str;
	int num;

	len_of_str = ft_strlen(str);
	len_of_num = 0;
	if(str && str[0] == '-' && (len_of_num = 1))
			num = ft_atoi(str + 1);
		else
			num = ft_atoi(str);
		*num_copy = num;
		while (num /= 10)
			len_of_num++;
		len_of_num++;	
		if (len_of_num != len_of_str)
			return (0);
		if (str[0] == '-')
			*num_copy = -(*num_copy);
	return (1);
}

static int if_label(int *num_copy, char **lable_name, t_command **c_copy)
{
	*num_copy = 2147483647;
	*lable_name = ft_strsub((*c_copy)->str, 1, ft_strlen((*c_copy)->str) - 1);
	if(!check_lable_name(*lable_name))
		return (0);
	if (check_duplicates((*c_copy)->down_un, *lable_name))
	{
		while ((*c_copy)->next)
			(*c_copy) = (*c_copy)->next;
		(*c_copy)->down_un = add_new_u_l(init_u_label(*lable_name, g_num_str,\
			ft_strstr((*c_copy)->str_orig,\
				(*c_copy)->str) - (*c_copy)->str_orig), (*c_copy)->down_un);
	}
	return (1);
}

int check_ind(char **str, int *size, t_command *command, char **str_orig)
{
	t_command *c_copy;
	int num_copy;
	char *lable_name;

	c_copy = command;
	lable_name = NULL;
	while (c_copy->next)
		c_copy = c_copy->next;
	if (*str && (*str)[0] == ':')
	{
		if (!if_label(&num_copy, &lable_name, &c_copy))
			return (0);
	}
	else
		if (!if_num(*str, &num_copy))
			return (0);
	c_copy->num = num_copy;
	free(c_copy->str);
	c_copy->str = ft_strdup("11");
	set_data(c_copy, &lable_name, 2);
	(*size) += 2;
	return (1);
}

