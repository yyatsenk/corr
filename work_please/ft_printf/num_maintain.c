/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_maintain.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 15:21:33 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/02/01 15:21:34 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		type_defind(char *format_line, t_typer **type, int i)
{
	if (format_line[i - 1] == 'o')
		**type = o;
	else if (format_line[i - 1] == 'O')
		**type = O;
	else if (format_line[i - 1] == 'u')
		**type = u;
	else if (format_line[i - 1] == 'U')
		**type = U;
	else if (format_line[i - 1] == 'D')
		**type = D;
	else if (format_line[i - 1] == 'x')
		**type = x;
	else if (format_line[i - 1] == 'X')
		**type = X;
}

static char		*str_with_type(char *format_line,
	va_list *ap, t_typer **type, int i)
{
	char		*str;

	str = NULL;
	if (**type == d)
		str = ft_itoa_l(va_arg(*ap, int));
	else if (**type == D)
		str = ft_itoa_l_l(va_arg(*ap, long long));
	else if (**type == O)
		str = ft_itoa_base_u_l_l(va_arg(*ap, long long), 8, 0);
	else if (format_line[i - 1] == 'U')
		str = ft_itoa_l_u(va_arg(*ap, unsigned long));
	else
	{
		if (**type == o)
			str = ft_itoa_base(va_arg(*ap, unsigned int), 8, 0);
		else if (**type == x)
			str = ft_itoa_base(va_arg(*ap, unsigned int), 16, 0);
		else if (**type == X)
			str = ft_itoa_base(va_arg(*ap, unsigned int), 16, 1);
		else
			str = ft_itoa_l(va_arg(*ap, unsigned int));
	}
	return (str);
}

int				num_maintain(char *format_line, va_list *ap,
	t_typer *type, t_perech *data)
{
	int			i;
	intmax_t	num;
	char		*str;

	num = 0;
	i = 0;
	while (format_line[i])
		i++;
	if ((format_line[i - 1] == 'd' || format_line[i - 1] == 'D'
	|| format_line[i - 1] == 'i') && (*type = d))
		num = (int)num;
	else
		num = (unsigned int)num;
	type_defind(format_line, &type, i);
	if (!(str = ft_modify(format_line, ap, data, *type)))
		str = str_with_type(format_line, ap, &type, i);
	str = flag_width_pres_maintain(format_line, str, *type);
	i = ft_strlen(str);
	write(1, str, i);
	free(str);
	return (i);
}
