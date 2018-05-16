/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 13:07:09 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/02/02 13:07:10 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		plus_null_hash(t_flag *flag, char **format_line)
{
	int			i;

	i = -1;
	while ((*format_line)[++i])
		if ((*format_line)[i] == '.')
			flag->pres = 1;
	while (!ft_isdigit(**format_line) && **format_line)
	{
		if (**format_line == '#')
			flag->hash = 1;
		*format_line = *format_line + 1;
		while (**format_line == '0')
			*format_line = *format_line + 1;
		if ((**format_line == '+' || **format_line == ' ') && flag->pres == 0)
			flag->rozmir = -1;
	}
}

static void		prec_and_flag_finder(char **str,
	t_flag *flag, char *format_line)
{
	if ((*str)[0] == '+')
		flag->rozmir = 0;
	else if ((*str)[0] == '-' && (*str)[1] != '0'
		&& !(flag->rozmir = 0))
	{
		flag->sign = 1;
		*str = *str + 1;
	}
	flag->rozmir += ft_atoi(format_line);
}

static void		new_str_maker_width(char **str,
	char **str_new, char c, t_flag *flag)
{
	char		*str_new_2;
	int			i;

	str_new_2 = NULL;
	i = -1;
	while (++i < flag->chlen)
		(*str_new)[i] = c;
	(*str_new)[i] = '\0';
	if (c == ' ' && flag->sign == 1 && !(flag->sign = 0))
		*str = *str - 1;
	str_new_2 = *str;
	*str = ft_strjoin(*str_new, *str);
	free(*str_new);
	if (flag->sign == 1)
		str_new_2--;
	if (str_new_2[0] == '-' && c != ' ')
		*str = ft_strjoin("-", *str);
	free(str_new_2);
}

char			*width_num(char *format_line, char *str, char c, t_typer type)
{
	t_flag		flag;
	char		*str_new;

	if (str == NULL)
		return (str);
	flag.hash = 0;
	flag.pres = 0;
	flag.rozmir = 0;
	flag.sign = 0;
	plus_null_hash(&flag, &format_line);
	if (*format_line == '\0')
		return (str);
	prec_and_flag_finder(&str, &flag, format_line);
	flag.chlen = flag.rozmir - ft_strlen(str) - flag.sign;
	if ((type == x || type == X) && c == '0' && flag.hash == 1)
		flag.chlen -= 2;
	if (flag.chlen > 0)
		str_new = ft_strnew(flag.chlen - flag.sign);
	else if (*(str - 1) == '-')
		return (str - 1);
	else
		return (str);
	new_str_maker_width(&str, &str_new, c, &flag);
	return (str);
}
