/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 12:45:04 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/02/02 12:45:05 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		prec_part_1(char **format_line, int *hash)
{
	while (**format_line != '.' && **format_line)
	{
		if (**format_line == '#')
			*hash = 1;
		*format_line = *format_line + 1;
	}
}

static void		prec_part_2(int *chlen, char **str, char **str_new, int sign)
{
	char		*str_new_2;
	char		*str_new_3;
	int			i;

	str_new_2 = NULL;
	str_new_3 = NULL;
	i = -1;
	while (++i < *chlen)
		(*str_new)[i] = '0';
	(*str_new)[i] = '\0';
	str_new_2 = *str;
	*str = ft_strjoin(*str_new, *str);
	free(*str_new);
	if (sign)
		str_new_2--;
	if (str_new_2[0] == '-' && (str_new_3 = *str))
		*str = ft_strjoin("-", *str);
	free(str_new_2);
	if (str_new_3)
		free(str_new_3);
}

static void		prec_part_3(int *rozmir, char *format_line,
	char **str, int *sign)
{
	*rozmir = ft_atoi((format_line + 1));
	if ((*str)[0] == '-' && (*sign = 1))
		*str = *str + 1;
}

char			*precision_num(char *format_line, char *str,
	t_typer type, int *nil)
{
	int			rozmir;
	int			chlen;
	int			hash;
	int			sign;
	char		*str_new;

	hash = 0;
	sign = 0;
	prec_part_1(&format_line, &hash);
	if (*format_line == '\0')
		return (str);
	if (!(*nil = 0) && ((!ft_isdigit(format_line[1]) || format_line[1] == '0'))
		&& type != d && str[0] == '0' && (str = ft_strnew(0)))
		return (str);
	prec_part_3(&rozmir, format_line, &str, &sign);
	chlen = rozmir - ft_strlen(str);
	if (chlen >= 0)
		str_new = ft_strnew(chlen);
	else if (*(str - 1) == '-')
		return (str - 1);
	else
		return (str);
	prec_part_2(&chlen, &str, &str_new, sign);
	return (str);
}
