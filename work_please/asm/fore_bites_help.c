/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fore_bites_help.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 12:45:43 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/05/12 12:45:44 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cor.h"

void fore_bites_help(int *argument, int begin, int end, char *str_binary)
{
	char *mem_del;

	mem_del = ft_strsub(str_binary, begin, end);
	*argument = make_decimal(mem_del, 7);
	free(mem_del);
}
