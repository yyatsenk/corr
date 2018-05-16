/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 17:23:50 by yyatsenk          #+#    #+#             */
/*   Updated: 2017/12/15 17:23:51 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "./ft_printf.h"
#include "libft/libft.h"
#include <limits.h>
#include <wchar.h>

static int		proc_finder(char **format)
{
	int			count;

	count = 0;
	while (**format != '%' && **format)
	{
		write(1, &**format, 1);
		*format = *format + 1;
		count++;
	}
	return (count);
}

int				ft_printf(char *format, ...)
{
	t_perech	data;
	t_typer		type;
	int			retur;
	va_list		ap;

	retur = 0;
	va_start(ap, format);
	while (*format)
	{
		data = no;
		type = none;
		retur += proc_finder(&format);
		if (*format == '\0')
			return (retur);
		retur += way_definder(format_cat(&format), &ap, &type, &data);
	}
	va_end(ap);
	return (retur);
}
