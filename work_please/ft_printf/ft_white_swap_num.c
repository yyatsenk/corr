/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_white_swap_num.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 14:08:09 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/02/02 14:08:10 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		mem_free(char **res, char **tmp_1, char **str, char **white)
{
	char	*tmp_2;

	tmp_2 = *res;
	*res = ft_strjoin(*res, *white);
	free(*tmp_1);
	free(tmp_2);
	free(*str);
}

void		last(int *j, char *str)
{
	while (ft_isalpha(str[*j]) || ft_isdigit(str[*j]) || ft_isascii(str[*j]))
		*j = *j + 1;
}

void		str_check(int *i, char *str)
{
	while (str[*i] == ' ' && str[*i])
		(*i)++;
}

char		*ft_white_swap_num(char *str, int space)
{
	char	*white;
	char	*tmp_1;
	char	*res;
	int		i;
	int		j;

	res = 0;
	if (!(i = 0) && str != NULL)
	{
		str_check(&i, str);
		if (i == 0 || !(white = ft_strnew(i)))
			return (str);
		i -= space;
		white = ft_strncpy(white, str, i);
		if (*white == '\0')
			return (str);
		tmp_1 = white;
		j = i;
		last(&j, str);
		if (j == 0 || !(res = (char*)malloc(sizeof(char) * (j - i + 1))))
			return (str);
		res = ft_strncpy(res, &str[i], j - i);
		mem_free(&res, &tmp_1, &str, &white);
	}
	return (res);
}
