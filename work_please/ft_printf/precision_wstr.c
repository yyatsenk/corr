/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision_wstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 12:48:05 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/02/03 12:48:06 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

wchar_t			*precision_wstr(char *format_line,
	wchar_t *str, int wstrlen, int *nil)
{
	int			rozmir;
	int			chlen;
	wchar_t		*str_new;
	int			i;

	i = -1;
	while (*format_line != '.' && *format_line)
	{
		if (*format_line == '0' && !ft_isdigit(*(format_line - 1)))
			*nil = 1;
		format_line++;
	}
	if (*format_line == '\0')
		return (str);
	rozmir = ft_atoi((format_line + 1));
	chlen = rozmir - wstrlen;
	if (chlen < 0)
		str_new = (wchar_t*)malloc(sizeof(wchar_t) * (wstrlen + chlen + 1));
	else
		return (str);
	str_new = ft_wstrncpy(str_new, str, wstrlen + chlen);
	return (str_new);
}
