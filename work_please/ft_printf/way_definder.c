/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way_defidned.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 15:09:12 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/02/01 15:09:14 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	format_num_finder(char *format_line, int *i)
{
	while (format_line[*i])
		*i = *i + 1;
	if (format_line[*i - 1] == 'd' || format_line[*i - 1] == 'D'
	|| format_line[*i - 1] == 'i' || format_line[*i - 1] == 'o'
	|| format_line[*i - 1] == 'O' || format_line[*i - 1] == 'u'
	|| format_line[*i - 1] == 'U' || format_line[*i - 1] == 'x'
	|| format_line[*i - 1] == 'X')
		return (1);
	else
		return (0);
}

int			way_definder(char *format_line, va_list *ap,
	t_typer *type, t_perech *data)
{
	int		i;
	int		retur;

	i = 0;
	retur = 0;
	if (format_line == NULL)
		return (0);
	if (format_num_finder(format_line, &i))
		retur = num_maintain(format_line, ap, type, data);
	else if (format_line[i - 1] == 's' || format_line[i - 1] == 'S')
		retur = str_maintain(format_line, ap, type, data);
	else if (format_line[i - 1] == 'c' || format_line[i - 1] == 'C')
		retur = char_maintain(format_line, ap);
	else if (format_line[i - 1] == 'p')
		retur = ptr_maintain(format_line, ap);
	else if (format_line[i - 1] == '%' && (retur = 1))
		retur = char_maintain_percent(format_line);
	else
		retur = error_maintain(format_line);
	free(format_line);
	return (retur);
}
