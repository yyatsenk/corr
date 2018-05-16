/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 12:36:39 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/02/03 12:36:40 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_wstrlen(wchar_t *wstr)
{
	int	size;
	int	res;
	int	i;

	i = -1;
	size = 0;
	res = 0;
	while (wstr && wstr[++i] != L'\0')
	{
		size = ft_size_bin(wstr[i]);
		if (size <= 7)
			res += 1;
		else if (size <= 11)
			res += 2;
		else if (size <= 16)
			res += 3;
		else
			res += 4;
	}
	return (res);
}
