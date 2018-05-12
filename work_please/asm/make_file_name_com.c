/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_file_name_com.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 11:05:40 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/05/09 11:05:41 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cor.h"

static int make_cor_file(char *name)
{
	int fd;
	char *name_res;
	char *no_s;
	int i;

	i = 0;
	while (name[i] && name[i] != '.')
		i++;
	no_s = ft_strsub(name, 0, i);
	name_res = ft_strjoin(no_s, ".co");
	fd = open(name_res, O_WRONLY|O_TRUNC|O_CREAT, 0664);
	free(no_s);
	free(name_res);
	return (fd);
}

static void put_name(int fd, char *name)
{
	int i;
	int name_size;
	char *null;

	i = -1;
	null = ft_strdup("");
	null[0] = 0;
	while (name[++i])
		write(fd, &name[i], 1);
	name_size = i + 3;
	while (++name_size < 128)
		write(fd, &null[0], 1);
	free(null);
}

static void put_comment_help(char **arr, t_command *c_copy, int i)
{
	int beg;
	int end;
	char *str_binary;
	int program_len;
	char *hui;

	beg = 0;
	end = 8;
	str_binary = NULL;
	program_len = c_copy->position + c_copy->size;
	make_binary(&str_binary, program_len, 12);
	while (++i < 12)
	{
		hui = ft_strsub(str_binary, beg , end);
		(*arr)[i] = make_decimal(hui, 7);
		free(hui);
		beg = end;
		end += 8;
	}
	free(str_binary);
}
static void put_comment(int fd, char *comment, t_command *command)
{
	t_command *c_copy;
	char *arr;
	int i;
	int comment_size;

	i = -1;
	arr = (char *)malloc(sizeof(char) * 13);
	arr[12] = '\0';
	c_copy = command;
	while (c_copy->next)
		c_copy = c_copy->next;
	put_comment_help(&arr, c_copy, -1);
	i = -1;
	while (++i < 12)
		write(fd, &arr[i], 1);
	i = -1;
	while (comment && comment[++i])
		write(fd, &comment[i], 1);
	comment_size = i - 1;
	arr[0] = 0;
	while (++comment_size < 2052)
		write(fd, &arr[0], 1);
	free(arr);
}

void make_evil_warrior(t_command *command, char *arg, char *name, char *comment)
{
	char *str;
	int i;
	int fd;
	unsigned	char *arr;

	fd = make_cor_file(arg);
	arr = (unsigned char *)malloc(sizeof(unsigned char) * 4);
	arr[0] = 0;
	arr[1] = 234;
	arr[2] = 131;
	arr[3] = 243;
	i = -1;
	while (++i < 4)
		write(fd, &arr[i], 1);
	free(arr);
	put_name(fd, name);
	put_comment(fd, comment, command);
	put_commads(fd, command);
}

