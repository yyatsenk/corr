/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_maintain.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 16:49:28 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/02/02 16:49:47 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	error_maintain(char *format_line)
{
	char	c;
	char	*str;
	char	*str_free;
	int		i;

	i = 0;
	while (format_line[i])
		i++;
	c = format_line[i - 1];
	format_line[i - 1] = 'c';
	str = ft_strnew(1);
	str[0] = c;
	str[1] = '\0';
	str_free = str;
	str = flag_width_pres_maintain_char(format_line, str);
	i = ft_strlen(str);
	write(1, str, i);
	free(str);
	return (i);
}
