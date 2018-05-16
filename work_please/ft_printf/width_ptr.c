/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 11:42:30 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/02/03 11:42:32 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*first_part(char **format_line, char *str)
{
	while (!ft_isdigit(**format_line) && **format_line)
	{
		if (**format_line == '.')
			return (str);
		(*format_line)++;
		if (**format_line == '0')
			(*format_line)++;
	}
	if (**format_line == '\0')
		return (str);
	return (NULL);
}

static void	end_part(char **str, char **str_new, t_flag flag, char c)
{
	int		i;
	char	*str_free;

	i = -1;
	while (++i < flag.chlen)
		(*str_new)[i] = c;
	(*str_new)[i] = '\0';
	*str = ft_strjoin(*str_new, *str);
	free(*str_new);
	if (c == '0' && (str_free = *str))
	{
		*str = ft_strjoin("0x", *str);
		free(str_free);
	}
}

char		*width_ptr(char *format_line, char *str, char c)
{
	t_flag	flag;
	char	*str_new;

	if (str == NULL)
		return (str);
	flag.chlen = 0;
	if (first_part(&format_line, str))
		return (str);
	flag.rozmir = ft_atoi(format_line);
	if (c == '0' && (flag.chlen = -2))
		str += 2;
	flag.chlen += flag.rozmir - ft_strlen(str);
	if (flag.chlen >= 0)
		str_new = ft_strnew(flag.chlen);
	else
	{
		if (c == '0')
			str -= 2;
		return (str);
	}
	end_part(&str, &str_new, flag, c);
	return (str);
}
