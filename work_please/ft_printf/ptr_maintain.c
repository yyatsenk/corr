/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_maintain.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 12:10:19 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/02/03 12:10:20 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	flag_width_check_ptr(char *format_line,
	char **str, int *i, int prec)
{
	while (format_line[*i] && format_line[*i] != '0')
		(*i)++;
	if (format_line[*i] && !ft_isdigit(format_line[(*i) - 1])
		&& !(*i = 0) && prec != 1)
	{
		while (format_line[*i] && format_line[*i] != '-')
			(*i)++;
		if (!format_line[*i])
			*str = width_ptr(format_line, *str, '0');
	}
	if (prec == 1 || format_line[*i] || !format_line[*i])
		*str = width_ptr(format_line, *str, ' ');
	*i = 0;
	while (format_line[*i] && format_line[*i] != '-')
		(*i)++;
}

int			ptr_maintain(char *format_line, va_list *ap)
{
	size_t	num_ptr;
	char	*str;
	char	*str_free;
	int		prec;
	int		i;

	i = 0;
	prec = 0;
	num_ptr = va_arg(*ap, size_t);
	str = ft_itoa_base_size(num_ptr, 16, 0);
	str_free = str;
	str = ft_strjoin("0x", str);
	free(str_free);
	str = precision_ptr(format_line, str, &prec);
	flag_width_check_ptr(format_line, &str, &i, prec);
	if (format_line[i])
		str = ft_white_swap_num(str, 0);
	i = ft_strlen(str);
	write(1, str, i);
	free(str);
	return (i);
}
