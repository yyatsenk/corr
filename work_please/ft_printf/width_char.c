/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 16:53:51 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/02/02 16:53:52 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*width_norm(char **format_line, char *str)
{
	while (!ft_isdigit(**format_line) && **format_line)
	{
		if (**format_line == '.')
			return (str);
		*format_line = *format_line + 1;
		if (**format_line == '0')
			*format_line = *format_line + 1;
	}
	if (**format_line == '\0')
		return (str);
	return (NULL);
}

char		*width_char(char *format_line, char *str, char c)
{
	int		rozmir;
	int		chlen;
	int		i;
	char	*str_new;

	if (str == NULL)
		return (str);
	i = -1;
	if (width_norm(&format_line, str))
		return (str);
	rozmir = ft_atoi(format_line);
	chlen = rozmir - ft_strlen(str);
	if (chlen >= 0)
		str_new = ft_strnew(chlen);
	else
		return (str);
	while (++i < chlen)
		str_new[i] = c;
	str_new[i] = '\0';
	str = ft_strjoin(str_new, str);
	free(str_new);
	return (str);
}
