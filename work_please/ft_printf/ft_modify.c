/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_modify.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 16:46:34 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/02/01 16:46:35 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*mod_help_2(char *format, t_typer type,
	intmax_t num, t_perech **data)
{
	char		*str;

	str = NULL;
	if (format[0] == 'h' && format[1] && format[1] != 'h' && (**data = H))
	{
		if (type == u || type == o || type == O || type == x || type == X)
		{
			num = (unsigned short int)num;
			if (type == u)
				str = ft_itoa_base_u_short(num, 10, 0);
			else if (type == o || type == O)
				str = ft_itoa_base_u_short(num, 8, 0);
			else if (type == x)
				str = ft_itoa_base_u_short(num, 16, 0);
			else if (type == X)
				str = ft_itoa_base_u_short(num, 16, 1);
		}
		else if (type == U)
			str = ft_itoa_l_u((unsigned long int)num);
		else if (type == D)
			str = ft_itoa_base_u_short((unsigned short int)num, 10, 0);
		else
			str = ft_itoa_l((short int)num);
	}
	return (str);
}

static int		mod_help_3(char *format, t_perech **data)
{
	int			res;

	res = 0;
	if (format[0] == 'l' && format[1] && format[1] != 'l' && (res = 1))
		**data = L;
	else if (!ft_strncmp(format, "ll", 2) && (res = 1))
		**data = LL;
	else if (!ft_strncmp(format, "hh", 2) && (res = 1))
		**data = HH;
	else if (format[0] == 'j' && (res = 1))
		**data = J;
	else if (format[0] == 'z' && (res = 1))
		**data = Z;
	return (res);
}

static char		*mod_help(char *format, va_list *ap,
	t_perech *data, t_typer type)
{
	intmax_t	num;
	char		*str;

	str = NULL;
	num = 0;
	num = va_arg(*ap, intmax_t);
	while (*format && *format != 'j' && *format != 'z')
		format += 1;
	while (*format != 'h' && *format != 'l' && *format != 'j' && *format != 'z')
		format -= 1;
	if (*format == 'h' || *format == 'l')
		if (*(format - 1) == 'h' || *(format - 1) == 'l')
			format -= 1;
	str = mod_help_2(format, type, num, &data);
	if (mod_help_3(format, &data))
		;
	else
	{
		*data = no;
		return (str);
	}
	mod_norm_help(format, &str, type, num);
	return (str);
}

char			*ft_modify(char *format, va_list *ap,
	t_perech *data, t_typer type)
{
	char		*str;

	str = NULL;
	while (*format != 'h' && *format != 'l' && ft_strncmp(format, "ll", 2)
	&& *format != 'j' && *format != 'z' && *format)
		format++;
	if (*format != '\0')
		str = mod_help(format, ap, data, type);
	return (str);
}
