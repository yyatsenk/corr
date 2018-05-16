/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_width_pres_maintain_str.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 12:33:22 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/02/03 12:33:23 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*flag_width_pres_maintain_str(char *format_line, char *str)
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
	str = precision_str(format_line, str, &flag.nil);
	if (flag.nil == 1 && flag.minus != 1)
		str = width_str(format_line, str, '0');
	else
		str = width_str(format_line, str, ' ');
	if (flag.minus == 1)
		str = ft_white_swap(str);
	return (str);
}
