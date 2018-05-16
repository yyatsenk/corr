/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 19:36:17 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/05/08 19:36:18 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cor.h"

static void		error_one_arg(char *str, int i)
{
	ft_printf("Syntax error at token [TOKEN][%03i:%03i]\
	INSTRUCTION \"%s\"\n", g_num_str, i + 1, str);
	exit(1);
}

static int		put_error_help(char *str)
{
	int			i;

	i = -1;
	while (str[++i])
	{
		if ((str[i] < '0' || str[i] > '9') && (str[i] < 'a' || str[i] > 'z')\
		&& str[i] != ' ' && str[i] != '\t' && str[i] != ':' && str[i] != '%')
		{
			if (str[i] == '#')
				return (0);
			ft_printf("Lexical error at [%03i:%03i]\n", g_num_str, i + 1);
			exit(1);
		}
	}
	return (1);
}

static void		put_error(char *str, char *command)
{
	char		*my_str;
	int			i;

	if (!(put_error_help(str)))
		return ;
	i = ft_strlen(command) - 1;
	my_str = ft_strstr(str, command);
	check_maybe_arg(str, my_str, i + 1, command);
	while (my_str[++i])
		if (my_str[i] != ' ' && my_str[i] != '\t')
			break ;
	if (!my_str[i])
	{
		ft_printf("Syntax error at token [TOKEN][%03i:%03i] ENDLINE\n",\
			g_num_str, (int)ft_strlen(str) + 1);
		exit(1);
	}
	else
		error_one_arg(&my_str[i],\
			(int)(ft_strstr(str, &my_str[i]) - str));
}

t_op			check_command(char *command, char *str)
{
	int			i;

	i = 0;
	while (g_op_tab[i].name)
	{
		if (!ft_strcmp(command, g_op_tab[i].name))
			return (g_op_tab[i]);
		i++;
	}
	put_error(str, command);
	exit(1);
}
