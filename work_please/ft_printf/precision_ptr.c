/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 12:03:52 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/02/03 12:03:54 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*precision_check(char **format_line, char *str, int **prec)
{
	while (**format_line != '.' && **format_line)
		(*format_line)++;
	if (**format_line == '\0')
		return (str);
	**prec = 1;
	return (NULL);
}

char		*precision_ptr(char *format_line, char *str, int *prec)
{
	int		rozmir;
	int		chlen;
	char	*str_new;
	char	*str_new_2;
	int		i;

	i = -1;
	if (precision_check(&format_line, str, &prec))
		return (str);
	if (*(format_line + 1) == '0' || !ft_isdigit(*(format_line + 1)))
		return (ft_strdup("0x"));
	rozmir = ft_atoi((format_line + 1));
	str += 2;
	chlen = rozmir - ft_strlen(str);
	if (chlen > 0)
		str_new = ft_strnew(chlen);
	else
		return (str - 2);
	while (++i < chlen)
		str_new[i] = '0';
	str_new[i] = '\0';
	str_new_2 = ft_strjoin(str_new, str);
	free(str_new);
	str_new_2 = ft_strjoin("0x", str_new_2);
	return (str_new_2);
}
