/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_data_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 11:01:39 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/05/09 11:01:40 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cor.h"

static void		print_one_byte(long long num, int fd)
{
	char		*arr;

	arr = ft_strdup("");
	arr[0] = num;
	write(fd, &arr[0], 1);
	free(arr);
}

static void		print_two_bytes(long long num, int fd)
{
	char		*arr;
	int			first;
	int			second;
	char		*str_binary;
	char		*mem_del;

	if (num < 0)
		num = make_positive(num, 2);
	arr = (char*)malloc(sizeof(char) * 2);
	make_binary(&str_binary, num, 2);
	mem_del = ft_strsub(str_binary, 0, 8);
	first = make_decimal(mem_del, 7);
	free(mem_del);
	mem_del = ft_strsub(str_binary, 8, 16);
	second = make_decimal(mem_del, 7);
	free(mem_del);
	arr[0] = first;
	arr[1] = second;
	write(fd, &arr[0], 1);
	write(fd, &arr[1], 1);
	free(arr);
	free(str_binary);
}

static void		print_fore_bytes(long long num, int fd, int first, int second)
{
	char		*arr;
	int			third;
	int			forth;
	char		*str_binary;

	if (num < 0)
		num = make_positive(num, 4);
	arr = (char*)malloc(sizeof(char) * 4);
	make_binary(&str_binary, num, 4);
	fore_bites_help(&first, 0, 8, str_binary);
	fore_bites_help(&second, 8, 16, str_binary);
	fore_bites_help(&third, 16, 24, str_binary);
	fore_bites_help(&forth, 24, 32, str_binary);
	arr[0] = first;
	arr[1] = second;
	arr[2] = third;
	arr[3] = forth;
	write(fd, &arr[0], 1);
	write(fd, &arr[1], 1);
	write(fd, &arr[2], 1);
	write(fd, &arr[3], 1);
	free(arr);
	free(str_binary);
}

static void		write_args(t_args_code args, int fd)
{
	int			num_of_arg;
	t_bytes		special;

	num_of_arg = 1;
	while (num_of_arg <= 3)
	{
		if (num_of_arg == 1)
			special = args.one;
		else if (num_of_arg == 2)
			special = args.two;
		else if (num_of_arg == 3)
			special = args.three;
		if (special.num_of_bytes == 1)
			print_one_byte(special.num_to_code, fd);
		else if (special.num_of_bytes == 2)
			print_two_bytes(special.num_to_code, fd);
		else if (special.num_of_bytes == 4)
			print_fore_bytes(special.num_to_code, fd, 0, 0);
		num_of_arg++;
	}
}

void			put_commads(int fd, t_command *command)
{
	t_command	*c_copy;
	char		*arr1;

	arr1 = ft_strdup("");
	arr1[0] = 0;
	c_copy = command;
	c_copy = c_copy->next;
	while (c_copy)
	{
		if (c_copy->is_label == 0)
		{
			arr1[0] = c_copy->index;
			write(fd, &arr1[0], 1);
			if (c_copy->code_param != 1)
			{
				arr1[0] = c_copy->c_code.result;
				write(fd, &arr1[0], 1);
			}
			write_args(c_copy->a_code, fd);
		}
		c_copy = c_copy->next;
	}
	free(arr1);
}
