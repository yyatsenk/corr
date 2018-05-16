/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_width_pres_maintain_char.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 17:04:37 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/02/02 17:04:44 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*flag_width_pres_maintain_char(char *format_line, char *str)
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
	i = -1;
	while (format_line[++i] != '.' && format_line[i])
	{
		if (format_line[i] == '0' && !ft_isdigit(format_line[i - 1]))
			flag.nil = 1;
	}
	if (flag.nil == 1 && flag.minus != 1)
		str = width_char(format_line, str, '0');
	else
		str = width_char(format_line, str, ' ');
	if (flag.minus == 1)
		str = ft_white_swap_num(str, 0);
	return (str);
}
