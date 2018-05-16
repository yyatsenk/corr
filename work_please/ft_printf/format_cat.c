/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_cat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 13:07:42 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/02/03 13:07:43 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*error_format_cat(char **format)
{
	int		counter;
	char	*format_line;

	counter = 1;
	while ((*format)[counter] && ((*format)[counter] == '-'
		|| (*format)[counter] == '+' || (*format)[counter] == ' '
		|| (*format)[counter] == '#' || (*format)[counter] == '0'
		|| ft_isdigit((*format)[counter]) || (*format)[counter] == '.'
		|| (*format)[counter] == 'h' || (*format)[counter] == 'l'
		|| (*format)[counter] == 'j' || (*format)[counter] == 'z'
		|| !ft_strncmp("ll", &(*format)[counter], 2)
		|| !ft_strncmp("hh", &(*format)[counter], 2)))
		counter++;
	if ((*format)[counter])
	{
		format_line = ft_strnew(counter + 1);
		format_line = ft_strncpy(format_line, *format, counter + 1);
		*format += counter + 1;
		return (format_line);
	}
	else
	{
		*format += counter;
		return (NULL);
	}
}

static void	counter_cat(char **format, int *counter)
{
	while ((*format)[*counter] && (*format)[*counter] != 's'
	&& (*format)[*counter] != 'S'
	&& (*format)[*counter] != 'd' && (*format)[*counter] != 'D'
	&& (*format)[*counter] != 'i' && (*format)[*counter] != 'o'
	&& (*format)[*counter] != 'O' && (*format)[*counter] != 'u'
	&& (*format)[*counter] != 'U' && (*format)[*counter] != 'x'
	&& (*format)[*counter] != 'X' && (*format)[*counter] != 'p'
	&& (*format)[*counter] != 'c' && (*format)[*counter] != 'C'
	&& (*format)[*counter] != '%' && ((*format)[*counter] == '-'
	|| (*format)[*counter] == '+' || (*format)[*counter] == ' '
	|| (*format)[*counter] == '#' || (*format)[*counter] == '0'
	|| ft_isdigit((*format)[*counter]) || (*format)[*counter] == '.'
	|| (*format)[*counter] == 'h' || (*format)[*counter] == 'l'
	|| (*format)[*counter] == 'j' || (*format)[*counter] == 'z'
	|| !ft_strncmp("ll", &(*format)[*counter], 2)
	|| !ft_strncmp("hh", &(*format)[*counter], 2)))
		(*counter)++;
}

char		*format_cat(char **format)
{
	char	*format_line;
	int		counter;

	counter = 1;
	counter_cat(format, &counter);
	if ((*format)[counter])
	{
		format_line = ft_strnew(counter + 1);
		format_line = ft_strncpy(format_line, *format, counter + 1);
		*format += counter + 1;
		return (format_line);
	}
	else if (!(*format)[counter])
	{
		format_line = error_format_cat(format);
		return (format_line);
	}
	else
		*format = *format + 1;
	return (NULL);
}
