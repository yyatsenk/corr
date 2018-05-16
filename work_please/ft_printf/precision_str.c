/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 12:29:55 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/02/03 12:29:57 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*precision_str(char *format_line, char *str, int *nil)
{
	int		rozmir;
	int		chlen;
	char	*str_new;
	int		i;

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
	chlen = rozmir - ft_strlen(str);
	if (chlen < 0)
		str_new = ft_strnew(ft_strlen(str) + chlen);
	else
		return (str);
	str_new = ft_strncpy(str_new, str, ft_strlen(str) + chlen);
	return (str_new);
}
