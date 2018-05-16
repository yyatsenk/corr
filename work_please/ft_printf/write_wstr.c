/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_wstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 12:38:35 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/02/03 12:38:36 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_wstr(wchar_t *wstr)
{
	int	i;
	int	counter;

	i = -1;
	counter = 0;
	if (!wstr)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (*wstr && *wstr != L'\0')
	{
		counter += write_wchar(*wstr);
		wstr += 1;
	}
	return (counter);
}
