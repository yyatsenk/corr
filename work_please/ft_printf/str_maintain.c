/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_maintain.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 12:51:42 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/02/03 12:51:43 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_modify_str(char *format, t_perech *data, int *nill)
{
	while (*format && *format != 'l' && *format != 'S')
	{
		if (*format == '0')
			*nill = 1;
		format++;
		if (!ft_strncmp(format, "ll", 2))
			return ;
	}
	if (*format != '\0' && (*data = L))
		;
}

static int	regular_str_main(char **str, char *format_line, int nill)
{
	if (*str == NULL && nill == 1 && (*str = ft_strnew(1)))
		if (*str != NULL)
			(*str)[0] = '0';
	if (*str != NULL)
	{
		*str = flag_width_pres_maintain_str(format_line, *str);
		write(1, *str, ft_strlen(*str));
		return (ft_strlen(*str));
	}
	write(1, "(null)", 6);
	return (6);
}

int			str_maintain(char *f, va_list *ap, t_typer *type, t_perech *data)
{
	char	*str;
	wchar_t	*str_w_pres;
	wchar_t	*str_w;
	int		nill;

	nill = 0;
	ft_modify_str(f, data, &nill);
	if (*data == L && (*type = S))
	{
		str_w = va_arg(*ap, wchar_t*);
		str_w_pres = flag_width_pres_maintain_wstr(f, str_w, ft_wstrlen(str_w));
		return (write_wstr(str_w_pres));
	}
	else if ((*type = s))
	{
		str = va_arg(*ap, char *);
		return (regular_str_main(&str, f, nill));
	}
	return (-1);
}
