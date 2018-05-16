/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 19:24:22 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/05/08 19:24:23 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cor.h"

static void		dir_er_help(char *arg, char *str, int i, char *command)
{
	if (i == 0 || (arg[i - 1] == ':' || arg[i - 1] == '%'))
	{
		ft_printf("Lexical error at [%03i:%03i]\n",\
			g_num_str, (int)(ft_strstr(str, arg) - str) + 1);
		exit(1);
	}
	ft_printf("Invalid instruction at token [TOKEN][%03i:%03i]\
		INSTRUCTION \"%s\"\n",\
		g_num_str, (int)(ft_strstr(str, command) - str) + 1, command);
}

static void		reg_er(char *arg, char *str, char *command)
{
	int			i;
	long long	reg;

	i = 1;
	if (!arg)
		return ;
	if (arg && arg[0] != 'r')
		return ;
	reg = ft_atoi(&arg[1]);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return ;
		i++;
	}
	ft_printf("Invalid instruction at token [TOKEN][%03i:%03i]\
	INSTRUCTION \"%s\"\n",\
		g_num_str, (int)(ft_strstr(str, command) - str) + 1, command);
	exit(1);
}

static void		dir_er(char *arg, char *str, char *command)
{
	int			i;
	char		*value;

	if ((i = -1) && !arg)
		return ;
	if (arg && arg[0] != '%')
		return ;
	value = ft_strsub(arg, 1, ft_strlen(arg) - 1);
	while (value[++i])
		if (!ft_isdigit(value[i]) && value[i] != '-'\
			&& !ft_isalpha(value[i]) && value[i] != ':')
		{
			ft_printf("Lexical error at [%03i:%03i]\n",\
				g_num_str, (int)(ft_strstr(str, arg) - str) + 1);
			exit(1);
		}
		else if (value[i] == '-' && i != 0)
			return ;
	dir_er_help(arg, str, i, command);
	free(value);
	exit(1);
}

static void		ind_er(char *arg, char *str, char *command)
{
	int			num;
	int			len_of_num;
	int			len_of_str;

	if (!arg)
		return ;
	len_of_num = 0;
	len_of_str = ft_strlen(arg);
	if (arg && arg[0] == '-' && (len_of_num = 1))
		num = ft_atoi(arg + 1);
	else
		num = ft_atoi(arg);
	while (num /= 10)
		len_of_num++;
	len_of_num++;
	if (len_of_num != len_of_str)
		return ;
	ft_printf("Invalid instruction at token [TOKEN][%03i:%03i]\
	INSTRUCTION \"%s\"\n",\
		g_num_str, (int)(ft_strstr(str, command) - str) + 1, command);
	exit(1);
}

void			check_maybe_arg(char *str, char *my_str, int i, char *command)
{
	char		*arg;
	int			i_copy;
	int			j;

	j = i;
	i_copy = i;
	arg = arg_cat(my_str, &i);
	reg_er(arg, str, command);
	dir_er(arg, str, command);
	ind_er(arg, str, command);
}
