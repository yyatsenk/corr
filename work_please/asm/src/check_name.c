/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 12:59:42 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/05/09 12:59:45 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cor.h"

static void		help_0(char *str, int i, int j)
{
	if (!str[i])
	{
		i = 4;
		while (str[++i])
		{
			j = i - 1;
			while ((str[++j] >= 'a' && str[j] <= 'z')\
				|| (str[j] >= '0' && str[j] <= '9'))
				if (!ft_isalpha(str[j]) && !ft_isdigit(str[j]))
				{
					ft_printf("Syntax error at token [TOKEN][%03i:%03i]\
	INSTRUCTION \"%s\"\n",\
						g_num_str, i + 1, ft_strsub(str, i, j - i));
					exit(1);
				}
		}
	}
	if (!str[i])
	{
		ft_printf("Syntax error at token [TOKEN][%03i:%03i] ENDLINE\n",\
			g_num_str, i + 1);
		exit(1);
	}
}

static void		help_1(char *str, int i, int fd, int kavi)
{
	if (!str[i])
	{
		while (kavi != 2 && get_next_line(fd, &str) != 0)
		{
			g_num_str++;
			i = -1;
			while (str[++i])
				if (str[i] == '\"')
				{
					kavi++;
					break ;
				}
		}
		if (kavi == 2)
			ft_printf("Lexical error at [%i:%i]\n", g_num_str, i + 2);
		else
			ft_printf("Syntax error at token [TOKEN][%03i:%03i]\
	END \"(null)\"\n", g_num_str, 1);
		exit(1);
	}
}

int				check_name(char *str, char **name, int fd)
{
	int			i;
	int			j;
	int			kavi;

	kavi = 0;
	if (ft_strncmp(str, ".name", 5))
		return (0);
	i = 4;
	while (str[++i] && str[i] != '\"')
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			ft_printf("Lexical error at [%i:%i]\n", g_num_str, i + 1);
			exit(1);
		}
	help_0(str, i, 0);
	kavi++;
	i++;
	j = i;
	while (str[i] && str[i] != '\"')
		i++;
	help_1(str, i, fd, kavi);
	if (str[i] && str[i + 1])
		return (0);
	*name = ft_strsub(str, j, i - j);
	return (1);
}
