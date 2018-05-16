/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_wstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 12:43:31 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/02/03 12:43:32 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static wchar_t	*width_check_wstr(char **format_line, wchar_t *str)
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

wchar_t			*width_wstr(char *format_line, wchar_t *str, wchar_t c)
{
	int			rozmir;
	int			chlen;
	int			i;
	wchar_t		*str_new;

	if (str == NULL)
		return (str);
	i = -1;
	if (width_check_wstr(&format_line, str))
		return (str);
	rozmir = ft_atoi(format_line);
	chlen = rozmir - ft_wstrlen(str);
	if (chlen >= 0)
		str_new = (wchar_t*)malloc(sizeof(wchar_t) * (chlen + 1));
	else
		return (str);
	while (++i < chlen)
		str_new[i] = c;
	str_new[i] = L'\0';
	str = ft_wstrjoin(str_new, str);
	free(str_new);
	return (str);
}
