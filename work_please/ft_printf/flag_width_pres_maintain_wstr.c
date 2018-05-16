/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_width_pres_maintain_wstr.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 12:49:49 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/02/03 12:49:50 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

wchar_t		*flag_width_pres_maintain_wstr(char *format_line,
	wchar_t *str, int wstrlen)
{
	t_flag	flag;
	int		i;

	i = -1;
	flag.minus = 0;
	flag.nil = 0;
	while (format_line[++i] && format_line[i] != '-')
		;
	if (format_line[i] != '\0')
		flag.minus = 1;
	str = precision_wstr(format_line, str, wstrlen, &flag.nil);
	if (flag.nil == 1 && flag.minus != 1)
		str = width_wstr(format_line, str, L'0');
	else
		str = width_wstr(format_line, str, L' ');
	if (flag.minus == 1)
		str = ft_white_swap_wstr(str, wstrlen);
	return (str);
}
