/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byte_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 18:40:23 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/05/08 18:40:25 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cor.h"

void			make_binary(char **str_binary, long long num, int num_bytes)
{
	int			i;

	(*str_binary) = (char*)malloc(sizeof(char) * (num_bytes * 8) + 1);
	i = (num_bytes * 8) - 1;
	(*str_binary)[(num_bytes * 8)] = '\0';
	while (i >= 0)
	{
		if ((num / 2) == 0)
		{
			if (num == 1)
			{
				(*str_binary)[i] = '1';
				num--;
			}
			else
				(*str_binary)[i] = '0';
		}
		else
		{
			(*str_binary)[i] = num % 2 + '0';
			num = num / 2;
		}
		i--;
	}
}

long long		make_decimal(char *octet, int octet_size)
{
	int			i;
	long long	res;

	res = 0;
	i = 0;
	while (octet[i])
	{
		if (octet[i] == '1')
			res += my_pow(2, ((i - octet_size) * (-1)));
		i++;
	}
	return (res);
}

long long		make_positive(long long num, int bytes)
{
	char		*str_binary;
	int			i;
	int			last_index;

	i = 0;
	num = -num;
	make_binary(&str_binary, num, bytes);
	while (str_binary[i])
	{
		if (str_binary[i] == '0')
			str_binary[i] = '1';
		else if (str_binary[i] == '1')
			str_binary[i] = '0';
		i++;
	}
	last_index = (bytes * 7 + bytes / 2);
	if (bytes == 4)
		last_index = 31;
	num = make_decimal(str_binary, last_index);
	num++;
	free(str_binary);
	return (num);
}
