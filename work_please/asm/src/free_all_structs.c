/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_atructs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 16:06:05 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/05/11 16:06:08 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cor.h"

static void		free_down(t_command *command)
{
	t_un_label	*down_copy;
	t_un_label	*tmp;

	down_copy = command->down_un;
	while (down_copy)
	{
		if (down_copy->name)
			free(down_copy->name);
		tmp = down_copy;
		down_copy = down_copy->next;
		free(tmp);
	}
}

void			free_all_structs(t_command *command)
{
	t_command	*tmp;

	tmp = command;
	while (command)
	{
		free_down(command);
		if (command->name)
			free(command->name);
		command = command->next;
	}
}
