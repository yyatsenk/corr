/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 11:22:43 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/05/09 11:22:47 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cor.h"

static t_command	*check_fill_size(t_command *command, char *str,\
	t_op darling, char *str_orig)
{
	t_command		*copy;
	int				i;
	int				j;

	j = 0;
	copy = command;
	while (copy->next)
		copy = copy->next;
	copy->index = darling.opcode;
	copy->code_param = darling.cod_octal;
	i = 0;
	if (!copy->prev)
		copy->position = 0;
	else
		copy->position = copy->prev->position + copy->prev->size;
	if (copy->is_label)
		return (copy);
	while (str[i] && ft_strncmp(&str[i], copy->name, ft_strlen(copy->name)))
		i++;
	i += ft_strlen(copy->name);
	while (str[i] && (str[i] == '\t' || str[i] == ' '))
		i++;
	check_args(darling, &str[i], &copy, str_orig);
	return (command);
}

static int			count_block_size(char *str,\
	int end, t_command *command)
{
	int				i;
	char			*constuct;
	t_op			darling;
	t_command		*c_copy;
	char			*test;

	i = end + 1;
	c_copy = command;
	while (c_copy->next)
		c_copy = c_copy->next;
	if (c_copy->is_label)
		command = check_fill_size(command, str, g_op_tab[16], str);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (!str[i] || str[i] == '#' || str[i] == ';')
		return (0);
	constuct = comm_cat(&str[i], i);
	darling = check_command(constuct, str);
	free(constuct);
	test = ft_strdup(darling.name);
	command = add_c(init_c(&test, 0, 0, 0), command);
	command = check_fill_size(command, &str[i], darling, str);
	return (0);
}

int					check_line(char *str,\
	t_command *command)
{
	int				i;
	char			*name;
	int				end;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i] && str[i] != ':')
		i++;
	if (str[i] == ':' && str[i - 1] != '%' &&\
		str[i - 1] != ' ' && str[i - 1] != '\t')
	{
		name = label_cat(str, &end);
		command = add_c(init_c(&name, 0, 0, 1), command);
		count_block_size(str, end, command);
	}
	else
		count_block_size(str, -1, command);
	return (0);
}
