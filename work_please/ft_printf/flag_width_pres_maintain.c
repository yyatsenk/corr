/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_widrh_pres_maintain.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 17:12:20 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/02/01 17:12:21 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_flag	struct_fill(char *format, int i)
{
	t_flag		flag;

	flag.minus = 0;
	flag.plus = 0;
	flag.space = 0;
	flag.hash = 0;
	flag.nil = 0;
	while (format[++i] && (format[i] == '-' || format[i] == '+'
	|| format[i] == ' ' || format[i] == '#' || format[i] == '0'
	|| ft_isdigit(format[i]) || !ft_strncmp("ll", &format[i], 2)
	|| format[i] == 'h' || format[i] == 'j' || format[i] == 'l'
	|| format[i] == 'z' || ft_isdigit(format[i]) || format[i] == '.'))
	{
		if (format[i] == '-')
			flag.minus = 1;
		else if (format[i] == '+')
			flag.plus = 1;
		else if (format[i] == ' ')
			flag.space = 1;
		else if (format[i] == '#')
			flag.hash = 1;
		else if (format[i] == '0' && !ft_isdigit(format[i - 1]))
			flag.nil = 1;
	}
	return (flag);
}

static void		pres_width_join(char **str, char *format_line,
	t_flag *flag, t_typer *type)
{
	char		*str_free;

	str_free = NULL;
	if (flag->minus == 1)
		flag->nil = 0;
	if (flag->plus == 1)
		flag->space = 0;
	if ((*str)[0] == '0' && (*str)[1] == '\0' && *type != o && *type != O)
		*type = none;
	*str = precision_num(format_line, *str, *type, &flag->nil);
	if (flag->nil == 1)
		*str = width_num(format_line, *str, '0', *type);
	if (flag->hash == 1 && (*type == o || *type == O)
		&& (*str)[0] != '0' && (str_free = *str))
		*str = ft_strjoin("0", *str);
	else if (flag->hash == 1 && *type == x && (str_free = *str))
		*str = ft_strjoin("0x", *str);
	else if (flag->hash == 1 && *type == X && (str_free = *str))
		*str = ft_strjoin("0X", *str);
	if (str_free)
		free(str_free);
}

static void		last_join(t_flag *flag, t_typer type,
	char **str, char **str_free)
{
	if ((*str)[0] != '-' && flag->space == 1 && type != u
	&& type != x && type != o && type != O && type != X
	&& (*str_free = *str))
	{
		*str = ft_strjoin(" ", *str);
		free(*str_free);
	}
	if ((*str)[0] == '-' || type == u)
		flag->space = 0;
}

char			*flag_width_pres_maintain(char *format_line,
	char *str, t_typer type)
{
	t_flag		flag;
	int			i;
	char		*str_free;

	i = 0;
	str_free = NULL;
	flag = struct_fill(format_line, i);
	pres_width_join(&str, format_line, &flag, &type);
	if (type == u || type == d || type == i || type == none)
		if (flag.plus == 1)
			if (str[0] != '-' && flag.space != 1
				&& type != u && (str_free = str))
			{
				str = ft_strjoin("+", str);
				free(str_free);
			}
	last_join(&flag, type, &str, &str_free);
	if (flag.nil == 0)
		str = width_num(format_line, str, ' ', type);
	if (flag.minus == 1)
		str = ft_white_swap_num(str, flag.space);
	return (str);
}
