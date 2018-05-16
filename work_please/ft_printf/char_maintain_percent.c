/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_maintain_percent.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 16:43:29 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/02/02 16:43:30 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	char_maintain_percent(char *format_line)
{
	char	*str;
	int		i;

	str = ft_strnew(1);
	str[0] = '%';
	str[1] = '\0';
	str = flag_width_pres_maintain_char(format_line, str);
	i = ft_strlen(str);
	write(1, str, i);
	free(str);
	return (i);
}
