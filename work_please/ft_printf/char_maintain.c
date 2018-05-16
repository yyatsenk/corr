/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_maintain.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 17:09:05 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/02/02 17:09:07 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	regular_char_case(char c, int i, char *format_line, va_list **ap)
{
	char	*str;

	str = NULL;
	c = va_arg(**ap, int);
	if (c == 0)
	{
		c = '\0';
		str = ft_strnew(0);
		str[0] = '\0';
		str = flag_width_pres_maintain_char(format_line, str);
		i = ft_strlen(str + 1);
		write(1, str + 1, i + 1);
		free(str);
		return (i + 1);
	}
	else
	{
		str = ft_strnew(1);
		str[0] = c;
		str[1] = '\0';
	}
	str = flag_width_pres_maintain_char(format_line, str);
	write(1, str, ft_strlen(str));
	return (ft_strlen(str));
}

int			char_maintain(char *format_line, va_list *ap)
{
	char	c;
	wchar_t	c_w;
	int		i;

	i = 0;
	c = '\0';
	while (format_line[i] && ft_strncmp("hh", &format_line[i], 2))
		i++;
	if (format_line[i])
		c = (unsigned char)c;
	i = 0;
	while (format_line[i] && format_line[i] != 'l' && format_line[i] != 'C')
		i++;
	if (!format_line[i])
		return (regular_char_case(c, i, format_line, &ap));
	else
	{
		c_w = va_arg(*ap, wint_t);
		return (write_wchar(c_w));
	}
}
