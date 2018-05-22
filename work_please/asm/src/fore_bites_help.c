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

void		fore_bites_help(int *argument, int begin, int end, char *str_binary)
{
	char	*mem_del;

	mem_del = ft_strsub(str_binary, begin, end);
	*argument = make_decimal(mem_del, 7);
	free(mem_del);
}

void		check_if_dir(char *str, int fd)
{
	if (!str)
	{
		ft_printf("Seems to be a dir\n");
		close(fd);
		exit(1);
	}
}

void		bad_file(int *ret, int *fd, char **str, char *file_name)
{
	*ret = 1;
	*fd = open(file_name, O_RDONLY);
	*str = (char *)malloc(sizeof(char) * BUFF_SIZE + 1);
	if ((*ret = read(*fd, *str, BUFF_SIZE)) == -1)
	{
		free(*str);
		ft_printf("I can't open this shit\n");
		exit(1);
	}
}
