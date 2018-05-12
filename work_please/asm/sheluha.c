/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sheluha.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 10:56:56 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/05/09 10:56:57 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cor.h"

int check_lable_name(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if ((str[i] < 'a' || str[i] > 'z') && str[i] != '_' && !ft_isdigit(str[i]))
			return (0);
	return (1);
}

int check_duplicates(t_un_label *down, char *name)
{
	t_un_label *copy;

	copy = down;
	while (copy)
	{
		if (!ft_strcmp(name, copy->name))
			return (0);
		copy = copy->next;
	}
	copy = down;
	return (1);
}

int comma_find(char *str, int *i, t_op command, int read)
{
	int comma_found;

	comma_found = 0;
	if (read != command.arg_num)
		while (str[*i])
		{
			if (str[*i] != ' ' && str[*i] != '\t' && str[*i] != ',')
			{
				printf("Comma missed\n");
				exit(1);
			}
			if (str[*i] == ',' && (comma_found = 1))
				break;
			(*i)++;
		}
	if (!comma_found && read != command.arg_num && command.arg_num != 1)
	{
			printf("Comma missed\n");
			exit(1);
	}
	if (str[*i] && str[*i] != '#' && str[*i] != ';')
		(*i)++;
	return (1);
}

int check_end_line(char *str, char *str_orig)
{
	int i;
	int j;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '#' || str[i] == ';')
			return (1);
		if (str[i] != ' ' && str[i] != '\t')
		{
			j = i;
			while (str[j] && str[j] != ' ' && str[j] != '\t')
				j++;
			printf("Syntax error at token [TOKEN][%03i:%03i] \"%s\"\n",\
				g_num_str, (int)(ft_strstr(str_orig, str) - str_orig + 1), str);
			exit(1);
		}
		i++;
	}
	return (1);
}

char *join_cooler(t_command_code *code)
{
	char *str_copy_1;
	char *res;

	res = ft_strdup("00");
	str_copy_1 = res;
	if (code->three)
	{
		res = ft_strjoin(code->three, res);
		free(str_copy_1);
		free(code->three);
	}
	if (code->two)
	{
		str_copy_1 = res;
		res = ft_strjoin(code->two, res);
		free(str_copy_1);
		free(code->two);
	}
	if (code->one)
	{
		str_copy_1 = res;
		res = ft_strjoin(code->one, res);
		free(str_copy_1);
		free(code->one);
	}
	return (res);
}

